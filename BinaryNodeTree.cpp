#include <algorithm> // For std::max
#include <iostream>
#include <memory>
#include <new>
#include <limits>
#include <climits>

#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"
#include "BinaryNodeTree.h"

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

// returns height of binary tree
template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNodePtr subTreePtr) const {

   if (subTreePtr) {
      return 1 + std::max(getHeightHelper(subTreePtr->leftChildPtr),
                          getHeightHelper(subTreePtr->rightChildPtr) );
   }

   return 0;
}

// returns number of nodes of binary tree
template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNodePtr subTreePtr) const {

   if (subTreePtr) {
      return 1 +
         getNumberOfNodesHelper(subTreePtr->leftChildPtr) +
         getNumberOfNodesHelper(subTreePtr->rightChildPtr);
   }

   return 0;
}

// link into the parent node
template <typename ItemType>
auto BinaryNodeTree<ItemType>::balancedAdd(BinaryNodePtr subTreePtr,
                                           BinaryNodePtr newNodePtr) {

   if (!subTreePtr) {
      return newNodePtr;
   }

   if (getHeightHelper(subTreePtr->leftChildPtr) >
       getHeightHelper(subTreePtr->rightChildPtr) ) {
      subTreePtr->rightChildPtr = balancedAdd(subTreePtr->rightChildPtr,
                                              newNodePtr);
   }
   else {
      subTreePtr->leftChildPtr = balancedAdd(subTreePtr->leftChildPtr,
                                             newNodePtr);
   }

   return subTreePtr;
}

// remove the node that subTreePtr points at
template <typename ItemType>
auto BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNodePtr subTreePtr) {

   if (isLeaf(subTreePtr) ) {
      subTreePtr = nullptr;
      return subTreePtr;
   }

   if (getHeightHelper(subTreePtr->leftChildPtr) >
       getHeightHelper(subTreePtr->rightChildPtr) ) {
      subTreePtr->item = subTreePtr->leftChildPtr->item;
      subTreePtr->leftChildPtr = moveValuesUpTree(subTreePtr->leftChildPtr);
   }
   else {
      subTreePtr->item = subTreePtr->rightChildPtr->item;
      subTreePtr->rightChildPtr = moveValuesUpTree(subTreePtr->rightChildPtr);
   }

   return subTreePtr;
}

/** Depth-first search of tree for item.
 *
 *  @param subTreePtr The tree to search.
 *
 *  @param target The target item to find.
 *
 *  @param success Communicate to client whether we found the target.
 *
 *  @return A pointer to the node containing the target. */

// 
template <typename ItemType>
auto BinaryNodeTree<ItemType>::removeValue(BinaryNodePtr subTreePtr,
                                           const ItemType& target,
                                           bool& success) {

   if (!subTreePtr) {
      return BinaryNodePtr(); // A nullptr with type 'BinaryNodePtr'.
   }

   if (subTreePtr->item == target) {
      success = true;
      return moveValuesUpTree(subTreePtr);
   }

   subTreePtr->leftChildPtr = removeValue(subTreePtr->leftChildPtr,
                                          target,
                                          success);
   if (!success) {
      subTreePtr->rightChildPtr = removeValue(subTreePtr->rightChildPtr,
                                              target,
                                              success);
   }

   return subTreePtr;
}


// find a node in a tree
template <typename ItemType>
auto BinaryNodeTree<ItemType>::findNode(BinaryNodePtr subTreePtr,
                                        const ItemType& target) const {

   BinaryNodePtr returnPtr;

   if (!subTreePtr) {
      return returnPtr;
   }

   if (subTreePtr->item == target) {
      return subTreePtr;
   }

   returnPtr = findNode(subTreePtr->leftChildPtr,
                        target);
   if (!returnPtr) {
      returnPtr = findNode(subTreePtr->rightChildPtr,
                           target);
   }

   return returnPtr;
}


// deep copy of the tree pointed to by the sub tree ptr and return it
template <typename ItemType>
auto BinaryNodeTree<ItemType>::copyTree(const BinaryNodePtr& subTreePtr) const {

   if (!subTreePtr) {
      return BinaryNodePtr();
   }

   // Copy tree nodes using a preorder traversal
   return std::make_shared<BinaryNode>(subTreePtr->item,
                                       copyTree(subTreePtr->leftChildPtr),
                                       copyTree(subTreePtr->rightChildPtr) );
}

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

// 

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&),
                                        BinaryNodePtr subTreePtr) {

   if (subTreePtr) {
      visit(subTreePtr->item);

      preorder(visit, subTreePtr->leftChildPtr);
      preorder(visit, subTreePtr->rightChildPtr);
   }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&),
                                       BinaryNodePtr subTreePtr) {

   if (subTreePtr) {
      inorder(visit, subTreePtr->leftChildPtr);

      visit(subTreePtr->item);

      inorder(visit, subTreePtr->rightChildPtr);
   }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&),
                                         BinaryNodePtr subTreePtr) {

   if (subTreePtr) {
      postorder(visit, subTreePtr->leftChildPtr);
      postorder(visit, subTreePtr->rightChildPtr);

      visit(subTreePtr->item);
   }
}

//////////////////////////////////////////////////////////////
//      Protected Node Access Sub-Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isLeaf(BinaryNodePtr nodePtr) const {

   return !nodePtr->leftChildPtr && !nodePtr->rightChildPtr;
}

