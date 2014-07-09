//=================================================================================================
/*!
//  \file blazetest/mathtest/sparserow/ClassTest.h
//  \brief Header file for the SparseRow class test
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

#ifndef _BLAZETEST_MATHTEST_SPARSEROW_CLASSTEST_H_
#define _BLAZETEST_MATHTEST_SPARSEROW_CLASSTEST_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <sstream>
#include <stdexcept>
#include <string>
#include <blaze/math/constraints/SparseMatrix.h>
#include <blaze/math/constraints/SparseVector.h>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/SparseRow.h>
#include <blaze/math/typetraits/IsRowMajorMatrix.h>
#include <blazetest/system/Types.h>


namespace blazetest {

namespace mathtest {

namespace sparserow {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Auxiliary class for all tests of the SparseRow class template.
//
// This class represents a test suite for the blaze::SparseRow class template. It performs
// a series of both compile time as well as runtime tests.
*/
class ClassTest
{
 public:
   //**Constructors********************************************************************************
   /*!\name Constructors */
   //@{
   explicit ClassTest();
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
   void testConstructors();
   void testAssignment  ();
   void testAddAssign   ();
   void testSubAssign   ();
   void testMultAssign  ();
   void testDivAssign   ();
   void testSubscript   ();
   void testIterator    ();
   void testNonZeros    ();
   void testReset       ();
   void testAppend      ();
   void testInsert      ();
   void testErase       ();
   void testReserve     ();
   void testScale       ();
   void testFind        ();
   void testLowerBound  ();
   void testUpperBound  ();
   void testIsDefault   ();
   void testIsNan       ();
   void testMinimum     ();
   void testMaximum     ();
   void testSubvector   ();

   template< typename Type >
   void checkSize( const Type& row, size_t expectedSize ) const;

   template< typename Type >
   void checkRows( const Type& matrix, size_t expectedRows ) const;

   template< typename Type >
   void checkColumns( const Type& matrix, size_t expectedColumns ) const;

   template< typename Type >
   void checkCapacity( const Type& object, size_t minCapacity ) const;

   template< typename Type >
   void checkNonZeros( const Type& object, size_t expectedNonZeros ) const;

   template< typename Type >
   void checkNonZeros( const Type& row, size_t index, size_t expectedNonZeros ) const;
   //@}
   //**********************************************************************************************

   //**Utility functions***************************************************************************
   /*!\name Utility functions */
   //@{
   void initialize();
   //@}
   //**********************************************************************************************

   //**Type definitions****************************************************************************
   typedef blaze::CompressedMatrix<int,blaze::rowMajor>  MT;   //!< Row-major compressed matrix type
   typedef MT::OppositeType                              TMT;  //!< Column-major compressed matrix type
   typedef blaze::SparseRow<MT>                          RT;   //!< Sparse row type for row-major matrices.
   typedef blaze::SparseRow<TMT>                         TRT;  //!< Sparse row type for column-major matrices.
   //**********************************************************************************************

   //**Member variables****************************************************************************
   /*!\name Member variables */
   //@{
   MT  mat_;   //!< Row-major compressed matrix.
               /*!< The \f$ 5 \times 4 \f$ matrix is initialized as
                    \f[\left(\begin{array}{*{4}{c}}
                     0 &  0 &  0 &  0 \\
                     0 &  1 &  0 &  0 \\
                    -2 &  0 & -3 &  0 \\
                     0 &  4 &  5 & -6 \\
                     7 & -8 &  9 & 10 \\
                    \end{array}\right)\f]. */
   TMT tmat_;  //!< Column-major compressed matrix.
               /*!< The \f$ 5 \times 4 \f$ matrix is initialized as
                    \f[\left(\begin{array}{*{4}{c}}
                     0 &  0 &  0 &  0 \\
                     0 &  1 &  0 &  0 \\
                    -2 &  0 & -3 &  0 \\
                     0 &  4 &  5 & -6 \\
                     7 & -8 &  9 & 10 \\
                    \end{array}\right)\f]. */

   std::string test_;  //!< Label of the currently performed test.
   //@}
   //**********************************************************************************************

