#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

long top_down_count(const vector<int>& data, vector<long>& mem, int idx) {
	// base case: our index has reached the end.
	// There is only one combination here.
	if(idx == data.size()-1) {
		return 1;
	}
	// Memoized short-cut.
	if(mem[idx] >= 0) {
		return mem[idx];
	}
	// Recursively try the next three values and add their counts.
	long count = 0;
	for(int inc : {1,2,3}){
		int n_idx = idx + inc;
		if(n_idx < data.size() & data[n_idx] <= data[idx]+3){
			count += top_down_count(data, mem, n_idx);
		}
	}
	// Memoize the count for future use.
	mem[idx] = count;
	return count;
}

long bottom_up_count(const vector<int>& data) {
	// Declare our memory vector, same length as data
	// Must be long to avoid overflow
	// This array stores the number of combinations possible ...
	// for the subarray of data starting at each index
	vector<long> mem(data.size());

	// We'll build off of this last value.
	// There's only one combination possible starting at the last value.
	mem[data.size()-1] = 1;
	
	// Working backwards from second-to-last until first values
	for(int i = data.size()-2; i >= 0; i--) {
		long count = 0;
		
		// Try each of the next three values
		for(int inc : {1,2,3}) {
			int n_idx = i+inc;
			// If its a valid index and within the range, get its
			// value from data and add it to count.
			if(n_idx < data.size() & data[n_idx] <= data[i] + 3) {
				count += mem[n_idx];
			}
		}
		// Store the count for future use as we work backwards.
		mem[i] = count;
	}
	// The first element holds the requested value.
	return mem[0];
}

void print_greedy_intervals(const vector<int>& data) {
	int count_one = 0;
	int count_two = 0;
	int count_three = 0;

	int prev = data.front();
	for(int i=1; i < data.size(); i++){
		if(data[i] == prev + 1) {
			count_one++;
		}else if(data[i] == prev + 3) {
			count_three++;
		}else if(data[i] == prev + 2) {
			count_two++;
		} else {
			cout << "Error at " << i << endl;
		}
		prev = data[i];

	}
	cout << "intervals:\t1\t3\n ";
        cout << "counts: \t"<<count_one<<"\t"<<count_three << endl;
	cout << "product: " << count_one * count_three << endl;
}	


int main() {

	fstream infile("input.txt", fstream::in);

	int d;
	vector<int> data;
	while(infile >> d) {
		data.push_back(d);
	}
	infile.close();

	data.push_back(0);
	sort(data.begin(), data.end()); 
	data.push_back(data.back()+3);

	print_greedy_intervals(data);

	vector<long> mem(data.size(), -1);
	cout <<"combinations: "<< top_down_count(data, mem, 0) << " (top down)" <<endl;
	cout <<"combinations: "<< bottom_up_count(data) << " (bottom up)" <<endl;
	return 0;
}

