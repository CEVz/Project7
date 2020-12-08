#include <iostream>
#include <string>
#include <memory>
#include <limits>

#include "BinaryNodeTree.h"

template <typename ItemType>
void display(ItemType& anItem) {

	std::cout << anItem << std::endl;

}

void reverse(std::string& anItem) {

	anItem = std::string(anItem.rbegin(), anItem.rend());

}

int main() {

	BinaryNodeTree<int> bt;
	std::cout << "Standard Binary Tree" << std::endl;
	bt.add(5);
	bt.add(3);
	bt.add(7);
	bt.add(2);
	bt.add(6);
	bt.add(4);
	bt.add(1);
	bt.add(8);
	bt.displayTree();
	std::cout << " " << std::endl;
	bt.testBST();
	std::cout << " " << std::endl;
	std::cout << " " << std::endl;
	std::cout << "Flipped Binary Tree" << std::endl;
	bt.flipTree();
	bt.displayTree();
	std::cout << " " << std::endl;
	bt.testBST();

}