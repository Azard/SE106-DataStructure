#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <bitset>
using namespace std;

struct Node {
	uint8_t ch;
	uint32_t times;
	Node* left;
	Node* right;
};

struct Read_Node {
	Read_Node();
	Read_Node* left;
	Read_Node* right;
};
Read_Node::Read_Node() {
	left = NULL;
	right = NULL;
}


void com_AnalyseInputfile(fstream& input_file, map<uint8_t, uint32_t>& stat);
Node* com_DeleteMin(vector<Node*>& minvec);
void com_WriteTree(fstream& output_file, Node* root, int flag, map<uint8_t, string>& ch_to_bits, string& bits_stack);
void dec_ReadTree(map<string, uint8_t>& bits_to_ch, string& now, fstream& input_file, vector<Read_Node>& save_read_node, Read_Node* node);


void com_AnalyseInputfile(fstream& input_file, map<uint8_t, uint32_t>& stat) {
	char ch;
	uint8_t temp;
	while(input_file.get(ch)) {
		temp = reinterpret_cast<uint8_t&>(ch);
		if (stat.find(temp) == stat.end())
			stat[temp] = 1;
		else
			stat[temp]++;
	}
	cout << "\nstat:\n";
	for (auto& i : stat)	// show stat
		cout << "key: " << int(i.first) << "  val: " << i.second << endl; 
}

Node* com_DeleteMin(vector<Node*>& minvec) {
	// find least
	uint32_t min_times = minvec[0]->times;
	int save_i = 0;
	for (unsigned int i = 0; i < minvec.size(); i++) {
		if (minvec[i]->times < min_times) {
			min_times = minvec[i]->times;
			save_i = i;
		}
	}
	Node* temp = minvec[save_i];
	minvec[save_i] = minvec[minvec.size()-1];
	minvec[minvec.size()-1] = temp;
	minvec.resize(minvec.size()-1);
	return temp;
}

void com_WriteTree(fstream& output_file, Node* node, int flag, map<uint8_t, string>& ch_to_bits, string& bits_stack) {
	// flag  0:root 1:left 2:right
	if (node->left == NULL) {
		ch_to_bits[node->ch] = bits_stack;
		uint16_t temp = node->ch;
		// not write head
		output_file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
		bits_stack.pop_back();
		return;
	} else {
		uint16_t temp = 0;
		if (flag == 0)
			temp = 0x1100;
		else if (flag == 1)
			temp = 0x1000;
		else
			temp = 0x0100;
		// not write head
		output_file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
		bits_stack += "0";
		com_WriteTree(output_file, node->left, 1, ch_to_bits, bits_stack);
		bits_stack += "1";
		com_WriteTree(output_file, node->right, 2, ch_to_bits, bits_stack);
		if (bits_stack.length())
			bits_stack.pop_back();
		return;
	}
}





void compress(string inputFilename, string outputFilename) {
	fstream input_file(inputFilename, ios::in | ios::binary);
	fstream output_file(outputFilename, ios::out | ios::binary);
	// is empty?
	input_file.seekg(0, ios::end);
	if (input_file.tellg() == 0) {
		cout << "empty\n";
		return;
	}
	input_file.seekg(0, ios::beg);

	// Analyse input file, <char, times>
	map<uint8_t, uint32_t> stat;
	com_AnalyseInputfile(input_file, stat);
	unsigned int total_length = 0;
	for (auto& i:stat)
		total_length += i.second;
	cout << "\ntotla length:\n" << total_length << endl;
	
	// write total length
	output_file.write(reinterpret_cast<char*>(&total_length), sizeof(unsigned int));

	// save nodes to a vector, save_node[0] not use
	int n = stat.size();
	vector<Node> save_node(2*n);
	int temp_pos = 1;
	save_node[0].ch = 0;
	save_node[0].times = 0;
	for (auto& i:stat) {
		save_node[temp_pos].ch = i.first;
		save_node[temp_pos].times = i.second;
		save_node[temp_pos].left = NULL;
		save_node[temp_pos].right = NULL;
		temp_pos++;
	}
	cout << "\nsave_node:\n";
	for (auto& i:save_node) {
		cout << int(i.ch) << "    " << i.times << endl;
	}
	cout << endl;

	// create a huffman tree
	vector<Node*> minvec;
	for(int i = 1; i <= n; i++) { 
		minvec.push_back(&save_node[i]);
	}
	for(int i = n+1; i <= 2*n-1; i++) {
		Node* min_node_1 = com_DeleteMin(minvec);
		Node* min_node_2 = com_DeleteMin(minvec);
		save_node[i].left = min_node_1;
		save_node[i].right = min_node_2;
		save_node[i].ch = 0;
		save_node[i].times = min_node_1->times + min_node_2->times;
		minvec.push_back(&save_node[i]);
	}
	Node* root = &save_node[save_node.size()-1];

	// write head in
	map<uint8_t, string> ch_to_bits;
	string bits_stack = "";
	com_WriteTree(output_file, root, 0, ch_to_bits, bits_stack);

	cout << "compress map:\n";
	for (auto& i:ch_to_bits) {
		cout << int(i.first) << " : " << i.second << endl;
	}
	cout << endl;
	
	// write body in
	char ch;
	string bits = "";
	input_file.close();
	input_file.open(inputFilename, ios::in | ios::binary);
	cout << "write row body:\n";
	while(input_file.get(ch)) {
		bits += ch_to_bits[ch];
		cout << ch_to_bits[ch];
		

		while(bits.length() >= 8) {
			cout << "\n";
			bitset<8> temp(bits.substr(0, 8));
			if (bits.length() == 8)
				bits = "";
			else
				bits = bits.substr(8);
			uint8_t temp_int8 = uint8_t(temp.to_ulong());
			output_file.write(reinterpret_cast<char*>(&temp_int8), 1);
		}
	}
	cout << endl << endl;
	if (bits != "") {
		bits += "0000000";
		bitset<8> temp(bits.substr(0, 8));
		uint8_t temp_int8 = uint8_t(temp.to_ulong());
		output_file.write(reinterpret_cast<char*>(&temp_int8), sizeof(uint8_t));
		bits = "";
	}

	input_file.close();
	output_file.close();
}


