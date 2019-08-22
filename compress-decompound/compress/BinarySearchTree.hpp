//
//  BinarySearchTree.hpp
//  CS300HW2_v3
//
//  Created by caghank on 18.11.2018.
//  Copyright © 2018 caghank. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp


#include <stdio.h>
#include <iostream>
using namespace std;

template <class Comparable>
struct BinaryNode
{
    Comparable element;
    int position;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comparable & theElement,int position, BinaryNode *lt, BinaryNode *rt )
    : element( theElement ), position(position),left( lt ), right( rt ) { }
    //friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
    //BinarySearchTree( const Comparable & notFound );
    //BinarySearchTree( const BinarySearchTree & rhs );
    BinarySearchTree(const Comparable & notFound );
   // BinarySearchTree( );
    //~BinarySearchTree( );
    //const Comparable & findMin( ) const;
    //const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const;
    const int & findPosition( const Comparable & x ) const;
    bool isEmpty( ) const;
    void printTree( ) const;
    //void makeEmpty( );
    void insert( const Comparable & x ,int position);
    void remove( const Comparable & x );
    //const BinarySearchTree & operator=( const BinarySearchTree & rhs );
    
private:
    BinaryNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND;
    
    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
    const int & positionAt( BinaryNode<Comparable> *t ) const;
    
    void insert( const Comparable & x,int position, BinaryNode<Comparable> * & t ) const;
    void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    //BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
   // BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
    //void makeEmpty( BinaryNode<Comparable> * & t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;

};

/**
 * Construct the tree.
 */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound ) :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}



/**
 * Internal method to get element field in node t.
 * Return the element field or ITEM_NOT_FOUND if t is NULL.
 */


template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}
template <class Comparable>
const int & BinarySearchTree<Comparable>::positionAt( BinaryNode<Comparable> *t ) const
{
    return t == NULL ? -9999: t->position;
}

template <class Comparable>
const int & BinarySearchTree<Comparable>::findPosition( const Comparable & x ) const
{
    return positionAt(find( x, root ) );
}

/**
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x )
        return find( x, t->right );
    else
        return t;    // Match
}

/**
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x,int position  )
{
    insert( x,position, root );
}
/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x,int position, BinaryNode<Comparable> * & t) const
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( x ,position, NULL, NULL );
    else if( x < t->element )
        insert( x, position,t->left );  // insert at the left or
    else if( t->element < x )
        insert( x, position, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}




/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}



/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */


template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}




/**
 * Copy constructor.
 */
/*
template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}


/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::
printTree( BinaryNode<Comparable> *t ) const
{
    if( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}
template<class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const
{
    if(root==NULL)
        return true;
    else
        return false;
}

#endif /* BinarySearchTree_hpp */
