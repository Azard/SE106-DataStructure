#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define TEST_NUM 50
using namespace std;

void radix_sort(float input[], int length)
{
	// positive: sign bit set 0 to 1
	// negative: all bit trans
	// 32bits split into 4 bytes, sort 1 byte 1 time
	for (int i=0; i<length; i++)
		reinterpret_cast<int&>(input[i]) = (reinterpret_cast<int&>(input[i])>>31 & 0x1)? ~reinterpret_cast<int&>(input[i]) : reinterpret_cast<int&>(input[i]) | 0x80000000;
	vector<float> bucket[256];
	for (int i=0; i<4; i++) {
		for (int j=0; j<length; j++)
			bucket[reinterpret_cast<int&>(input[j])>>(i*8) & 0xff].push_back(input[j]);
		int count = 0;
		for (int j=0; j<256; j++) {
			for (int k=0; k<bucket[j].size(); k++)
				input[count++] = bucket[j][k];
			bucket[j].clear();
		}
	}
	// after sort, recover
	for (int i=0; i<length; i++)
		reinterpret_cast<int&>(input[i]) = (reinterpret_cast<int&>(input[i])>>31 & 0x1)? reinterpret_cast<int&>(input[i]) & 0x7fffffff : ~reinterpret_cast<int&>(input[i]);
}

int main()
{
	// generate random pos or nega float number
	cout << "======Before sort======:\n\n";
	float raw_array[TEST_NUM];
	int length = sizeof(raw_array)/sizeof(float);
	srand(time(0));
	for (int i=0; i<length; i++) {
		while(true) {
			int rand_left = rand();
			int rand_num = rand_left<<16 | rand();
			if ((rand_num>>23 & 0xff) != 0xff) {	// except NaN INF -INF
				raw_array[i] = reinterpret_cast<float&>(rand_num);
				break;
			}
		}
		cout << raw_array[i] << endl;
	}
	radix_sort(raw_array, length);
	cout << "\n======After sort======:\n\n";
	for (int i=0; i<length; i++)
		cout << raw_array[i] << endl;
}
