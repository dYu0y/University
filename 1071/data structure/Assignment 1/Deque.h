#ifndef DEQUE_H
#define DEQUE_H

// DequeIterator class template definition
template< typename T >
class DequeIterator
{
   template< typename T > friend class deque;
public:
   DequeIterator() // default constructor
   {
   }

   DequeIterator( deque< T > *container, unsigned int offset )
      : myCont( container ),
        myOff( offset )
   {
   }

   DequeIterator( const DequeIterator &iteratorToCopy ) // copy constructor
      : myCont( iteratorToCopy.myCont ),
        myOff( iteratorToCopy.myOff )
   {
   }

   ~DequeIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeIterator &operator=( const DequeIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   T& operator*() const // dereferencing operator
   {
      unsigned int block = ( myOff % ( 4 * myCont->mapSize ) ) / 4;
      unsigned int off = myOff % 4;
      return ( myCont->map )[ block ][ off ];
   }

   DequeIterator& operator++() // prefix increment operator
   {
      ++myOff;
      return *this;
   }

   bool operator==( const DequeIterator &right ) const // equal to
   {
      return ( myCont == right.myCont ) && ( myOff == right.myOff );
   }

   bool operator!=( const DequeIterator &right ) const // not equal to
   {
      return ( myCont != right.myCont ) || ( myOff != right.myOff );
   }

   bool operator<( const DequeIterator &right ) const // less than equal to
   {
      return ( myCont == right.myCont ) && ( myOff < right.myOff );
   }

   bool operator<=( const DequeIterator &right ) const // less than equal to
   {
      return ( myCont == right.myCont ) && ( myOff <= right.myOff );
   }

   DequeIterator operator+( unsigned int i ) const
   {
      return DequeIterator( myCont, myOff + i );
   }

   DequeIterator operator-( unsigned int i ) const
   {
      return DequeIterator( myCont, myOff - i );
   }

private:
   deque< T > *myCont = nullptr; // keep a pointer to deque
   unsigned int myOff = 0;       // offset of element in deque
}; // end class template DequeIterator


// deque class template definition
template< typename T >
class deque
{
   template< typename T > friend class DequeIterator;

   template< typename T >
   friend bool operator==( const deque< T > &lhs, const deque< T > &rhs );

   template< typename T >
   friend bool operator!=( const deque< T > &lhs, const deque< T > &rhs );

public:
   using iterator = DequeIterator< T >;

   deque(); // Constructs an empty deque container, with no elements.

   // Constructs a deque container with n elements. Each element is a copy of val.
   deque( unsigned int n, const T &val );

   ~deque(); // Destroys the deque container.

   // Returns an iterator pointing to the first element in the deque container.
   // If the deque is empty, the returned iterator shall not be dereferenced.
   iterator begin();

   // Returns an iterator referring to the past-the-end element in the deque container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the deque container.
   // It does not point to any element, and thus shall not be dereferenced.
   iterator end();

   // Returns the number of elements in the deque container.
   unsigned int size() const;

   // The deque container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the container size by one.
   void insert( const iterator position, const T &val );

   // Removes from the deque container a single element at the specified position.
   // This effectively reduces the container size by one.
   void erase( const iterator position );

private:
   T **map = nullptr;         // pointer to array of pointers to blocks
   unsigned int mapSize = 0;  // size of map array, zero or 2^N
   unsigned int myOff = 0;    // offset of initial element
   unsigned int mySize = 0;   // current length of sequence, in [ 0 .. 4 * mapSize )

