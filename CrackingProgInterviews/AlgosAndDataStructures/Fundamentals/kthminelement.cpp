//
// Created by Ranga on 6/26/16.
//

#include <vector>
#include <iostream>
#include <chrono>
#include "sortutils.h"

int main( int argc, char *argv[] ) {

    std::vector< std::vector< int > > sample1, sample2;
    int totalSamples = 100, valuesPerSample = 10000;
    sample1.reserve( totalSamples );
    sample2.reserve( totalSamples );
    for( auto i = 0; i < totalSamples; ++i ) {
        std::vector< int > randomInts = SortUtils::GetNBoundedRandomInts( 1, 1000000, valuesPerSample );
        sample1.push_back( randomInts );
        sample2.push_back( randomInts );
    }

    std::cout << "Data gathered. Staring test\n";

    std::vector< int > kValues{ valuesPerSample * 0.05, valuesPerSample * 0.25, valuesPerSample * 0.5, valuesPerSample * 0.75, valuesPerSample * 0.90, valuesPerSample * 0.95 };
    for( auto k : kValues ) {
        auto step1 = std::chrono::system_clock::now();
        for( auto i = 0; i < totalSamples; ++i ) {
            std::vector< int > randomInts = sample1[ i ];
            SortUtils::KthMinQSort( randomInts, k );
        }
        auto step2 = std::chrono::system_clock::now();
        for( auto i = 0; i < totalSamples; ++i ) {
            std::vector< int > randomInts = sample2[ i ];
            SortUtils::KthMinSelectionSort( randomInts, k );
        }
        auto step3 = std::chrono::system_clock::now();
        std::chrono::duration< double > usingQPartition = step2 - step1;
        std::chrono::duration< double > usingSelectSort = step3 - step2;
        std::cout << "For " << k << ": Quicksort Partition - " << usingQPartition.count() << ", Selection Sort - " << usingSelectSort.count() << std::endl;
    }

    return 0;
}