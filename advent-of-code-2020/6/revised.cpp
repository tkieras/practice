#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


vector<string> get_entries(string filepath) {
	fstream infile(filepath, fstream::in);

	vector<string> entries;
	stringstream entry_buffer;
	string line;
	while(getline(infile, line)) {
		if( line.size() == 0 ){
			entries.push_back(entry_buffer.str());
			
			entry_buffer.str("");
		} else {
			entry_buffer << ' ' << line;
		}

	}

	infile.close();

	return entries;
}



int main() {
	
	vector<string> entries = get_entries("input.txt");

	int total_group_counts = 0;
	int total_unanimous = 0;

	for(auto e: entries) {
		// cout << e << endl;
		map<char, int> entry_tally;
		int group_size = 0;
		int group_unanimous = 0;


		stringstream entry(e);
		string response;
		while(entry >> response) {
			// cout << response << "|";
			group_size += 1;
			char c;
			stringstream response_stream(response);
			while(response_stream >> c) {
				entry_tally[c]++;
			}
		}
		// cout << endl;
		// cout << "group size: " << group_size << endl;

		for(auto e : entry_tally) {
			// cout << e.first << ":" << e.second << endl;
			group_unanimous += (e.second == group_size);
		}
		
		total_group_counts += entry_tally.size();
		total_unanimous += group_unanimous;

		// cout << "part 1: " <<entry_tally.size()<<endl;
		// cout << "part 2: " << group_unanimous << endl;

		// cout << "--- END ENTRY ---" << endl;
	}

	cout << "part 1: " << total_group_counts << endl;
	cout << "part 2: " << total_unanimous << endl;
	return 0;
}