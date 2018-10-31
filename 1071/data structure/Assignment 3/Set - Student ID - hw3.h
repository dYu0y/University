#ifndef SET_H
#define SET_H

enum Color{ Red, Black };

// TreeNode class template definition
template< typename Kty >
class TreeNode
{
   template< typename K > friend class set;
private:
   TreeNode *left;   // left subtree, or smallest element if head
   TreeNode *parent; // parent, or root of tree if head
   TreeNode *right;  // right subtree, or largest element if head
   Color color;      // red or black, black if head
   bool isNil;       // true only if head (also nil) node
   Kty myval;
}; // end class template TreeNode

// set class template definition
template< typename Kty >
class set
{
public:
   set(); // Constructs an empty set object, with head node.

   ~set(); // Destroys the set object.

   // Extends the set container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const Kty &val );

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   unsigned int erase( const Kty &val );

private:
   TreeNode< Kty > *myHead; // pointer to head node
   unsigned int mySize;     // number of elements ( not include head node )

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< Kty > *node );

   // rebalance for insertion
   void reBalance( TreeNode< Kty > *node );

   // rotate right at g, where p = g->left and node = p->left
   void LLRotation( TreeNode< Kty > *p );

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< Kty > *node );

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< Kty > *node );

   // rotate left at g, where p = g->right and node = p->right
   void RRRotation( TreeNode< Kty > *p );

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< Kty > *node );

   // rebalance for deletion
   void fixUp( TreeNode< Kty > *N, TreeNode< Kty > *P );

   void twoTraversals(); // preorder traversal and inorder traversal

   void preorder( TreeNode< Kty > *node ); // preorder traversal

   void inorder( TreeNode< Kty > *node ); // inorder traversal
}; // end class template set

// Constructs an empty set object, with head node.
template< typename Kty >
set< Kty >::set()
   : myHead( new TreeNode< Kty > ),
     mySize( 0 )
{
   myHead->left = myHead;
   myHead->parent = myHead;
   myHead->right = myHead;
   myHead->color = Black;
   myHead->isNil = true;
}

// Destroys the set object.
template< typename Kty >
set< Kty >::~set()
{
   clear( myHead->parent );
   delete myHead;
}

// Extends the container by inserting a new element,
// effectively increasing the container size by one.
template< typename Kty >
void set< Kty >::insert( const Kty& val )
{

}

// Removes from the set container a single element whose value is val
// This effectively reduces the container size by one, which are destroyed.
// Returns the number of elements erased.
template< typename Kty >
unsigned int set< Kty >::erase( const Kty &val )
{

}

// Removes all elements from the set object (which are destroyed)
template< typename Kty >
void set< Kty >::clear( TreeNode< Kty > *node )
{
   if( !node->isNil ) // node is not an external node
   {
      clear( node->left );
      clear( node->right );
      delete node;
   }
}

// rebalance for insertion
template< typename Kty >
void set< Kty >::reBalance( TreeNode< Kty > *node )
{

}

// rotate right at g, where p = g->left and node = p->left
template< typename Kty >
void set< Kty >::LLRotation( TreeNode< Kty > *p )
{

}

// LR rotation; p = g->left and node = p->right
template< typename Kty >
void set< Kty >::LRRotation( TreeNode< Kty > *node )
{

}

// RL rotation; p = g->right and node = p->left
template< typename Kty >
void set< Kty >::RLRotation( TreeNode< Kty > *node )
{

}

// rotate left at g, where p = g->right and node = p->right
template< typename Kty >
void set< Kty >::RRRotation( TreeNode< Kty > *p )
{

}

// erase node provided that the degree of node is at most one
template< typename Kty >
void set< Kty >::eraseDegreeOne( TreeNode< Kty > *node )
{

}

// rebalance for deletion
template< typename Kty >
void set< Kty >::fixUp( TreeNode< Kty > *N, TreeNode< Kty > *P )
{

}

// preorder traversal and inorder traversal
template< typename Kty >
void set< Kty >::twoTraversals()
{
   cout << "Preorder sequence:\n";
   preorder( myHead->parent );

   cout << "\nInorder sequence:\n";
   inorder( myHead->parent );
   cout << endl;
}

// preorder traversal
template< typename Kty >
void set< Kty >::preorder( TreeNode< Kty > *node )
{
   if( node != myHead )
   {
      cout << setw( 5 ) << node->myval << ( node->color == Red ? "R" : "B" );
      preorder( node->left );
      preorder( node->right );
   }
}

// inorder traversal
template< typename Kty >
void set< Kty >::inorder( TreeNode< Kty > *node )
{
   if( node != myHead )
   {
      inorder( node->left );
      cout << setw( 5 ) << node->myval << ( node->color == Red ? "R" : "B" );
      inorder( node->right );
   }
}

#endif