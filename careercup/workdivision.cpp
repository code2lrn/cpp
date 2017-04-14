//
// Created by Ranga on 3/19/17.
//

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <iterator>

void GetAssignments( std::vector< unsigned > taskCost, const unsigned numWorkers ) {
    std::sort( taskCost.begin(), taskCost.end() );
    using WorkerTasks = std::pair< unsigned, std::vector< unsigned > >;
    auto comparator = []( const WorkerTasks &l, const WorkerTasks &r ) { return l.first > r.first; };
    std::priority_queue< WorkerTasks, std::vector< WorkerTasks >, decltype( comparator ) > pq( comparator );
    for( unsigned i = 0; i < numWorkers; ++i ) {
        pq.push( std::make_pair( 0, std::vector< unsigned >{} ) );
    }

    for( auto it = taskCost.rbegin(); it != taskCost.rend(); ++it ) {
        auto worker = pq.top();
        pq.pop();
        worker.first += *it;
        worker.second.push_back( *it );
        pq.push( worker );
    }

    while( !pq.empty() ) {
        auto item = pq.top();
        pq.pop();

        std::cout << "Total Work - " << item.first << ": ";
        std::copy( item.second.begin(), item.second.end(), std::ostream_iterator< unsigned >( std::cout, ", " ) );
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[] ) {

    const std::vector< unsigned > taskCost{ 2,2,3,7,1 };
    const unsigned numWorkers = 2;
    GetAssignments( taskCost, numWorkers );
    return 0;
}