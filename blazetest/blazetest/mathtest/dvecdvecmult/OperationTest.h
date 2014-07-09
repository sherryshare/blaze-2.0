//=================================================================================================
/*!
//  \file blazetest/mathtest/dvecdvecmult/OperationTest.h
//  \brief Header file for the dense vector/dense vector multiplication operation test
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

#ifndef _BLAZETEST_MATHTEST_DVECDVECMULT_OPERATIONTEST_H_
#define _BLAZETEST_MATHTEST_DVECDVECMULT_OPERATIONTEST_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/constraints/Computation.h>
#include <blaze/math/constraints/DenseVector.h>
#include <blaze/math/constraints/SparseVector.h>
#include <blaze/math/constraints/TransposeFlag.h>
#include <blaze/math/constraints/VecVecMultExpr.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/shims/Equal.h>
#include <blaze/math/StaticVector.h>
#include <blaze/math/traits/MultExprTrait.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/math/typetraits/BaseElementType.h>
#include <blaze/math/typetraits/IsRowVector.h>
#include <blaze/math/Views.h>
#include <blaze/util/constraints/Numeric.h>
#include <blaze/util/constraints/SameType.h>
#include <blazetest/system/MathTest.h>
#include <blazetest/mathtest/Creator.h>
#include <blazetest/mathtest/IsEqual.h>
#include <blazetest/mathtest/RandomMaximum.h>
#include <blazetest/mathtest/RandomMinimum.h>


namespace blazetest {

namespace mathtest {

namespace dvecdvecmult {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Auxiliary class template for the dense vector/dense vector multiplication operation test.
//
// This class template represents one particular vector multiplication test between two vectors of
// a particular type. The two template arguments \a VT1_ and \a VT2_ represent the types of the
// left-hand side and right-hand side vector, respectively.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
class OperationTest
{
 private:
   //**Type definitions****************************************************************************
   typedef typename VT1_::TransposeType                 TVT1_;  //!< Transpose vector type 1
   typedef typename VT2_::TransposeType                 TVT2_;  //!< Transpose vector type 2
   typedef typename blaze::MultTrait<VT1_,VT2_>::Type    RE;    //!< Default result type
   typedef typename blaze::MultTrait<TVT1_,TVT2_>::Type  TRE;   //!< Transpose default result type
   //**********************************************************************************************

   //**Enumerations********************************************************************************
   enum { TF = blaze::IsRowVector<VT1_>::value };
   //**********************************************************************************************

   //**Type definitions****************************************************************************
   typedef typename VT1_::ElementType        ET1;    //!< Element type 1
   typedef typename VT2_::ElementType        ET2;    //!< Element type 2
   typedef typename RE::ElementType         RET;    //!< Resulting element type
   typedef blaze::DynamicVector<ET1,TF>     RT1;    //!< Reference type 1
   typedef blaze::CompressedVector<ET2,TF>  RT2;    //!< Reference type 2
   typedef typename RT1::TransposeType      TRT1;   //!< Transpose reference type 1
   typedef typename RT2::TransposeType      TRT2;   //!< Transpose reference type 2
   typedef blaze::DynamicVector<RET,TF>     DRRE;   //!< Dense reference result type
   typedef blaze::CompressedVector<RET,TF>  SRRE;   //!< Sparse reference result type
   typedef typename DRRE::TransposeType     TDRRE;  //!< Transpose dense reference result type
   typedef typename SRRE::TransposeType     TSRRE;  //!< Transpose sparse reference result type
   typedef RE                               DRE;    //!< Dense result type
   typedef SRRE                             SRE;    //!< Sparse result type
   typedef TRE                              TDRE;   //!< Transpose dense result type
   typedef TSRRE                            TSRE;   //!< Transpose sparse result type

   //! Type of the vector/vector multiplication expression
   typedef typename blaze::MultExprTrait<VT1_,VT2_>::Type  VecVecMultExprType;

   //! Type of the transpose vector/transpose vector multiplication expression
   typedef typename blaze::MultExprTrait<TVT1_,TVT2_>::Type  TVecTVecMultExprType;
   //**********************************************************************************************

 public:
   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   explicit OperationTest( const Creator<VT1_>& creator1, const Creator<VT2_>& creator2 );
   // No explicitly declared copy constructor.
   //@}
   //**********************************************************************************************

   //**Destructor**********************************************************************************
   // No explicitly declared destructor.
   //**********************************************************************************************

 private:
   //**Test functions******************************************************************************
   /*!\name Test functions */
   //@{
                          void testInitialStatus     ();
                          void testAssignment        ();
                          void testElementAccess     ();
                          void testBasicOperation    ();
                          void testNegatedOperation  ();
   template< typename T > void testScaledOperation   ( T scalar );
                          void testTransposeOperation();
                          void testAbsOperation      ();
                          void testSubvectorOperation();
   //@}
   //**********************************************************************************************

   //**Error detection functions*******************************************************************
   /*!\name Error detection functions */
   //@{
   template< typename LT, typename RT > void checkResults();
   template< typename LT, typename RT > void checkTransposeResults();
   //@}
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   void initResults();
   void initTransposeResults();
   template< typename LT, typename RT > void convertException( const std::exception& ex );
   //@}
   //**********************************************************************************************

   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   VT1_   lhs_;      //!< The left-hand side dense vector.
   VT2_   rhs_;      //!< The right-hand side dense vector.
   DRE   dres_;     //!< The dense vector for the result of the vector multiplication.
   SRE   sres_;     //!< The sparse vector for the result of the vector multiplication.
   RT1   reflhs_;   //!< The reference left-hand side vector.
   RT2   refrhs_;   //!< The reference right-hand side vector.
   DRRE  refres_;   //!< The reference result.
   TVT1_  tlhs_;     //!< The transpose left-hand side vector.
   TVT2_  trhs_;     //!< The transpose right-hand side vector.
   TDRE  tdres_;    //!< The dense vector for the result of the transpose vector multiplication.
   TSRE  tsres_;    //!< The sparse vector for the result of the transpose vector multiplication.
   TRT1  treflhs_;  //!< The reference left-hand side transpose vector.
   TRT2  trefrhs_;  //!< The reference right-hand side transpose vector.
   TDRRE trefres_;  //!< The transpose reference result.

   std::string test_;   //!< Label of the currently performed test.
   std::string error_;  //!< Description of the current error type.
   //@}
   //**********************************************************************************************

   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( VT1_   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( VT2_   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TVT1_  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TVT2_  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( RT1   );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( RT2   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TRT1  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( TRT2  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( DRE   );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( SRE   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( DRRE  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( SRRE  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TDRE  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( TSRE  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TDRRE );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( TSRRE );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( VT1_ , VT2_   );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( VT1_ , RT1   );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TVT1_, TVT2_  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TVT1_, TRT1  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( RT1 , RT2   );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TRT1, TRT2  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( VT1_ , DRE   );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( VT1_ , SRE   );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( RT1 , DRRE  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( RT1 , SRRE  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TVT1_, TDRE  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TVT1_, TSRE  );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TRT1, TDRRE );
   BLAZE_CONSTRAINT_VECTORS_MUST_HAVE_SAME_TRANSPOSE_FLAG( TRT1, TSRRE );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( ET1, typename TVT1_::ElementType   );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( ET2, typename TVT2_::ElementType   );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( VT1_, typename TVT1_::TransposeType );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( VT2_, typename TVT2_::TransposeType );
   BLAZE_CONSTRAINT_MUST_BE_VECVECMULTEXPR_TYPE( VecVecMultExprType   );
   BLAZE_CONSTRAINT_MUST_BE_VECVECMULTEXPR_TYPE( TVecTVecMultExprType );
   BLAZE_CONSTRAINT_MUST_BE_COMPUTATION_TYPE( VecVecMultExprType   );
   BLAZE_CONSTRAINT_MUST_BE_COMPUTATION_TYPE( TVecTVecMultExprType );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the dense vector/dense vector multiplication operation test.
//
// \param creator1 The creator for the left-hand side dense vector of the vector multiplication.
// \param creator2 The creator for the right-hand side dense vector of the vector multiplication.
// \exception std::runtime_error Operation error detected.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
OperationTest<VT1_,VT2_>::OperationTest( const Creator<VT1_>& creator1, const Creator<VT2_>& creator2 )
   : lhs_( creator1() )    // The left-hand side dense vector
   , rhs_( creator2() )    // The right-hand side dense vector
   , dres_()               // The dense vector for the result of the vector multiplication
   , sres_()               // The sparse vector for the result of the vector multiplication
   , reflhs_( lhs_ )       // The reference left-hand side vector
   , refrhs_( rhs_ )       // The reference right-hand side vector
   , refres_()             // The reference result
   , tlhs_( trans(lhs_) )  // The transpose left-hand side vector
   , trhs_( trans(rhs_) )  // The transpose right-hand side vector
   , tdres_()              // The dense vector for the result of the transpose vector multiplication
   , tsres_()              // The sparse vector for the result of the transpose vector multiplication
   , treflhs_( tlhs_ )     // The reference left-hand side transpose vector
   , trefrhs_( trhs_ )     // The reference right-hand side transpose vector
   , trefres_()            // The transpose reference result
   , test_()               // Label of the currently performed test
   , error_()              // Description of the current error type
{
   testInitialStatus();
   testAssignment();
   testElementAccess();
   testBasicOperation();
   testNegatedOperation();
   testScaledOperation( 2 );
   testScaledOperation( 2UL );
   testScaledOperation( 2.0F );
   testScaledOperation( 2.0 );
   testTransposeOperation();
   testAbsOperation();
   testSubvectorOperation();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Tests on the initial status of the vectors.
//
// \return void
// \exception std::runtime_error Initialization error detected.
//
// This function runs tests on the initial status of the vectors. In case any initialization
// error is detected, a \a std::runtime_error exception is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testInitialStatus()
{
   //=====================================================================================
   // Performing initial tests with the given vectors
   //=====================================================================================

   // Checking the size of the left-hand side operand
   if( lhs_.size() != reflhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of left-hand side dense operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT1_ ).name() << "\n"
          << "   Detected size = " << lhs_.size() << "\n"
          << "   Expected size = " << reflhs_.size() << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the size of the right-hand side operand
   if( rhs_.size() != refrhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of right-hand side dense operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Detected size = " << rhs_.size() << "\n"
          << "   Expected size = " << refrhs_.size() << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the initialization of the left-hand side operand
   if( !isEqual( lhs_, reflhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Initial test of initialization of left-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT1_ ).name() << "\n"
          << "   Current initialization:\n" << lhs_ << "\n"
          << "   Expected initialization:\n" << reflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the initialization of the right-hand side operand
   if( !isEqual( rhs_, refrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Initial test of initialization of right-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Current initialization:\n" << rhs_ << "\n"
          << "   Expected initialization:\n" << refrhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }


   //=====================================================================================
   // Performing initial tests with the transpose types
   //=====================================================================================

   // Checking the size of the left-hand side operand
   if( tlhs_.size() != treflhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of transpose left-hand side dense operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Detected size = " << tlhs_.size() << "\n"
          << "   Expected size = " << treflhs_.size() << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the size of the right-hand side operand
   if( trhs_.size() != trefrhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of transpose right-hand side dense operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT2_ ).name() << "\n"
          << "   Detected size = " << trhs_.size() << "\n"
          << "   Expected size = " << trefrhs_.size() << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the initialization of the left-hand side operand
   if( !isEqual( tlhs_, treflhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Initial test of initialization of transpose left-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Current initialization:\n" << tlhs_ << "\n"
          << "   Expected initialization:\n" << treflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the initialization of the right-hand side operand
   if( !isEqual( trhs_, trefrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Initial test of initialization of transpose right-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT2_ ).name() << "\n"
          << "   Current initialization:\n" << trhs_ << "\n"
          << "   Expected initialization:\n" << trefrhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the vector assignment.
//
// \return void
// \exception std::runtime_error Assignment error detected.
//
// This function tests the vector assignment. In case any error is detected, a
// \a std::runtime_error exception is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testAssignment()
{
   //=====================================================================================
   // Performing an assignment with the given vectors
   //=====================================================================================

   try {
      lhs_ = reflhs_;
      rhs_ = refrhs_;
   }
   catch( std::exception& ex ) {
      std::ostringstream oss;
      oss << " Test: Assignment with the given vectors\n"
          << " Error: Failed assignment\n"
          << " Details:\n"
          << "   Left-hand side dense vector type:\n"
          << "     " << typeid( VT1_ ).name() << "\n"
          << "   Right-hand side dense vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Error message: " << ex.what() << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( lhs_, reflhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of left-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT1_ ).name() << "\n"
          << "   Current initialization:\n" << lhs_ << "\n"
          << "   Expected initialization:\n" << reflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( rhs_, refrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of right-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Dense vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Current initialization:\n" << rhs_ << "\n"
          << "   Expected initialization:\n" << refrhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }


   //=====================================================================================
   // Performing an assignment with the transpose types
   //=====================================================================================

   try {
      tlhs_ = treflhs_;
      trhs_ = trefrhs_;
   }
   catch( std::exception& ex ) {
      std::ostringstream oss;
      oss << " Test: Assignment with the transpose types\n"
          << " Error: Failed assignment\n"
          << " Details:\n"
          << "   Transpose left-hand side dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Transpose right-hand side dense vector type:\n"
          << "     " << typeid( TVT2_ ).name() << "\n"
          << "   Error message: " << ex.what() << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( tlhs_, treflhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of transpose left-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Current initialization:\n" << tlhs_ << "\n"
          << "   Expected initialization:\n" << treflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( trhs_, trefrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of transpose right-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT2_ ).name() << "\n"
          << "   Current initialization:\n" << trhs_ << "\n"
          << "   Expected initialization:\n" << trefrhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the vector element access.
//
// \return void
// \exception std::runtime_error Element access error detected.
//
// This function tests the element access via the subscript operator. In case any
// error is detected, a \a std::runtime_error exception is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testElementAccess()
{
   using blaze::equal;


   //=====================================================================================
   // Testing the element access with the given vectors
   //=====================================================================================

   if( lhs_.size() > 0UL && rhs_.size() > 0UL )
   {
      if( !equal( ( lhs_ * rhs_ )[0UL], ( reflhs_ * refrhs_ )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Left-hand side dense vector type:\n"
             << "     " << typeid( VT1_ ).name() << "\n"
             << "   Right-hand side dense vector type:\n"
             << "     " << typeid( VT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( lhs_ * eval( rhs_ ) )[0UL], ( reflhs_ * eval( refrhs_ ) )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of right evaluated multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Left-hand side dense vector type:\n"
             << "     " << typeid( VT1_ ).name() << "\n"
             << "   Right-hand side dense vector type:\n"
             << "     " << typeid( VT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( eval( lhs_ ) * rhs_ )[0UL], ( eval( reflhs_ ) * refrhs_ )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of left evaluated multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Left-hand side dense vector type:\n"
             << "     " << typeid( VT1_ ).name() << "\n"
             << "   Right-hand side dense vector type:\n"
             << "     " << typeid( VT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( eval( lhs_ ) * eval( rhs_ ) )[0UL], ( eval( reflhs_ ) * eval( refrhs_ ) )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of fully evaluated multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Left-hand side dense vector type:\n"
             << "     " << typeid( VT1_ ).name() << "\n"
             << "   Right-hand side dense vector type:\n"
             << "     " << typeid( VT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Testing the element access with the transpose types
   //=====================================================================================

   if( tlhs_.size() > 0UL && trhs_.size() > 0UL )
   {
      if( !equal( ( tlhs_ * trhs_ )[0UL], ( treflhs_ * trefrhs_ )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of transpose multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Transpose left-hand side dense vector type:\n"
             << "     " << typeid( TVT1_ ).name() << "\n"
             << "   Transpose right-hand side dense vector type:\n"
             << "     " << typeid( TVT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( tlhs_ * eval( trhs_ ) )[0UL], ( treflhs_ * eval( trefrhs_ ) )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of right evaluated transpose multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Transpose left-hand side dense vector type:\n"
             << "     " << typeid( TVT1_ ).name() << "\n"
             << "   Transpose right-hand side dense vector type:\n"
             << "     " << typeid( TVT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( eval( tlhs_ ) * trhs_ )[0UL], ( eval( treflhs_ ) * trefrhs_ )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of left evaluated transpose multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Transpose left-hand side dense vector type:\n"
             << "     " << typeid( TVT1_ ).name() << "\n"
             << "   Transpose right-hand side dense vector type:\n"
             << "     " << typeid( TVT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }

      if( !equal( ( eval( tlhs_ ) * eval( trhs_ ) )[0UL], ( eval( treflhs_ ) * eval( trefrhs_ ) )[0UL] ) ) {
         std::ostringstream oss;
         oss << " Test : Element access of fully evaluated transpose multiplication expression\n"
             << " Error: Unequal resulting elements at index 0 detected\n"
             << " Details:\n"
             << "   Transpose left-hand side dense vector type:\n"
             << "     " << typeid( TVT1_ ).name() << "\n"
             << "   Transpose right-hand side dense vector type:\n"
             << "     " << typeid( TVT2_ ).name() << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the plain dense vector/dense vector multiplication.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the plain vector multiplication with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from the
// multiplication or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testBasicOperation()
{
#if BLAZETEST_MATHTEST_TEST_BASIC_OPERATION
   if( BLAZETEST_MATHTEST_TEST_BASIC_OPERATION > 1 )
   {
      //=====================================================================================
      // Multiplication
      //=====================================================================================

      // Multiplication with the given vectors
      {
         test_  = "Multiplication with the given vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = lhs_ * rhs_;
            sres_   = lhs_ * rhs_;
            refres_ = reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = tlhs_ * trhs_;
            tsres_   = tlhs_ * trhs_;
            trefres_ = treflhs_ * trefrhs_;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Multiplication with evaluated vectors
      {
         test_  = "Multiplication with evaluated vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = eval( lhs_ ) * eval( rhs_ );
            sres_   = eval( lhs_ ) * eval( rhs_ );
            refres_ = eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = eval( tlhs_ ) * eval( trhs_ );
            tsres_   = eval( tlhs_ ) * eval( trhs_ );
            trefres_ = eval( treflhs_ ) * eval( trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Multiplication with addition assignment
      //=====================================================================================

      // Multiplication with addition assignment with the given vectors
      {
         test_  = "Multiplication with addition assignment with the given vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += lhs_ * rhs_;
            sres_   += lhs_ * rhs_;
            refres_ += reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += tlhs_ * trhs_;
            tsres_   += tlhs_ * trhs_;
            trefres_ += treflhs_ * trefrhs_;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Multiplication with addition assignment with the given vectors
      {
         test_  = "Multiplication with addition assignment with evaluated vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += eval( lhs_ ) * eval( rhs_ );
            sres_   += eval( lhs_ ) * eval( rhs_ );
            refres_ += eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += eval( tlhs_ ) * eval( trhs_ );
            tsres_   += eval( tlhs_ ) * eval( trhs_ );
            trefres_ += eval( treflhs_ ) * eval( trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Multiplication with subtraction assignment
      //=====================================================================================

      // Multiplication with subtraction assignment with the given vectors
      {
         test_  = "Multiplication with subtraction assignment with the given vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= lhs_ * rhs_;
            sres_   -= lhs_ * rhs_;
            refres_ -= reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= tlhs_ * trhs_;
            tsres_   -= tlhs_ * trhs_;
            trefres_ -= treflhs_ * trefrhs_;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Multiplication with subtraction assignment with evaluated vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= eval( lhs_ ) * eval( rhs_ );
            sres_   -= eval( lhs_ ) * eval( rhs_ );
            refres_ -= eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= eval( tlhs_ ) * eval( trhs_ );
            tsres_   -= eval( tlhs_ ) * eval( trhs_ );
            trefres_ -= eval( treflhs_ ) * eval( trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Multiplication with multiplication assignment
      //=====================================================================================

      // Multiplication with multiplication assignment with the given vectors
      {
         test_  = "Multiplication with multiplication assignment with the given vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= lhs_ * rhs_;
            sres_   *= lhs_ * rhs_;
            refres_ *= reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= tlhs_ * trhs_;
            tsres_   *= tlhs_ * trhs_;
            trefres_ *= treflhs_ * trefrhs_;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Multiplication with multiplication assignment with evaluated vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= eval( lhs_ ) * eval( rhs_ );
            sres_   *= eval( lhs_ ) * eval( rhs_ );
            refres_ *= eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= eval( tlhs_ ) * eval( trhs_ );
            tsres_   *= eval( tlhs_ ) * eval( trhs_ );
            trefres_ *= eval( treflhs_ ) * eval( trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the negated dense vector/dense vector multiplication.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the negated vector multiplication with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from the
// multiplication or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testNegatedOperation()
{
#if BLAZETEST_MATHTEST_TEST_NEGATED_OPERATION
   if( BLAZETEST_MATHTEST_TEST_NEGATED_OPERATION > 1 )
   {
      //=====================================================================================
      // Negated multiplication
      //=====================================================================================

      // Negated multiplication with the given vectors
      {
         test_  = "Negated multiplication with the givven types";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = -( lhs_ * rhs_ );
            sres_   = -( lhs_ * rhs_ );
            refres_ = -( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = -( tlhs_ * trhs_ );
            tsres_   = -( tlhs_ * trhs_ );
            trefres_ = -( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Negated multiplication with evaluated vectors
      {
         test_  = "Negated multiplication with evaluated vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = -( eval( lhs_ ) * eval( rhs_ ) );
            sres_   = -( eval( lhs_ ) * eval( rhs_ ) );
            refres_ = -( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = -( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   = -( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ = -( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Negated multiplication with addition assignment
      //=====================================================================================

      // Negated multiplication with addition assignment with the given vectors
      {
         test_  = "Negated multiplication with addition assignment with the given vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += -( lhs_ * rhs_ );
            sres_   += -( lhs_ * rhs_ );
            refres_ += -( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += -( tlhs_ * trhs_ );
            tsres_   += -( tlhs_ * trhs_ );
            trefres_ += -( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Negated multiplication with addition assignment with evaluated vectors
      {
         test_  = "Negated multiplication with addition assignment with evaluated vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += -( eval( lhs_ ) * eval( rhs_ ) );
            sres_   += -( eval( lhs_ ) * eval( rhs_ ) );
            refres_ += -( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += -( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   += -( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ += -( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Negated multiplication with subtraction assignment
      //=====================================================================================

      // Negated multiplication with subtraction assignment with the given vectors
      {
         test_  = "Negated multiplication with subtraction assignment with the given vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= -( lhs_ * rhs_ );
            sres_   -= -( lhs_ * rhs_ );
            refres_ -= -( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();
         try {
            initTransposeResults();
            tdres_   -= -( tlhs_ * trhs_ );
            tsres_   -= -( tlhs_ * trhs_ );
            trefres_ -= -( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Negated multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Negated multiplication with subtraction assignment with evaluated vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= -( eval( lhs_ ) * eval( rhs_ ) );
            sres_   -= -( eval( lhs_ ) * eval( rhs_ ) );
            refres_ -= -( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= -( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   -= -( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ -= -( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Negated multiplication with multiplication assignment
      //=====================================================================================

      // Negated multiplication with multiplication assignment with the given vectors
      {
         test_  = "Negated multiplication with multiplication assignment with the given vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= -( lhs_ * rhs_ );
            sres_   *= -( lhs_ * rhs_ );
            refres_ *= -( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= -( tlhs_ * trhs_ );
            tsres_   *= -( tlhs_ * trhs_ );
            trefres_ *= -( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Negated multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Negated multiplication with multiplication assignment with evaluated vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= -( eval( lhs_ ) * eval( rhs_ ) );
            sres_   *= -( eval( lhs_ ) * eval( rhs_ ) );
            refres_ *= -( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= -( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   *= -( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ *= -( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the scaled dense vector/dense vector multiplication.
//
// \param scalar The scalar value.
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the scaled vector multiplication with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from the
// multiplication or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
template< typename T >    // Type of the scalar
void OperationTest<VT1_,VT2_>::testScaledOperation( T scalar )
{
   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( T );

   if( scalar == T(0) )
      throw std::invalid_argument( "Invalid scalar parameter" );


#if BLAZETEST_MATHTEST_TEST_SCALED_OPERATION
   if( BLAZETEST_MATHTEST_TEST_SCALED_OPERATION > 1 )
   {
      //=====================================================================================
      // Self-scaling (v*=s)
      //=====================================================================================

      // Self-scaling (v*=s)
      {
         test_ = "Self-scaling (v*=s)";

         try {
            dres_   = lhs_ * rhs_;
            sres_   = dres_;
            refres_ = dres_;

            dres_   *= scalar;
            sres_   *= scalar;
            refres_ *= scalar;
         }
         catch( std::exception& ex ) {
            std::ostringstream oss;
            oss << " Test : " << test_ << "\n"
                << " Error: Failed self-scaling operation\n"
                << " Details:\n"
                << "   Scalar = " << scalar << "\n"
                << "   Error message: " << ex.what() << "\n";
            throw std::runtime_error( oss.str() );
         }

         checkResults<VT1_,VT2_>();
      }


      //=====================================================================================
      // Self-scaling (v=v*s)
      //=====================================================================================

      // Self-scaling (v=v*s)
      {
         test_ = "Self-scaling (v=v*s)";

         try {
            dres_   = lhs_ * rhs_;
            sres_   = dres_;
            refres_ = dres_;

            dres_   = dres_   * scalar;
            sres_   = sres_   * scalar;
            refres_ = refres_ * scalar;
         }
         catch( std::exception& ex ) {
            std::ostringstream oss;
            oss << " Test : " << test_ << "\n"
                << " Error: Failed self-scaling operation\n"
                << " Details:\n"
                << "   Scalar = " << scalar << "\n"
                << "   Error message: " << ex.what() << "\n";
            throw std::runtime_error( oss.str() );
         }

         checkResults<VT1_,VT2_>();
      }


      //=====================================================================================
      // Self-scaling (v=s*v)
      //=====================================================================================

      // Self-scaling (v=s*v)
      {
         test_ = "Self-scaling (v=s*v)";

         try {
            dres_   = lhs_ * rhs_;
            sres_   = dres_;
            refres_ = dres_;

            dres_   = scalar * dres_;
            sres_   = scalar * sres_;
            refres_ = scalar * refres_;
         }
         catch( std::exception& ex ) {
            std::ostringstream oss;
            oss << " Test : " << test_ << "\n"
                << " Error: Failed self-scaling operation\n"
                << " Details:\n"
                << "   Scalar = " << scalar << "\n"
                << "   Error message: " << ex.what() << "\n";
            throw std::runtime_error( oss.str() );
         }

         checkResults<VT1_,VT2_>();
      }


      //=====================================================================================
      // Self-scaling (v/=s)
      //=====================================================================================

      // Self-scaling (v/=s)
      {
         test_ = "Self-scaling (v/=s)";

         try {
            dres_   = lhs_ * rhs_;
            sres_   = dres_;
            refres_ = dres_;

            dres_   /= scalar;
            sres_   /= scalar;
            refres_ /= scalar;
         }
         catch( std::exception& ex ) {
            std::ostringstream oss;
            oss << " Test : " << test_ << "\n"
                << " Error: Failed self-scaling operation\n"
                << " Details:\n"
                << "   Scalar = " << scalar << "\n"
                << "   Error message: " << ex.what() << "\n";
            throw std::runtime_error( oss.str() );
         }

         checkResults<VT1_,VT2_>();
      }


      //=====================================================================================
      // Self-scaling (v=v/s)
      //=====================================================================================

      // Self-scaling (v=v/s)
      {
         test_ = "Self-scaling (v=v/s)";

         try {
            dres_   = lhs_ * rhs_;
            sres_   = dres_;
            refres_ = dres_;

            dres_   = dres_   / scalar;
            sres_   = sres_   / scalar;
            refres_ = refres_ / scalar;
         }
         catch( std::exception& ex ) {
            std::ostringstream oss;
            oss << " Test : " << test_ << "\n"
                << " Error: Failed self-scaling operation\n"
                << " Details:\n"
                << "   Scalar = " << scalar << "\n"
                << "   Error message: " << ex.what() << "\n";
            throw std::runtime_error( oss.str() );
         }

         checkResults<VT1_,VT2_>();
      }


      //=====================================================================================
      // Scaled multiplication (s*OP)
      //=====================================================================================

      // Scaled multiplication with the given vectors
      {
         test_  = "Scaled multiplication with the given vectors (s*OP)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = scalar * ( lhs_ * rhs_ );
            sres_   = scalar * ( lhs_ * rhs_ );
            refres_ = scalar * ( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
             convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = scalar * ( tlhs_ * trhs_ );
            tsres_   = scalar * ( tlhs_ * trhs_ );
            trefres_ = scalar * ( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with evaluated vectors
      {
         test_ = "Scaled multiplication with evaluated vectors (s*OP)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            sres_   = scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            refres_ = scalar * ( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   = scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ = scalar * ( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication (OP*s)
      //=====================================================================================

      // Scaled multiplication with the given vectors
      {
         test_  = "Scaled multiplication with the given vectors (OP*s)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = ( lhs_ * rhs_ ) * scalar;
            sres_   = ( lhs_ * rhs_ ) * scalar;
            refres_ = ( reflhs_ * refrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = ( tlhs_ * trhs_ ) * scalar;
            tsres_   = ( tlhs_ * trhs_ ) * scalar;
            trefres_ = ( treflhs_ * trefrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with evaluated vectors
      {
         test_  = "Scaled multiplication with evaluated vectors (OP*s)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            sres_   = ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            refres_ = ( eval( reflhs_ ) * eval( refrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            tsres_   = ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            trefres_ = ( eval( treflhs_ ) * eval( trefrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication (OP/s)
      //=====================================================================================

      // Scaled multiplication with the given vectors
      {
         test_  = "Scaled multiplication with the given vectors (OP/s)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = ( lhs_ * rhs_ ) / scalar;
            sres_   = ( lhs_ * rhs_ ) / scalar;
            refres_ = ( reflhs_ * refrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = ( tlhs_ * trhs_ ) / scalar;
            tsres_   = ( tlhs_ * trhs_ ) / scalar;
            trefres_ = ( treflhs_ * trefrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with evaluated vectors
      {
         test_  = "Scaled multiplication with evaluated vectors (OP/s)";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            sres_   = ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            refres_ = ( eval( reflhs_ ) * eval( refrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            tsres_   = ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            trefres_ = ( eval( treflhs_ ) * eval( trefrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with addition assignment (s*OP)
      //=====================================================================================

      // Scaled multiplication with addition assignment with the given vectors
      {
         test_  = "Scaled multiplication with addition assignment with the given vectors (s*OP)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += scalar * ( lhs_ * rhs_ );
            sres_   += scalar * ( lhs_ * rhs_ );
            refres_ += scalar * ( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += scalar * ( tlhs_ * trhs_ );
            tsres_   += scalar * ( tlhs_ * trhs_ );
            trefres_ += scalar * ( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with addition assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with addition assignment with evaluated vectors (s*OP)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            sres_   += scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            refres_ += scalar * ( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   += scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ += scalar * ( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with addition assignment (OP*s)
      //=====================================================================================

      // Scaled multiplication with addition assignment with the given vectors
      {
         test_  = "Scaled multiplication with addition assignment with the given vectors (OP*s)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += ( lhs_ * rhs_ ) * scalar;
            sres_   += ( lhs_ * rhs_ ) * scalar;
            refres_ += ( reflhs_ * refrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += ( tlhs_ * trhs_ ) * scalar;
            tsres_   += ( tlhs_ * trhs_ ) * scalar;
            trefres_ += ( treflhs_ * trefrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with addition assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with addition assignment with evaluated vectors (OP*s)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            sres_   += ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            refres_ += ( eval( reflhs_ ) * eval( refrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            tsres_   += ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            trefres_ += ( eval( treflhs_ ) * eval( trefrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with addition assignment (OP/s)
      //=====================================================================================

      // Scaled multiplication with addition assignment with the given vectors
      {
         test_  = "Scaled multiplication with addition assignment with the given vectors (OP/s)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += ( lhs_ * rhs_ ) / scalar;
            sres_   += ( lhs_ * rhs_ ) / scalar;
            refres_ += ( reflhs_ * refrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += ( tlhs_ * trhs_ ) / scalar;
            tsres_   += ( tlhs_ * trhs_ ) / scalar;
            trefres_ += ( treflhs_ * trefrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with addition assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with addition assignment with evaluated vectors (OP/s)";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            sres_   += ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            refres_ += ( eval( reflhs_ ) * eval( refrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            tsres_   += ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            trefres_ += ( eval( treflhs_ ) * eval( trefrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with subtraction assignment (s*OP)
      //=====================================================================================

      // Scaled multiplication with subtraction assignment with the given vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with the given vectors (s*OP)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= scalar * ( lhs_ * rhs_ );
            sres_   -= scalar * ( lhs_ * rhs_ );
            refres_ -= scalar * ( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= scalar * ( tlhs_ * trhs_ );
            tsres_   -= scalar * ( tlhs_ * trhs_ );
            trefres_ -= scalar * ( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with evaluated vectors (s*OP)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            sres_   -= scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            refres_ -= scalar * ( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   -= scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ -= scalar * ( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with subtraction assignment (OP*s)
      //=====================================================================================

      // Scaled multiplication with subtraction assignment with the given vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with the given vectors (OP*s)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= ( lhs_ * rhs_ ) * scalar;
            sres_   -= ( lhs_ * rhs_ ) * scalar;
            refres_ -= ( reflhs_ * refrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= ( tlhs_ * trhs_ ) * scalar;
            tsres_   -= ( tlhs_ * trhs_ ) * scalar;
            trefres_ -= ( treflhs_ * trefrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with evaluated vectors (OP*s)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            sres_   -= ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            refres_ -= ( eval( reflhs_ ) * eval( refrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            tsres_   -= ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            trefres_ -= ( eval( treflhs_ ) * eval( trefrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with subtraction assignment (OP/s)
      //=====================================================================================

      // Scaled multiplication with subtraction assignment with the given vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with the given vectors (OP/s)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= ( lhs_ * rhs_ ) / scalar;
            sres_   -= ( lhs_ * rhs_ ) / scalar;
            refres_ -= ( reflhs_ * refrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= ( tlhs_ * trhs_ ) / scalar;
            tsres_   -= ( tlhs_ * trhs_ ) / scalar;
            trefres_ -= ( treflhs_ * trefrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with subtraction assignment with evaluated vectors (OP/s)";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            sres_   -= ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            refres_ -= ( eval( reflhs_ ) * eval( refrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            tsres_   -= ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            trefres_ -= ( eval( treflhs_ ) * eval( trefrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with multiplication assignment (s*OP)
      //=====================================================================================

      // Scaled multiplication with multiplication assignment with the given vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with the given vectors (s*OP)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= scalar * ( lhs_ * rhs_ );
            sres_   *= scalar * ( lhs_ * rhs_ );
            refres_ *= scalar * ( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= scalar * ( tlhs_ * trhs_ );
            tsres_   *= scalar * ( tlhs_ * trhs_ );
            trefres_ *= scalar * ( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with evaluated vectors (s*OP)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            sres_   *= scalar * ( eval( lhs_ ) * eval( rhs_ ) );
            refres_ *= scalar * ( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   *= scalar * ( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ *= scalar * ( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with multiplication assignment (OP*s)
      //=====================================================================================

      // Scaled multiplication with multiplication assignment with the given vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with the given vectors (OP*s)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= ( lhs_ * rhs_ ) * scalar;
            sres_   *= ( lhs_ * rhs_ ) * scalar;
            refres_ *= ( reflhs_ * refrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= ( tlhs_ * trhs_ ) * scalar;
            tsres_   *= ( tlhs_ * trhs_ ) * scalar;
            trefres_ *= ( treflhs_ * trefrhs_ ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with evaluated vectors (OP*s)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            sres_   *= ( eval( lhs_ ) * eval( rhs_ ) ) * scalar;
            refres_ *= ( eval( reflhs_ ) * eval( refrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            tsres_   *= ( eval( tlhs_ ) * eval( trhs_ ) ) * scalar;
            trefres_ *= ( eval( treflhs_ ) * eval( trefrhs_ ) ) * scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Scaled multiplication with multiplication assignment (OP/s)
      //=====================================================================================

      // Scaled multiplication with multiplication assignment with the given vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with the given vectors (OP/s)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= ( lhs_ * rhs_ ) / scalar;
            sres_   *= ( lhs_ * rhs_ ) / scalar;
            refres_ *= ( reflhs_ * refrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= ( tlhs_ * trhs_ ) / scalar;
            tsres_   *= ( tlhs_ * trhs_ ) / scalar;
            trefres_ *= ( treflhs_ * trefrhs_ ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Scaled multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Scaled multiplication with multiplication assignment with evaluated vectors (OP/s)";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            sres_   *= ( eval( lhs_ ) * eval( rhs_ ) ) / scalar;
            refres_ *= ( eval( reflhs_ ) * eval( refrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            tsres_   *= ( eval( tlhs_ ) * eval( trhs_ ) ) / scalar;
            trefres_ *= ( eval( treflhs_ ) * eval( trefrhs_ ) ) / scalar;
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the transpose dense vector/dense vector multiplication.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the transpose vector multiplication with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from the
// multiplication or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testTransposeOperation()
{
#if BLAZETEST_MATHTEST_TEST_TRANSPOSE_OPERATION
   if( BLAZETEST_MATHTEST_TEST_TRANSPOSE_OPERATION > 1 )
   {
      //=====================================================================================
      // Transpose multiplication
      //=====================================================================================

      // Transpose multiplication with the given vectors
      {
         test_  = "Transpose multiplication with the given vectors";
         error_ = "Failed multiplication operation";

         try {
            initTransposeResults();
            tdres_   = trans( lhs_ * rhs_ );
            tsres_   = trans( lhs_ * rhs_ );
            trefres_ = trans( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   = trans( tlhs_ * trhs_ );
            sres_   = trans( tlhs_ * trhs_ );
            refres_ = trans( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }

      // Transpose multiplication with evaluated vectors
      {
         test_  = "Transpose multiplication with evaluated vectors";
         error_ = "Failed multiplication operation";

         try {
            initTransposeResults();
            tdres_   = trans( eval( lhs_ ) * eval( rhs_ ) );
            tsres_   = trans( eval( lhs_ ) * eval( rhs_ ) );
            trefres_ = trans( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   = trans( eval( tlhs_ ) * eval( trhs_ ) );
            sres_   = trans( eval( tlhs_ ) * eval( trhs_ ) );
            refres_ = trans( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Transpose multiplication with addition assignment
      //=====================================================================================

      // Transpose multiplication with addition assignment with the given vectors
      {
         test_  = "Transpose multiplication with addition assignment with the given vectors";
         error_ = "Failed addition assignment operation";

         try {
            initTransposeResults();
            tdres_   += trans( lhs_ * rhs_ );
            tsres_   += trans( lhs_ * rhs_ );
            trefres_ += trans( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   += trans( tlhs_ * trhs_ );
            sres_   += trans( tlhs_ * trhs_ );
            refres_ += trans( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }

      // Transpose multiplication with addition assignment with evaluated vectors
      {
         test_  = "Transpose multiplication with addition assignment with evaluated vectors";
         error_ = "Failed addition assignment operation";

         try {
            initTransposeResults();
            tdres_   += trans( eval( lhs_ ) * eval( rhs_ ) );
            tsres_   += trans( eval( lhs_ ) * eval( rhs_ ) );
            trefres_ += trans( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   += trans( eval( tlhs_ ) * eval( trhs_ ) );
            sres_   += trans( eval( tlhs_ ) * eval( trhs_ ) );
            refres_ += trans( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Transpose multiplication with subtraction assignment
      //=====================================================================================

      // Transpose multiplication with subtraction assignment with the given vectors
      {
         test_  = "Transpose multiplication with subtraction assignment with the given vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initTransposeResults();
            tdres_   -= trans( lhs_ * rhs_ );
            tsres_   -= trans( lhs_ * rhs_ );
            trefres_ -= trans( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   -= trans( tlhs_ * trhs_ );
            sres_   -= trans( tlhs_ * trhs_ );
            refres_ -= trans( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }

      // Transpose multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Transpose multiplication with subtraction assignment with evaluated vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initTransposeResults();
            tdres_   -= trans( eval( lhs_ ) * eval( rhs_ ) );
            tsres_   -= trans( eval( lhs_ ) * eval( rhs_ ) );
            trefres_ -= trans( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   -= trans( eval( tlhs_ ) * eval( trhs_ ) );
            sres_   -= trans( eval( tlhs_ ) * eval( trhs_ ) );
            refres_ -= trans( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Transpose multiplication with multiplication assignment
      //=====================================================================================

      // Transpose multiplication with multiplication assignment with the given vectors
      {
         test_  = "Transpose multiplication with multiplication assignment with the given vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initTransposeResults();
            tdres_   *= trans( lhs_ * rhs_ );
            tsres_   *= trans( lhs_ * rhs_ );
            trefres_ *= trans( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   *= trans( tlhs_ * trhs_ );
            sres_   *= trans( tlhs_ * trhs_ );
            refres_ *= trans( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }

      // Transpose multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Transpose multiplication with multiplication assignment with evaluated vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initTransposeResults();
            tdres_   *= trans( eval( lhs_ ) * eval( rhs_ ) );
            tsres_   *= trans( eval( lhs_ ) * eval( rhs_ ) );
            trefres_ *= trans( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkTransposeResults<VT1_,VT2_>();

         try {
            initResults();
            dres_   *= trans( eval( tlhs_ ) * eval( trhs_ ) );
            sres_   *= trans( eval( tlhs_ ) * eval( trhs_ ) );
            refres_ *= trans( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the abs dense vector/dense vector multiplication.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the abs vector multiplication with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from the
// multiplication or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testAbsOperation()
{
#if BLAZETEST_MATHTEST_TEST_ABS_OPERATION
   if( BLAZETEST_MATHTEST_TEST_ABS_OPERATION > 1 )
   {
      //=====================================================================================
      // Abs multiplication
      //=====================================================================================

      // Abs multiplication with the given vectors
      {
         test_  = "Abs multiplication with the given vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = abs( lhs_ * rhs_ );
            sres_   = abs( lhs_ * rhs_ );
            refres_ = abs( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = abs( tlhs_ * trhs_ );
            tsres_   = abs( tlhs_ * trhs_ );
            trefres_ = abs( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Abs multiplication with evaluated vectors
      {
         test_  = "Abs multiplication with evaluated vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            dres_   = abs( eval( lhs_ ) * eval( rhs_ ) );
            sres_   = abs( eval( lhs_ ) * eval( rhs_ ) );
            refres_ = abs( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   = abs( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   = abs( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ = abs( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Abs multiplication with addition assignment
      //=====================================================================================

      // Abs multiplication with addition assignment with the given vectors
      {
         test_  = "Abs multiplication with addition assignment with the given vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += abs( lhs_ * rhs_ );
            sres_   += abs( lhs_ * rhs_ );
            refres_ += abs( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += abs( tlhs_ * trhs_ );
            tsres_   += abs( tlhs_ * trhs_ );
            trefres_ += abs( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Abs multiplication with addition assignment with evaluated vectors
      {
         test_  = "Abs multiplication with addition assignment with evaluated vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            dres_   += abs( eval( lhs_ ) * eval( rhs_ ) );
            sres_   += abs( eval( lhs_ ) * eval( rhs_ ) );
            refres_ += abs( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   += abs( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   += abs( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ += abs( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Abs multiplication with subtraction assignment
      //=====================================================================================

      // Abs multiplication with subtraction assignment with the given vectors
      {
         test_  = "Abs multiplication with subtraction assignment with the given types";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= abs( lhs_ * rhs_ );
            sres_   -= abs( lhs_ * rhs_ );
            refres_ -= abs( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= abs( tlhs_ * trhs_ );
            tsres_   -= abs( tlhs_ * trhs_ );
            trefres_ -= abs( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Abs multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Abs multiplication with subtraction assignment with evaluated vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            dres_   -= abs( eval( lhs_ ) * eval( rhs_ ) );
            sres_   -= abs( eval( lhs_ ) * eval( rhs_ ) );
            refres_ -= abs( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   -= abs( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   -= abs( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ -= abs( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Abs multiplication with multiplication assignment
      //=====================================================================================

      // Abs multiplication with multiplication assignment with the given vectors
      {
         test_  = "Abs multiplication with multiplication assignment with the given vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= abs( lhs_ * rhs_ );
            sres_   *= abs( lhs_ * rhs_ );
            refres_ *= abs( reflhs_ * refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= abs( tlhs_ * trhs_ );
            tsres_   *= abs( tlhs_ * trhs_ );
            trefres_ *= abs( treflhs_ * trefrhs_ );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Abs multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Abs multiplication with multiplication assignment with evaluated vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            dres_   *= abs( eval( lhs_ ) * eval( rhs_ ) );
            sres_   *= abs( eval( lhs_ ) * eval( rhs_ ) );
            refres_ *= abs( eval( reflhs_ ) * eval( refrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            tdres_   *= abs( eval( tlhs_ ) * eval( trhs_ ) );
            tsres_   *= abs( eval( tlhs_ ) * eval( trhs_ ) );
            trefres_ *= abs( eval( treflhs_ ) * eval( trefrhs_ ) );
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the subvector-wise dense vector/dense vector multiplication.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the subvector-wise vector multiplication with plain assignment, addition
// assignment, and subtraction assignment. In case any error resulting from the multiplication
// or the subsequent assignment is detected, a \a std::runtime_error exception is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::testSubvectorOperation()
{
#if BLAZETEST_MATHTEST_TEST_SUBVECTOR_OPERATION
   if( BLAZETEST_MATHTEST_TEST_SUBVECTOR_OPERATION > 1 )
   {
      if( lhs_.size() == 0UL )
         return;


      //=====================================================================================
      // Subvector-wise multiplication
      //=====================================================================================

      // Subvector-wise multiplication with the given vectors
      {
         test_  = "Subvector-wise multiplication with the given vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) = subvector( lhs_ * rhs_      , index, size );
               subvector( sres_  , index, size ) = subvector( lhs_ * rhs_      , index, size );
               subvector( refres_, index, size ) = subvector( reflhs_ * refrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) = subvector( tlhs_ * trhs_      , index, size );
               subvector( tsres_  , index, size ) = subvector( tlhs_ * trhs_      , index, size );
               subvector( trefres_, index, size ) = subvector( treflhs_ * trefrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Subvector-wise multiplication with evaluated vectors
      {
         test_  = "Subvector-wise multiplication with evaluated vectors";
         error_ = "Failed multiplication operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) = subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( sres_  , index, size ) = subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( refres_, index, size ) = subvector( eval( reflhs_ ) * eval( refrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) = subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( tsres_  , index, size ) = subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( trefres_, index, size ) = subvector( eval( treflhs_ ) * eval( trefrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Subvector-wise multiplication with addition assignment
      //=====================================================================================

      // Subvector-wise multiplication with addition assignment with the given vectors
      {
         test_  = "Subvector-wise multiplication with addition assignment with the given vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) += subvector( lhs_ * rhs_      , index, size );
               subvector( sres_  , index, size ) += subvector( lhs_ * rhs_      , index, size );
               subvector( refres_, index, size ) += subvector( reflhs_ * refrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) += subvector( tlhs_ * trhs_      , index, size );
               subvector( tsres_  , index, size ) += subvector( tlhs_ * trhs_      , index, size );
               subvector( trefres_, index, size ) += subvector( treflhs_ * trefrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Subvector-wise multiplication with addition assignment with evaluated vectors
      {
         test_  = "Subvector-wise multiplication with addition assignment with evaluated vectors";
         error_ = "Failed addition assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) += subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( sres_  , index, size ) += subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( refres_, index, size ) += subvector( eval( reflhs_ ) * eval( refrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) += subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( tsres_  , index, size ) += subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( trefres_, index, size ) += subvector( eval( treflhs_ ) * eval( trefrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Subvector-wise multiplication with subtraction assignment
      //=====================================================================================

      // Subvector-wise multiplication with subtraction assignment with the given vectors
      {
         test_  = "Subvector-wise multiplication with subtraction assignment with the given vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) -= subvector( lhs_ * rhs_      , index, size );
               subvector( sres_  , index, size ) -= subvector( lhs_ * rhs_      , index, size );
               subvector( refres_, index, size ) -= subvector( reflhs_ * refrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) -= subvector( tlhs_ * trhs_      , index, size );
               subvector( tsres_  , index, size ) -= subvector( tlhs_ * trhs_      , index, size );
               subvector( trefres_, index, size ) -= subvector( treflhs_ * trefrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Subvector-wise multiplication with subtraction assignment with evaluated vectors
      {
         test_  = "Subvector-wise multiplication with subtraction assignment with evaluated vectors";
         error_ = "Failed subtraction assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) -= subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( sres_  , index, size ) -= subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( refres_, index, size ) -= subvector( eval( reflhs_ ) * eval( refrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) -= subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( tsres_  , index, size ) -= subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( trefres_, index, size ) -= subvector( eval( treflhs_ ) * eval( trefrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }


      //=====================================================================================
      // Subvector-wise multiplication with multiplication assignment
      //=====================================================================================

      // Subvector-wise multiplication with multiplication assignment with the given vectors
      {
         test_  = "Subvector-wise multiplication with multiplication assignment with the given vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) *= subvector( lhs_ * rhs_      , index, size );
               subvector( sres_  , index, size ) *= subvector( lhs_ * rhs_      , index, size );
               subvector( refres_, index, size ) *= subvector( reflhs_ * refrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) *= subvector( tlhs_ * trhs_      , index, size );
               subvector( tsres_  , index, size ) *= subvector( tlhs_ * trhs_      , index, size );
               subvector( trefres_, index, size ) *= subvector( treflhs_ * trefrhs_, index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }

      // Subvector-wise multiplication with multiplication assignment with evaluated vectors
      {
         test_  = "Subvector-wise multiplication with multiplication assignment with evaluated vectors";
         error_ = "Failed multiplication assignment operation";

         try {
            initResults();
            for( size_t index=0UL, size=0UL; index<lhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, lhs_.size() - index );
               subvector( dres_  , index, size ) *= subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( sres_  , index, size ) *= subvector( eval( lhs_ ) * eval( rhs_ )      , index, size );
               subvector( refres_, index, size ) *= subvector( eval( reflhs_ ) * eval( refrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<VT1_,VT2_>( ex );
         }

         checkResults<VT1_,VT2_>();

         try {
            initTransposeResults();
            for( size_t index=0UL, size=0UL; index<tlhs_.size(); index+=size ) {
               size = blaze::rand<size_t>( 1UL, tlhs_.size() - index );
               subvector( tdres_  , index, size ) *= subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( tsres_  , index, size ) *= subvector( eval( tlhs_ ) * eval( trhs_ )      , index, size );
               subvector( trefres_, index, size ) *= subvector( eval( treflhs_ ) * eval( trefrhs_ ), index, size );
            }
         }
         catch( std::exception& ex ) {
            convertException<TVT1_,TVT2_>( ex );
         }

         checkTransposeResults<TVT1_,TVT2_>();
      }
   }
#endif
}
//*************************************************************************************************




//=================================================================================================
//
//  ERROR DETECTION FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Checking and comparing the computed results.
//
// \return void
// \exception std::runtime_error Incorrect dense result detected.
// \exception std::runtime_error Incorrect sparse result detected.
//
// This function is called after each test case to check and compare the computed results. The
// two template arguments \a LT and \a RT indicate the types of the left-hand side and right-hand
// side operands used for the computations.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
template< typename LT     // Type of the left-hand side operand
        , typename RT >   // Type of the right-hand side operand
void OperationTest<VT1_,VT2_>::checkResults()
{
   using blaze::IsRowVector;

   if( !isEqual( dres_, refres_ ) ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect dense result vector detected\n"
          << " Details:\n"
          << "   Left-hand side dense " << ( IsRowVector<LT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( LT ).name() << "\n"
          << "   Right-hand side dense " << ( IsRowVector<RT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( RT ).name() << "\n"
          << "   Result:\n" << dres_ << "\n"
          << "   Expected result:\n" << refres_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( sres_, refres_ ) ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect sparse result vector detected\n"
          << " Details:\n"
          << "   Left-hand side dense " << ( IsRowVector<LT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( LT ).name() << "\n"
          << "   Right-hand side dense " << ( IsRowVector<RT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( RT ).name() << "\n"
          << "   Result:\n" << sres_ << "\n"
          << "   Expected result:\n" << refres_ << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking and comparing the computed transpose results.
//
// \return void
// \exception std::runtime_error Incorrect dense result detected.
// \exception std::runtime_error Incorrect sparse result detected.
//
// This function is called after each test case to check and compare the computed transpose
// results. The two template arguments \a LT and \a RT indicate the types of the left-hand
// side and right-hand side operands used for the computations.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
template< typename LT     // Type of the left-hand side operand
        , typename RT >   // Type of the right-hand side operand
void OperationTest<VT1_,VT2_>::checkTransposeResults()
{
   using blaze::IsRowVector;

   if( !isEqual( tdres_, trefres_ ) ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect dense result vector detected\n"
          << " Details:\n"
          << "   Left-hand side dense " << ( IsRowVector<LT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( LT ).name() << "\n"
          << "   Right-hand side dense " << ( IsRowVector<RT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( RT ).name() << "\n"
          << "   Result:\n" << tdres_ << "\n"
          << "   Expected result:\n" << trefres_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( tsres_, trefres_ ) ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect sparse result vector detected\n"
          << " Details:\n"
          << "   Left-hand side dense " << ( IsRowVector<LT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "     " << typeid( LT ).name() << "\n"
          << "   Right-hand side dense " << ( IsRowVector<RT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
          << "   " << ( IsRowVector<RT>::value ? ( "Transpose r" ) : ( "R" ) ) << "ight-hand side dense vector type:\n"
          << "     " << typeid( RT ).name() << "\n"
          << "   Result:\n" << tsres_ << "\n"
          << "   Expected result:\n" << trefres_ << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  UTILITY FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Initializing the non-transpose result vectors.
//
// \return void
//
// This function is called before each non-transpose test case to initialize the according result
// vectors to random values.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::initResults()
{
   const typename blaze::BaseElementType<RE>::Type min( randmin );
   const typename blaze::BaseElementType<RE>::Type max( randmax );

   randomize( dres_, min, max );
   sres_    = dres_;
   refres_  = dres_;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Initializing the transpose result vectors.
//
// \return void
//
// This function is called before each transpose test case to initialize the according result
// vectors to random values.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void OperationTest<VT1_,VT2_>::initTransposeResults()
{
   const typename blaze::BaseElementType<RE>::Type min( randmin );
   const typename blaze::BaseElementType<RE>::Type max( randmax );

   randomize( tdres_, min, max );
   tsres_   = tdres_;
   trefres_ = tdres_;
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Convert the given exception into a \a std::runtime_error exception.
//
// \param ex The \a std::exception to be extended.
// \return void
// \exception std::runtime_error The converted exception.
//
// This function converts the given exception to a \a std::runtime_error exception. Additionally,
// the function extends the given exception message by all available information for the failed
// test. The two template arguments \a LT and \a RT indicate the types of the left-hand side and
// right-hand side operands used for the computations.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
template< typename LT     // Type of the left-hand side operand
        , typename RT >   // Type of the right-hand side operand
void OperationTest<VT1_,VT2_>::convertException( const std::exception& ex )
{
   using blaze::IsRowVector;

   std::ostringstream oss;
   oss << " Test : " << test_ << "\n"
       << " Error: " << error_ << "\n"
       << " Details:\n"
       << "   Left-hand side dense " << ( IsRowVector<LT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
       << "     " << typeid( LT ).name() << "\n"
       << "   Right-hand side dense " << ( IsRowVector<RT>::value ? ( "row" ) : ( "column" ) ) << " vector type:\n"
       << "     " << typeid( RT ).name() << "\n"
       << "   Error message: " << ex.what() << "\n";
   throw std::runtime_error( oss.str() );
}
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Testing the vector multiplication between two specific vector types.
//
// \param creator1 The creator for the left-hand side dense vector.
// \param creator2 The creator for the right-hand side dense vector.
// \return void
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side dense vector
void runTest( const Creator<VT1_>& creator1, const Creator<VT2_>& creator2 )
{
   for( size_t rep=0; rep<repetitions; ++rep ) {
      OperationTest<VT1_,VT2_>( creator1, creator2 );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  MACRO DEFINITIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the definition of a dense vector/dense vector multiplication test case.
*/
#define DEFINE_DVECDVECMULT_OPERATION_TEST( VT1_, VT2_ ) \
   extern template class blazetest::mathtest::dvecdvecmult::OperationTest<VT1_,VT2_>
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the execution of a dense vector/dense vector multiplication test case.
*/
#define RUN_DVECDVECMULT_OPERATION_TEST( C1, C2 ) \
   blazetest::mathtest::dvecdvecmult::runTest( C1, C2 )
/*! \endcond */
//*************************************************************************************************

} // namespace dvecdvecmult

} // namespace mathtest

} // namespace blazetest

#endif
