#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <utility>

using namespace std;

typedef enum{OCCUPIED, EMPTY, FLOOR} state;
typedef pair<int, int> node;
typedef vector<vector<state>> grid;


const map<char, state> CHAR_MAP{{'L', EMPTY},{'#', OCCUPIED}, {'.', FLOOR}};
const map<state, char> STATE_MAP{{EMPTY, 'L'}, {OCCUPIED, '#'}, {FLOOR, '.'}};

grid read_input(string filepath){
	fstream infile(filepath, fstream::in);

	grid data;
	string line;

	while(getline(infile, line)) {
		vector<state> line_data;
		for(auto c : line) {
			state c_state = CHAR_MAP.at(c);			
			line_data.push_back(c_state);
		}
		data.push_back(line_data);
	}

	infile.close();

	return data;
}


void print_data(const grid& data) {

	for(auto l : data) {

		for(auto c : l) {
			cout<<STATE_MAP.at(c);
		}
		cout<<endl;
	}
	cout<<endl;
}

bool in_range(const grid& data, node n) {
	
	if(n.first < 0 || n.second < 0) {
		return false;
	}
	if(n.first >= data.size() || n.second >= data[0].size()){
		return false;
	}
	return true;
}

vector<node> get_neighbors(grid data, node n) {

	vector<node> neighbors;
	for(int y : {-1,0,1}) {
		for(int x : {-1,0,1}){
			if(x == 0 & y == 0) {
				continue;
			}
			node neighbor{n.first + y, n.second + x};
			if(in_range(data, neighbor)) {
				neighbors.push_back(neighbor);
			}
		}
	}
	return neighbors;
}

int count_neighbors(const grid& data, node n) {
	int count = 0;
	for(auto nbr : get_neighbors(data, n)) {
		count += (data[nbr.first][nbr.second] == OCCUPIED);
	}
	return count;
}


int count_visible(const grid& data, node n) {

	vector<node> t{ {-1,-1},{-1,0},{-1,1},
			{0,-1},{0,1},
			{1,-1},{1,0},{1,1}};

	int count = 0;

	for(auto d : t){

		node visible{n.first+d.first, n.second+d.second};
		while(in_range(data, visible) && data[visible.first][visible.second] == FLOOR){
			visible = {visible.first+d.first, visible.second+d.second};
		}
		if(in_range(data, visible) && data[visible.first][visible.second] == OCCUPIED){
			count++;
		}
	}

	return count;
}


state mutate(const grid& data, node n) {
	//part 1
	int count = count_neighbors(data, n);
	int upper_thresh = 4;

	//part 2
	// int count = count_visible(data, n);
	// int upper_thresh = 5;

	// both parts
	state result = data[n.first][n.second];
	if(count == 0 & data[n.first][n.second] == EMPTY) {
		result = OCCUPIED;
	} else if(count >= upper_thresh && data[n.first][n.second] == OCCUPIED) {
		result = EMPTY;
	}

	return result;
}

grid step(const grid& data) {
	grid next;

	for(int y=0; y < data.size(); y++) {
		vector<state> row;
		for(int x=0; x < data[0].size(); x++) {
			row.push_back(mutate(data, {y,x}));
	 	}
		next.push_back(row);
	}
	return next;	
}

bool equilibrium(const grid& d1, const grid& d2) {
	bool result = true;

	for(int i=0; i < d1.size(); i++) {
		result = result & (d1[i] == d2[i]);
	}
	return result;
}
int main() {

	auto data = read_input("input.txt");
	print_data(data);

	auto next = step(data);
	int count = 1;
	while(!equilibrium(data, next)) {
		print_data(next);
		data = next;
		next = step(data);
		count++;
	}

	int occupied_seats = 0;
	for(auto l : next) {
		for(auto c: l) {
			occupied_seats += (c == OCCUPIED);
		}
	}

	cout << "--- iteration count: " <<count << " ---\n";
	cout << "+++ occupied seat count: "<<occupied_seats<< " +++\n";
	print_data(next);
	
	return 0;
}
