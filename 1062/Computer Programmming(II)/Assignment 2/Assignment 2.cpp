// string test program.
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;

#include "String.h"
#include <string>

void testString();

int main()
{
   for( unsigned int seed = 0; seed < 40; seed++ )
   {
      srand( seed );
      testString();
   }

   system( "pause" );
} // end main

void testString()
{
   unsigned int n = 20;
   char s[ 100 ];
   for( unsigned int i = 0; i < n; i++ )
      s[ i ] = static_cast< char >( 97 + rand() % 26 );
      // Randomly generates a lower-case letter of English.
   s[ n ] = '\0';

   string str1( s, n ); // Constructs a string object, str1, initializing its value by s[0..n-1].
   std::string str2( s, n ); // Constructs a string object, str2, initializing its value by s[0..n-1].

   unsigned int numErrors = 2000; // number of errors
   unsigned int pos;              // position
   unsigned int length;           // the length of a string
   char c;                        // a character
   unsigned int choice;
   for( unsigned int i = 0; i < 2000; i++ )
   {
      choice = rand() % 6;
      switch( choice )
      {
      case 0:
         n = rand() % 200;
         str1.resize( n ); // Resizes str1 to a length of n characters.
         str2.resize( n ); // Resizes str2 to a length of n characters.
         if( str1.equal( str2 ) )
            numErrors--;
         else
            cout << "\nResize Error\n\n";
         break;
      case 1:
         // Randomly generates a lower-case letter of English.
         c = static_cast< char >( 97 + rand() % 26 );
         str1.push_back( c ); // Appends character c to the end of str1
         str2.push_back( c ); // Appends character c to the end of str2
         if( str1.equal( str2 ) )
            numErrors--;
         else
            cout << "\npush_back Error\n\n";
         break;
      case 2:
         if( str2.empty() )
            numErrors--;
         else
         {
            str1.pop_back(); // Erases the last character of str1
            str2.pop_back(); // Erases the last character of str2
            if( str1.equal( str2 ) )
               numErrors--;
            else
               cout << "\npop_back Error\n\n";
         }
         break;
      case 3:
         length = 1 + rand() % 50;
         for( unsigned int i = 0; i < length; i++ )
            s[ i ] = static_cast< char >( 97 + rand() % 26 );
            // Randomly generates a lower-case letter of English.
         s[ length ] = '\0';

         n = rand() % length;
         str1.assign( s, n ); // Assigns s[0..n-1] to str1, replacing its current contents.
         str2.assign( s, n ); // Assigns s[0..n-1] to str2, replacing its current contents.
         if( str1.equal( str2 ) )
            numErrors--;
         else
            cout << "\nassign Error\n\n";
         break;
      case 4:
         if( str2.empty() )
            numErrors--;
         else
         {
            pos = rand() % str2.size();
            n = rand() % str2.size();
            str1.erase( pos, n ); // Erases the portion str1[pos..pos+n-1] of str1.
            str2.erase( pos, n ); // Erases the portion str2[pos..pos+n-1] of str2.
            if( str1.equal( str2 ) )
               numErrors--;
            else
               cout << "\nerase Error\n\n";
         }
         break;
      case 5:
         if( str2.empty() )
            numErrors--;
         else
         {
            pos = rand() % str2.size();
            n = rand() % str2.size();
            // if the substring str1[pos..pos+n-1] of str1 is equal
            // the substring str2[pos..pos+n-1] of str2
            if( ( str1.substr( pos, n ) ).equal( str2.substr( pos, n ) ) )
               numErrors--;
            else
               cout << "\nsubstr Error\n\n";
         }
         break;
      default:
         break;
      }

 //     cout << setw( 4 ) << str1.size() << setw( 4 ) << str1.capacity() << endl;
 //     cout << setw( 4 ) << str2.size() << setw( 4 ) << str2.capacity() << endl << endl;
   }

   cout << "There are " << numErrors << " errors.\n";
}