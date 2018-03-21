#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include "String.h" // string class definition

#define minRes (sizeof(bx) - 1) // (sizeof(bx) / sizeof(char) - 1)

static void copy(char const* begin, char const* end, char* out) //  std::copy exploded QQ
{
	for (; begin != end;)	*out++ = *begin++;
}

string::string()
{
   bx.buf[ 0 ] = '\0';
}

string::string( const string &str )
{
   mySize = str.mySize;
   myRes = str.myRes;

   if( myRes == 15 )
      for( unsigned int i = 0; i <= mySize; i++ )
         bx.buf[ i ] = str.bx.buf[ i ];
   else
   {
      bx.ptr = new char[ myRes + 1 ];
      for( unsigned int i = 0; i <= mySize; i++ )
         bx.ptr[ i ] = str.bx.ptr[ i ];
   }
}

string::string( const char *s, unsigned int n )
{
	resize(n);

	if (myRes == minRes)
	{
		copy(s, s + n, bx.buf);
		std::fill(bx.buf + mySize, bx.buf + myRes + 1, char());
	}
	else
		copy(s, s + n, bx.ptr);
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

unsigned int string::size() const
{
   return mySize;
}

unsigned int string::capacity() const
{
   return myRes;
}

void string::resize( unsigned int n )
{
	char* str = (myRes != minRes) ? bx.ptr : bx.buf;

	if (myRes < n)
	{
		auto cap = std::_Max_value(myRes + myRes / 2, n | 15);
		
		char* tmp = new char[cap + 1]();
		copy(str, str + mySize, tmp);

		if (str == bx.ptr)
			delete[] bx.ptr;
		
		myRes = cap;
		bx.ptr = tmp;
	}
	else if(mySize < n)
		std::fill(str + mySize, str + n, char());
	
	mySize = n;
}

void string::clear()
{
   mySize = 0;
   if( myRes == 15 )
      bx.buf[ 0 ] = '\0';
   else
      bx.ptr[ 0 ] = '\0';
}

void string::push_back( char c )
{
   if (mySize == myRes)
        resize(mySize + 1);
   else
        ++mySize;
    
   ((myRes != minRes) ? bx.ptr : bx.buf)[mySize - 1] = c;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string& string::assign( const char *s, unsigned int n )
{
	resize(n);
	
	char* str = (myRes != minRes) ? bx.ptr : bx.buf;
	
	copy(s, s + n, str);	// now I think "str0.assign(&str0[0], n);" is safe if not out of range
	
   return *this;
}

string& string::erase( unsigned int pos, unsigned int len )
{
	if (pos < mySize)
	{
		char* str = (myRes != minRes) ? bx.ptr : bx.buf;
		if (mySize < pos + len || len == npos)
			len = mySize - pos;
		else
			copy(str + pos + len, str + mySize, str + pos);

		std::fill(str + mySize - len, str + mySize, char());

		mySize -= len;
	}

	return *this;
}

unsigned int string::find( char c, unsigned int pos ) const
{
   if( pos < mySize )
      if( myRes == 15 )
      {
         for( unsigned int i = pos; i < mySize; i++ )
            if( c == bx.buf[ i ] )
               return i;
      }
      else
      {
         for( unsigned int i = pos; i < mySize; i++ )
            if( c == bx.ptr[ i ] )
               return i;
      }

   return npos;
}

string string::substr(unsigned int pos, unsigned int len) const
{
	if (pos < mySize)
	{
		if (mySize < pos + len)
			len = mySize - pos;

		char const* str = (myRes != minRes) ? bx.ptr : bx.buf;

		return string(str + pos, len);
	}
	return string();
}

bool string::equal( std::string const &str )
{
   if( myRes != str.capacity() )
      return false;

   if( mySize != str.size() )
      return false;

   if( myRes == 15 )
   {
      for( unsigned int i = 0; i < mySize; i++ )
         if( bx.buf[ i ] != str[ i ] )
            return false;
   }
   else
   {
      for( unsigned int i = 0; i < mySize; i++ )
         if( bx.ptr[ i ] != str[ i ] )
            return false;
   }

   return true;
}

#undef minRes
