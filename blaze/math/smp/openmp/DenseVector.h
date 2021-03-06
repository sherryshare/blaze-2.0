//=================================================================================================
/*!
//  \file blaze/math/smp/openmp/DenseVector.h
//  \brief Header file for the OpenMP-based dense vector SMP implementation
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_SMP_OPENMP_DENSEVECTOR_H_
#define _BLAZE_MATH_SMP_OPENMP_DENSEVECTOR_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <omp.h>
#include <blaze/math/DenseSubvector.h>
#include <blaze/math/expressions/DenseVector.h>
#include <blaze/math/expressions/SparseVector.h>
#include <blaze/math/Functions.h>
#include <blaze/math/intrinsics/IntrinsicTrait.h>
#include <blaze/math/smp/SerialSection.h>
#include <blaze/math/SparseSubvector.h>
#include <blaze/math/traits/SubvectorExprTrait.h>
#include <blaze/system/OpenMP.h>
#include <blaze/util/Assert.h>
#include <blaze/util/EnableIf.h>
#include <blaze/util/logging/FunctionTrace.h>
#include <blaze/util/StaticAssert.h>
#include <blaze/util/typetraits/IsSame.h>


namespace blaze {

//=================================================================================================
//
//  GLOBAL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default implementation of the OpenMP-based SMP assignment of a vector to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side vector to be assigned.
// \return void
//
// This function implements the default OpenMP-based SMP assignment of a vector to a dense
// vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side vector
        , bool TF2 >    // Transpose flag of the right-hand side vector
inline void smpAssign( DenseVector<VT1_,TF1>& lhs, const Vector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );
   assign( ~lhs, ~rhs );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP assignment of a dense vector to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side dense vector to be assigned.
// \return void
//
// This function implements the OpenMP-based SMP assignment of a dense vector to a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpAssign( DenseVector<VT1_,TF1>& lhs, const DenseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      assign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef IntrinsicTrait<typename VT1_::ElementType>         IT;
   typedef typename SubvectorExprTrait<VT1_,aligned>::Type    AlignedTarget;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

   const bool vectorizable( VT1_::vectorizable && VT2_::vectorizable && IsSame<ET1,ET2>::value );
   const bool lhsAligned  ( (~lhs).isAligned() );
   const bool rhsAligned  ( (~rhs).isAligned() );

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t equalShare   ( (~lhs).size() / threads + addon );
      const size_t rest         ( equalShare & ( IT::size - 1UL ) );
      const size_t sizePerThread( ( vectorizable && rest )?( equalShare - rest + IT::size ):( equalShare ) );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );

         if( vectorizable && lhsAligned && rhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            assign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && lhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            assign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && rhsAligned ) {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            assign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            assign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP assignment of a sparse vector to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side sparse vector to be assigned.
// \return void
//
// This function implements the OpenMP-based SMP assignment of a sparse vector to a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpAssign( DenseVector<VT1_,TF1>& lhs, const SparseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      assign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t sizePerThread( (~lhs).size() / threads + addon );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );
         UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
         assign( target, subvector<unaligned>( ~rhs, index, size ) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default implementation of the OpenMP-based SMP addition assignment of a vector to a
//        dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side vector to be added.
// \return void
//
// This function implements the default OpenMP-based SMP addition assignment of a vector to
// a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side vector
        , bool TF2 >    // Transpose flag of the right-hand side vector
inline void smpAddAssign( DenseVector<VT1_,TF1>& lhs, const Vector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );
   addAssign( ~lhs, ~rhs );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP addition assignment of a dense vector to a
//        dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side dense vector to be added.
// \return void
//
// This function implements the OpenMP-based SMP addition assignment of a dense vector to a
// dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpAddAssign( DenseVector<VT1_,TF1>& lhs, const DenseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      addAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef IntrinsicTrait<typename VT1_::ElementType>         IT;
   typedef typename SubvectorExprTrait<VT1_,aligned>::Type    AlignedTarget;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

   const bool vectorizable( VT1_::vectorizable && VT2_::vectorizable && IsSame<ET1,ET2>::value );
   const bool lhsAligned  ( (~lhs).isAligned() );
   const bool rhsAligned  ( (~rhs).isAligned() );

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t equalShare   ( (~lhs).size() / threads + addon );
      const size_t rest         ( equalShare & ( IT::size - 1UL ) );
      const size_t sizePerThread( ( vectorizable && rest )?( equalShare - rest + IT::size ):( equalShare ) );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );

         if( vectorizable && lhsAligned && rhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            addAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && lhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            addAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && rhsAligned ) {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            addAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            addAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP addition assignment of a sparse vector to a
//        dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side sparse vector to be added.
// \return void
//
// This function implements the OpenMP-based SMP addition assignment of a sparse vector to a
// dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpAddAssign( DenseVector<VT1_,TF1>& lhs, const SparseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      addAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t sizePerThread( (~lhs).size() / threads + addon );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );
         UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
         addAssign( target, subvector<unaligned>( ~rhs, index, size ) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default implementation of the OpenMP-based SMP subtraction assignment of a vector to
//        a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side vector to be subtracted.
// \return void
//
// This function implements the default OpenMP-based SMP subtraction assignment of a vector to
// a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side vector
        , bool TF2 >    // Transpose flag of the right-hand side vector
inline void smpSubAssign( DenseVector<VT1_,TF1>& lhs, const Vector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );
   subAssign( ~lhs, ~rhs );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP subtraction assignment of a dense vector to a
//        dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side dense vector to be subtracted.
// \return void
//
// This function implements the OpenMP-based SMP subtraction assignment of a dense vector to
// a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpSubAssign( DenseVector<VT1_,TF1>& lhs, const DenseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      subAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef IntrinsicTrait<typename VT1_::ElementType>         IT;
   typedef typename SubvectorExprTrait<VT1_,aligned>::Type    AlignedTarget;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

   const bool vectorizable( VT1_::vectorizable && VT2_::vectorizable && IsSame<ET1,ET2>::value );
   const bool lhsAligned  ( (~lhs).isAligned() );
   const bool rhsAligned  ( (~rhs).isAligned() );

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t equalShare   ( (~lhs).size() / threads + addon );
      const size_t rest         ( equalShare & ( IT::size - 1UL ) );
      const size_t sizePerThread( ( vectorizable && rest )?( equalShare - rest + IT::size ):( equalShare ) );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );

         if( vectorizable && lhsAligned && rhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            subAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && lhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            subAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && rhsAligned ) {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            subAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            subAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP subtraction assignment of a sparse vector to a
//        dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side sparse vector to be subtracted.
// \return void
//
// This function implements the OpenMP-based SMP subtraction assignment of a sparse vector to
// a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpSubAssign( DenseVector<VT1_,TF1>& lhs, const SparseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      subAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t sizePerThread( (~lhs).size() / threads + addon );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );
         UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
         subAssign( target, subvector<unaligned>( ~rhs, index, size ) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Default implementation of the OpenMP-based SMP multiplication assignment of a vector
//        to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side vector to be multiplied.
// \return void
//
// This function implements the default OpenMP-based SMP multiplication assignment of a vector
// to a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side vector
        , bool TF2 >    // Transpose flag of the right-hand side vector
inline void smpMultAssign( DenseVector<VT1_,TF1>& lhs, const Vector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );
   multAssign( ~lhs, ~rhs );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP multiplication assignment of a dense vector
//        to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side dense vector to be multiplied.
// \return void
//
// This function implements the OpenMP-based SMP multiplication assignment of a dense vector
// to a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpMultAssign( DenseVector<VT1_,TF1>& lhs, const DenseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      multAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef IntrinsicTrait<typename VT1_::ElementType>         IT;
   typedef typename SubvectorExprTrait<VT1_,aligned>::Type    AlignedTarget;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

   const bool vectorizable( VT1_::vectorizable && VT2_::vectorizable && IsSame<ET1,ET2>::value );
   const bool lhsAligned  ( (~lhs).isAligned() );
   const bool rhsAligned  ( (~rhs).isAligned() );

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t equalShare   ( (~lhs).size() / threads + addon );
      const size_t rest         ( equalShare & ( IT::size - 1UL ) );
      const size_t sizePerThread( ( vectorizable && rest )?( equalShare - rest + IT::size ):( equalShare ) );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );

         if( vectorizable && lhsAligned && rhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            multAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && lhsAligned ) {
            AlignedTarget target( subvector<aligned>( ~lhs, index, size ) );
            multAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
         else if( vectorizable && rhsAligned ) {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            multAssign( target, subvector<aligned>( ~rhs, index, size ) );
         }
         else {
            UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
            multAssign( target, subvector<unaligned>( ~rhs, index, size ) );
         }
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Implementation of the OpenMP-based SMP multiplication assignment of a sparse vector
//        to a dense vector.
// \ingroup smp
//
// \param lhs The target left-hand side dense vector.
// \param rhs The right-hand side sparse vector to be multiplied.
// \return void
//
// This function implements the OpenMP-based SMP multiplication assignment of a sparse vector
// to a dense vector.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in erroneous results and/or in compilation errors. Instead of using this function use the
// assignment operator.
*/
template< typename VT1_  // Type of the left-hand side dense vector
        , bool TF1      // Transpose flag of the left-hand side dense vector
        , typename VT2_  // Type of the right-hand side dense vector
        , bool TF2 >    // Transpose flag of the right-hand side dense vector
