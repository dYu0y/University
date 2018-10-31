#ifndef UNORDERED_SET
#define UNORDERED_SET

unsigned int maxValue = 99;

// unordered_set class template definition
template< typename T >
class unordered_set
{
public:
   using iterator = typename list< T >::iterator;

   unordered_set();

   ~unordered_set();

   // Returns the number of elements in the unordered_set container.
   unsigned int size() const;

   // Searches the container for an element with k as value and
   // returns an iterator to it if found,
   // otherwise it returns an iterator to unordered_set::end
   // (the element past the end of the container).
   iterator find( const T &k );

   // Inserts a new element in the unordered_set.
   // The element is inserted only if it is not equivalent to any other element
   // already in the container ( elements in an unordered_set have unique values ).
   // This effectively increases the container size by one.
   void insert( const T &val );

   // Removes from the unordered_set container a single element.
   // This effectively reduces the container size by one.
   void erase( const T &k );

   // Returns the number of buckets in the unordered_set container.
   unsigned int bucket_count() const;

   // Returns the number of elements in bucket n.
   unsigned int bucket_size( unsigned int n ) const;

   // Returns the bucket number where the element with value k is located.
   unsigned int bucket( const T &k ) const;

   // Returns true iff the current object is equal to data
   bool operator==( std::unordered_set< T > &data );

//   void verify( std::unordered_set< T > &data );

private:
   list< T > myList;	   // list of elements, must initialize before myVec

   vector< iterator > myVec;  // vector of list iterators, begin() then end() - 1

   unsigned int maxidx = 8; // current maximum key value

   // put a new element in the unordered_set when myVec is large enough
   void putIn( const T& val );

   // Computes hash value which will be used to compute bucket number
   unsigned int hashSeq( const unsigned int &key, unsigned int count ) const;
}; // end class template unordered_set


template< typename T >
unordered_set< T >::unordered_set()
{
   myVec.reserve( 16 );
   myVec.assign( 16, myList.end() );
}

template< typename T >
unordered_set< T >::~unordered_set()
{
   myList.clear();
   myVec.clear();
}

template< typename T >
unsigned int unordered_set< T >::size() const
{
   return myList.size();
}

template< typename T >
typename unordered_set< T >::iterator unordered_set< T >::find( const T &k )
{
	auto buck_num_ = bucket(k) * 2;
	auto it = myVec[buck_num_];
	auto end_ = myVec[buck_num_ + 1];
	if (it != myList.end()) {
		do
			if (*it == k)
				return it;
		while (it++ != end_);
	}
	return myList.end();
}

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

template< typename T >
void unordered_set< T >::insert( const T& val )
{
	if (bucket_count() == size()) {
		if (size() < 512)
			maxidx *= 8;
		else
			maxidx *= 2;
		myVec.assign(bucket_count() * 2, myList.end());
		list<T> newList;
		newList.splice(newList.begin(), myList);

		putIn(val);
		for (auto e : newList)
			putIn(e);
	}
	else
		putIn(val);
}

template< typename T >
void unordered_set< T >::erase( const T &k )
{
	auto it = find(k);
	if (it == myList.end())
		return;
	auto& buck_first = myVec[bucket(k) * 2];
	auto& buck_last = myVec[bucket(k) * 2 + 1];
	if (buck_first == buck_last)
		buck_first = buck_last = myList.end();
	else if (it == buck_first)
		--buck_first;
	else if (it == buck_last)
		++buck_last;
	myList.erase(it);
}

template< typename T >
unsigned int unordered_set< T >::bucket_count() const
{
   return maxidx;
}

template< typename T >
unsigned int unordered_set< T >::bucket_size( unsigned int n ) const
{	// return size of bucket n
	auto size_ = 0u;
	if (myVec[n * 2] != myList.end()) {
		auto it = myVec[n * 2];
		auto end_ = myVec[n * 2 + 1];
		do {
			++size_;
		} while (it++ != end_);
	}

	return size_;
}

template< typename T >
unsigned int unordered_set< T >::bucket( const T &k ) const
{
   unsigned int hashValue = hashSeq( k, sizeof( T ) );
   return hashValue % maxidx; // bucket number
}

template< typename T >
void unordered_set< T >::putIn( const T& val )
{
	auto buck_num_ = bucket(val) * 2;
	myList.insert(myVec[buck_num_], val);
	--myVec[buck_num_];
	if (myVec[buck_num_ + 1] == myList.end())
		--myVec[buck_num_ + 1];
}

template< typename T >
unsigned int unordered_set< T >::hashSeq( const unsigned int &key, unsigned int count ) const
{
   const unsigned int _FNV_offset_basis = 2166136261U; // 10000001 00011100 10011101 11000101
   const unsigned int _FNV_prime = 16777619U;          // 00000001 00000000 00000001 10010011
   const unsigned char *first = reinterpret_cast< const unsigned char * >( &key );
   unsigned int val = _FNV_offset_basis;
   for( unsigned int next = 0; next < count; ++next )
   {	// fold in another byte
      val ^= static_cast< unsigned int >( first[ next ] );
      val *= _FNV_prime;
   }

   return val;
}

template< typename T >
bool unordered_set< T >::operator==( std::unordered_set< T > &data )
{
   if( myList.size() != data.size() )
      return false;

   unsigned int *firstVec = *( reinterpret_cast< unsigned int ** >( &data ) + 5 );
   vector< list< T >::iterator >::iterator it = myVec.begin();
   for( unsigned int bucketNo = 0; it != myVec.end(); ++it, bucketNo++ )
   {
      if( data.bucket_size( bucketNo ) != bucket_size( bucketNo ) )
         return false;

      unsigned int *stlBucketFirst = *( reinterpret_cast< unsigned int ** >( &firstVec[ 2 * bucketNo ] ) );
      unsigned int *stlBucketLast = *( reinterpret_cast< unsigned int ** >( &firstVec[ 2 * bucketNo + 1 ] ) );

      list< T >::iterator myBucketFirst = *it;
      ++it;
      list< T >::iterator myBucketLast = *it;
      if( myBucketFirst != myList.end() )
      {
         if( myBucketFirst == myBucketLast )
         {
            if( *myBucketFirst != *( stlBucketFirst + 2 ) )
               return false;
         }
         else
         {
            unsigned int *stlPtr = stlBucketFirst;
            list< T >::iterator myIt = myBucketFirst;
            while( myIt != myBucketLast )
            {
               if( *myIt != *( stlPtr + 2 ) )
                  return false;
               stlPtr = *( reinterpret_cast< unsigned int ** >( stlPtr ) );
               ++myIt;
            }

            if( *myBucketLast != *( stlBucketLast + 2 ) )
               return false;
         }
      }
   }

   for( unsigned int key = 1; key <= maxValue; key++ )
      if( data.bucket( key ) != bucket( key ) )
         return false;

   return true;
}

#endif
