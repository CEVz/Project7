#include <iostream>
#include <string>
#include <memory>

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
	bt.add(5);
	bt.add(8);
	bt.add(4);
	bt.add(3);
	bt.add(1);
	bt.add(7);
	bt.add(6);
	bt.add(2);
	bt.displayTree();
	std::cout << " " << std::endl;
	bt.flipTree();
	bt.displayTree();
}