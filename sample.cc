// Examples using Burg’s approximation algorithm

#include <math.h>
#include <stdio.h>
#include "burg.hpp"

#define TEST_SEQUENCE( expr ) do { \
    enum { NEW_ITEMS = 4 }; \
    /* CREATE DATA TO APPROXIMATE */ \
    std::vector<double> original( 128 + NEW_ITEMS ); \
    for( double i = 0; i < original.size(); i++ ) { \
        original[ unsigned(i) ] = double(expr); \
    } \
    /* TRUNCATE SEQUENCE AND RECONSTRUCT A FEW NEW ITEMS */ \
    std::vector<double> predicted( original ); \
    predicted.resize( predicted.size() - NEW_ITEMS ); \
    burg::expand( predicted, NEW_ITEMS ); \
    /* CALCULATE AND DISPLAY APPROXIMATION ERROR */ \
    printf( "Expression (i) = %s\n", #expr ); \
    double error = 0.0; \
    for( size_t i = predicted.size() - NEW_ITEMS, end = predicted.size(); i < end; i++ ) { \
        printf( "value[ %d ] = %.6f (vs expected %.6f)\n", i, predicted[ i ], original[ i ] ); \
        double delta = predicted[ i ] - original[ i ]; \
        error += delta * delta; \
    } \
    printf( "Error: %f\n\n", error ); \
} while(0) 

int main( int argc, const char **argv ) {
    TEST_SEQUENCE( i );
    TEST_SEQUENCE( i * i );
    TEST_SEQUENCE( i * i * i );
    TEST_SEQUENCE( i * i - sin(i) );
    TEST_SEQUENCE( sin(i) );
    TEST_SEQUENCE( cos( i * 0.01 ) + 0.75 * cos( i * 0.03 ) + 0.5 * cos( i * 0.05 ) + 0.25 * cos( i * 0.11 ) );
} 
