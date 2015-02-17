// Burg linear predictor. Original code by Cedrick Collomb.
// - rlyeh. boost licensed.

#pragma once
#include <stddef.h>
#include <vector>

namespace burg {
    template<typename T>
    void expand( std::vector<T> &original, unsigned N, const unsigned quality = 8 /*[4..11]*/ ) {
        if( N ) {
            const auto zero = T();
            const auto one = !T();
            const auto two = one + one;
            auto calc_burg_coeff = [&]( std::vector<T> &coeffs, const std::vector<T> &x ) {
                // Returns in vector coefficients calculated using Burg algorithm applied to the input source data x
                // GET SIZE FROM INPUT VECTORS
                size_t N = x.size() - 1;
                size_t m = coeffs.size();
                // INITIALIZE Ak
                std::vector<T> Ak( m + 1, zero );
                Ak[ 0 ] = one;
                // INITIALIZE f and b
                std::vector<T> f( x );
                std::vector<T> b( x );
                // INITIALIZE Dk
                T Dk = zero;
                for( size_t j = 0; j <= N; j++ ) {
                    Dk += two * f[ j ] * f[ j ];
                }
                Dk -= f[ 0 ] * f[ 0 ] + b[ N ] * b[ N ];
                // BURG RECURSION
                for( size_t k = 0; k < m; k++ ) {
                    // COMPUTE MU
                    T mu = zero;
                    for( size_t n = 0; n <= N - k - 1; n++ ) {
                        mu += f[ n + k + 1 ] * b[ n ];
                    }
                    mu *= -two / Dk;
                    // UPDATE Ak
                    for( size_t n = 0; n <= ( k + 1 ) / 2; n++ ) {
                        T t1 = Ak[ n ] + mu * Ak[ k + 1 - n ];
                        T t2 = Ak[ k + 1 - n ] + mu * Ak[ n ];
                        Ak[ n ] = t1;
                        Ak[ k + 1 - n ] = t2;
                    }
                    // UPDATE f and b
                    for( size_t n = 0; n <= N - k - 1; n++ ) {
                        T t1 = f[ n + k + 1 ] + mu * b[ n ];
                        T t2 = b[ n ] + mu * f[ n + k + 1 ];
                        f[ n + k + 1 ] = t1;
                        b[ n ] = t2;
                    }
                    // UPDATE Dk
                    Dk = ( one - mu * mu ) * Dk - f[ k + 1 ] * f[ k + 1 ] - b[ N - k - 1 ] * b[ N - k - 1 ];
                }
                // ASSIGN COEFFICIENTS
                coeffs.assign( ++Ak.begin(), Ak.end() );
                // INVERT SIGN, SO PREDICTION ACCUM BECOMES ADDITIVE
                for( auto &c : coeffs ) c = -c;
            };

            // GET LINEAR PREDICTION COEFFICIENTS
            std::vector<T> coeffs( quality, 0.0 );
            calc_burg_coeff( coeffs, original );

            // LINEAR PREDICT DATA
            const size_t S = original.size(), m = coeffs.size();
            original.resize( S + N );

            for( size_t i = S, end = i + N; i < end; i++ ) {
                for( size_t j = 0; j < m; j++ ) {
                    original[ i ] = original[ i ] + original[ i - 1 - j ] * coeffs[ j ];
                }
            } 
        }
    }
}
