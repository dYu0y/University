// HugeInteger class definition.
#define _SCL_SECURE_NO_WARNINGS
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include "Vector - s1061506 - hw5.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, const HugeInteger<T> &hugeInteger );
public:
   HugeInteger(); // default constructor; construct a HugeInteger with size 0

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( const HugeInteger &op2 ) const;

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( const HugeInteger &op2 ) const;

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( const  HugeInteger &op2 ) const;

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( const HugeInteger &op2 ) const;

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( const HugeInteger &op2 ) const;
     
   HugeInteger& operator++(); // prefix increment operator
     
   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   void convert( vector<T> v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   vector<T> integer;

   HugeInteger( unsigned int n ); // constructor; construct a zero HugeInteger with size n
   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger<T>::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger<T>::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger<T>::HugeInteger( const HugeInteger<T> &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger<T>::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger<T>& HugeInteger<T>::operator=( const HugeInteger<T> &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger<T>::operator==( const HugeInteger<T> &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger<T> is less than or equal to another
template< typename T >
bool HugeInteger<T>::operator<=( const HugeInteger<T> &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger<T> + HugeInteger<T>
template< typename T >
HugeInteger<T> HugeInteger<T>::operator+( const HugeInteger<T> &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector<T>::iterator it1 = integer.begin();
   vector<T>::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector<T>::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// modulus operator; HugeInteger<T> % HugeInteger<T> provided that the divisor is not equal to 0
template< typename T >
HugeInteger<T> HugeInteger<T>::operator%( const HugeInteger<T> &op2 ) const
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger remainder = ( *this ) - ( quotient * op2 );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger<T>::convert( vector<T> v )
{
   integer.resize( v.size() );
   typename vector<T>::iterator it1 = integer.end() - 1;
   typename vector<T>::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger<T>::isZero() const
{
   typename vector<T>::iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger<T>::divideByTen()
{
   typename vector<T>::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger<T>::helpIncrement()
{
   typename vector<T>::iterator it = integer.begin();
   ( *it )++;
   typename vector<T>::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, const HugeInteger<T> &hugeInteger )
{
   auto it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

// start here

template< typename T >
bool HugeInteger<T>::operator<( const HugeInteger<T> &right ) const
{
   if(integer.size() != right.integer.size())
      return integer.size() < right.integer.size();
   else {
      auto it1 = integer.end(), it2 = right.integer.end();
      for(; it1 != integer.begin(); --it1, --it2)
         if(it1[-1] != it2[-1])
            return it1[-1] < it2[-1];
   }
   return false;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::operator-( const HugeInteger<T> &op2 ) const
{
   auto subtrahend{op2};
   auto difference{*this};
   auto it1 = difference.integer.begin(), it2 = op2.integer.begin();
   for(auto i = 0u; i < op2.integer.size(); ++i)
      it1[i] -= it2[i];
   for(auto& i : difference.integer) // difference.integer.end()[-1] >= 0
      if(i>>((sizeof(i)<<3)-1)) {
         i += 10;
         --(&i)[1];
      }
   while(difference.integer.size() > 1 && !difference.integer.end()[-1])
      difference.integer.pop_back();
   return difference;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::operator*( const HugeInteger<T> &op2 ) const
{
   if(isZero() || op2.isZero())
      return HugeInteger<T>{};
   auto size1 = integer.size();
   auto size2 = op2.integer.size();
   auto size3 = size1 + size2;
   HugeInteger<T> product{size3};
   for(auto i = 0u; i < size1; ++i)
      for (auto j = 0u; j < size2; ++j)
         product.integer.begin()[i + j] += integer.begin()[i] * op2.integer.begin()[j];
   for(auto& i : product.integer)
      if(i > 9) {
         (&i)[1] += i / 10;
         i %= 10;
      }
   if(!product.integer.end()[-1])
      product.integer.pop_back();
   return product;
}
#include <algorithm> // std::reverse

template< typename T >
HugeInteger<T> HugeInteger<T>::operator/( const HugeInteger<T> &op2 ) const
{
   if(*this < op2)
      return HugeInteger<T>{};
   auto dividend{*this};
   HugeInteger<T> divisor{this->integer.size()};
   std::copy(op2.integer.begin(), op2.integer.end(), divisor.integer.end()-op2.integer.size());
   HugeInteger<T> quotient{this->integer.size()};
   quotient.integer.resize(0);

   while(op2 <= divisor) {
      quotient.integer.push_back(T());
      while(divisor <= dividend) {
         dividend = dividend - divisor;
         ++quotient.integer.end()[-1];
      }
      divisor.divideByTen();
   }
   std::reverse(quotient.integer.begin(), quotient.integer.end());
   while(quotient.integer.size() > 1 && !quotient.integer.end()[-1])
      quotient.integer.pop_back();
   return quotient;
}

template< typename T >
HugeInteger<T>& HugeInteger<T>::operator++()
{
   helpIncrement();
   return *this;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::operator++( int )
{
   auto tmp{*this};
   ++*this;
   return tmp;
}

template< typename T >
HugeInteger<T>& HugeInteger<T>::operator--()
{
   helpDecrement();
   return *this;
}

template< typename T >
HugeInteger<T> HugeInteger<T>::operator--( int )
{
   auto tmp{*this};
   --*this;
   return tmp;
}

template< typename T >
void HugeInteger<T>::helpDecrement()
{
   auto it = integer.begin();
   --( *it );
   auto it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it>>((sizeof(*it)<<3)-1) )
      {
         *it += 10;
         --*it2;
      }

   if( *it == 0 )
      integer.resize( integer.size() - 1 );
}

#endif