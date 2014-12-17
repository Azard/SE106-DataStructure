#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
	int key;
	Node *left;
	Node *right;
};


void insertNode(Node* &t, int key) {
	if (t == NULL) {
		t = new Node;
		t->key = key;
		t->left = t->right = NULL;
		return;
	}
	if (key == t->key) return;
	if (key < t->key) {
		insertNode(t->left, key);
	} else {
		insertNode(t->right, key);
	}
}

class TreeIterator {
	public:
		TreeIterator(Node* node) {
			Node *current = node;
			while (NULL != current) {
				myStack.push(current);
				current = current->left;
			}
		}
		Node* next() {
			if (myStack.empty())
				return NULL;
			Node* top = myStack.top();
			myStack.pop();
			if (NULL != top->right) {
				Node* current = top->right;
				while(NULL != current) {
					myStack.push(current);
					current = current->left;
				}
			}
			return top;
		}

	private:
		stack<Node*> myStack;

};







