#include <fstream>
using std::ifstream;
using std::ios;

#include "Identifier.h" // Identifier class definition
#include "SourceLine.h" // SourceLine class definition

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( Identifier identifiers[], int pos );

int main()
{
   ifstream inFile( "test_alt.cpp", ios::in );

   // exit program if ifstream could not open file
   if ( !inFile ) 
   {
      std::cout << "File could not be opened" << std::endl;
      system( "pause" );
      exit( 1 );
   }
   
   char source[ 200 ];
   SourceLine sourceLine;
   Identifier identifiers[ 1000 ];
   string identifier;
   string null;
   int numIdentifiers = 0;

   while( inFile.getline( source, sizeof( source ), '\n' ) )
   {
      sourceLine.assign( source, strlen( source ) );
      sourceLine.delComments(); // deletes the comment beginning with "//" in sourceLine
      sourceLine.delStrConst(); // deletes all string constants in sourceLine
      sourceLine.delCharConst(); // deletes all character constants in sourceLine

      // extracts all identifiers from sourceLine
      while( ( identifier = sourceLine.delFirstIdentifier() ) != null )
         identifiers[ numIdentifiers++ ] = identifier;
   }

   for( int i = 0; i < numIdentifiers; i++ )
      if( !identifiers[ i ].keyword() && !duplicate( identifiers, i ) )
         std::cout << identifiers[ i ] << std::endl;

   system( "pause" );
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( Identifier identifiers[], int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}
