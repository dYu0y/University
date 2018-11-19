#include "Matrix.h"

MatrixNode::MatrixNode( bool b, Triple &t )  // constructor
{
   head = b;
   if( b )
      right = down = next = this; // row/column header node
   else
      triple = t; // element node or header node for list of header nodes
}

Matrix::Matrix()
   : headNode( nullptr )
{
}

Matrix::Matrix( TwoDimArray &twoDimArray )
{
   Triple s;
   s.row = twoDimArray.numRows;
   s.col = twoDimArray.numCols;
   s.value = twoDimArray.numValues;

   if( s.col <= 0 || s.row <= 0 )
      return;

   // set up header node for the list of header nodes.
   headNode = new MatrixNode(false, s);

   Triple *triples = new Triple[ s.value ];
   int count = 0;
   for( int i = 0; i < s.row; i++ )
      for( int j = 0; j < s.col; j++ )
         if( twoDimArray.ptr[ i ][ j ] != 0 )
         {
            triples[ count ].row = i;
            triples[ count ].col = j;
            triples[ count ].value = twoDimArray.ptr[ i ][ j ];
            count++;
         }

   int p = ( s.col > s.row ) ? s.col : s.row;

   // at least one row and column
   MatrixNode **head = new MatrixNode *[ p ];
   Triple zeroTriple = {};
   for( int i = 0; i < p; i++ )
	   head[i] = new MatrixNode(true, zeroTriple); // create header nodes

   int currentRow = 0;
   MatrixNode *last = head[ 0 ]; // last node in current row
   for( int i = 0; i < s.value; i++ ) // input triples
   {
      if( triples[ i ].row > currentRow ) // close current row
      {
         last->right = head[ currentRow ];
         currentRow = triples[ i ].row;
         last = head[ currentRow ];
      }
	  
      // link new node into row list
      last = last->right = new MatrixNode( false, triples[ i ] );

      // link into column list
      head[ triples[ i ].col ]->next = head[ triples[ i ].col ]->next->down = last;
   }

   last->right = head[ currentRow ];// close last row

   // close all column lists
   for( int i = 0; i < s.col; i++ )
      head[ i ]->next->down = head[ i ];

   // link the header nodes together
   for( int i = 0; i < p - 1; i++ )
      head[ i ]->next = head[ i + 1 ];

   head[ p - 1 ]->next = headNode;
   headNode->right = head[ 0 ];
   delete[] head;
}

Matrix::Matrix( const Matrix &matrixToCopy )
{
	this->Matrix::Matrix();
	*this = matrixToCopy;
}

Matrix::~Matrix()
{
   erase();
}

const Matrix &Matrix::operator=( const Matrix &op2 )
{
	if (&op2 != this) {
		erase();
		if (op2.headNode) {
			Triple rhs = op2.headNode->triple;
			TwoDimArray res(rhs.row, rhs.col);
			res.numValues = rhs.value;

			MatrixNode* head = op2.headNode->right;
			for(; head != op2.headNode; head = head->next)
				for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
					Triple t = tmp->triple;
					res.ptr[t.row][t.col] = t.value;
				}

			this->Matrix::Matrix(res);
		}
	}
	return *this;
}

Matrix Matrix::operator+( Matrix &op2 )
{
   // ver1
	Triple rhs = op2.headNode->triple;
	TwoDimArray sum(rhs.row, rhs.col);
	MatrixNode* head = op2.headNode->right;
	for (; head != op2.headNode; head = head->next)
		for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
			Triple t = tmp->triple;
			sum.ptr[t.row][t.col] += t.value;
		}
	head = headNode->right;
	for (; head != headNode; head = head->next)
		for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
			Triple t = tmp->triple;
			sum.ptr[t.row][t.col] += t.value;
		}
	for (int i = 0; i < headNode->triple.row; ++i)
		for (int j = 0; j < headNode->triple.col; ++j)
			if (sum.ptr[i][j])
				++sum.numValues;

	return sum;

   // ver2
   /*
   Triple rhs = op2.headNode->triple;
   TwoDimArray r(rhs.row, rhs.col);
   r.numValues = rhs.value;

   MatrixNode* head = op2.headNode->right;
   for (; head != op2.headNode; head = head->next)
      for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
         Triple t = tmp->triple;
         r.ptr[t.row][t.col] = t.value;
      }

   Triple lhs = headNode->triple;
   TwoDimArray l(lhs.row, lhs.col);
   l.numValues = lhs.value;

   head = headNode->right;
   for (; head != headNode; head = head->next)
      for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
         Triple t = tmp->triple;
         l.ptr[t.row][t.col] = t.value;
      }
   return l + r;
   */
}

