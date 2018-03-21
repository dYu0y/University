// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "Vector.h"

void testVector1();
void testVector2();

int main()
{
   srand( 2 );
   testVector1();

   for( unsigned int seed = 0; seed < 20 * 2; seed++ )
   {
      srand( seed );
      testVector2();
   }

   system( "pause" );

} // end main

void testVector1()
{
   vector v1;
   std::vector< int > v2;

//   cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
//   cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

   unsigned int numErrors = 11 * 10; // number of errors
   unsigned int number;
   for( unsigned int i = 0; i < 11 * 10; i++ )
   {
      number = 1 + rand() % 99;
      v1.push_back( number );
      v2.push_back( number );
      cout << setw( 4 ) << number << endl;
      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

      if( v1.equal( v2 ) )
         numErrors--;
   }

   if( numErrors == 0 )
      cout << "push_back is correct.\n";
   else
      cout << "push_back is incorrect.\n";

   unsigned int originalSize = v1.size();
   numErrors = 16 * 10;
   for( unsigned int length = 0; length < 16 * 10; length++ )
   {
      v1.resize( length );
      v2.resize( length );

//      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
//      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

      if( v1.equal( v2 ) )
         numErrors--;
   }

   if( numErrors == 0 )
      cout << "resize is correct.\n\n";
   else
      cout << "resize is incorrect.\n\n";
}

void testVector2()
{
   vector v1;
   std::vector< int > v2;

   unsigned int numErrors = 1000 * 2; // number of errors
   unsigned int number;
   unsigned int length;
   unsigned int choice;
   for( unsigned int i = 0; i < 1000 * 2; i++ )
   {
      choice = rand() % 3;
      switch( choice )
      {
      case 0:
         number = 1 + rand() % 99;
         v1.push_back( number );
         v2.push_back( number );
         break;
      case 1:
         if( !v2.empty() )
         {
            v1.pop_back();
            v2.pop_back();
         }
         break;
      case 2:
         length = rand() % 200;
         v1.resize( length );
         v2.resize( length );
         break;
      default:
         break;
      }

//      cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
//      cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;

      if( v1.equal( v2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}