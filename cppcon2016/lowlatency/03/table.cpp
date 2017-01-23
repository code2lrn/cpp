//
// Created by Ranga on 9/18/16.
//

#include <iostream>
#include <memory>

using namespace std;

template< typename T >
class Table {
public:
    using value_type = T;
    using size_type  = std::size_t;

private:
    value_type *elems;
    size_type  nelems, cap;

public:
    size_type size() const noexcept { return nelems; }
    size_type capacity() const noexcept { return cap; }
    bool empty() const noexcept { return nelems == 0; }

private:
    bool full() const noexcept { return size() == capacity(); }
    void swap( const Table &t ) noexcept {
        std::swap( this->elems, t.elems );
        std::swap( this->nelems, t.nelems );
        std::swap( this->cap, t.cap );
    }
    void grow() {
        size_type newCap = capacity() * 1.5;
        unique_ptr< value_type[] > newElems{ new value_type[ newCap ] };
        auto pp = newElems.get();
        for( auto q = begin(); q != end(); ++q ) {
            *pp++ = move_if_noexcept( *q );
        }
        cap = newCap;
        delete[] elems;
        elems = newElems.release();
    }

public:
    using iterator = value_type *;
    using const_iterator = const value_type *;
    iterator begin() noexcept { return elems; }
    const_iterator begin() const noexcept { return elems; }
    iterator end() noexcept { return begin() + size(); }
    const_iterator end() const noexcept { return begin() + size(); }

    Table() = default;
    Table( size_type n, const value_type &init ) : elems{ new value_type[ n ] }, nelems{ n }, cap{ n } {
        try{
            fill( begin(), end (), init );
        }
        catch( ... ) {
            delete[] elems;
            throw;
        }
    }

    Table( const Table &t ) : elems{ new value_type[ t.size() ] }, nelems{ t.size() }, cap{ t.size() } {
        try {
            copy( t.begin(), t.end(), begin() );
        }
        catch( ... ) {
            delete[] elems;
            throw;
        }
    }

    ~Table() {
        delete[] elems;
    }

    Table& operator =( const Table &t ) {
        if( this == &t )
            return *this;
        Table{ t }.swap( *this );
        return *this;
    }

    Table( Table &&t ) noexcept : elems{ t.elems }, nelems{ t.nelems }, cap{ t.cap } {
        t.elems = nullptr;
        t.nelems = t.cap = 0;
    }

    value_type& operator[]( size_type n ) noexcept {
        return elems[ n ];
    }

    const value_type& operator[]( size_type n ) const noexcept {
        return elems[ n ];
    }

    void push_back( const value_type &v ) {
        if( full() )
            grow();

        elems[ size() ] = v;
        ++nelems;
    }

    template < typename ... Args >
    void emplace_back( Args &&... args ) {
        if( full() )
            grow();

        elems[ size() ] = value_type{ std::forward<Args>( args )... };
        ++nelems;
    }
};

int main() {

    return 0;
}