   //**Compile time checks*************************************************************************
   /*! \cond BLAZE_INTERNAL */
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( MT  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_MATRIX_TYPE( TMT );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( RT  );
   BLAZE_CONSTRAINT_MUST_BE_SPARSE_VECTOR_TYPE( TRT );
   BLAZE_CONSTRAINT_MUST_BE_ROW_VECTOR_TYPE   ( RT  );
   BLAZE_CONSTRAINT_MUST_BE_ROW_VECTOR_TYPE   ( TRT );
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Checking the size of the given sparse row.
//
// \param row The sparse row to be checked.
// \param expectedSize The expected size of the sparse row.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the size of the given sparse row. In case the actual size does not
// correspond to the given expected size, a \a std::runtime_error exception is thrown.
*/
template< typename Type >  // Type of the sparse row
void ClassTest::checkSize( const Type& row, size_t expectedSize ) const
{
   if( row.size() != expectedSize ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid size detected\n"
          << " Details:\n"
          << "   Size         : " << row.size() << "\n"
          << "   Expected size: " << expectedSize << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking the number of rows of the given compressed matrix.
//
// \param matrix The compressed matrix to be checked.
// \param expectedRows The expected number of rows of the compressed matrix.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the number of rows of the given compressed matrix. In case the
// actual number of rows does not correspond to the given expected number of rows, a
// \a std::runtime_error exception is thrown.
*/
template< typename Type >  // Type of the compressed matrix
void ClassTest::checkRows( const Type& matrix, size_t expectedRows ) const
{
   if( matrix.rows() != expectedRows ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid number of rows detected\n"
          << " Details:\n"
          << "   Number of rows         : " << matrix.rows() << "\n"
          << "   Expected number of rows: " << expectedRows << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking the number of columns of the given compressed matrix.
//
// \param matrix The compressed matrix to be checked.
// \param expectedRows The expected number of columns of the compressed matrix.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the number of columns of the given compressed matrix. In case the
// actual number of columns does not correspond to the given expected number of columns,
// a \a std::runtime_error exception is thrown.
*/
template< typename Type >  // Type of the compressed matrix
void ClassTest::checkColumns( const Type& matrix, size_t expectedColumns ) const
{
   if( matrix.columns() != expectedColumns ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid number of columns detected\n"
          << " Details:\n"
          << "   Number of columns         : " << matrix.columns() << "\n"
          << "   Expected number of columns: " << expectedColumns << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking the capacity of the given sparse row or compressed matrix.
//
// \param object The sparse row or compressed matrix to be checked.
// \param minCapacity The expected minimum capacity.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the capacity of the given sparse row or compressed matrix. In case the
// actual capacity is smaller than the given expected minimum capacity, a \a std::runtime_error
// exception is thrown.
*/
template< typename Type >  // Type of the sparse row or compressed matrix
void ClassTest::checkCapacity( const Type& object, size_t minCapacity ) const
{
   if( object.capacity() < minCapacity ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid capacity detected\n"
          << " Details:\n"
          << "   Capacity                 : " << object.capacity() << "\n"
          << "   Expected minimum capacity: " << minCapacity << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking the number of non-zero elements of the given sparse row or compressed matrix.
//
// \param object The sparse row or compressed matrix to be checked.
// \param expectedNonZeros The expected number of non-zero elements.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the number of non-zero elements of the given sparse row or compressed
// matrix. In case the actual number of non-zero elements does not correspond to the given
// expected number, a \a std::runtime_error exception is thrown.
*/
template< typename Type >  // Type of the sparse row or compressed matrix
void ClassTest::checkNonZeros( const Type& object, size_t expectedNonZeros ) const
{
   if( object.nonZeros() != expectedNonZeros ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid number of non-zero elements\n"
          << " Details:\n"
          << "   Number of non-zeros         : " << object.nonZeros() << "\n"
          << "   Expected number of non-zeros: " << expectedNonZeros << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( object.capacity() < object.nonZeros() ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid capacity detected\n"
          << " Details:\n"
          << "   Number of non-zeros: " << object.nonZeros() << "\n"
          << "   Capacity           : " << object.capacity() << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Checking the number of non-zero elements in a specific row/column of the given compressed matrix.
//
// \param matrix The compressed matrix to be checked.
// \param index The row/column to be checked.
// \param expectedNonZeros The expected number of non-zero elements in the specified row/column.
// \return void
// \exception std::runtime_error Error detected.
//
// This function checks the number of non-zero elements in the specified row/column of the
// given compressed matrix. In case the actual number of non-zero elements does not correspond
// to the given expected number, a \a std::runtime_error exception is thrown.
*/
template< typename Type >  // Type of the compressed matrix
void ClassTest::checkNonZeros( const Type& matrix, size_t index, size_t expectedNonZeros ) const
{
   if( matrix.nonZeros( index ) != expectedNonZeros ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid number of non-zero elements in "
          << ( blaze::IsRowMajorMatrix<Type>::value ? "row " : "column " ) << index << "\n"
          << " Details:\n"
          << "   Number of non-zeros         : " << matrix.nonZeros( index ) << "\n"
          << "   Expected number of non-zeros: " << expectedNonZeros << "\n";
      throw std::runtime_error( oss.str() );
   }

   if( matrix.capacity( index ) < matrix.nonZeros( index ) ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Invalid capacity detected in "
          << ( blaze::IsRowMajorMatrix<Type>::value ? "row " : "column " ) << index << "\n"
          << " Details:\n"
          << "   Number of non-zeros: " << matrix.nonZeros( index ) << "\n"
          << "   Capacity           : " << matrix.capacity( index ) << "\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Testing the functionality of the SparseRow class template.
//
// \return void
*/
void runTest()
{
   ClassTest();
}
//*************************************************************************************************




//=================================================================================================
//
//  MACRO DEFINITIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Macro for the execution of the SparseRow class test.
*/
#define RUN_SPARSEROW_CLASS_TEST \
   blazetest::mathtest::sparserow::runTest()
/*! \endcond */
//*************************************************************************************************

} // namespace sparserow

} // namespace mathtest

} // namespace blazetest

#endif