void dec_ReadTree(map<string, uint8_t>& bits_to_ch, string& now, fstream& input_file, vector<Read_Node>& save_read_node, Read_Node* node) {
	
	uint16_t temp;
	input_file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
	if ((temp & 0xff00) == 0) {
		bits_to_ch[now] = uint8_t(temp & 0x00ff);
		now.pop_back();
		return;
	}
	else if (temp == 0x1100) {
		Read_Node root;
		Read_Node left;
		Read_Node right;
		save_read_node.push_back(root);
		save_read_node.push_back(left);
		save_read_node.push_back(right);
		save_read_node[0].left = &save_read_node[1];
		save_read_node[0].right = &save_read_node[2];
		now += "0";
		dec_ReadTree(bits_to_ch, now, input_file, save_read_node, &save_read_node[1]);
		now += "1";
		dec_ReadTree(bits_to_ch, now, input_file, save_read_node, &save_read_node[2]);
		return;
	}
	else {
		Read_Node left;
		Read_Node right;
		save_read_node.push_back(left);
		save_read_node.push_back(right);
		node->left = &save_read_node[save_read_node.size()-2];
		node->right = &save_read_node[save_read_node.size()-1];
		int save_left = save_read_node.size()-2;
		int save_right = save_read_node.size()-1;
		now += "0";
		dec_ReadTree(bits_to_ch, now, input_file, save_read_node, &save_read_node[save_left]);
		now += "1";
		dec_ReadTree(bits_to_ch, now, input_file, save_read_node, &save_read_node[save_right]);
		now.pop_back();
		return;
	}
}




void decompress(string inputFilename, string outputFilename) {
	fstream input_file(inputFilename, ios::in | ios::binary);
	fstream output_file(outputFilename, ios::out | ios::binary);
	// is empty ?
	input_file.seekg(0, ios::end);
	if (input_file.tellg() == 0) {
		cout << "empty\n";
		return;
	}
	input_file.seekg(0, ios::beg);
	// read head
	uint32_t total_length = 0;
	input_file.read(reinterpret_cast<char*>(&total_length), sizeof(uint32_t));
	map<string, uint8_t> bits_to_ch;
	string now = "";
	vector<Read_Node> save_read_node;
	dec_ReadTree(bits_to_ch, now, input_file, save_read_node, NULL);
	
	cout << "\ntotal length:\n" << total_length << endl;
	cout << "\nread tree:\n";
	for (auto& i : bits_to_ch)
		cout << i.first << "\t" << int(i.second) << endl;
	cout << endl;

	// write
	string compare = "";
	string buf = "";
	uint32_t find_length = 0;
	while(true) {
		if (buf.length() == 0) {
			uint8_t get_char;
			input_file.read(reinterpret_cast<char*>(&get_char), sizeof(uint8_t));
			bitset<8> get_bits(get_char);
			buf += get_bits.to_string();
		}
		if (bits_to_ch.find(compare) != bits_to_ch.end()) {	// find it
			output_file.write(reinterpret_cast<char*>(&(bits_to_ch[compare])), sizeof(uint8_t));
			output_file.flush();
			compare = "";
			find_length++;
			if (find_length == total_length)
				break;
		}
		else {	// not find
			compare += buf[0];
			if (buf.length() == 1)
				buf = "";
			else
				buf = buf.substr(1);
		}
	}
	cout << endl;

	input_file.close();
	output_file.close();
}

void useage(string prog) {
	cerr << "Useage: " << endl
		<< "    " << prog << "[-d] input_file output_file" << endl;
	exit(2);
}

int main(int argc, char* argv[]) {
	int i;
	string inputFilename, outputFilename;
	bool isDecompress = false;
	for (i = 1; i < argc; i++) {
		if (argv[i] == string("-d")) isDecompress = true;
		else if (inputFilename == "") inputFilename = argv[i];
		else if (outputFilename == "") outputFilename = argv[i];
		else useage(argv[0]);
	}
	if (outputFilename == "") useage(argv[0]);
	if (isDecompress) decompress(inputFilename, outputFilename);
	else compress(inputFilename, outputFilename);
	return 0;
}
