// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "List - 1061506 - hw8.h" // include definition of class template list

// #include <list> // include definition of class template list
// using std::list;

template< typename T >
class HugeInteger : public list< T >
{
   template< typename T >
   friend ostream &operator<<( ostream &output, HugeInteger< T > const &hugeInteger );
public:
   using iterator = typename list<T>::iterator;
   using reverse_iterator = typename list<T>::reverse_iterator;

   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with mySize n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator
   const HugeInteger &operator=( const list<T> &right ); // assignment operator

   bool operator< ( HugeInteger const&right ) const;  // less than

   bool operator<=( HugeInteger const&right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger const& op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger const& op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger const& op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger const& op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger const& op2 ) const;

   HugeInteger &operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger &operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   bool isZero() const; // return true if and only if all digits are zero

private:

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : list<T>( ( n > 0 ) ? n : 1 )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : list<T>( integerToCopy )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      list< T >::operator=( right );

   return *this; // enables x = y = z, for example
} // end function operator=

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const list< T > &right )
{
   if( &right != this ) // avoid self-assignment
      list< T >::operator=( right );

   return *this; // enables x = y = z, for example
} // end function operator=

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger< T > const &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > const& op2 ) const
{
   unsigned int op1Size = this->size();
   unsigned int op2Size = op2.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );
   iterator it1 = this->begin();
   iterator it3 = sum.begin();
   for( ; it1 != this->end(); ++it1, ++it3 )
      *it3 = *it1;

   iterator it2 = op2.begin();
   it3 = sum.begin();
   for( ; it2 != op2.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.begin();
   iterator it4 = it3;
   for( ++it4; it4 != sum.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.pop_back();

   return sum;
} // end function operator+

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > const& op2 ) const
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger< T > temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   for(iterator it = this->begin(); it != this->end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   iterator it1 = this->begin();
   iterator it2 = it1;
   for( ++it2; it2 != this->end(); ++it1, ++it2 )
      *it1 = *it2;
   this->pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   iterator it = this->begin();
   ( *it )++;
   iterator it2 = it;
   for( ++it2; it2 != this->end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *it = 0;
      this->resize( this->size() + 1 );
      it = this->end();
      --it;
      *it = 1;
   }
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<( ostream &output, HugeInteger< T > const& hugeInteger )
{
   typename list< T >::reverse_iterator it = hugeInteger.rbegin();
   for( ; it != hugeInteger.rend(); ++it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}


// start from here


template<typename T>
bool HugeInteger<T>::operator<( HugeInteger const& right ) const
{
   if (this->size() != right.size())
      return this->size() < right.size();
   for (auto it1 = this->rbegin(), it2 = right.rbegin(); it1 != this->rend(); ++it1, ++it2)
      if (*it1 != *it2)
         return *it1 < *it2;
   return false;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator-( HugeInteger const& op2 ) const
{
   auto difference = HugeInteger<T>{ *this };
   auto it = difference.begin();
   auto it2 = op2.begin();
   for (; it2 != op2.end(); ++it, ++it2) {
      if (*it < *it2) {
         *it += 10;
         auto tmp = it;
         while (!*++tmp)
            *tmp = 9;
         --*tmp;
      }
      *it -= *it2;
   }
   while (difference.size() > 1 && !*difference.rbegin())
      difference.pop_back();
   return difference;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator*( HugeInteger const& op2 ) const
{
   if (isZero() || op2.isZero())
      return HugeInteger<T>{};

   HugeInteger<T> product{ this->size() + op2.size() };

   auto it1 = this->begin();
   for (auto it0 = product.begin(); it1 != this->end(); ++it1, ++it0)
      for (auto it = it0, it2 = op2.begin(); it2 != op2.end(); ++it, ++it2)
         *it += *it1 * *it2;

   auto carry = 0;
   for (auto& i : product) {
      i += carry;
      carry = i / 10;
      i %= 10;
   }

   if (!*product.rbegin())
      product.pop_back();

   return product;
}

template<typename T>
HugeInteger<T> HugeInteger<T>::operator/( HugeInteger const& op2 ) const
{
   if (*this < op2)
      return HugeInteger<T>{};
   auto dividend = HugeInteger<T>{ *this };
   auto divisor = HugeInteger<T>{ this->size() };
   auto it = divisor.rbegin();
   auto it2 = op2.rbegin();
   for (; it2 != op2.rend(); ++it, ++it2)
      *it = *it2;
   
   auto quotient = HugeInteger<T>{};

   while (!(divisor < op2)) {
      quotient.push_front(0);
      while (!(dividend < divisor)) { 
         dividend = dividend - divisor;
         ++*quotient.begin();
      }
      divisor.divideByTen();
   }
   
   while (quotient.size() > 1 && !*quotient.rbegin())
      quotient.pop_back();
   return quotient;
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   iterator it = this->begin();
   while(!*it)
      *it = 9, ++it;
   --*it;
}
