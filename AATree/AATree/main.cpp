//
//  main.cpp
//  AATree
//
//  Created by Rockabye Saw on 30/03/2021.
//  Copyright © 2021 Rockabye Saw. All rights reserved.
//

#include <iostream>

using namespace std;
// AATree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order


  // Node and forward declaration because g++ does
  // not understand nested classes.
template <class Comparable>
class AATree;

template <class Comparable>
class AANode
{
    Comparable element;
    AANode    *left;
    AANode    *right;
    int        level;

    AANode( ) : left( NULL ), right( NULL ), level( 1 ) { }
    AANode( const Comparable & e, AANode *lt, AANode *rt, int lv = 1 )
      : element( e ), left( lt ), right( rt ), level( lv ) { }

    friend class AATree<Comparable>;
};

template <class Comparable>
class AATree
{
  public:
    explicit AATree( const Comparable & notFound );
    AATree( const AATree & rhs );
    ~AATree( );

    const Comparable & findMin( ) const;
    const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const;
    bool isEmpty( ) const;
    void printTree( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    const AATree & operator=( const AATree & rhs );
  private:
    AANode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND;
    AANode<Comparable> *nullNode;

      // Recursive routines
    void insert( const Comparable & x, AANode<Comparable> * & t );
    void remove( const Comparable & x, AANode<Comparable> * & t );
    void makeEmpty( AANode<Comparable> * & t );
    void printTree( AANode<Comparable> *t ) const;

      // Rotations
    void skew( AANode<Comparable> * & t ) const;
    void split( AANode<Comparable> * & t ) const;
    void rotateWithLeftChild( AANode<Comparable> * & t ) const;
    void rotateWithRightChild( AANode<Comparable> * & t ) const;
    AANode<Comparable> * clone( AANode<Comparable> * t ) const;
};

template <class Comparable>
AATree<Comparable>::AATree( const Comparable & notFound ) :
  ITEM_NOT_FOUND( notFound )
{
    nullNode = new AANode<Comparable>;
    nullNode->left = nullNode->right = nullNode;
    nullNode->level = 0;
    root = nullNode;
}

/**
 * Copy constructor.
 */
template <class Comparable>
AATree<Comparable>::AATree( const AATree<Comparable> & rhs ) :
  ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    nullNode = new AANode<Comparable>;
    nullNode->left = nullNode->right = nullNode;
    nullNode->level = 0;
    root = clone( rhs.root );
}

/**
 * Destructor for the tree.
 */
