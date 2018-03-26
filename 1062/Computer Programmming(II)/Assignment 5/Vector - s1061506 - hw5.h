#define _SCL_SECURE_NO_WARNINGS
#ifndef VECTOR_H
#define VECTOR_H
// vector class template definition
template< typename T >
class vector
{
   template< typename T >
   friend bool operator==( const vector< T > &lhs, const vector< T > &rhs );

   template< typename T >
   friend bool operator!=( const vector< T > &lhs, const vector< T > &rhs );
public:
   using iterator = T*;

   vector( unsigned int n = 0 ); // Constructor; Constructs a zero vector with size n

   // Copy constructor; Constructs a vector with a copy of each of the elements in x.
   vector( const vector &x );

   ~vector(); // Destroys the vector.

   const vector& operator=( const vector &x ); // assignment operator

   iterator begin() const; // Returns a pointer pointing to the first element in the vector.
                           // If the vector is empty, the returned pointer shall not be dereferenced.

   // Returns an pointer pointing to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end() const;

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   unsigned int size() const;

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   unsigned int capacity() const;
   
   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const T val );

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back();

   // Resizes the vector so that it contains n elements.
   // If n is smaller than the current vector size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   // The new elements are initialized as 0.
   // If n is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( unsigned int n );

private:
   T *myFirst = nullptr;
   T *myLast = nullptr;
   T *myEnd = nullptr;
}; // end class template vector


// constructor; constructs a zero vector with size n
template< typename T >
vector< T >::vector( unsigned int n )
   : myFirst( n == 0 ? nullptr : new T[ n ]() ),
     myLast( n == 0 ? nullptr : myFirst + n ),
     myEnd( n == 0 ? nullptr : myLast )
{
} // end vector default constructor

// destructor; destroys the vector
template< typename T >
vector< T >::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
} // end destructor

template< typename T >
T* vector< T >::begin() const
{
   return myFirst;
}

template< typename T >
T* vector< T >::end() const
{
   return myLast;
}

template< typename T >
unsigned int vector< T >::size() const
{
   return ( myLast - myFirst );
}

template< typename T >
unsigned int vector< T >::capacity() const
{
   return ( myEnd - myFirst );
}

// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=( const vector< T > &lhs, const vector< T > &rhs )
{
   return !( lhs == rhs ); // invokes vector::operator==
}

// start here
#include <algorithm> // std::copy, std::swap, std::fill, std::equal

template< typename T >
vector<T>::vector( const vector<T> &x )
   : vector(x.size())
{
   (*this) = x;
}

template< typename T >
const vector<T>& vector<T>::operator=( const vector &x )
{
   resize(x.size());
   std::copy(x.begin(), x.end(), begin());
   return *this;
}

template< typename T >
void vector<T>::push_back( const T val )
{
   if(size() == capacity())
      resize(size() + 1);
   else
      ++myLast;
   end()[-1] = val;
}

template< typename T >
void vector<T>::pop_back()
{
   if(size())
      --myLast;
}

template< typename T >
void vector<T>::resize( unsigned int n )
{
   if(capacity() < n) {
      vector<T> tmp{ std::max(n, capacity() + capacity() / 2) };
      tmp = *this;
      std::swap(tmp.myFirst, myFirst);
      std::swap(tmp.myEnd, myEnd);
   }
   else if(size() < n)
      std::fill(end(), begin() + n, T());
   myLast = myFirst + n;
}

template< typename T >
bool operator==( const vector< T > &lhs, const vector< T > &rhs )
{
   return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

#endif