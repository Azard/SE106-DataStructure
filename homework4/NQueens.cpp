// se106/homework4
// Name:熊伟伦 ID:5120379076

#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

int N = 0;
int total = 0;

bool can_set(char grid[10][10], int x, int y)
{
	for (int i = 0; i < N; i++)
		if (grid[y][i] == 'Q' || grid[i][x] == 'Q')
			return false;
	for (int i = -N+1; i < N; i++) {
		if (x+i >=0 && x+i<N && y+i>=0 && y+i<N && grid[y+i][x+i] == 'Q')
			return false;
		if (x+i >=0 && x+i<N && y-i>=0 && y-i<N && grid[y-i][x+i] == 'Q')
			return false;
	}
	return true;
}

void print_grid(char  grid[10][10])
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++)
			cout << grid[y][x];
		cout << endl;
	}
	cout << endl;
}

bool cal_Queens(char grid[10][10], int now_col)
{
	if (now_col == N) {
		print_grid(grid);
		total++;
		for (int i = 0; i < N; i++)
			grid[i][now_col-1] = '.';
		return true;
	}
	for (int i = 0; i < N; i++) {
		if (can_set(grid, now_col, i)) {
			grid[i][now_col] = 'Q';
			cal_Queens(grid, now_col+1);
			grid[i][now_col] = '.';
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (argc != 2 || !isdigit(*argv[1])) {
		cout << "Please enter a number argv" << endl;
		return 0;
	}
	N = atoi(argv[1]);
	if (N < 4 || N > 10 ) {
		cout << "Range between 4 to 10" << endl;
		return 0;
	}
	char grid[10][10];
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			grid[y][x] = '.';
	cal_Queens(grid, 0);
	cout << total << " in total." << endl;
	return 0;
}
