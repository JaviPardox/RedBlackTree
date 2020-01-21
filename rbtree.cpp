 
/**
 *  @file rbtree.cpp   
 *   
 *  @brief Source file of the management of the Red Black Tree, 
 *         with its function and helper functions.
 *    
 *  @author Javier Pardo
 *  @date 4/29/20147
 */

#include <iostream>
#include <iomanip>
#include<string>
#include<vector>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;


/**
 *  @brief Constructor of the tree, creates nil
 *         and sets root to nil.
 *
 *  @param None.
 * 
 *  @return Nothing.
 * 
 */

RBTree::RBTree()
{
  nil = new Node();
  root = nil;
}

/**
 *  @brief Destructor of the tree, deletes nil.
 *
 *  @param None.
 * 
 *  @return Nothing.
 * 
 */

RBTree::~RBTree()
{
  //deleteTree(root);
  delete nil;
}

/**
 *  @brief Default constructor of a Node.
 *
 *  @param None.
 * 
 *  @return Nothing.
 * 
 */

RBTree::Node::Node()
{
  key = nullptr;
  value = nullptr;
  color = 'B';
}

/**
 *  @brief Constructor of a Node, dinamically allocates a new string 
 *         for key and a new string for value.
 *
 *  @param Key and Value
 * 
 *  @return Nothing.
 * 
 */

RBTree::Node::Node(const string& key, const string& value)
{
  this->key = new string(key);
  this->value = new string(value);
}

/**
 *  @brief Destructor of a Node, deletes both key and value.
 *
 *  @param None.
 * 
 *  @return Nothing.
 * 
 */

RBTree::Node::~Node()
{
  delete key;
  delete value;
}

/**
 *  @brief Calls the function to print the tree.
 *   
 *  @param None.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbPrintTree()
{
  reverseInOrderPrint(root,0);
}

/**
 *  @brief Prints the tree in reverse order and
 *         sideways.
 *
 *  @param A pointer to a Node, and integer depth.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/**
 *  @brief Calls rbInsert which inserts the created node into
 *         the tree.
 *
 *  @param String key and data
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbInsert(const string& key, const string& data)
{
  //cout << key << " " << data << endl;
  rbInsert(new Node(key,data));
}

/**
 *  @brief Inserts the node into the tree while rearranging it
 *         to keep the red black tree properties.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbInsert(Node* z)
{
  Node* y = nil;
  Node* x = root;
  while(x != nil)
  {
    y = x;
    if(*z->key < *x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if(y == nil)
    root = z;
  else if(*z->key < *y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
  z->left = nil;
  z->right = nil;
  z->color = 'R';
  rbInsertFixup(z);
}

/**
 *  @brief Called from the initial insertion function, insert fixup
 *         is responsible of rearranging the tree to keep the red
 *         black properties.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbInsertFixup(Node* z)
{
  while(z->parent->color == 'R')
  {
    if(z->parent == z->parent->parent->left)
    {
      Node* y = z->parent->parent->right;
      if(y->color == 'R')
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      } 
      else
      {
        if(z == z->parent->right)
        {
            z = z->parent;
            leftRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(z->parent->parent);
      }
    }
    else
    {
      Node* y = z->parent->parent->left;
      if(y->color == 'R')
      {
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';
        z = z->parent->parent;
      }
      else
      {
        if(z == z->parent->left)
        {
            z = z->parent;
            rightRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(z->parent->parent);
      }
    }
  }
  root->color = 'B';
}

/**
 *  @brief Part of the rearraging algorithm, this function
 *         rotates the selected node to the left, while also
 *         maintaining the read balck tree properties.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::leftRotate(Node* z)
{
  Node* y = z->right;
  z->right = y->left;
  if(y->left != nil)
    y->left->parent = z;
  y->parent = z->parent;
  if(z->parent == nil)
    root = y;
  else if(z == z->parent->left)
    z->parent->left = y;
  else
    z->parent->right = y;
  y->left = z;
  z->parent = y;
}

/**
 *  @brief Part of the rearraging algorithm, this function
 *         rotates the selected node to the right, while also
 *         maintaining the read balck tree properties.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rightRotate(Node* z)
{
  Node* y = z->left;
  z->left = y->right;
  if(y->right != nil)
    y->right->parent = z;
  y->parent = z->parent;
  if(z->parent == nil)
    root = y;
  else if(z == z->parent->right)
    z->parent->right = y;
  else
    z->parent->left = y;
  y->right = z;
  z->parent = y;
}

/**
 *  @brief This function is in charge of finding the desired node,
 *         insert it into a vector and later deleting it.
 *
 *  @param Two strings, dkey and ddata.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbDelete(const string& dkey, const string& ddata)
{
  Node* x = root;
  Node* y = rbTreeSearch(x,dkey);
  vector<Node*> deleteNode;
  if(y != nil)
  {
    if(*y->key == dkey && *y->value == ddata)
    {
      deleteNode.push_back(y);
    }
    Node* pre = rbTreePredecessor(y);
    while(pre != nil)
    {
      if(pre != y && *pre->key == dkey && *pre->value == ddata)
      {
        deleteNode.push_back(pre);
      }
      pre = rbTreePredecessor(pre);
    }
    Node* suc = rbTreeSuccessor(y);
    while(suc != nil)
    {
      if(suc != y && *suc->key == dkey && *suc->value == ddata)
      {
        deleteNode.push_back(suc);
      }
      suc = rbTreeSuccessor(suc);
    }
  }
  for(std::vector<Node*>::iterator it = deleteNode.begin(); it != deleteNode.end(); it++)
  {
    rbDelete(*it);
    delete (*it);
  }
}

/**
 *  @brief This function removes the desired Node from the tree,
 *  and makes sure the red black tree properties are intact.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbDelete(Node* z)
{
  Node* y = z;
  Node* x;
  char yOriginalColor = y->color;
  if(z->left == nil)
  {
    x = z->right;
    rbTransplant(z,z->right);
  }
  else if(z->right == nil)
  {
    x = z->left;
    rbTransplant(z,z->left);
  }
  else
  {
    y = rbTreeMaximum(z->left);
    yOriginalColor = y->color;
    x = y->left;
    if(y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      rbTransplant(y,y->left);
      y->left = z->left;
      y->left->parent = y;
    }
    rbTransplant(z,y);
    y->right = z->right;
    y->right->parent = y;
    y->color = z->color;
  }
  if(yOriginalColor == 'B')
    rbDeleteFixup(x);
}

/**
 *  @brief This function is designed to keep the red black properties
 *         after removing a Node from the tree.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbDeleteFixup(Node* x)
{
  Node* w;
  while(x != root && x->color == 'B')
  {
    if(x == x->parent->left)
    {
      w = x->parent->right;
      if(w->color == 'R')
      {
        w->color = 'B';
        x->parent->color = 'R';
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if(w->left->color == 'B' && w->right->color == 'B')
      {
        w->color = 'R';
        x = x->parent;
      }
      else
      {
        if(w->right->color == 'B')
        {
          w->left->color = 'B';
          w->color = 'R';
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->right->color = 'B';
        leftRotate(x->parent);
        x = root;
      }
    }
    else
    {
      w = x->parent->left;
      if(w->color == 'R')
      {
        w->color = 'B';
        x->parent->color = 'R';
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if(w->right->color == 'B' && w->left->color == 'B')
      {
        w->color = 'R';
        x = x->parent;
      }
      else
      {
        if(w->left->color == 'B')
        {
          w->right->color = 'B';
          w->color = 'R';
          leftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = 'B';
        w->left->color = 'B';
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 'B';
}

/**
 *  @brief This function changes two nodes of position between them.
 *
 *  @param Pointer to Node u and another pointer to a Node v.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::rbTransplant(Node* u, Node* v)
{
  if(u->parent == nil)
    root = v;
  else if(u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}

/**
 *  @brief This function finds the minimum child of the 
 *         subtree of the desired Node.
 *
 *  @param Pointer to a Node.
 * 
 *  @return A pointer to a node.
 * 
 */

