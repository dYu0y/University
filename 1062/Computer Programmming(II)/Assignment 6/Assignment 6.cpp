// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "list.h" // include definition of class template list

void testList1();
void testList2();

int main()
{
//   system( "mode con:cols=60 lines=22" );
//   system( "color F0" );
   srand( 1 );

   testList1();

   testList2();

   system( "pause" );
}

void testList1()
{
   list< int > list1;
   std::list< int > list2;

//   cout << setw( 4 ) << list1.size() << setw( 4 ) << list1.capacity() << endl;
//   cout << setw( 4 ) << list2.size() << setw( 4 ) << list2.capacity() << endl << endl;

   unsigned int numErrors = 11; // number of errors
   unsigned int number;
   for( unsigned int i = 0; i < 11; i++ )
   {
      number = 1 + rand() % 99;
      list1.push_front( number );
      list2.push_front( number );
//      cout << setw( 4 ) << number << endl;
//      cout << setw( 4 ) << list1.size() << endl;
//      cout << setw( 4 ) << list2.size() << endl << endl;

      if( list1.equal( list2 ) )
         numErrors--;
   }

   if( numErrors == 0 )
      cout << "push_front is correct\n\n";
   else
      cout << "push_front is incorrect\n\n";

   numErrors = 11; // number of errors
   for( unsigned int i = 0; i < 11; i++ )
   {
      number = 1 + rand() % 99;
      list1.push_back( number );
      list2.push_back( number );
//      cout << setw( 4 ) << number << endl;
//      cout << setw( 4 ) << list1.size() << endl;
//      cout << setw( 4 ) << list2.size() << endl << endl;

      if( list1.equal( list2 ) )
         numErrors--;
   }

   if( numErrors == 0 )
      cout << "push_back is correct\n\n";
   else
      cout << "push_back is incorrect\n\n";

   unsigned int originalSize = list1.size();
   numErrors = 30;
   for( unsigned int length = 0; length < 30; length++ )
   {
      list1.resize( length );
      list2.resize( length );

//      cout << setw( 4 ) << list1.size() << endl;
//      cout << setw( 4 ) << list2.size() << endl << endl;

      if( list1.equal( list2 ) )
         numErrors--;
   }

   if( numErrors == 0 )
      cout << "resize is correct\n\n";
   else
      cout << "resize is incorrect\n\n";
}

void testList2()
{
   unsigned int numErrors = 1001; // number of errors
   unsigned int number = 1 + rand() % 9;

   list< int > list1( number );
   std::list< int > list2( number );

   if( list1.equal( list2 ) )
      numErrors--;

   unsigned int length;
   unsigned int choice;
   for( unsigned int i = 0; i < 1000; i++ )
   {
      choice = rand() % 4;
      switch( choice )
      {
      case 0:
         number = 1 + rand() % 99;
         list1.push_front( number );
         list2.push_front( number );
         break;
      case 1:
         number = 1 + rand() % 99;
         list1.push_back( number );
         list2.push_back( number );
         break;
      case 2:
         if( !list2.empty() )
         {
            list1.pop_back();
            list2.pop_back();
         }
         break;
      case 3:
         length = rand() % 200;
         list1.resize( length );
         list2.resize( length );
         break;
      default:
         break;
      }

//      cout << setw( 4 ) << list1.size() << setw( 4 ) << list1.capacity() << endl;
//      cout << setw( 4 ) << list2.size() << setw( 4 ) << list2.capacity() << endl << endl;

      if( list1.equal( list2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n\n";
}