template <class Comparable>
AATree<Comparable>::~AATree( )
{
    makeEmpty( );
    delete nullNode;
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable>
void AATree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <class Comparable>
void AATree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

/**
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable & AATree<Comparable>::findMin( ) const
{
    if( isEmpty( ) )
        return ITEM_NOT_FOUND;

    AANode<Comparable> *ptr = root;
    while( ptr->left != nullNode )
        ptr = ptr->left;

    return ptr->element;
}

/**
 * Find the largest item in the tree.
 * Return the largest item of ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable & AATree<Comparable>::findMax( ) const
{
    if( isEmpty( ) )
        return ITEM_NOT_FOUND;

    AANode<Comparable> *ptr = root;
    while( ptr->right != nullNode )
        ptr = ptr->right;

    return ptr->element;
}

/**
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */
template <class Comparable>
const Comparable & AATree<Comparable>::
find( const Comparable & x ) const
{
    AANode<Comparable> *current = root;
    nullNode->element = x;

    for( ; ; )
    {
        if( x < current->element )
            current = current->left;
        else if( current->element < x )
            current = current->right;
        else if( current != nullNode )
            return current->element;
        else
            return ITEM_NOT_FOUND;
    }
}

/**
 * Make the tree logically empty.
 */
template <class Comparable>
void AATree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <class Comparable>
bool AATree<Comparable>::isEmpty( ) const
{
    return root == nullNode;
}

/**
 * Print the tree contents in sorted order.
 */
template <class Comparable>
void AATree<Comparable>::printTree( ) const
{
    if( root == nullNode )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}

/**
 * Deep copy.
 */
template <class Comparable>
const AATree<Comparable> &
AATree<Comparable>::operator=( const AATree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }

    return *this;
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void AATree<Comparable>::
insert( const Comparable & x, AANode<Comparable> * & t )
{
    if( t == nullNode )
        t = new AANode<Comparable>( x, nullNode, nullNode );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        return;  // Duplicate; do nothing

    skew( t );
    split( t );
}

/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void AATree<Comparable>::
remove( const Comparable & x, AANode<Comparable> * & t )
{
    static AANode<Comparable> *lastNode, *deletedNode = nullNode;

    if( t != nullNode )
    {
        // Step 1: Search down the tree and set lastNode and deletedNode
        lastNode = t;
        if( x < t->element )
            remove( x, t->left );
        else
        {
            deletedNode = t;
            remove( x, t->right );
        }

        // Step 2: If at the bottom of the tree and
        //         x is present, we remove it
        if( t == lastNode )
        {
            if( deletedNode == nullNode || x != deletedNode->element )
                return;   // Item not found; do nothing
            deletedNode->element = t->element;
            deletedNode = nullNode;
            t = t->right;
            delete lastNode;
        }

        // Step 3: Otherwise, we are not at the bottom; rebalance
        else
            if( t->left->level < t->level - 1 ||
                t->right->level < t->level - 1 )
            {
                if( t->right->level > --t->level )
                    t->right->level = t->level;
                skew( t );
                skew( t->right );
                skew( t->right->right );
                split( t );
                split( t->right );
            }
    }
}

/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void AATree<Comparable>::makeEmpty( AANode<Comparable> * & t )
{
    if( t != nullNode )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullNode;
}

/**
 * Internal method to print a subtree in sorted order.
 * @param t the node that roots the tree.
 */
template <class Comparable>
void AATree<Comparable>::printTree( AANode<Comparable> *t ) const
{
    if( t != nullNode )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}


/**
 * Rotate binary tree node with left child.
 */
template <class Comparable>
void AATree<Comparable>::rotateWithLeftChild( AANode<Comparable> * & k2 ) const
{
    AANode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

/**
 * Rotate binary tree node with right child.
 */
template <class Comparable>
void AATree<Comparable>::rotateWithRightChild( AANode<Comparable> * & k1 ) const
{
    AANode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

/**
 * Skew primitive for AA-trees.
 * t is the node that roots the tree.
 */
template <class Comparable>
void AATree<Comparable>::skew( AANode<Comparable> * & t ) const
{
    if( t->left->level == t->level )
        rotateWithLeftChild( t );
}

/**
 * Split primitive for AA-trees.
 * t is the node that roots the tree.
 */
template <class Comparable>
void AATree<Comparable>::split( AANode<Comparable> * & t ) const
{
    if( t->right->right->level == t->level )
    {
        rotateWithRightChild( t );
        t->level++;
    }
}

/**
 * Internal method to clone subtree.
 */
template <class Comparable>
AANode<Comparable> *
AATree<Comparable>::clone( AANode<Comparable> * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new AANode<Comparable>( t->element, clone( t->left ),
                                       clone( t->right ), t->level );
}

int main(int argc, const char * argv[]) {
    const int ITEM_NOT_FOUND = -9999;
    AATree<int> t( ITEM_NOT_FOUND );
    int NUMS = 20000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );
    t.remove( 0 );
    for( i = 1; i < NUMS; i += 2 )
        t.remove( i );

    if( NUMS < 40 )
        t.printTree( );
    if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i += 2 )
        if( t.find( i ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t.find( i ) != ITEM_NOT_FOUND )
            cout << "Find error2!" << endl;
    }

    AATree<int> t2( ITEM_NOT_FOUND );
    t2 = t;

    for( i = 2; i < NUMS; i += 2 )
        if( t2.find( i ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( t2.find( i ) != ITEM_NOT_FOUND )
            cout << "Find error2!" << endl;
    }


    return 0;
}