RBTree::Node* RBTree::rbTreeMinimum(Node* x)
{
  while(x->left != nil)
    x = x->left;
  return x;
}

/**
 *  @brief This function finds the maximum child of the 
 *         subtree of the desired Node.
 *
 *  @param Pointer to a Node.
 * 
 *  @return A pointer to a node.
 * 
 */

RBTree::Node* RBTree::rbTreeMaximum(Node* x)
{
  while(x->right != nil)
    x = x->right;
  return x;
}

/**
 *  @brief This function finds the successor of the desired node.
 *
 *  @param Pointer to a Node.
 * 
 *  @return A pointer to a node.
 * 
 */

RBTree::Node* RBTree::rbTreeSuccessor(Node* x)
{
  if(x->right != nil)
    return rbTreeMinimum(x->right);
  Node* y = x->parent;
  while(y != nil && x == y->right)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

/**
 *  @brief This function finds the predecessor
 *         of the desired Node.
 *
 *  @param Pointer to a Node.
 * 
 *  @return A pointer to a node.
 * 
 */

RBTree::Node* RBTree::rbTreePredecessor(Node* x)
{
  if(x->left != nil)
    return rbTreeMaximum(x->left);
  Node* y = x->parent;
  while(y != nil && x == y->left)
  {
    x = y;
    y = y->parent;
  }
  return y;
}

/**
 *  @brief This function finds looks for the desired node
 *         and inserts it into a vector, if there are duplicates
 *         it will look for them using successor's and predecessor's
 *         functions.
 *
 *  @param A key string.
 * 
 *  @return A vector of pointers to strings.
 * 
 */

vector<const string*> RBTree::rbFind(const string& fkey)
{
  Node* y;
  Node* x = root;
  vector<const string*>find;
  y = rbTreeSearch(x,fkey); 
  find.push_back(y->key);
  find.push_back(y->value);
  if(y != nil)
  {
    Node *suc = rbTreeSuccessor(y);
    Node *pre = rbTreePredecessor(y);
    while(pre != nil)
    {
      if(pre != y && *y->key == *pre->key)
      {
        find.push_back(pre->value);
      }
      pre = rbTreePredecessor(pre);
    }
    while(suc != nil)
    {
      if(suc != y && *y->key == *suc->key)
      {
        find.push_back(suc->value);
      }
      suc = rbTreeSuccessor(suc);
    }
  }
    return find;
}

/**
 *  @brief This function recursively calls itself to go
 *         through the tree to find the desired Node.
 *
 *  @param Pointer to a Node and a string of a key.
 * 
 *  @return A pointer to a node.
 * 
 */

RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& fkey)
{
  if(x == nil || fkey == *x->key)
    return x;
  if(fkey < *x->key)
    return rbTreeSearch(x->left,fkey);
  else
    return rbTreeSearch(x->right,fkey);
}

/**
 *  @brief Helper function to delete the whole tree
 *         at the end of the execution of the program.
 *
 *  @param Pointer to a Node.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::deleteTree(Node* x)
{
  if(x != nil)
  {
    deleteTree(x->left);
    deleteTree(x->right);
    delete x;
  }
}

/**
 *  @brief Public function to delete the tree 
 *         at the end of the execution of the program.
 *         Calls the private function.
 *
 *  @param Nothing.
 * 
 *  @return Nothing.
 * 
 */

void RBTree::deleteTree()
{
  deleteTree(root);
}
