//
// Created by Ranga on 5/15/17.
//

Maximum Sum of Contiguous Subarray

        Given an array of numbers:

int array[N];

find the contiguous subarray with the maximum sum (maximize sum(i = i1 .. i2, array[i])). For example, given this array:

10 20 -40 5 5 10 30 -60

The subarray with the largest sum is array[3] .. array[6] (5 5 10 30) at 50.

Contiguous sub arrays must have consecutive indexes
(10 20 5 5 10 30) is not a contiguous sub array

.

int GetMaxContiguousSum( const vector<int> &array ) {
    if( array.size() == 0 ) {
        return numeric_limits< int >::min();
    }

    int maxSum = array[ 0 ], sum = array[ 0 ];
    std::pair< int, int > maxStartEnd;
    for( int i = 1; i < array.size(); ++i ) {
        if( sum + array[ i ] < array[ i ] )
            maxStartsAt = i;

        sum = std::max( array[ i ], sum + array[ i ] );

        if( maxSum < sum ) {
            maxSum = sum;
            maxStartEnd.first = maxStartsAt;
            maxStartEnd.second = i;
        }
    }

    int sum = 0;
    for( int i = maxStartEnd.first; i >= 0; --i ){
        sum += array[ i ];
        std::cout << array[ i ] << " ";
        if( sum == maxSum ) {
            break;
        }
    }


    return maxSum;
}


maxSum = 30, sum

10 20 -40 5 5  10 30 -60

maxAt = [ 10 20 -10 5 10 20 50 -10 ]
maxEndsAt = 6;

sum = 50
maxSum = 30



int main(int argc, char *argv[]) {

    return 0;
}