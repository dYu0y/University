// Member-function definitions for class HugeInteger
#define _SCL_SECURE_NO_WARNINGS // let me use std::equal without warning

#include <iostream>
#include <algorithm> // std::copy, std::equal, std::for_each, std::reverse
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( const HugeInteger &op2 ) const
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function add

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( const HugeInteger &op2 ) const
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// convert a vector of decimal digits into a HugeInteger
void HugeInteger::convert( vector v )
{
   integer.resize( v.size() );
   vector::iterator it1 = integer.end() - 1;
   vector::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output



bool HugeInteger::equal( const HugeInteger &right ) const
{
   if (integer.size() == right.integer.size())
      return std::equal(integer.begin(), integer.end(), right.integer.begin());

   return false;
}

bool HugeInteger::less( const HugeInteger &right ) const
{
   auto& op1 = integer;
   auto& op2 = right.integer;
   if (op1.size() != op2.size())
      return op1.size() < op2.size();

   auto it1{ op1.end() }, it2{ op2.end() };
   for (; it1 != op1.begin(); --it1, --it2)
      if (it1[-1] != it2[-1])
         return it1[-1] < it2[-1];

   return false;
}

HugeInteger HugeInteger::subtract( const HugeInteger &op2 ) const
{
   HugeInteger difference{op2};
   std::for_each(difference.integer.begin(), difference.integer.end(),
      [](auto& i)
      { i = -i; });

   // use operator+= instead would be better if there is
   difference.assign(difference.add(*this));
   
   std::for_each(difference.integer.begin(), difference.integer.end() - 1,
      [](int& n) {
         if (n < 0) {
            n += 10;
            --*(&n + 1);
         }
      });
      
   while (difference.integer.size() > 1 && !difference.integer.end()[-1])
      difference.integer.pop_back();

   return difference;
}

HugeInteger HugeInteger::multiply( const  HugeInteger &op2 ) const
{
   if(this->isZero() || op2.isZero())
      return HugeInteger();
   auto& lhs = integer;
   auto& rhs = op2.integer;
   HugeInteger product{ lhs.size() + rhs.size() };

   for (auto i = 0u; i < lhs.size(); ++i)
      for (auto j = 0u; j < rhs.size(); ++j)
         product.integer.begin()[i + j] += lhs.begin()[i] * rhs.begin()[j];
   
   std::for_each(product.integer.begin(), product.integer.end() - 1,
      [](int& n) {
         if (n > 9) {
            (&n)[1] += n / 10;
            n %= 10;
         }
      });

   if(product.integer.end()[-1] == 0)
      product.integer.pop_back();

   return product;
}

HugeInteger HugeInteger::divide( const HugeInteger &op2 ) const
{
   if(less(op2))
      return HugeInteger();

   HugeInteger dividend{ *this };
   HugeInteger divisor{ this->integer.size() }, quotient{ divisor };

   std::copy(op2.integer.begin(), op2.integer.end(), divisor.integer.end() - op2.integer.size());
   quotient.integer.resize(0); // new a bigger size first to avoid renewing size when push_back

   while(op2.lessEqual(divisor)) {
      quotient.integer.push_back(0);
      while(divisor.lessEqual(dividend)) {
         // if there is operator-= would be better, can decrease lots of copies
         dividend.assign(dividend.subtract(divisor));
         ++quotient.integer.end()[-1];
      }
      divisor.divideByTen();
   }
   std::reverse(quotient.integer.begin(), quotient.integer.end());
   while (quotient.integer.size() > 1 && !quotient.integer.end()[-1])
      quotient.integer.pop_back();

   return quotient;
}
