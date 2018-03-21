// Identifier class member-function definitions.

#include "Identifier.h" // Identifier class definition
#include <cstring>
char keywords[ 61 ][ 20 ] = { "auto", "break", "case", "char", "const", "continue",
                              "default", "do", "double", "else", "enum", "extern",
                              "float", "for", "goto", "if", "int", "long",
                              "register", "return", "short", "signed", "sizeof",
                              "static", "struct", "switch", "typedef", "union",
                              "unsigned", "void", "volatile", "while", "bool",
                              "catch", "class", "const_cast", "delete",
                              "dynamic_cast", "explicit", "false", "friend",
                              "inline", "mutable", "namespace","new", "operator",
                              "private", "protected", "public", "reinterpret_cast",
                              "static_cast", "template", "this", "throw", "true",
                              "try", "typeid", "typename", "using", "virtual",
                              "include" };

// default/conversion constructor
Identifier::Identifier() : identifier()
{
}

// overloaded = operator; avoids self assignment
const Identifier &Identifier::operator=( const string &right )
{
   identifier = right;

   return *this; // enables cascaded assignments
} // end function operator=

bool operator==( const Identifier &lhs, const Identifier &rhs )
{
   return lhs.identifier == rhs.identifier;
}

std::ostream &operator<<( std::ostream &output, Identifier &id )
{
   output << id.identifier;
   return output; // enables cout << x << y;
}

// start here
static const auto keywordNum = 61u;
// check if the current identifier is a C++ keyword
bool Identifier::keyword()
{
   int i;
   static bool uninitialized { true };
   static string keywords[keywordNum];
   if (uninitialized) {
      for (i = 0; i < keywordNum; ++i)
         keywords[i] = string(::keywords[i], strlen(::keywords[i]));
      uninitialized = false;
   }
   for (i = 0; i < keywordNum; ++i)
      if(identifier == keywords[i])
         break;
   return i != keywordNum;
}