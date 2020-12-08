#pragma once

#include <iostream>
#include <memory>

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNode::BinaryNode(const ItemType& anItem, 
						 BinaryNodePtr leftPtr = nullptr,
						 BinaryNodePtr rightPtr = nullptr) :
	item(anItem),
	leftChildPtr(leftPtr),
	rightChildPtr(rightPtr) {


}

#ifdef DTOR_TEST

template <typename ItemType>
BinaryNodeTree<ItemType>::BinaryNode::~BinaryNode() {

    std::cout << "BinaryNode destructor called on:\n\titem: "
        << item
        << "\n\tleftChildPtr: "
        << leftChildPtr.get()
        << "\n\trightChildPtr: "
        << rightChildPtr.get()
        << std::endl;
}

#endif
