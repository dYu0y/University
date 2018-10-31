// insert內部的流程：

   // 如果mapSize==0, 則將mapSize設為8

   // 接下來判斷插入的位子(position.myOff)是否<=myOff+mySize/2
   // 是的話就是第一種情況(插入的位子在前半段)
   // 不然的話就是第二種狀況(插入的位子位子在後半段)

   // 對於第一種情況，如果以下條件成立了：
   // 如果begin的位子在四格小陣列的最前端( myOff % 4 == 0
   // 並且剩餘的空間小於等於四格( mapSize <= mySize / 4 + 1
   // 那就呼叫doubleMapSize()

   // 第二種情況則是：
   // 如果end的位子在四格小陣列的最前端( end().myOff % 4 -- 0
   // 並且剩餘的空間小於等於四格( mapSize <= mySize / 4 + 1
   // 那就呼叫doubleMapSize()

   // 這時看你先要
   // 1.把舊資料往前往後搬, 插入新元素, 並且將mySize+1
   // 或是
   // 2.先檢查myOff>=mapSize*4是否成立, 是的話將它設為除以mapSize*4的餘數
   // 都可以

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
   if( n == 0 )
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

template< typename T >
void deque< T >::insert( const iterator position, const T &val )
{
   // 等價於 map == nullptr 或是 mapSize == 0
	if (!map) {
		mapSize = 8;
		map = new T*[mapSize]();
	}

   // position是代表要插入哪裡的iterator
   // position.myOff儲存了時既要插入的絕對座標
   // 先算出相對要插入哪裡, 因為等等myOff可能會變動
	unsigned pos = position.myOff - myOff;
	if (position.myOff <= myOff + mySize / 2) {
		if (!(myOff % 4) && mapSize * 4 <= mySize + 4)
			doubleMapSize();

      // myOff往前移一格
      // 但是不能直接 --myOff
      // 不然如果 myOff == 0 的話會爆炸
		myOff = (myOff + mapSize * 4 - 1) % (mapSize * 4);

		if (!map[myOff / 4])
			map[myOff / 4] = new T[4];

		for (iterator it = begin(); it != begin() + pos; ++it)
			*it = *(it + 1);
	}
	else {
		if (!(end().myOff % 4) && mapSize * 4 <= mySize + 4)
			doubleMapSize();

		myOff %= mapSize * 4;

		if (!map[end().myOff % (mapSize * 4) / 4])
			map[end().myOff % (mapSize * 4) / 4] = new T[4];

		for (iterator it = end(); it != begin() + pos; it = it - 1)
			*it = *(it - 1);
	}

	*(begin() + pos) = val;
	++mySize;
}

template< typename T >
void deque< T >::erase( const iterator position )
{
   // erase也有分從前半或是後半
	if (position.myOff < myOff + mySize / 2) {
		for (iterator it = position; it != begin(); it = it - 1)
			*it = *(it - 1);
		++myOff;
	}
	else {
		for (iterator it = position; it != end() - 1; ++it)
			*it = *(it + 1);
	}
	if (!--mySize)
		myOff = 0;
}

// double the size of map array without changing myOff and mySize
template< typename T >
void deque< T >::doubleMapSize()
{
	unsigned int block = myOff % (mapSize * 4) / 4;
	T** newMap = new T*[mapSize * 2]();

	for (unsigned i = 0u; i < mapSize; ++i)
		newMap[myOff / 4 + i] = map[(block + i) % mapSize];
   //         ^~~~~~~~~~~~~ 為了維持myOff不變
   // 前變這裡不可以寫成 (myOff / 4 + i) % mapSize

	delete[] map;
	map = newMap;

	mapSize *= 2;
}

// determine if two deques are equal and return true, otherwise return false
template< typename T >
bool operator==( const deque< T > &lhs, const deque< T > &rhs )
{
	if (lhs.size() != rhs.size())
		return false;

	auto lhs_ = const_cast<deque<T>&>(lhs);
	auto rhs_ = const_cast<deque<T>&>(rhs);

	auto it1 = lhs_.begin(), it2 = rhs_.begin();
	for (; it1 != lhs_.end(); ++it1, ++it2) {
		if (*it1 != *it2)
			return false;
	}
	return true;
} // end function operator==

// inequality operator; returns opposite of == operator
template< typename T >
bool operator!=( const deque< T > &lhs, const deque< T > &rhs )
{
   return !( lhs == rhs ); // invokes operator==
}

#endif

