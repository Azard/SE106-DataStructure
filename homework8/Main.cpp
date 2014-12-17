#include <iostream>
#include <vector>
using namespace std;

// 节点实现
struct Node
{
	Node();
	int data;
	Node* left;
	Node* right;
};

Node::Node()
{
	data = 0;
	left = NULL;
	right = NULL;
}

// 最小堆实现
class MinHeap
{
public:
	vector<Node*> heap;
	MinHeap();
	void percolate_up(int num);
	void percolate_down(int num);
	void insert(Node* element);
	Node* delete_min();
};


// 最小堆构造
MinHeap::MinHeap()
{
	Node zero;
	heap.push_back(&zero); // 第0项不用
}


// 最小堆上滤
void MinHeap::percolate_up(int num)
{
	int pos = num;
	int val = heap[num]->data;
	while(val < heap[pos/2]->data && pos > 1) {
		Node* temp = heap[pos/2];
		heap[pos/2] = heap[pos];
		heap[pos] = temp;
		pos /= 2; 
	}
}

// 最小堆下滤
void MinHeap::percolate_down(int num)
{
	int pos = num;
	int val = heap[num]->data;
	while(pos*2 <= heap.size()) {
		// 两个子树都有值
		if (pos*2 + 1 <= heap.size()) {
			// 和左子树置换
			if (heap[pos*2]->data <= heap[pos*2+1]->data && heap[pos*2]->data < val) {
				Node* temp = heap[pos*2];
				heap[pos*2] = heap[pos];
				heap[pos] = temp;
				pos = pos*2;
			}
			// 和右子树置换
			else if (heap[pos*2+1]->data < heap[pos*2]->data && heap[pos*2+1]->data < val) {
				Node* temp = heap[pos*2+1];
				heap[pos*2+1] = heap[pos];
				heap[pos] = temp;
				pos = pos*2 + 1;
			}
			else break;
		}
		// 只有左子树有值
		else {
			if (heap[pos*2]->data < val) {
				Node* temp = heap[pos*2];
				heap[pos*2] = heap[pos];
				heap[pos] = temp;
				pos = pos*2;
			}
			else break;
		}
	}
}

// 最小堆插入
void MinHeap::insert(Node* element)
{
	heap.push_back(element);
	percolate_up(heap.size()-1);
}

// 最小堆取出最小值
Node* MinHeap::delete_min()
{
	Node* ret_val = heap[1];
	heap[1] = heap[heap.size()-1];
	heap.resize(heap.size()-1);
	percolate_down(1);
	return ret_val;
}


Node* creat_huffman(vector<Node>& save, MinHeap& minhp)
{
	int n = save.size();
//	if (n == 1)
//		return &save[0];
	save.resize(2*n-1);
	for (int i = 0; i < n; i ++)
		minhp.insert(&save[i]);
	for (int i = n; i < 2*n-1; i++) {

		cout << "Heap:\n";
		for(int k = 1; k < minhp.heap.size(); k++)
			cout << minhp.heap[k]->data << " | ";
		cout << endl;

		Node* min_node_1 = minhp.delete_min();
		Node* min_node_2 = minhp.delete_min();
		save[i].left = min_node_1;
		save[i].right = min_node_2;
		save[i].data = min_node_1->data + min_node_2->data;

		cout << "get left:  " << min_node_1->data << endl;
		cout << "get right: " << min_node_2->data << endl;
		cout << "sum data : " << save[i].data << endl << endl;

		minhp.insert(&save[i]);
		if (i == 2*n-2)
			return &save[i];
	}
}


void trave_huffman(Node* node, int& weight_sum, int& depth)
{
	if (node->left == NULL) {
		weight_sum += node->data * depth;
		depth -= 1;
		return;
	}
	depth += 1;
	trave_huffman(node->left, weight_sum, depth);
	depth += 1;
	trave_huffman(node->right, weight_sum, depth);
	depth -= 1;
	return;
}

int main()
{
	cout << "Input(-1 to quit):\n";
	vector<Node> save;
	while(true) {
		int temp_val;
		cin >> temp_val;
		if (temp_val == -1)
			break;
		Node temp_node;
		temp_node.data = temp_val;
		save.push_back(temp_node);
	}
	MinHeap minhp;
	Node* root = creat_huffman(save, minhp);
	int weight_sum = 0;
	int depth = 0;
	trave_huffman(root, weight_sum, depth);
	cout << "Output:\n" << weight_sum << endl;		
	return 0;
}

