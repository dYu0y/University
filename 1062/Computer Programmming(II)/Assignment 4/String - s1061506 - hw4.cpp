// string class member-function definitions.
#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
using std::cerr;

#include "String.h" // string class definition

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::string( const string &str )
   : mySize( str.mySize ),
     myRes( str.myRes )
{
   if( myRes == 15 )
      for( size_t i = 0; i <= mySize; i++ )
         bx.buf[ i ] = str.bx.buf[ i ];
   else
   {
      bx.ptr = new char[ myRes + 1 ];
      for( size_t i = 0; i <= mySize; i++ )
         bx.ptr[ i ] = str.bx.ptr[ i ];
   }
}

// destructor
string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
} // end destructor

char* string::begin()
{
   if( myRes == 15 )
      return bx.buf;
   else
      return bx.ptr;
}

char* string::end()
{
   if( myRes == 15 )
      return bx.buf + mySize;
   else
      return bx.ptr + mySize;
}

size_t string::size() const
{
   return mySize;
}

std::ostream &operator<<( std::ostream &output, string &str )
{
   if( str.myRes == 15 )
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.buf[ i ];
   else
      for( size_t i = 0; i < str.mySize; i++ )
         output << str.bx.ptr[ i ];

   return output; // enables cout << x << y;
}

bool operator==( const string &lhs, const string &rhs )
{
   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=( const string &lhs, const string &rhs )
{
   return ( lhs.compare( rhs ) != 0 );
}

// start here

#define MinRes (sizeof(bx) - 1)
#include <algorithm> // std::copy, std::fill

string::string( const char *s, size_t n )
   : string()
{
   assign(s, n);
}

string& string::operator=( const string &str )
{
   return str.size() ? assign(&str[0], str.size()) : resize(0); // to avoid str.size() == 0 and str[0] would out of range
}

void string::resize( size_t n )
{
   if (n > myRes) {
      auto newCap = std::max(myRes + myRes / 2, n | 15);
      char* tmp { new char[newCap + 1]{} };
      std::copy(begin(), end(), tmp);
      this->~string();
      bx.ptr = tmp;
      myRes = newCap;
   }
   else if (n > size())
      std::fill(begin() + size(), begin() + n, char());
   mySize = n;
}

char& string::operator[]( size_t pos )
{
   return const_cast<char&>(static_cast<const string&>(*this)[pos]);
}

const char& string::operator[]( size_t pos ) const
{
   if (pos < size())
      return (myRes == MinRes ? bx.buf : bx.ptr)[pos];
   throw ("Out of range");
}

string& string::assign( const char *s, size_t n )
{
   resize(n);
   for (auto it = begin(); it != end();)
      *it++ = *s++;
   return *this;
}

string& string::erase( size_t pos, size_t len)
{
   if (len && pos < size()) { // 當pos > size() 時, 運算 size() - pos 會因為結果應為負數, 但是unsigned是沒負數的而導致出錯
      if (len > size() - pos) // when len == npos, len + pos would overflow
         len = size() - pos;
      std::copy(begin()+pos+len, end(), begin()+pos);
      mySize -= len;
   }
   return *this;
}

size_t string::find( char c, size_t pos) const
{
   auto ans { npos };
   for (; pos < size(); ++pos) {
      if ((*this)[pos] == c) {
         ans = pos;
         break;
      }
   }
   return ans;
}

string string::substr( size_t pos, size_t len) const
{
   if (pos < size()) {
      if (len == npos || len > size() - pos)
         len = size() - pos;
      return string(&(*this)[0] + pos, len);
   }
   return string();
}

int string::compare(const string& str) const
{
   if (size() <= str.size()) {
      for (auto i{ 0u }; i < size(); ++i)
         if ((*this)[i] != str[i])
            return (*this)[i] - str[i];
      return size() == str.size() ? 0 : -1;
   }
   else
      return -str.compare(*this);
}

#undef MinRes
