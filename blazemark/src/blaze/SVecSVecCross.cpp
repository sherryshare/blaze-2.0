//=================================================================================================
/*!
//  \file src/blaze/SVecSVecCross.cpp
//  \brief Source file for the Blaze sparse vector/sparse vector cross product kernel
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

#include <iostream>
#include <vector>
#include <blaze/math/CompressedVector.h>
#include <blaze/math/StaticVector.h>
#include <blaze/util/AlignedAllocator.h>
#include <blaze/util/Timing.h>
#include <blazemark/blaze/SVecSVecCross.h>
#include <blazemark/blaze/init/CompressedVector.h>
#include <blazemark/blaze/init/StaticVector.h>
#include <blazemark/system/Config.h>


namespace blazemark {

namespace blaze {

//=================================================================================================
//
//  KERNEL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Blaze sparse vector/sparse vector cross product kernel.
//
// \param N The number of cross products to be computed.
// \param F The number of non-zero elements for the sparse vector.
// \param steps The number of iteration steps to perform.
// \return Minimum runtime of the kernel function.
//
// This kernel function implements the sparse vector/sparse vector cross product by means of
// the Blaze functionality.
*/
double svecsveccross( size_t N, size_t F, size_t steps )
{
   using ::blazemark::element_t;
   using ::blaze::columnVector;

   typedef ::blaze::StaticVector<element_t,3UL,columnVector>  VectorType;
   typedef ::blaze::AlignedAllocator<VectorType>              AllocatorType;

   ::blaze::setSeed( seed );

   ::std::vector< ::blaze::CompressedVector<element_t,columnVector> > a( N ), b( N );
   ::std::vector< VectorType, AllocatorType > c( N );
   ::blaze::timing::WcTimer timer;

   for( size_t i=0UL; i<N; ++i ) {
      a[i].resize( 3UL );
      b[i].resize( 3UL );
      init( a[i], F );
      init( b[i], F );
   }

   for( size_t i=0UL; i<N; ++i ) {
      c[i] = a[i] % b[i];
   }

   for( size_t rep=0UL; rep<reps; ++rep )
   {
      timer.start();
      for( size_t step=0UL, i=0UL; step<steps; ++step, ++i ) {
         if( i == N ) i = 0UL;
         c[i] = a[i] % b[i];
      }
      timer.end();

      for( size_t i=0UL; i<N; ++i )
         if( c[i].size() != 3UL )
            std::cerr << " Line " << __LINE__ << ": ERROR detected!!!\n";

      if( timer.last() > maxtime )
         break;
   }

   const double minTime( timer.min()     );
   const double avgTime( timer.average() );

   if( minTime * ( 1.0 + deviation*0.01 ) < avgTime )
      std::cerr << " Blaze kernel 'svecsveccross': Time deviation too large!!!\n";

   return minTime;
}
//*************************************************************************************************

} // namespace blaze

} // namespace blazemark