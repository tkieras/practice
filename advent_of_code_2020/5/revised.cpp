#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <limits>

using namespace std;

map<char, char> row_map {{'F','0'}, {'B','1'}};
map<char, char> col_map {{'L','0'}, {'R','1'}};

string map_string(map<char, char> m, string s) {
	for(int i=0; i < s.size(); i++) {
		s[i] = m[s[i]];
	}
	return s;
}

int main() {
	
	fstream infile("input.txt", fstream::in);

	string line;

	set<int> seat_ids;

	int max_seat_id = 0;
	float min_seat_id = numeric_limits<float>::infinity();

	while(infile >> line) {
		string substr_row = map_string(row_map, line.substr(0, 7));
		string substr_col = map_string(col_map, line.substr(7, 3));
		
		int row_id = stoi(substr_row, nullptr, 2);
		int col_id = stoi(substr_col, nullptr, 2);
		
		int seat_id = ((row_id * 8) + col_id);
		max_seat_id = max(max_seat_id, seat_id);
		min_seat_id = min(min_seat_id, float(seat_id));
		seat_ids.insert(seat_id); 
	}

	infile.close();

	cout << "max seat id: " << max_seat_id << endl;
	cout << "min seat id: " << min_seat_id << endl;


	for(int i = min_seat_id; i < max_seat_id; i++) {
		if(!seat_ids.count(i) & seat_ids.count(i-1) & seat_ids.count(i+1)) {
			cout << "Missing seat (with neighbors present): " << i << endl;
		}
	}
	return 0;
}