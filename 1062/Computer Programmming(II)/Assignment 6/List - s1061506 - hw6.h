#ifndef LIST_H
#define LIST_H

#include <list>

// ListNode class template definition
template< typename T >
struct ListNode
{
   ListNode *next;
   T myVal;
   ListNode *prev;
}; // end class template ListNode


// list class template definition
template< typename T >
class list
{
public:

   list(); // Constructs an empty list container, with no elements.
   list( unsigned int n ); // Constructs a list container with n elements.

   // Destroys all list elements,
   // and deallocates all the storage allocated by the list container.
   ~list();

   // Returns the number of elements in the list container.
   unsigned int size() const;

   // Inserts a new element at the beginning of the list container,
   // right before its current first element.
   // The content of val is copied (or moved) to the inserted element.
   // This effectively increases the container size by one.
   void push_front( const T val );

   // Adds a new element at the end of the list container,
   // after its current last element.
   // The content of val is copied to the new element.
   // This effectively increases the container size by one.
   void push_back( const T val );

   // Removes the last element in the list container,
   // effectively reducing the container size by one.
   void pop_back();

   // Resizes the list container so that it contains n elements.
   // If n is smaller than the current list container mySize,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current list container mySize,
   // the content is expanded by inserting at the end
   // as many elements as needed to reach a mySize of n.
   void resize( unsigned int n );

   // Removes all elements from the list container (which are destroyed).
   void clear();

   // determine if two lists are equal
   bool equal( std::list< T > &stdList );

private:
   unsigned int mySize = 0; // the number of elements in the list container

   // pointing to the past-the-end element in the list container
   ListNode< T > *myHead = nullptr;
}; // end class template list


// Constructs an empty list container, with no elements.
template< typename T >
list< T >::list()
{
   myHead = new ListNode< T >;
   myHead->myVal = T();
   myHead->prev = myHead->next = myHead;
}

// Constructs a list container with n elements.
template< typename T >
list< T >::list( unsigned int n )
{
   myHead = new ListNode< T >;
   myHead->myVal = T();
   myHead->prev = myHead->next = myHead;

   for( unsigned int i = 0; i < n; i++ )
      push_back( T() );
}

// Destroys all list elements, and deallocates all the storage allocated by the list container.
template< typename T >
list< T >::~list()
{
   clear();
   delete myHead;
}

template< typename T >
unsigned int list< T >::size() const
{
   return mySize;
}

template< typename T >
void list< T >::push_front( const T val )
{
   push_back(T());
   myHead->myVal = val;
   myHead = myHead->prev;
}

template< typename T >
void list< T >::push_back( const T val )
{
   auto tmp = new ListNode< T >{ myHead, val, myHead->prev };
   myHead->prev->next = tmp;
   myHead->prev = tmp;
   ++mySize;
}

template< typename T >
void list< T >::pop_back()
{
   if(mySize) {
      --mySize;
      auto tmp = myHead->prev;
      myHead->prev->prev->next = myHead;
      myHead->prev = myHead->prev->prev;
      tmp->prev = tmp->next = nullptr;
      delete tmp;
   }
}

template< typename T >
void list< T >::resize( unsigned int n )
{
   if( n > mySize )
   {
      unsigned int difference = n - mySize;
      for( unsigned int i = 0; i < difference; i++ ) // create n - mySize elements
         push_back( T() );
   }
   else if( n < mySize )
   {
      unsigned int difference = mySize - n;
      for( unsigned int i = 0; i < difference; i++ ) // erase mySize - n elements
         pop_back();
   }
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void list< T >::clear()
{
   while( mySize > 0 )
      pop_back();
}

// determine if two lists are equal
template< typename T >
bool list< T >::equal( std::list< T > &stdList )
{
   if( mySize != stdList.size() ) // different number of elements
      return false;

   ListNode< T > *ptr = myHead->next;
   std::list< T >::iterator it = stdList.begin();
   for( ; ptr != myHead && it != stdList.end(); ptr = ptr->next, ++it )
      if( ptr->myVal != *it )
         return false;

   return true;
}

#endif