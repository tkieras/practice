#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <list>

using namespace std;


set<int> make_set(string filepath) {
	set<int> int_set = set<int>();

	fstream infile(filepath, fstream::in);

	int value;
	while(infile >> value) {
		int_set.insert(value);
	}
	infile.close();
	return int_set;

}

list<int> find_pair(set<int> data, int target_sum) {

	list<int> result;

	for(int i : data) {
		int complement = target_sum - i;
		if(data.count(complement) == 1) {
			result.push_back(i); 
			result.push_back(complement);
			return result;
		}
	}

	return result;
}

list<int> find_triplet(set<int> data, int target_sum) {

	list<int> result;

	for(int i : data) {
		int complement = target_sum - i;

		list<int> subresult = find_pair(data, complement);
		if(subresult.size() == 2){
			result.push_back(i);
			result.merge(subresult);
			return result;
		}
	}
	return result;
}

int main() {
	

	list<int> result = find_pair(make_set("input.txt"), 2020);

	int sum = 0;
	long product = 1;
	for(int i : result) {
		sum += i;
		product *= i;
		cout << i << " "; 
	}
	cout<<"-->"<<sum<<"---->"<<product<<endl;

	result = find_triplet(make_set("input.txt"), 2020);
	sum = 0;
	product = 1;
	for(int i : result) {
		sum += i;
		product *= i;
		cout << i << " "; 
	}
	cout<<"-->"<<sum<<"---->"<<product<<endl;
	
	return 0;
}
