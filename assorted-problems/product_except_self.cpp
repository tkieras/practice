#include <iostream>
#include <vector>


using namespace std;


vector<int> simple(const vector<int>& data){
	vector<int> result;
	long product = 1;
	for(auto v: data) {
		product *= v;
	}

	for(auto v: data){
		result.push_back(product / v);
	}

	return result;
}

vector<int> improved(const vector<int>& data){
	vector<int> tmp(data.size(), 1);
	for(int i=1; i < data.size(); i++){
		tmp[i] = tmp[i-1] * data[i-1];
	}
	
	int acc = 1;

	for(int i=data.size()-1; i >= 0; i--){
		tmp[i] = tmp[i]*acc;
		acc = acc*data[i];
	}
	return tmp;
}

int recursive_in_place(vector<int>& data, int left, int i) {
	if(i==data.size()){
		return 1;
	}

	int curr = data[i];

	int right = recursive_in_place(data, left*curr, i+1);

	data[i] = left*right;

	return curr * right;

}

int main() {
	vector<int> data{1,5,3,6,7,8,2,4,9};
//	vector<int> data{1,2,3,4};

	auto simple_result = simple(data);

	for(auto v : simple_result){
		cout << v << " ";
	}
	cout << "\n";
	
	auto improved_result = improved(data);

	for(auto v: improved_result) {
		cout << v << " ";
	}
	cout << "\n";
	
	recursive_in_place(data, 1, 0);

	for(auto v : data) {
		cout << v << " ";
	}
	cout << "\n";
	return 0;
}
