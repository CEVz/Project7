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
	bt.add(1);
	bt.add(2);
	bt.add(3);
	bt.add(4);
	bt.displayTree();
	
	
	
	
	//auto treePtr(std::make_unique<BinaryNodeTree<std::string>>());

	//bt.getNumberOfNodesHelper(tree1Ptr);

	return 0;


}