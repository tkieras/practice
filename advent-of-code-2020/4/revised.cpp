#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <regex>
#include <set>

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

map<string, string> parse_entry(string input) {
	map<string, string> entry;

	stringstream input_stream(input);
	string field;
	string key;
	string value;
	while(input_stream >> field) {
		stringstream field_stream(field);
		getline(field_stream, key, ':');
		field_stream >> value;
		entry[key] = value;
	}

	return entry;
}

bool test_four_integers(string s) {
	return regex_match(s, regex("^\\d{4}$"));
}

bool test_integer_range_inclusive(string s, int low, int high) {
	int value = stoi(s);
	return (value <= high & value >= low);
}

bool test_valid_pid(string s) {
	return regex_match(s, regex("^\\d{9}$"));
}

bool test_valid_eyr(string s) {
	return test_four_integers(s) & test_integer_range_inclusive(s, 2020, 2030);
}

bool test_valid_iyr(string s) {
	return test_four_integers(s) & test_integer_range_inclusive(s, 2010, 2020);
}

bool test_valid_byr(string s) {
	return test_four_integers(s) & test_integer_range_inclusive(s, 1920, 2002);
}

bool test_valid_ecl(string s) {
	set<string> valid_ecls = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
	return valid_ecls.count(s);
}

bool test_valid_hcl(string s) {
	return regex_match(s, regex("^#[0-9a-f]{6}$"));
}

bool test_valid_hgt(string s) {
	if (regex_match(s, regex("^\\d{2}in$"))) {
		return test_integer_range_inclusive(s.substr(0,2), 59, 76);
	} else if (regex_match(s, regex("^\\d{3}cm$"))) {
		return test_integer_range_inclusive(s.substr(0,3), 150, 193);
	}
	return false;
}
bool test_valid_cid(string s) {
	return true;
}
using test_fn = bool (*) (string);

map<string, test_fn> tests {
	{"pid", test_valid_pid},
	{"eyr", test_valid_eyr},
	{"iyr", test_valid_iyr},
	{"byr", test_valid_byr},
	{"ecl", test_valid_ecl},
	{"hcl", test_valid_hcl},
	{"hgt", test_valid_hgt},
	{"cid", test_valid_cid}
};

set<string> required_fields = {"pid", "eyr", "iyr", "byr", "ecl", "hcl", "hgt"};

bool test_valid(pair<string, string> item) {

	return tests[item.first](item.second);
}

int main() {
	vector<string> entries = get_entries("input.txt");

	long total_valid_entries = 0;
	long total_entries = 0;

	for (string entry : entries) {
		map<string, string> entry_map = parse_entry(entry);
		cout << " --- BEGIN ENTRY "<<total_entries<<" ---" << endl;
		cout << entry << endl;
		bool valid = true;

		for(auto r : required_fields) {
			valid = valid & (entry_map.count(r) == 1);
		}

		for(auto e : entry_map) {
			valid = valid & test_valid(e);

			cout << '\''<<e.first << "\' --> \'" << e.second << '\'';
			cout << " -----> " << test_valid(e) << endl;

		}
		total_valid_entries += valid;
		total_entries += 1;

		cout << "Valid: " << valid << endl;
		cout << "--- END ENTRY ---" <<endl;

	}

	cout << "Total valid entries: " << total_valid_entries << endl;

	cout << "Total entries: " << total_entries << endl;
}