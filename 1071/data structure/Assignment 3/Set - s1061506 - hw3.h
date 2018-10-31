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
   TreeNode< Kty > **n = &myHead->parent, *p = myHead;
   while (!(*n)->isNil) {
      p = *n;
      if (val < p->myval)
         n = &p->left;
      else
         n = &p->right;
   }
   (*n) = new TreeNode< Kty >;
   (**n).color = Red;
   (**n).parent = p;
   (**n).isNil = false;
   (**n).myval = val;
   (**n).left = (**n).right = myHead;

   if (p == myHead)
      myHead->left = myHead->right = *n;
   else if (p == myHead->left && n == &p->left)
      myHead->left = *n;
   else if (p == myHead->right && n == &p->right)
      myHead->right = *n;

   reBalance(*n);

   ++mySize;
}

// Removes from the set container a single element whose value is val
// This effectively reduces the container size by one, which are destroyed.
// Returns the number of elements erased.
template< typename Kty >
unsigned int set< Kty >::erase( const Kty &val )
{
   TreeNode< Kty >* m = myHead->parent;
   while (!m->isNil && m->myval != val) {
      if (val < m->myval)
         m = m->left;
      else
         m = m->right;
   }
   // can't find the val
   if(m->isNil)
      return 0;
   if (!m->left->isNil && !m->right->isNil) {
      TreeNode< Kty >* c = m->right;
      while (!c->left->isNil)
         c = c->left;
      m->myval = c->myval;
      m = c;
   }

   if (m == myHead->left)
      myHead->left = m->parent;
   if (m == myHead->right)
      myHead->right = m->parent;

   eraseDegreeOne(m);
   --mySize;

   if (mySize == 1)
      myHead->left = myHead->right = myHead->parent;

   return 1;
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
   TreeNode< Kty > *p = node->parent, *g = p->parent, *u;
   // node == root
   if (p == myHead)
      node->color = Black;
   else if (p->color == Red) {
      if (p == g->left)
         u = g->right;
      else
         u = g->left;
      // case XXr : do color change
      if (u->color == Red) {
         p->color = u->color = Black;
         g->color = Red;
         reBalance(g);
      }
      // LLb
      else if (p == g->left && node == p->left) {
         std::swap(p->color, g->color);
         LLRotation(p);
      }
      // RRb
      else if (p == g->right && node == p->right) {
         std::swap(p->color, g->color);
         RRRotation(p);
      }
      // LRb
      else if (p == g->left && node == p->right) {
         std::swap(node->color, g->color);
         LRRotation(p);
      }
      // RLb
      else if (p == g->right && node == p->left) {
         std::swap(node->color, g->color);
         RLRotation(p);
      }
   }
}

// rotate right at g, where p = g->left and node = p->left
template< typename Kty >
void set< Kty >::LLRotation( TreeNode< Kty > *p )
{
   TreeNode< Kty > *g = p->parent, *gg = g->parent;
   p->parent = gg;
   g->parent = p;
   g->left = p->right;
   if (!g->left->isNil)
      g->left->parent = g;
   p->right = g;
   if (gg == myHead)
      gg->parent = p;
   else if (g == gg->left)
      gg->left = p;
   else if (g == gg->right)
      gg->right = p;
}

// LR rotation; p = g->left and node = p->right
template< typename Kty >
void set< Kty >::LRRotation( TreeNode< Kty > *node )
{
   node = node->right;
   RRRotation(node);
   LLRotation(node);
}

// RL rotation; p = g->right and node = p->left
template< typename Kty >
void set< Kty >::RLRotation( TreeNode< Kty > *node )
{
   node = node->left;
   LLRotation(node);
   RRRotation(node);
}

// rotate left at g, where p = g->right and node = p->right
template< typename Kty >
void set< Kty >::RRRotation( TreeNode< Kty > *p )
{
   TreeNode< Kty > *g = p->parent, *gg = g->parent;
   p->parent = gg;
   g->parent = p;
   g->right = p->left;
   if (!g->right->isNil)
      g->right->parent = g;
   p->left = g;
   if (gg == myHead)
      gg->parent = p;
   else if (g == gg->left)
      gg->left = p;
   else if (g == gg->right)
      gg->right = p;
}

// erase node provided that the degree of node is at most one
template< typename Kty >
void set< Kty >::eraseDegreeOne( TreeNode< Kty > *node )
{
   TreeNode< Kty > *c = node->left;
   if (c->isNil)
      c = node->right;

   if (node == node->parent->left)
      node->parent->left = c;
   if (node == node->parent->right)
      node->parent->right = c;
   if (!c->isNil)
      c->parent = node->parent;
   

   // node is root
   if (node->parent == myHead) {
      myHead->parent = c;
      c->color = Black;
   }
   // two Blacks
   else if (node->color == c->color)
      fixUp(c, node->parent);
   // one Red, one Black
   else if (c->color == Red)
      c->color = Black;

   delete node;
}

// rebalance for deletion
template< typename Kty >
void set< Kty >::fixUp( TreeNode< Kty > *N, TreeNode< Kty > *P )
{
   if (P == myHead) {
      N->color = Black;
      return;
   }
   TreeNode< Kty > *S = N == P->left ? P->right : P->left;
   
   // case 1
   if (S->color == Red) {
      std::swap(P->color, S->color);
      if (N == P->left)
         RRRotation(S);
      else
         LLRotation(S);
      // goto case2, 3, or 4
      S = N == P->left ? P->right : P->left;
   }
   
   if (S->right->color == Black && S->left->color == Black) {
      // case 4
      if (P->color == Red)
         std::swap(P->color, S->color);
      // case 5
      else {
         S->color = Red;
         fixUp(P, P->parent);
      }
   }

   if (N == P->left) {
      // case 3
      if (S->right->color == Black && S->left->color == Red) {
         std::swap(S->color, S->left->color);
         LLRotation(S->left);
         S = N == P->left ? P->right : P->left;
      }
      // case 2
      if (S->right->color == Red) {
         std::swap(P->color, S->color);
         S->right->color = Black;
         RRRotation(S);
      }
   }
   else {
      // case 3
      if (S->left->color == Black && S->right->color == Red) {
         std::swap(S->color, S->right->color);
         RRRotation(S->right);
         S = N == P->left ? P->right : P->left;
      }
      // case 2
      if (S->left->color == Red) {
         std::swap(P->color, S->color);
         S->left->color = Black;
         LLRotation(S);
      }
   }
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