Matrix Matrix::operator*( Matrix &op2 )
{
	Triple rhs = op2.headNode->triple;
	TwoDimArray r(rhs.row, rhs.col);
	r.numValues = rhs.value;

	MatrixNode* head = op2.headNode->right;
	for (; head != op2.headNode; head = head->next)
		for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
			Triple t = tmp->triple;
			r.ptr[t.row][t.col] = t.value;
		}

	Triple lhs = headNode->triple;
	TwoDimArray l(lhs.row, lhs.col);
	l.numValues = lhs.value;

	head = headNode->right;
	for (; head != headNode; head = head->next)
		for (MatrixNode* tmp = head->right; tmp != head; tmp = tmp->right) {
			Triple t = tmp->triple;
			l.ptr[t.row][t.col] = t.value;
		}
	return l * r;
}

void Matrix::erase()
{  // erase the matrix, return the nodes to the heap
   MatrixNode *x, *y;
   if( headNode != nullptr )
   {
      MatrixNode *head = headNode->right;

      while( head != headNode ) // free the triple and header nodes by row
      {
         y = head->right;
         while( y != head )
         {
            x = y;
            y = y->right;
            delete x;
         }

         x = head;
         head = head->next;
         delete x;
      }

      delete headNode;
      headNode = nullptr;
   }
}

bool Matrix::operator==( TwoDimArray &twoDimArray )
{
   int numRows = headNode->triple.row;
   int numCols = headNode->triple.col;

   if( numRows != twoDimArray.numRows )
      return false;

   if( numCols != twoDimArray.numCols )
      return false;

   if( headNode->triple.value != twoDimArray.numValues )
      return false;

   int col;
   MatrixNode *head = headNode->right;
   // scan header nodes one by one
   for( int row = 0; row < numRows; row++, head = head->next )
   {
      col = 0;
      // scan elements in the current row
      for( MatrixNode *temp = head->right; temp != head; temp = temp->right )
      {
         if( row != temp->triple.row )
            return false;

         // find next nonzero element in the current row
         while( twoDimArray.ptr[ row ][ col ] == 0 )
            col++;

         if( col != temp->triple.col )
            return false;

         if( twoDimArray.ptr[ row ][ col ] != temp->triple.value )
            return false;

         col++;
      }
   }
   
   int row;
   head = headNode->right;
   // scan header nodes one by one
   for( int col = 0; col < numRows; col++, head = head->next )
   {
      row = 0;
      // scan elements in the current column
      for( MatrixNode *temp = head->down; temp != head; temp = temp->down )
      {
         if( col != temp->triple.col )
            return false;

         // find next nonzero element in the current column
         while( twoDimArray.ptr[ row ][ col ] == 0 )
            row++;

         if( row != temp->triple.row )
            return false;

         if( twoDimArray.ptr[ row ][ col ] != temp->triple.value )
            return false;

         row++;
      }
   }

   return true;
}

ostream &operator<<( ostream &os, Matrix &matrix )
{  // print out the matrix in row major form
   int preCol;
   int numRows = matrix.headNode->triple.row;
   MatrixNode *head = matrix.headNode->right;
   // scan header nodes one by one
   for( int row = 0; row < numRows; row++, head = head->next )
   {
      preCol = -1;
      // scan elements in the current row
      for( MatrixNode *temp = head->right; temp != head; temp = temp->right )
      {
         // display zero elements
         for( int i = 1; i < temp->triple.col - preCol; i++ )
            os << setw( 4 ) << 0;
         os << setw( 4 ) << temp->triple.value; // display nonzero element
         preCol = temp->triple.col;
      }

      for( int i = 1; i < matrix.headNode->triple.col - preCol; i++ )
         os << setw( 4 ) << 0;
      os << endl;
   }

   return os; // enables os << x << y;
}