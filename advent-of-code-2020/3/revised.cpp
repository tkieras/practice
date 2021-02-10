#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const char TREE_CHAR = '#';

typedef vector<vector<bool>> grid;


grid read_file(string path) {
	grid result;

	fstream infile(path, fstream::in);
	string line;
	
	while(infile >> line) {
		vector<bool> line_list;
		for(char c : line) {
			line_list.push_back(c == TREE_CHAR);
		}
		result.push_back(line_list);
	}
	return result;
}


int evaluate_slope(grid g, pair<int, int> slope) {
	int m = g[0].size();

	int count_trees_on_slope = 0;

	int x = 0;
	for(int y = 0; y < g.size(); y+=slope.second) {
		count_trees_on_slope += g[y][x % m];
		x += slope.first;
	}
	return count_trees_on_slope;
}

int main() {
	
	grid g = read_file("input.txt");

	vector<pair<int,int>> slopes{ make_pair(1,1), 
								  make_pair(3,1),
								  make_pair(5,1),
								  make_pair(7,1),
								  make_pair(1,2)};

	long total_product = 1;

	for(auto s: slopes) {
		total_product *= evaluate_slope(g, s);
	}
	cout << total_product << endl;
	return 0;
}