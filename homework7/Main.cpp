#include <iostream>
#include <string>
#include "Tree.cpp"
using namespace std;

int main()
{
	Node* t = NULL;
	

	cout << "Enter interger number add to BST. (q to quit)\n";
	while(true) {
		string input;
		cin >> input;
		if ("q" == input)
			break;
		insertNode(t, stoi(input));
	}
	cout << "Enter target value\n";
	int v;
	cin >> v;
	int min = v;
	bool flag = false;
	TreeIterator iter(t);
	Node* node;
	node = iter.next();
	while(NULL != node) {
		if (!flag && !(node->key < v)) {
			min = node->key;
			flag = true;
		} else if (node->key < min && !(node->key < v)) {
			min = node->key;
			flag = true;
		}
		node = iter.next();
	}
	if (!flag) {
		cout << "Not find.\n";
		return 0;
	}
	cout << "Find: " << min << endl;
	return 0;
}
