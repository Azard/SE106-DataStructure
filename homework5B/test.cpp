#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#define CORRECT_TEST_ELE 10
#define PERFORMANCE_ELE 200000
#define PERFORMANCE_STEP 1000
#define SAME_TEST_TIMES 10
using namespace std;

vector<int> generate_int(int num)
{
	vector<int> raw_array;
	srand(time(0));
	for (int i=0; i<num; i++)
		raw_array.push_back(rand()<<16 | rand());
	return raw_array;
}

void merge_sort(vector<int>& vec)
{
	int n = vec.size();
	if (n <= 1) return;
	vector<int> v1;
	vector<int> v2;
	for (int i=0; i<n; i++)
		(i < n/2) ? v1.push_back(vec[i]) : v2.push_back(vec[i]);
	vec.clear();
	merge_sort(v1);
	merge_sort(v2);
	int n1 = v1.size();
	int n2 = v2.size();
	int p1 = 0;
	int p2 = 0;
	while (p1<n1 && p2<n2)
		(v1[p1] < v2[p2]) ? vec.push_back(v1[p1++]) : vec.push_back(v2[p2++]);
	while (p1<n1) vec.push_back(v1[p1++]);
	while (p2<n2) vec.push_back(v2[p2++]);
}


void quick_sort(vector<int>& vec, int begin, int end)
{
	int length = end-begin+1;
	if (length <= 1) return;
	int pivot = vec[end];
	int less_index = begin;
	for (int index = begin; index < end; ++index) {
		if (vec[index] < pivot) {
			int temp = vec[less_index];
			vec[less_index] = vec[index];
			vec[index] = temp;
			less_index ++;
		}
	}
	vec[end] = vec[less_index];
	vec[less_index] = pivot;
	if (less_index == begin)
		quick_sort(vec, begin + 1, end);
	else if (less_index == end)
		quick_sort(vec, begin, end - 1);
	else {
		quick_sort(vec, begin, less_index-1);
		quick_sort(vec, less_index + 1, end);
	}
}

int main()
{
//=====================SPEED========================
/*	
	cout << "\nMerge Sort:" << endl;
	for (int i=PERFORMANCE_STEP; i<=PERFORMANCE_ELE; i+=PERFORMANCE_STEP) {
		time_t time_count = 0;
		for (int j = 0; j < SAME_TEST_TIMES; ++j) {
			vector<int> raw_array = generate_int(i);
			time_t start = clock();
			merge_sort(raw_array);
			time_t end = clock();
			time_count += (end-start);
		}
		cout << time_count/SAME_TEST_TIMES << endl;
	}

	cout << "\nQuick Sort:" << endl;
	for (int i=PERFORMANCE_STEP; i<=PERFORMANCE_ELE; i+=PERFORMANCE_STEP) {
		time_t time_count = 0;
		for (int j = 0; j < SAME_TEST_TIMES; ++j) {
			vector<int> raw_array = generate_int(i);
			time_t start = clock();
			quick_sort(raw_array, 0, raw_array.size());
			time_t end = clock();
			time_count += (end-start);
		}
		cout << time_count/SAME_TEST_TIMES << endl;
	}
*/
//================CORRECTNESS====================
	cout << "Show correctness:\n\n";
	cout << "Before sort:\n";
	vector<int> raw_array = generate_int(CORRECT_TEST_ELE);
	for (int i = 0; i < CORRECT_TEST_ELE; i++)
		cout << raw_array[i] << endl;
	cout << "\nAfter merge sort:\n";
	vector<int> save_array = raw_array;
	merge_sort(raw_array);
	for (int i = 0; i < CORRECT_TEST_ELE; i++)
		cout << raw_array[i] << endl;
	raw_array = save_array;
	cout << "\nAfter quick sort:\n";
	quick_sort(raw_array, 0 , raw_array.size()-1);
	for (int i = 0; i < CORRECT_TEST_ELE; i++)
		cout << raw_array[i] << endl;
	
	cout << "\nChange comment of code to get speed difference\n";
}