template <typename ItemType>
auto BinaryNodeTree<ItemType>::getRootPtr() const {

   return rootPtr;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootPtr(BinaryNodePtr newRootPtr) {

   rootPtr = newRootPtr;
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
   : rootPtr(std::make_shared<BinaryNode>(rootItem) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
   : rootPtr(std::make_shared<BinaryNode>(rootItem,
                                          copyTree(leftTreePtr->rootPtr),
                                          copyTree(rightTreePtr->rootPtr)) ) {
}

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr) {

   try {
      rootPtr = copyTree(treePtr.rootPtr);
   }
   catch (const std::bad_alloc&) {
      clear();
      throw;
   }
}

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const {

   return !rootPtr;
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getHeight() const {

   return getHeightHelper(rootPtr);
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const {

   return getNumberOfNodesHelper(rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::clear() {

   rootPtr.reset();
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const {

   if (!isEmpty() ) {
      return rootPtr->item;
   }

   std::string message("BinaryNodeTree::getRootData: called ");
   message += "on an empty tree.";

   throw PrecondViolatedExcep(message);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem) {

   if (isEmpty() ) {
      try {
         rootPtr = std::make_shared<BinaryNode>(newItem);
      }
      catch (const std::bad_alloc&) {
         // What should we do with this? Return something? Throw a
         // different type of exception? Crash?
      }
   }
   else {
      rootPtr->item = newItem;
   }
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData) {

   try {
      rootPtr = balancedAdd(rootPtr,
                            std::make_shared<BinaryNode>(newData) );
   }
   catch (const std::bad_alloc&) {
      return false;
   }

   return true;
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target) {

   bool isSuccessful(false);

   rootPtr = removeValue(rootPtr, target, isSuccessful);

   return isSuccessful;
}

template <typename ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const {

   auto binaryNodePtr(findNode(rootPtr, anEntry) );

   if (binaryNodePtr) {
      return binaryNodePtr->item;
   }

   std::string message("BinaryNodeTree::getEntry: Entry ");
   message += "not found in this tree.";

   throw NotFoundException(message);
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const {

   return findNode(rootPtr, anEntry) != nullptr;
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&) ) {

   preorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&) ) {

   inorder(visit, rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&) ) {

   postorder(visit, rootPtr);
}

//////////////////////////////////////////////////////////////
//      Overloaded Operator
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNodeTree<ItemType>&
BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rhs) {

   auto oldTreePtr(rootPtr);

   if (this != &rhs) {
      try {
         rootPtr = copyTree(rhs.rootPtr);
      }
      catch (const std::bad_alloc&) {
         rootPtr = oldTreePtr;
         throw;
      }
   }

   return *this;
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::display(BinaryNodePtr myNode) {
    if (myNode->rightChildPtr) {
        curHeight++;
        display(myNode->rightChildPtr);
        curHeight--;
    }
    for (int i = 0; i < curHeight; i++) {
        std::cout << " ";
    }
    std::cout << myNode->item << std::endl;
    if (myNode->leftChildPtr) {
        curHeight++;
        display(myNode->leftChildPtr);
        curHeight--;
    }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::displayTree() {
    if (rootPtr) {
        display(rootPtr);
    }
    else {
        std::cout << "empty tree" << std::endl;
    }
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::flipTree() {
    flip(rootPtr);
}

template <typename ItemType>
void BinaryNodeTree<ItemType>::flip(BinaryNodePtr rootPtr) {
    if (rootPtr != NULL) {
        BinaryNodePtr temp;
        temp = rootPtr->leftChildPtr;
        rootPtr->leftChildPtr = rootPtr->rightChildPtr;
        rootPtr->rightChildPtr = temp;
        flip(rootPtr->leftChildPtr);
        flip(rootPtr->rightChildPtr);
    }
}

template <typename ItemType>
bool BinaryNodeTree<ItemType>::BST(BinaryNodePtr rootPtr, 
    int min, int max){

    BinaryNodePtr temp;
    BinaryNodePtr lel;

    temp = rootPtr->leftChildPtr;
    lel = rootPtr->rightChildPtr;

    if (temp > rootPtr || lel < rootPtr) {
        return false;
    }
    if (temp > rootPtr && lel < rootPtr) {
        return true;
    }
}

// test if this binary tree contains a binary search tree
template <typename ItemType>
void BinaryNodeTree<ItemType>::testBST() {
    if (BST(rootPtr, INT_MIN, INT_MAX)) {
        std::cout << "This is a BST";
    }
    if (!BST(rootPtr, INT_MIN, INT_MAX)){
        std::cout << "This is NOT a BST";
    }
}

template <typename ItemType>
int BinaryNodeTree<ItemType>::findMin() {}

// find max value in the binary tree
template <typename ItemType>
int BinaryNodeTree<ItemType>::findMax() {}

//prints all of the root to leaf paths 
template <typename ItemType>
void BinaryNodeTree<ItemType>::printRootToLeafPaths(BinaryNodePtr rootPtr,
    ItemType& anArray,
    ItemType& anItem) {}

//do the nodes in some path contain a given sum
template <typename ItemType>
bool BinaryNodeTree<ItemType>::doesSomePathHaveSum(ItemType& anItem) {}