typename EnableIfTrue< VT1_::smpAssignable && VT2_::smpAssignable >::Type
   smpMultAssign( DenseVector<VT1_,TF1>& lhs, const SparseVector<VT2_,TF2>& rhs )
{
   BLAZE_FUNCTION_TRACE;

   BLAZE_INTERNAL_ASSERT( (~lhs).size() == (~rhs).size(), "Invalid vector sizes" );

   if( isSerialSectionActive() || omp_get_num_threads() != 1 || !(~rhs).canSMPAssign() ) {
      multAssign( ~lhs, ~rhs );
      return;
   }

   typedef typename VT1_::ElementType                         ET1;
   typedef typename VT2_::ElementType                         ET2;
   typedef typename SubvectorExprTrait<VT1_,unaligned>::Type  UnalignedTarget;

#pragma omp parallel shared( lhs, rhs )
   {
      const int    threads      ( omp_get_num_threads() );
      const size_t addon        ( ( ( (~lhs).size() % threads ) != 0UL )? 1UL : 0UL );
      const size_t sizePerThread( (~lhs).size() / threads + addon );

#pragma omp for schedule(dynamic,1) nowait
      for( int i=0UL; i<threads; ++i )
      {
         const size_t index( i*sizePerThread );

         if( index >= (~lhs).size() )
            continue;

         const size_t size( min( sizePerThread, (~lhs).size() - index ) );
         UnalignedTarget target( subvector<unaligned>( ~lhs, index, size ) );
         multAssign( target, subvector<unaligned>( ~rhs, index, size ) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  COMPILE TIME CONSTRAINT
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
namespace {

BLAZE_STATIC_ASSERT( BLAZE_OPENMP_PARALLEL_MODE > 0 );

}
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
