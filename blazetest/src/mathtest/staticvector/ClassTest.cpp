//=================================================================================================
/*!
//  \file src/mathtest/staticvector/ClassTest.cpp
//  \brief Source file for the StaticVector class test
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


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/DynamicVector.h>
#include <blaze/math/shims/Equal.h>
#include <blaze/util/Complex.h>
#include <blaze/util/Random.h>
#include <blaze/util/UniqueArray.h>
#include <blazetest/mathtest/staticvector/ClassTest.h>
#include <blazetest/mathtest/RandomMaximum.h>
#include <blazetest/mathtest/RandomMinimum.h>


namespace blazetest {

namespace mathtest {

namespace staticvector {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the StaticVector class test.
//
// \exception std::runtime_error Operation error detected.
*/
ClassTest::ClassTest()
{
   testAlignment< char            >( "char"            );
   testAlignment< signed char     >( "signed char"     );
   testAlignment< unsigned char   >( "unsigned char"   );
   testAlignment< wchar_t         >( "wchar_t"         );
   testAlignment< short           >( "short"           );
   testAlignment< unsigned short  >( "unsigned short"  );
   testAlignment< int             >( "int"             );
   testAlignment< unsigned int    >( "unsigned int"    );
   testAlignment< float           >( "float"           );
   testAlignment< double          >( "double"          );
   testAlignment< complex<float>  >( "complex<float>"  );
   testAlignment< complex<double> >( "complex<double>" );

   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testDivAssign();
   testSubscript();
   testNonZeros();
   testReset();
   testScale();
   testSwap();
   testIsDefault();
   testIsNan();
   testLength();
   testNormalize();
   testMinimum();
   testMaximum();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the StaticVector constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testConstructors()
{
   //=====================================================================================
   // Default constructor
   //=====================================================================================

   {
      test_ = "StaticVector default constructor";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec;

      checkSize    ( vec, 5UL );
      checkCapacity( vec, 5UL );
      checkNonZeros( vec, 0UL );

      if( vec[0] != 0 || vec[1] != 0 || vec[2] != 0 || vec[3] != 0 || vec[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 0 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Homogeneous initialization
   //=====================================================================================

   {
      test_ = "StaticVector homogeneous initialization constructor";

      blaze::StaticVector<int,3UL,blaze::rowVector> vec( 2 );

      checkSize    ( vec, 3UL );
      checkCapacity( vec, 3UL );
      checkNonZeros( vec, 3UL );

      if( vec[0] != 2 || vec[1] != 2 || vec[2] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 2 2 2 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // 2D initialization constructor
   //=====================================================================================

   {
      test_ = "StaticVector 2D initialization constructor";

      blaze::StaticVector<int,2UL,blaze::rowVector> vec( 3, 5 );

      checkSize    ( vec, 2UL );
      checkCapacity( vec, 2UL );
      checkNonZeros( vec, 2UL );

      if( vec[0] != 3 || vec[1] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 3 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // 3D initialization constructor
   //=====================================================================================

   {
      test_ = "StaticVector 3D initialization constructor";

      blaze::StaticVector<int,3UL,blaze::rowVector> vec( 3, 5, 2 );

      checkSize    ( vec, 3UL );
      checkCapacity( vec, 3UL );
      checkNonZeros( vec, 3UL );

      if( vec[0] != 3 || vec[1] != 5 || vec[2] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 3 5 2 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // 4D initialization constructor
   //=====================================================================================

   {
      test_ = "StaticVector 4D initialization constructor";

      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 3, 5, 2, -7 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 3 || vec[1] != 5 || vec[2] != 2 || vec[3] != -7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 3 5 2 -7 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // 5D initialization constructor
   //=====================================================================================

   {
      test_ = "StaticVector 5D initialization constructor";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec( 3, 5, 2, -7, -1 );

      checkSize    ( vec, 5UL );
      checkCapacity( vec, 5UL );
      checkNonZeros( vec, 5UL );

      if( vec[0] != 3 || vec[1] != 5 || vec[2] != 2 || vec[3] != -7 || vec[4] != -1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 3 5 2 -7 -1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // 6D initialization constructor
   //=====================================================================================

   {
      test_ = "StaticVector 6D initialization constructor";

      blaze::StaticVector<int,6UL,blaze::rowVector> vec( 3, 5, 2, -7, -1, 4 );

      checkSize    ( vec, 6UL );
      checkCapacity( vec, 6UL );
      checkNonZeros( vec, 6UL );

      if( vec[0] != 3 || vec[1] != 5 || vec[2] != 2 || vec[3] != -7 || vec[4] != -1 || vec[5] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 3 5 2 -7 -1 4 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Array initialization
   //=====================================================================================

   {
      test_ = "StaticVector dynamic array initialization constructor";

      blaze::UniqueArray<int> array( new int[2] );
      array[0] = 1;
      array[1] = 2;
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 2UL, array.get() );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 2UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 0 || vec[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector dynamic array initialization constructor";

      blaze::UniqueArray<int> array( new int[4] );
      array[0] = 1;
      array[1] = 2;
      array[2] = 3;
      array[3] = 4;
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 4UL, array.get() );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector static array initialization constructor";

      int array[4] = { 1, 2, 3, 4 };
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( array );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Copy constructor
   //=====================================================================================

   {
      test_ = "StaticVector copy constructor";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec1( 1, 2, 3, 4, 5 );
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( vec1 );

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 5UL );

      if( vec2[0] != 1 || vec2[1] != 2 || vec2[2] != 3 || vec2[3] != 4 || vec2[4] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 2 3 4 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Dense vector constructor
   //=====================================================================================

   {
      test_ = "StaticVector dense vector constructor";

      blaze::DynamicVector<int,blaze::rowVector> vec1( 5UL );
      vec1[0] = 1;
      vec1[1] = 2;
      vec1[2] = 3;
      vec1[3] = 4;
      vec1[4] = 5;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( vec1 );

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 5UL );

      if( vec2[0] != 1 || vec2[1] != 2 || vec2[2] != 3 || vec2[3] != 4 || vec2[4] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 2 3 4 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   try {
      test_ = "StaticVector dense vector constructor (non-fitting vector)";

      blaze::DynamicVector<int,blaze::rowVector> vec1( 5UL );
      vec1[0] = 1;
      vec1[1] = 2;
      vec1[2] = 3;
      vec1[3] = 4;
      vec1[4] = 5;
      blaze::StaticVector<int,4UL,blaze::rowVector> vec2( vec1 );

      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Construction succeeded\n"
          << " Details:\n"
          << "   Result:\n" << vec2 << "\n"
          << "   Given vector:\n( 1 2 3 4 5 )\n";
      throw std::runtime_error( oss.str() );
   }
   catch( std::invalid_argument& )
   {}


   //=====================================================================================
   // Sparse vector constructor
   //=====================================================================================

   {
      test_ = "StaticVector sparse vector constructor";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL, 3UL );
      vec1[0] = 1;
      vec1[2] = 3;
      vec1[4] = 5;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( vec1 );

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 3UL );

      if( vec2[0] != 1 || vec2[1] != 0 || vec2[2] != 3 || vec2[3] != 0 || vec2[4] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 0 3 0 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   try {
      test_ = "HybridVector sparse vector constructor (non-fitting vector)";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL, 3UL );
      vec1[0] = 1;
      vec1[2] = 3;
      vec1[4] = 5;
      blaze::StaticVector<int,4UL,blaze::rowVector> vec2( vec1 );

      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Construction succeeded\n"
          << " Details:\n"
          << "   Result:\n" << vec2 << "\n"
          << "   Given vector:\n( 1 0 3 0 5 )\n";
      throw std::runtime_error( oss.str() );
   }
   catch( std::invalid_argument& )
   {}
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAssignment()
{
   //=====================================================================================
   // Homogeneous assignment
   //=====================================================================================

   {
      test_ = "StaticVector homogeneous assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec;
      vec = 2;

      checkSize    ( vec, 5UL );
      checkCapacity( vec, 5UL );
      checkNonZeros( vec, 5UL );

      if( vec[0] != 2 || vec[1] != 2 || vec[2] != 2 || vec[3] != 2 || vec[4] != 2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 2 2 2 2 2 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Array assignment
   //=====================================================================================

   {
      test_ = "StaticVector array assignment";

      int array[4] = { 1, 2 };
      blaze::StaticVector<int,4UL,blaze::rowVector> vec;
      vec = array;

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 2UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 0 || vec[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector array assignment";

      int array[4] = { 1, 2, 3, 4 };
      blaze::StaticVector<int,4UL,blaze::rowVector> vec;
      vec = array;

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Copy assignment
   //=====================================================================================

   {
      test_ = "StaticVector copy assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec1( 1, 2, 3, 4, 5 );
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2;
      vec2 = vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 5UL );

      if( vec2[0] != 1 || vec2[1] != 2 || vec2[2] != 3 || vec2[3] != 4 || vec2[4] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 2 3 4 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector copy assignment stress test";

      typedef blaze::StaticVector<int,10UL,blaze::rowVector>  RandomVectorType;

      blaze::StaticVector<int,10UL,blaze::rowVector> vec1;
      const int min( randmin );
      const int max( randmax );

      for( size_t i=0UL; i<100UL; ++i )
      {
         const RandomVectorType vec2( blaze::rand<RandomVectorType>( min, max ) );

         vec1 = vec2;

         if( vec1 != vec2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << vec1 << "\n"
                << "   Expected result:\n" << vec2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Dense vector assignment
   //=====================================================================================

   {
      test_ = "StaticVector dense vector assignment";

      blaze::DynamicVector<int,blaze::rowVector> vec1( 5UL );
      vec1[0] = 1;
      vec1[1] = 2;
      vec1[2] = 3;
      vec1[3] = 4;
      vec1[4] = 5;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2;
      vec2 = vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 5UL );

      if( vec2[0] != 1 || vec2[1] != 2 || vec2[2] != 3 || vec2[3] != 4 || vec2[4] != 5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 2 3 4 5 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector copy assignment stress test";

      typedef blaze::DynamicVector<int,blaze::rowVector>  RandomVectorType;

      blaze::StaticVector<int,10UL,blaze::rowVector> vec1;
      const int min( randmin );
      const int max( randmax );

      for( size_t i=0UL; i<100UL; ++i )
      {
         const RandomVectorType vec2( blaze::rand<RandomVectorType>( 10UL, min, max ) );

         vec1 = vec2;

         if( vec1 != vec2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << vec1 << "\n"
                << "   Expected result:\n" << vec2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Sparse vector assignment
   //=====================================================================================

   {
      test_ = "StaticVector sparse vector assignment";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL );
      vec1[0] = 1;
      vec1[2] = 2;
      vec1[3] = 3;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2;
      vec2 = vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 3UL );

      if( vec2[0] != 1 || vec2[1] != 0 || vec2[2] != 2 || vec2[3] != 3 || vec2[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 0 2 3 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      test_ = "StaticVector copy assignment stress test";

      typedef blaze::CompressedVector<int,blaze::rowVector>  RandomVectorType;

      blaze::StaticVector<int,10UL,blaze::rowVector> vec1;
      const int min( randmin );
      const int max( randmax );

      for( size_t i=0UL; i<100UL; ++i )
      {
         const RandomVectorType vec2( blaze::rand<RandomVectorType>( 10UL, min, max ) );

         vec1 = vec2;

         if( vec1 != vec2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment failed\n"
                << " Details:\n"
                << "   Result:\n" << vec1 << "\n"
                << "   Expected result:\n" << vec2 << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the StaticVector class
// template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testAddAssign()
{
   // Dense vector addition assignment
   {
      test_ = "StaticVector dense vector addition assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec1( 1, 0, -2,  3, 0 );
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( 0, 4,  2, -6, 7 );

      vec2 += vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 4UL );

      if( vec2[0] != 1 || vec2[1] != 4 || vec2[2] != 0 || vec2[3] != -3 || vec2[4] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 4 0 -3 7 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Sparse vector addition assignment
   {
      test_ = "DynamicVector sparse vector addition assignment";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL, 3UL );
      vec1[0] =  1;
      vec1[2] = -2;
      vec1[3] =  3;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( 0, 4, 2, -6, 7 );

      vec2 += vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 4UL );

      if( vec2[0] != 1 || vec2[1] != 4 || vec2[2] != 0 || vec2[3] != -3 || vec2[4] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 4 0 -3 7 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the StaticVector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSubAssign()
{
   // Dense vector subtraction assignment
   {
      test_ = "StaticVector dense vector subtraction assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec1( -1, 0, 2, -3, 0 );
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2(  0, 4, 2, -6, 7 );

      vec2 -= vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 4UL );

      if( vec2[0] != 1 || vec2[1] != 4 || vec2[2] != 0 || vec2[3] != -3 || vec2[4] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 4 0 -3 7 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Sparse vector subtraction assignment
   {
      test_ = "DynamicVector sparse vector subtraction assignment";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL, 3UL );
      vec1[0] = -1;
      vec1[2] =  2;
      vec1[3] = -3;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( 0, 4, 2, -6, 7 );

      vec2 -= vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 4UL );

      if( vec2[0] != 1 || vec2[1] != 4 || vec2[2] != 0 || vec2[3] != -3 || vec2[4] != 7 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 1 4 0 -3 7 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the StaticVector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMultAssign()
{
   // Dense vector multiplication assignment
   {
      test_ = "StaticVector dense vector multiplication assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec1( 1, 0, -2,  3, 0 );
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( 0, 4,  2, -6, 7 );

      vec2 *= vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 2UL );

      if( vec2[0] != 0 || vec2[1] != 0 || vec2[2] != -4 || vec2[3] != -18 || vec2[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 0 0 -4 -18 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Sparse vector multiplication assignment
   {
      test_ = "DynamicVector sparse vector multiplication assignment";

      blaze::CompressedVector<int,blaze::rowVector> vec1( 5UL, 3UL );
      vec1[0] =  1;
      vec1[2] = -2;
      vec1[3] =  3;
      blaze::StaticVector<int,5UL,blaze::rowVector> vec2( 0, 4, 2, -6, 7 );

      vec2 *= vec1;

      checkSize    ( vec2, 5UL );
      checkCapacity( vec2, 5UL );
      checkNonZeros( vec2, 2UL );

      if( vec2[0] != 0 || vec2[1] != 0 || vec2[2] != -4 || vec2[3] != -18 || vec2[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec2 << "\n"
             << "   Expected result:\n( 0 0 -4 -18 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Scalar multiplication assignment
   {
      test_ = "StaticVector scalar multiplication assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec( 1, 0, -2, 3, 0 );

      vec *= 2;

      checkSize    ( vec, 5UL );
      checkCapacity( vec, 5UL );
      checkNonZeros( vec, 3UL );

      if( vec[0] != 2 || vec[1] != 0 || vec[2] != -4 || vec[3] != 6 || vec[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 2 0 -4 6 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector division assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the division assignment operators of the StaticVector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testDivAssign()
{
   // Scalar division assignment
   {
      test_ = "StaticVector scalar division assignment";

      blaze::StaticVector<int,5UL,blaze::rowVector> vec( 2, 0, -4, 6, 0 );

      vec /= 2;

      checkSize    ( vec, 5UL );
      checkCapacity( vec, 5UL );
      checkNonZeros( vec, 3UL );

      if( vec[0] != 1 || vec[1] != 0 || vec[2] != -2 || vec[3] != 3 || vec[4] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Division assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 0 -2 3 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the StaticVector subscript operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the subscript operator
// of the StaticVector class template. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void ClassTest::testSubscript()
{
   test_ = "StaticVector::operator[]";

   // Writing the first element
   blaze::StaticVector<int,5UL,blaze::rowVector> vec;
   vec[2] = 1;

   checkSize    ( vec, 5UL );
   checkCapacity( vec, 5UL );
   checkNonZeros( vec, 1UL );

   if( vec[2] != 1 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 0 0 1 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Writing the second element
   vec[4] = 2;

   checkSize    ( vec, 5UL );
   checkCapacity( vec, 5UL );
   checkNonZeros( vec, 2UL );

   if( vec[2] != 1 || vec[4] != 2 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 0 0 1 0 2 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Writing the third element
   vec[3] = 3;

   checkSize    ( vec, 5UL );
   checkCapacity( vec, 5UL );
   checkNonZeros( vec, 3UL );

   if( vec[2] != 1 || vec[3] != 3 || vec[4] != 2 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 0 0 1 3 2 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Writing the fourth element
   vec[0] = 4;

   checkSize    ( vec, 5UL );
   checkCapacity( vec, 5UL );
   checkNonZeros( vec, 4UL );

   if( vec[0] != 4 || vec[2] != 1 || vec[3] != 3 || vec[4] != 2 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Subscript operator failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 4 0 1 3 2 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the nonZeros member function of StaticVector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the nonZeros member function of StaticVector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testNonZeros()
{
   test_ = "StaticVector::nonZeros()";

   {
      blaze::StaticVector<int,4UL,blaze::rowVector> vec;

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 0UL );

      if( vec[0] != 0 || vec[1] != 0 || vec[2] != 0 || vec[3] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 0 0 0 0 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 1, 2, 0, 3 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 3UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 0 || vec[3] != 3 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 0 3 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the reset member function of StaticVector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the reset member function of StaticVector. In case an
// error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testReset()
{
   test_ = "StaticVector::reset()";

   // Initialization check
   blaze::StaticVector<int,4UL,blaze::rowVector> vec( 1, 2, 3, 4 );

   checkSize    ( vec, 4UL );
   checkCapacity( vec, 4UL );
   checkNonZeros( vec, 4UL );

   if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Initialization failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 1 2 3 4 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Resetting the vector
   vec.reset();

   checkSize    ( vec, 4UL );
   checkCapacity( vec, 4UL );
   checkNonZeros( vec, 0UL );

   if( vec[0] != 0 || vec[1] != 0 || vec[2] != 0 || vec[3] != 0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Reset operation failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 0 0 0 0 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the scale member function of StaticVector.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the scale member function of StaticVector.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testScale()
{
   test_ = "StaticVector::scale()";

   {
      // Initialization check
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 1, 2, 3, 4 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Integral scaling of the vector
      vec.scale( 2 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 2 || vec[1] != 4 || vec[2] != 6 || vec[3] != 8 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 2 4 6 8 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Floating point scaling of the vector
      vec.scale( 0.5 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      using blaze::complex;

      blaze::StaticVector<complex<float>,2UL,blaze::rowVector> vec;
      vec[0] = complex<float>( 1.0F, 0.0F );
      vec[1] = complex<float>( 2.0F, 0.0F );
      vec.scale( complex<float>( 3.0F, 0.0F ) );

      checkSize    ( vec, 2UL );
      checkCapacity( vec, 2UL );
      checkNonZeros( vec, 2UL );

      if( vec[0] != complex<float>( 3.0F, 0.0F ) || vec[1] != complex<float>( 6.0F, 0.0F ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Scale operation failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( (3,0) (6,0) )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the swap functionality of the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the swap function of the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testSwap()
{
   test_ = "StaticVector swap";

   blaze::StaticVector<int,4UL,blaze::rowVector> vec1( 1, 2, 3, 4 );
   blaze::StaticVector<int,4UL,blaze::rowVector> vec2( 4, 3, 2, 1 );

   swap( vec1, vec2 );

   checkSize    ( vec1, 4UL );
   checkCapacity( vec1, 4UL );
   checkNonZeros( vec1, 4UL );

   if( vec1[0] != 4 || vec1[1] != 3 || vec1[2] != 2 || vec1[3] != 1 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Swapping the first vector failed\n"
          << " Details:\n"
          << "   Result:\n" << vec1 << "\n"
          << "   Expected result:\n( 1 2 3 4 )\n";
      throw std::runtime_error( oss.str() );
   }

   checkSize    ( vec2, 4UL );
   checkCapacity( vec2, 4UL );
   checkNonZeros( vec2, 4UL );

   if( vec2[0] != 1 || vec2[1] != 2 || vec2[2] != 3 || vec2[3] != 4 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Swapping the second vector failed\n"
          << " Details:\n"
          << "   Result:\n" << vec1 << "\n"
          << "   Expected result:\n( 4 3 2 1 )\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the isDefault function with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the isDefault function with the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsDefault()
{
   test_ = "isDefault() function";

   // isDefault with default vector
   {
      blaze::StaticVector<int,3UL,blaze::rowVector> vec;

      if( isDefault( vec ) != true ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isDefault evaluation\n"
             << " Details:\n"
             << "   Vector:\n" << vec << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // isDefault with non-default vector
   {
      blaze::StaticVector<int,3UL,blaze::rowVector> vec( 0, 1, 0 );

      if( isDefault( vec ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isDefault evaluation\n"
             << " Details:\n"
             << "   Vector:\n" << vec << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the isnan function with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the isnan function with the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testIsNan()
{
   test_ = "isnan() function";

   // isnan with empty 9-dimensional vector
   {
      blaze::StaticVector<float,9UL,blaze::rowVector> vec;

      if( blaze::isnan( vec ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isnan evaluation\n"
             << " Details:\n"
             << "   Vector:\n" << vec << "\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // isnan with filled 9-dimensional vector
   {
      blaze::StaticVector<float,9UL,blaze::rowVector> vec;
      vec[3] =  1.0F;
      vec[4] = -2.0F;
      vec[6] =  3.0F;
      vec[8] =  4.0F;

      if( blaze::isnan( vec ) != false ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Invalid isnan evaluation\n"
             << " Details:\n"
             << "   Vector:\n" << vec << "\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the length and sqrLength functions with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the length and sqrLength functions with the StaticVector
// class template. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testLength()
{
   test_ = "length() and sqrLength() functions";

   {
      blaze::StaticVector<double,2UL,blaze::rowVector> vec;

      // Computing the vector length
      const double len( length( vec ) );

      if( !blaze::equal( len, 0.0 ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Length computation failed\n"
             << " Details:\n"
             << "   Result: " << len << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }

      // Computing the vector square length
      const double sqrlen( sqrLength( vec ) );

      if( !blaze::equal( sqrlen, 0.0 ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Square length computation failed\n"
             << " Details:\n"
             << "   Result: " << sqrlen << "\n"
             << "   Expected result: 0\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      blaze::StaticVector<double,2UL,blaze::rowVector> vec( 3.0, 4.0 );

      // Computing the vector length
      const double len( length( vec ) );

      if( !blaze::equal( len, 5.0 ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Length computation failed\n"
             << " Details:\n"
             << "   Result: " << len << "\n"
             << "   Expected result: 5\n";
         throw std::runtime_error( oss.str() );
      }

      // Computing the vector square length
      const double sqrlen( sqrLength( vec ) );

      if( !blaze::equal( sqrlen, 25.0 ) ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Square length computation failed\n"
             << " Details:\n"
             << "   Result: " << sqrlen << "\n"
             << "   Expected result: 25\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the normalize function with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the normalize function with the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testNormalize()
{
   test_ = "normalize() function";

   // Initialization check
   blaze::StaticVector<double,4UL,blaze::rowVector> vec( 1.0, 2.0, 3.0, 4.0 );

   checkSize    ( vec, 4UL );
   checkCapacity( vec, 4UL );
   checkNonZeros( vec, 4UL );

   if( vec[0] != 1.0 || vec[1] != 2.0 || vec[2] != 3.0 || vec[3] != 4.0 ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Initialization failed\n"
          << " Details:\n"
          << "   Result:\n" << vec << "\n"
          << "   Expected result:\n( 1 2 3 4 )\n";
      throw std::runtime_error( oss.str() );
   }

   // Acquiring normalized vector
   const blaze::StaticVector<double,4UL,blaze::rowVector> normalized( normalize( vec ) );

   if( !blaze::equal( length( normalized ), 1.0 ) ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Normalization failed\n"
          << " Details:\n"
          << "   Result: " << length( normalized ) << "\n"
          << "   Expected result: 1\n";
      throw std::runtime_error( oss.str() );
   }

   // Normalizing the vector
   vec = normalize( vec );

   if( !blaze::equal( length( vec ), 1.0 ) ) {
      std::ostringstream oss;
      oss << " Test: " << test_ << "\n"
          << " Error: Self-normalization failed\n"
          << " Details:\n"
          << "   Result: " << length( vec ) << "\n"
          << "   Expected result: 1\n";
      throw std::runtime_error( oss.str() );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the min function with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the min function with the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMinimum()
{
   test_ = "min() function";

   {
      // Initialization check
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 1, -2, 3, -4 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != -2 || vec[2] != 3 || vec[3] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 -2 3 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Testing the min function
      const int minimum = min( vec );

      if( minimum != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: First computation failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      // Initialization check
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( -1, 2, 3, 4 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != -1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( -1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Testing the min function
      const int minimum = min( vec );

      if( minimum != -1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Second computation failed\n"
             << " Details:\n"
             << "   Result: " << minimum << "\n"
             << "   Expected result: -1\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the max function with the StaticVector class template.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the max function with the StaticVector class template.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void ClassTest::testMaximum()
{
   test_ = "max() function";

   {
      // Initialization check
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( 1, -2, -3, -4 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != 1 || vec[1] != -2 || vec[2] != -3 || vec[3] != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( 1 -2 -3 -4 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Testing the max function
      const int maximum = max( vec );

      if( maximum != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: First computation failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }
   }

   {
      // Initialization check
      blaze::StaticVector<int,4UL,blaze::rowVector> vec( -1, 2, 3, 4 );

      checkSize    ( vec, 4UL );
      checkCapacity( vec, 4UL );
      checkNonZeros( vec, 4UL );

      if( vec[0] != -1 || vec[1] != 2 || vec[2] != 3 || vec[3] != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << vec << "\n"
             << "   Expected result:\n( -1 2 3 4 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Testing the max function
      const int maximum = max( vec );

      if( maximum != 4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Second computation failed\n"
             << " Details:\n"
             << "   Result: " << maximum << "\n"
             << "   Expected result: 4\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************

} // namespace staticvector

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running StaticVector class test..." << std::endl;

   try
   {
      RUN_STATICVECTOR_CLASS_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during StaticVector class test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