   void doubleMapSize();      // double the size of map array without changing myOff and mySize
}; // end class template deque


// Constructs an empty deque container, with no elements.
template< typename T >
deque< T >::deque()
   :     map( nullptr ),
     mapSize( 0 ),
       myOff( 0 ),
      mySize( 0 )
{
} // end deque default constructor

// Constructs a deque container with n elements. Each element is a copy of val.
template< typename T >
deque< T >::deque( unsigned int n, const T &val )
   : myOff( 0 ),
    mySize( n )
{
   if( !n )
   {
      map = nullptr;
      mapSize = 0;
   }
   else
   {
      mapSize = 8;
      while( n > 4 * ( mapSize - 1 ) )
         mapSize *= 2;

      map = new T*[ mapSize ]();
      for( unsigned int i = 0; i <= ( n - 1 ) / 4; i++ )
         map[ i ] = new T[ 4 ];

      for( unsigned int i = 0; i < n; i++ )
         map[ i / 4 ][ i % 4 ] = val;
   }
} // end deque constructor

// destroys the deque container
template< typename T >
deque< T >::~deque()
{
   if( mapSize > 0 )
   {
      for( unsigned int i = 0; i < mapSize; i++ )
         if( map[ i ] != nullptr )
            delete [] map[ i ];
      delete[] map;
   }
} // end destructor

template< typename T >
typename deque< T >::iterator deque< T >::begin()
{
   return iterator( this, myOff );
}

template< typename T >
typename deque< T >::iterator deque< T >::end()
{
   return iterator( this, myOff + mySize );
}

template< typename T >
unsigned int deque< T >::size() const
{
   return mySize;
}





static constexpr auto dqSize_ = 4u;

template< typename T >
void deque< T >::insert( const iterator position, const T &val )
{
   if( !map ) {
      mapSize = 8;
      map = new T*[ mapSize ]{};
   }

   iterator first_, last_;
   iterator ( *next )( iterator );

   auto pos = position.myOff - myOff;
   if( position.myOff <= myOff + mySize / 2 ) {
      if( begin().myOff % dqSize_ == 0 && mapSize <= mySize / dqSize_ + 1 )
         doubleMapSize();

      myOff = ( myOff + mapSize * dqSize_ - 1 ) % ( mapSize * dqSize_ );
      
      first_ = begin();
      next = []( iterator it ) -> iterator { return ++it; };
   }
   else {
      if( end().myOff % dqSize_ == 0 && mapSize <= mySize / dqSize_ + 1 )
         doubleMapSize();

      myOff %= mapSize * dqSize_;

      first_ = end();
      next = []( iterator it ) -> iterator { return it - 1; };
   }
   last_ = begin() + pos;

   
   if( !map[ first_.myOff % ( mapSize * dqSize_ ) / dqSize_ ] )
      map[ first_.myOff % ( mapSize * dqSize_ ) / dqSize_ ] = new T[ dqSize_ ];

   while( first_ != last_ ) {
      *first_ = *next( first_ );
      first_ = next( first_ );
   }
   
   ++mySize;

   *last_ = val;
}

template< typename T >
void deque< T >::erase( const iterator position )
{
   auto first_ = position;
   auto last_ = end() - 1;
   iterator ( *next )( iterator ) = []( iterator it ) -> iterator { return ++it; };
   
   if( position.myOff < myOff + mySize / 2 ) {
      last_ = begin();
      next = []( iterator it ) -> iterator { return it - 1; };
      
      ++myOff;
   }

   while( first_ != last_ ) {
      *first_ = *next( first_ );
      first_ = next( first_ );
   }

   if(!--mySize)
      myOff = 0;
}

// double the size of map array without changing myOff and mySize
template< typename T >
void deque< T >::doubleMapSize()
{
   auto block = myOff % ( mapSize * dqSize_ ) / dqSize_;
   auto newMap = new T*[ mapSize * 2 ]{};

   for( auto i = 0u; i < mapSize; ++i )
      newMap[ myOff / dqSize_ + i ] = map[ ( block + i ) % mapSize ];

   delete[] map;

   map = newMap;
   mapSize *= 2;
}

// determine if two deques are equal and return true, otherwise return false
template< typename T >
bool operator==( const deque< T > &lhs, const deque< T > &rhs )
{
   auto& l = const_cast<deque<T>&>(lhs); // not good
   auto& r = const_cast<deque<T>&>(rhs); // but there is no const_iterator, cbegin(), and cend()

   if( l.size() == r.size() ) {
      auto it = r.begin();

      for( auto const& i : l )
         if( i != *it )
            return false;
         else
            ++it;

      return true;
   }

   return false;
} // end function operator==





// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=( const deque< T > &lhs, const deque< T > &rhs )
{
   return !( lhs == rhs ); // invokes operator==
}

#endif

