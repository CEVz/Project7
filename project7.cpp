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
	auto treePtr(std::make_unique<BinaryNodeTree<std::string>>());
	tree1Ptr->add(1);



	//tree1Ptr->add("10");
	//tree1Ptr->add("20");
	//std::cout << tree1Ptr->getHeight() << std::endl;
	//std::cout << tree1Ptr->getNumberOfNodes() << std::endl;
	//tree1Ptr->remove("10");
	//std::cout << tree1Ptr->getHeight() << std::endl;
	//std::cout << tree1Ptr->getNumberOfNodes() << std::endl;

	//bt.getNumberOfNodesHelper(tree1Ptr);

	return 0;


}