#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

/** @class BinaryNode BinaryNode.h "BinaryNode.h"
 *
 *  Specification of the nested node type for a linked-chain based ADT
 *  binary tree. */
template <typename ItemType>
class BinaryNodeTree<ItemType>::BinaryNode {
public:
   using BinaryNodePtr = std::shared_ptr<BinaryNode>;

   ItemType item;

   BinaryNodePtr leftChildPtr;
   BinaryNodePtr rightChildPtr;

   explicit BinaryNode(const ItemType& anItem,
                       BinaryNodePtr leftPtr = nullptr,
                       BinaryNodePtr rightPtr = nullptr);

#ifdef DTOR_TEST
   ~BinaryNode();
#else
   ~BinaryNode() = default;
#endif
};

#include "BinaryNode.cpp"

#endif
