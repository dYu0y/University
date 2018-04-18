// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector - 1061506 - hw7.h" // include definition of class template vector
#include "List - 1061506 - hw7.h" // include definition of class template list

/*
#include <vector> // include definition of class template vector
#include <list> // include definition of class template list
using std::vector;
using std::list;
*/

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger );
public:
   // constructor; construct a zero HugeInteger with mySize n
   HugeInteger( unsigned int n = 0 );

   // copy constructor; constructs a HugeInteger with a copy
   // of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger &operator=( const HugeInteger &right ); // assignment operator

   bool operator==( HugeInteger const &right ) const; // less than or equal to
   bool operator<( HugeInteger const &right ) const;  // less than
   bool operator<=( HugeInteger const &right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger const &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger const &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger const &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger const &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger const &op2 ) const;

   HugeInteger &operator++();     // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger &operator--();     // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   // convert a vector of decimal digits into a HugeInteger
   void convert( T const &buffer );
   bool isZero() const; // return true if and only if all digits are zero

private:
   T integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy
// of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
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
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( HugeInteger< T > const &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( HugeInteger< T > const &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > const &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger< T > sum( sumSize );
   typename T::iterator it1 = integer.begin();
   typename T::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename T::iterator it2 = op2.integer.begin();
   it3 = sum.integer.begin();
   for( ; it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.integer.begin();
   typename T::iterator it4 = it3;
   for( ++it4; it4 != sum.integer.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that
// the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > const &op2 ) const
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( T const &buffer )
{
   integer.resize( buffer.size() );
   typename T::reverse_iterator it1 = integer.rbegin();
   typename T::iterator it2 = buffer.begin();
   for( ; it2 != buffer.end(); ++it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   for( T::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != 0 )
         return false;

   return true;
}

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename T::iterator it1 = integer.begin();
   typename T::iterator it2 = it1;
   for( ++it2; it2 != integer.end(); ++it1, ++it2 )
      *it1 = *it2;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename T::iterator it = integer.begin();
   ( *it )++;
   typename T::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *it = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > const &hugeInteger )
{
   typename T::reverse_iterator it = hugeInteger.integer.rbegin();
   for( ; it != hugeInteger.integer.rend(); ++it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}


// start here


// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( HugeInteger< T > const &right ) const
{
   if (integer.size() != right.integer.size())
      return integer.size() < right.integer.size();
   for (auto it1 = integer.rbegin(), it2 = right.integer.rbegin(); it1 != integer.rend(); ++it1, ++it2)
      if (*it1 != *it2)
         return *it1 < *it2;
   return false;
} // end function operator<

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > const &op2 ) const
{
   auto difference = HugeInteger<T>{ *this };
   for (auto it = difference.integer.begin(), it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it, ++it2) {
      if (*it < *it2) {
         auto tmp = it;
         while (!*++tmp);
         while (tmp != it) {
            --*tmp;
            *--tmp += 10;
         }
      }
      *it -= *it2;
   }
   while (difference.integer.size() > 1 && !*difference.integer.rbegin())
      difference.integer.pop_back();
   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > const &op2 ) const
{
   if (isZero() || op2.isZero())
      return HugeInteger<T>{};
   auto const* fwInt = &integer;
   auto const* bwInt = &op2.integer;
   HugeInteger<T> product{ fwInt->size() + bwInt->size() };

   auto fwIt = fwInt->begin(); // foward_iterator
   auto bwIt = bwInt->begin(); // backward_iterator
   auto carry = 0;
   for (auto it = product.integer.begin(); it != product.integer.end(); ++it) {
      for (; fwIt != fwInt->end(); ++fwIt, --bwIt) {
         *it += *fwIt * *bwIt;

         if (fwIt == --fwInt->end()) {
            std::swap(fwIt, ++bwIt);
            break;
         }
         else if (bwIt == bwInt->begin()) {
            std::swap(++fwIt, bwIt);
            break;
         }
      }
      std::swap(fwInt, bwInt);
      *it += carry;
      carry = *it / 10;
      *it %= 10;
   }

   if (!*product.integer.rbegin())
      product.integer.pop_back();

   return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that
// the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > const &op2 ) const
{
   if(*this < op2)
      return HugeInteger<T>{};
   auto dividend = HugeInteger<T>{ *this };
   auto divisor = HugeInteger<T>{ integer.size() };
   for (auto it = divisor.integer.rbegin(), it2 = op2.integer.rbegin(); it2 != op2.integer.rend(); ++it, ++it2)
      *it = *it2;
   
   auto quotient = HugeInteger<T>{};
   T tmp;

   while (!(divisor < op2)) {
      tmp.push_back(0);
      while (!(dividend < divisor)) { 
         dividend = dividend - divisor;
         ++*tmp.rbegin();
      }
      divisor.divideByTen();
   }
   quotient.convert(tmp);
   while (quotient.integer.size() > 1 && !*quotient.integer.rbegin())
      quotient.integer.pop_back();
   return quotient;
   /* too slow
   if (*this < op2)
      return HugeInteger<T>{};
   auto quotient = HugeInteger<T>{ integer.size() - op2.integer.size() + 1 };
   for (auto it = quotient.integer.rbegin(); it != quotient.integer.rend(); --*it, ++it)
      while (!(*this < op2 * quotient))
         ++*it;
   if (quotient.integer.size() > 1 && !*quotient.integer.rbegin())
      quotient.integer.pop_back();
   return quotient;
   */
} // end function operator/

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
   helpIncrement();
   return *this;
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   auto tmp = HugeInteger<T>{ *this };
   ++*this;
   return tmp;
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T > &HugeInteger< T >::operator--()
{
   helpDecrement();
   return *this;
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   auto tmp = HugeInteger<T>{ *this };
   --*this;
   return tmp;
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   auto it = integer.begin();
   while (!*it)
      ++it;
   while (it != integer.begin()) {
      --*it;
      *--it += 10;
   }
   --*it;
   if (integer.size() > 1 && !*integer.rbegin())
      integer.pop_back();
}