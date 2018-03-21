#include "Vector.h" // include definition of class vector

#define _SCL_SECURE_NO_WARNINGS // let me use std::copy without warning
#include <algorithm>// std::copy, std::max, std::fill
#include <utility>   // std::move

// constructor; constructs a zero vector with size n
vector::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new int[ n ]() ),
      myLast( n == 0 ? nullptr : myFirst + n ),
       myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

vector::vector( const vector &x )
   : vector()
{
   assign(x);
}

// destructor; destroys the vector
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

const vector &vector::assign( const vector &x )
{
   if(&x != this) {
      // reserve would be better
      resize(x.size());
      std::copy(x.myFirst, x.myLast, myFirst);
   }
   return *this;
}

int* vector::begin() const
{
   return myFirst;
}

int* vector::end() const
{
   return myLast;
}

unsigned int vector::size() const
{
   return ( myLast - myFirst );
}

unsigned int vector::capacity() const
{
   return ( myEnd - myFirst );
}

void vector::push_back( const int val )
{
   if (myLast == myEnd)
      resize(size() + 1);
   else
      ++myLast;
   myLast[-1] = val;
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
   {
      --myLast;
      *myLast = int();
   }
}

void vector::resize( unsigned int n )
{
   if (n > capacity()) {
      vector tmp{ std::move(*this) };
      this->vector::vector(std::max(tmp.capacity() + tmp.capacity() / 2, n));
      std::copy(tmp.myFirst, tmp.myLast, myFirst);
   }
   else if(n > size())
      std::fill(myLast, myFirst + n, int());
   myLast = myFirst + n;
}
