//=================================================================================================
/*!
//  \file blazetest/mathtest/tdvecsvecmult/OperationTest.h
//  \brief Header file for the dense vector/sparse vector inner product operation test
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

#ifndef _BLAZETEST_MATHTEST_TDVECSVECMULT_OPERATIONTEST_H_
#define _BLAZETEST_MATHTEST_TDVECSVECMULT_OPERATIONTEST_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/constraints/DenseVector.h>
#include <blaze/math/constraints/SparseVector.h>
#include <blaze/math/constraints/TransposeFlag.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/StaticVector.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/util/constraints/Numeric.h>
#include <blaze/util/constraints/SameType.h>
#include <blazetest/system/MathTest.h>
#include <blazetest/mathtest/Creator.h>
#include <blazetest/mathtest/IsEqual.h>


namespace blazetest {

namespace mathtest {

namespace tdvecsvecmult {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Auxiliary class template for the dense vector/sparse vector inner product operation test.
//
// This class template represents one particular inner product test between two vectors of a
// particular type. The two template arguments \a VT1_ and \a VT2_ represent the types of the
// left-hand side and right-hand side vector, respectively.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
class OperationTest
{
 private:
   //**Type definitions****************************************************************************
   typedef typename VT1_::TransposeType                TVT1_;  //!< Transpose vector type 1
   typedef typename VT2_::TransposeType                TVT2_;  //!< Transpose vector type 2
   typedef typename blaze::MultTrait<TVT1_,VT2_>::Type  RE;    //!< Default result type
   //**********************************************************************************************

   //**Type definitions****************************************************************************
   typedef typename VT1_::ElementType        ET1;  //!< Element type 1
   typedef typename VT2_::ElementType        ET2;  //!< Element type 2
   typedef blaze::DynamicVector<ET1,true>   RT1;  //!< Reference type 1
   typedef blaze::DynamicVector<ET2,false>  RT2;  //!< Reference type 2
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
   void testInitialStatus ();
   void testAssignment    ();
   void testBasicOperation();
   //@}
   //**********************************************************************************************

   //**Error detection functions*******************************************************************
   /*!\name Error detection functions */
   //@{
   void checkResult();
   //@}
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   void convertException( const std::exception& ex );
   //@}
   //**********************************************************************************************

   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   TVT1_ lhs_;     //!< The left-hand side dense vector.
   VT2_  rhs_;     //!< The right-hand side sparse vector.
   RE   res_;     //!< The result of the inner product.
   RT1  reflhs_;  //!< The reference left-hand side vector.
   RT2  refrhs_;  //!< The reference right-hand side vector.
   RE   refres_;  //!< The reference result.

   std::string test_;   //!< Label of the currently performed test.
   std::string error_;  //!< Description of the current error type.
   //@}
   //**********************************************************************************************

   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( VT1_   );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( VT2_   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( TVT1_  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( TVT2_  );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( RT1   );
   BLAZE_CONSTRAINT_MUST_BE_DENSE_VECTOR_TYPE ( RT2   );
   BLAZE_CONSTRAINT_MUST_BE_COLUMN_VECTOR_TYPE( VT1_   );
   BLAZE_CONSTRAINT_MUST_BE_COLUMN_VECTOR_TYPE( VT2_   );
   BLAZE_CONSTRAINT_MUST_BE_ROW_VECTOR_TYPE   ( TVT1_  );
   BLAZE_CONSTRAINT_MUST_BE_ROW_VECTOR_TYPE   ( TVT2_  );
   BLAZE_CONSTRAINT_MUST_BE_ROW_VECTOR_TYPE   ( RT1   );
   BLAZE_CONSTRAINT_MUST_BE_COLUMN_VECTOR_TYPE( RT2   );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( ET1, typename TVT1_::ElementType );
   BLAZE_CONSTRAINT_MUST_BE_SAME_TYPE( ET2, typename TVT2_::ElementType );
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
/*!\brief Constructor for the dense vector/sparse vector inner product operation test.
//
// \param creator1 The creator for the left-hand side dense vector of the vector inner product.
// \param creator2 The creator for the right-hand side sparse vector of the vector inner product.
// \exception std::runtime_error Operation error detected.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
OperationTest<VT1_,VT2_>::OperationTest( const Creator<VT1_>& creator1, const Creator<VT2_>& creator2 )
   : lhs_( trans( creator1() ) )  // The left-hand side dense vector
   , rhs_( creator2() )           // The right-hand side sparse vector
   , res_()                       // The result of the inner product
   , reflhs_( lhs_ )              // The reference left-hand side vector
   , refrhs_( rhs_ )              // The reference right-hand side vector
   , refres_()                    // The reference result
   , test_()                      // Label of the currently performed test
   , error_()                     // Description of the current error type
{
   testInitialStatus();
   testAssignment();
   testBasicOperation();
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
        , typename VT2_ >  // Type of the right-hand side sparse vector
void OperationTest<VT1_,VT2_>::testInitialStatus()
{
   // Checking the size of the left-hand side operand
   if( lhs_.size() != reflhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of left-hand side dense operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Detected size = " << lhs_.size() << "\n"
          << "   Expected size = " << reflhs_.size() << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the size of the right-hand side operand
   if( rhs_.size() != refrhs_.size() ) {
      std::ostringstream oss;
      oss << " Test: Initial size comparison of right-hand side sparse operand\n"
          << " Error: Invalid vector size\n"
          << " Details:\n"
          << "   Sparse vector type:\n"
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
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Current initialization:\n" << lhs_ << "\n"
          << "   Expected initialization:\n" << reflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   // Checking the initialization of the right-hand side operand
   if( !isEqual( rhs_, refrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Initial test of initialization of right-hand side sparse operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Sparse vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Current initialization:\n" << rhs_ << "\n"
          << "   Expected initialization:\n" << refrhs_ << "\n";
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
        , typename VT2_ >  // Type of the right-hand side sparse vector
void OperationTest<VT1_,VT2_>::testAssignment()
{
   try {
      lhs_ = reflhs_;
      rhs_ = refrhs_;
   }
   catch( std::exception& ex ) {
      std::ostringstream oss;
      oss << " Test: Assignment with the given vectors\n"
          << " Error: Failed assignment\n"
          << " Details:\n"
          << "   Left-hand side transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Right-hand side sparse vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Error message: " << ex.what() << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( lhs_, reflhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of left-hand side dense operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Current initialization:\n" << lhs_ << "\n"
          << "   Expected initialization:\n" << reflhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( !isEqual( rhs_, refrhs_ ) ) {
      std::ostringstream oss;
      oss << " Test: Checking the assignment result of right-hand side sparse operand\n"
          << " Error: Invalid vector initialization\n"
          << " Details:\n"
          << "   Sparse vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Current initialization:\n" << rhs_ << "\n"
          << "   Expected initialization:\n" << refrhs_ << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Testing the plain dense vector/sparse vector inner product.
//
// \return void
// \exception std::runtime_error Multiplication error detected.
//
// This function tests the plain inner product with plain assignment, addition assignment,
// subtraction assignment, and multiplication assignment. In case any error resulting from
// the addition or the subsequent assignment is detected, a \a std::runtime_error exception
// is thrown.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
void OperationTest<VT1_,VT2_>::testBasicOperation()
{
#if BLAZETEST_MATHTEST_TEST_BASIC_OPERATION
   if( BLAZETEST_MATHTEST_TEST_BASIC_OPERATION > 1 )
   {
      //=====================================================================================
      // Inner product
      //=====================================================================================

      // Inner product with the given vectors
      {
         test_ = "Inner product with the given vectors";

         try {
            res_    = lhs_ * rhs_;
            refres_ = reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }

      // Inner product with evaluated vectors
      {
         test_ = "Inner product with evaluated vectors";

         try {
            res_ = eval( lhs_ ) * eval( rhs_ );
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }


      //=====================================================================================
      // Inner product with addition assignment
      //=====================================================================================

      // Inner product with addition assignment with the given vectors
      {
         test_ = "Inner product with addition assignment with the given vectors";

         try {
            res_    += lhs_ * rhs_;
            refres_ += reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }

      // Inner product with addition assignment with evaluated vectors
      {
         test_ = "Inner product with addition assignment with evaluated vectors";

         try {
            res_    += eval( lhs_ ) * eval( rhs_ );
            refres_ += eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }


      //=====================================================================================
      // Inner product with subtraction assignment
      //=====================================================================================

      // Inner product with subtraction assignment with the given vectors
      {
         test_ = "Inner product with subtraction assignment with the given vectors";

         try {
            res_    -= lhs_ * rhs_;
            refres_ -= reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }

      // Inner product with subtraction assignment with evaluated vectors
      {
         test_ = "Inner product with subtraction assignment with evaluated vectors";

         try {
            res_    -= eval( lhs_ ) * eval( rhs_ );
            refres_ -= eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }


      //=====================================================================================
      // Inner product with multiplication assignment
      //=====================================================================================

      // Inner product with multiplication assignment with the given vectors
      {
         test_ = "Inner product with multiplication assignment with the given vectors";

         try {
            res_    *= lhs_ * rhs_;
            refres_ *= reflhs_ * refrhs_;
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
      }

      // Inner product with multiplication assignment with evaluated vectors
      {
         test_ = "Inner product with multiplication assignment with evaluated vectors";

         try {
            res_    *= eval( lhs_ ) * eval( rhs_ );
            refres_ *= eval( reflhs_ ) * eval( refrhs_ );
         }
         catch( std::exception& ex ) {
            convertException( ex );
         }

         checkResult();
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
// \exception std::runtime_error Incorrect result detected.
//
// This function is called after each test case to check and compare the computed results.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
void OperationTest<VT1_,VT2_>::checkResult()
{
   if( !isEqual( res_, refres_ ) ) {
      std::ostringstream oss;
      oss.precision( 20 );
      oss << " Test : " << test_ << "\n"
          << " Error: Incorrect result detected\n"
          << " Details:\n"
          << "   Left-hand side transpose dense vector type:\n"
          << "     " << typeid( TVT1_ ).name() << "\n"
          << "   Right-hand side sparse vector type:\n"
          << "     " << typeid( VT2_ ).name() << "\n"
          << "   Result:\n" << res_ << "\n"
          << "   Expected result:\n" << refres_ << "\n";
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
/*!\brief Convert the given exception into a \a std::runtime_error exception.
//
// \param ex The \a std::exception to be extended.
// \return void
// \exception std::runtime_error The converted exception.
//
// This function converts the given exception to a \a std::runtime_error exception. Additionally,
// the function extends the given exception message by all available information for the failed
// test.
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
void OperationTest<VT1_,VT2_>::convertException( const std::exception& ex )
{
   std::ostringstream oss;
   oss << " Test : " << test_ << "\n"
       << " Error: " << error_ << "\n"
       << " Details:\n"
       << "   Left-hand side transpose dense vector type:\n"
       << "     " << typeid( TVT1_ ).name() << "\n"
       << "   Right-hand side sparse vector type:\n"
       << "     " << typeid( VT2_ ).name() << "\n"
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
/*!\brief Testing the vector inner product between two specific vector types.
//
// \param creator1 The creator for the left-hand side vector.
// \param creator2 The creator for the right-hand side vector.
// \return void
*/
template< typename VT1_    // Type of the left-hand side dense vector
        , typename VT2_ >  // Type of the right-hand side sparse vector
void runTest( const Creator<VT1_>& creator1, const Creator<VT2_>& creator2 )
{
   for( size_t rep=0; rep<repetitions; ++rep ) {
      OperationTest<VT1_,VT2_>( creator1, creator2 );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  MACROS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the definition of a dense vector/sparse vector inner product test case.
*/
#define DEFINE_TDVECSVECMULT_OPERATION_TEST( VT1_, VT2_ ) \
   extern template class blazetest::mathtest::tdvecsvecmult::OperationTest<VT1_,VT2_>
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the execution of a dense vector/sparse vector inner product test case.
*/
#define RUN_TDVECSVECMULT_OPERATION_TEST( C1, C2 ) \
   blazetest::mathtest::tdvecsvecmult::runTest( C1, C2 )
/*! \endcond */
//*************************************************************************************************

} // namespace tdvecsvecmult

} // namespace mathtest

} // namespace blazetest

#endif
