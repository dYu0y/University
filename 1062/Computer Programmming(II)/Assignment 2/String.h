// string class definition.

#ifndef STRING_H
#define STRING_H

class string
{
public:
   // the maximum unsigned int value that is equal to 4294967295
   static const unsigned int npos = -1;

   string(); // Constructs an empty string, with a length of zero characters.

   string( const string &str ); // Constructs a copy of str.

   // Constructs a string object, initializing its value by
   // Coping the first n characters from the array of characters pointed by s.
   string( const char *s, unsigned int n );

   ~string(); // Destroys the string object.

   unsigned int size() const; // Returns the number of characters in the string.

   // Returns the size of the storage space currently allocated for the string,
   // expressed in terms of bytes.
   unsigned int capacity() const;

   // Resizes the string to a length of n characters.
   // If n is smaller than the current string length,
   // the current value is shortened to its first n character,
   // removing the characters beyond the nth.
   // If n is greater than the current string length,
   // the current content is extended by inserting at the end
   // as many characters as needed to reach a size of n.
   // The new elements are initialized as copies of null characters.
   void resize( unsigned int n );

   // Erases the contents of the string, which becomes an empty string
   // (with a length of 0 characters).
   void clear();

   // Appends character c to the end of the string, increasing its length by one.
   void push_back( char c );

   // Erases the last character of the string,
   // effectively reducing its length by one.
   void pop_back();

   // Assigns a new value to the string, replacing its current contents.
   // Copies the first n characters from the array of characters pointed by s.
   string& assign( const char *s, unsigned int n );

   // Erases the portion of the string value that begins at the character
   // position pos and spans len characters (or until the end of the string,
   // if either the content is too short or if len is string::npos).
   // Returns *this
   string& erase( unsigned int pos = 0, unsigned int len = npos );

   // Searches the string for the first occurrence of the character specified by its arguments.
   // When pos is specified, the search only includes characters at or after position pos.
   // Returns the position of the first match. If no matches were found,
   // the function returns string::npos.
   unsigned int find( char c, unsigned int pos = 0 ) const;

   // Returns a newly constructed string object with its value
   // initialized to a copy of a substring of this object.
   // The substring is the portion of the object that starts at character
   // position pos and spans len characters
   // (or until the end of the string, whichever comes first).
   string substr( unsigned int pos = 0, unsigned int len = npos ) const;

   // Returns true if and only if str is equal to the current string object.
   bool equal( std::string const &str );

   friend std::ostream& operator<<(std::ostream& os, string const& str);
private:
   union Bxty
   {
      char buf[ 16 ]; // storage reserved for string provided that myRes == 15
      char *ptr;      // a pointer to a storage reserved for string provided that myRes > 15
   } bx;

   unsigned int mySize = 0; // current length of string

   unsigned int myRes = 15; // current length of storage reserved for string
}; // end class string

#endif