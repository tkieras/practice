#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

typedef enum{N,E,S,W} dir;

dir apply_dir(dir current, char c, int m) {

	int iter = m / 90;
	
	if(c == 'L') {
		iter *= 3;
	}

	if(c == 'R' || c == 'L') {
		int new_dir = (current + iter) % 4;
		return static_cast<dir>(new_dir);
	} 
	
	return current;
}

char regularize(dir d, char c) {
	if (c=='F') {
		return "NESW"[d];
	}

	return c;
}

int apply_move_x(char c, int m){
	if(c == 'E'){
		return m;
	} else if(c == 'W') {
		return -m;
	}
	return 0;
}
int apply_move_y(char c, int m){
	if(c == 'N'){ 
		return m;
	} else if(c == 'S'){
		return -m;
	}

	return 0;

}
int main() {

	dir d = E;

	int x = 0;
	int y = 0;

	fstream infile("input.txt", fstream::in);

	string command;
	char c;
	int m;
	
	while(infile >> command) {
		c = command[0];
		m = stoi(command.substr(1, string::npos));
		cout << "c: " << c << " m: " << m << endl;
		d = apply_dir(d, c, m);
	//	cout << d << endl;
		c = regularize(d, c);
	//	cout << c << endl;
		x += apply_move_x(c, m);
		y += apply_move_y(c, m);
		cout << "x: " << x << " y: " << y << endl;
	}

	
	//cout << apply_dir(W, 'L', 90) << endl;
	cout << "Manhattan distance from origin: " << abs(x) + abs(y) << endl;
	infile.close();
	return 0;
}
