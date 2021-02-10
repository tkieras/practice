#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct line_data {
	int low;
	int high;
	char c;
	string password;
};

bool evaluate_by_count(const line_data& ld) {
	map<char, int> counts;

	for(char x : ld.password) {
		counts[x]++;
	}

	return (counts[ld.c] >= ld.low) & (counts[ld.c] <= ld.high);
}

bool evaluate_by_position(const line_data& ld) {

	return (ld.password[ld.low-1] == ld.c) != (ld.password[ld.high-1] == ld.c);
}


line_data parse_line_data(string input) {

	line_data ld;
	stringstream ss(input);

	ss >> ld.low;
	ss.ignore(1, '-');
	ss >> ld.high;
	ss >> ld.c;
	ss.ignore(1, ':');
	ss >> ld.password;

	return ld;
}

void print_line_data(line_data ld) {
	cout << ld.low <<','<<ld.high<<',';
	cout << ld.c <<','<<ld.password<<"\n";
}

int main() {
	
	fstream infile("input.txt", fstream::in);

	string input;
	int total_passing_count_test = 0;
	int total_passing_position_test = 0;

	while(getline(infile, input)) {
		line_data ld = parse_line_data(input);
		//print_line_data(ld);
		total_passing_count_test += evaluate_by_count(ld);
		total_passing_position_test += evaluate_by_position(ld);
	}
	cout << total_passing_count_test <<endl;
	cout << total_passing_position_test <<endl;

	infile.close();
	return 0;
}