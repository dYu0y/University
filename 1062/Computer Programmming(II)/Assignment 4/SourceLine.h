// SourceLine class definition
#ifndef SOURCE_LINE_H
#define SOURCE_LINE_H

#include "String.h" // string class definition

class SourceLine 
{
public:
   static const size_t npos = -1; // the maximum unsigned int value that is equal to 4294967295

   SourceLine(); // default constructor

   void assign( const char *s, size_t n );
   void delComments(); // delete the comment beginning with "//" in sourceLine
   void delStrConst(); // deletes all string constants from sourceLine
   void delCharConst(); // deletes all character constants from sourceLine

   // delete the first identifier from sourceLine, and then return the identifier
   string delFirstIdentifier();

private:
   string sourceLine;
};

#endif