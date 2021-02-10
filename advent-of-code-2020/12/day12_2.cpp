#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Point{
	int x;
	int y;

	Point(): x{0}, y{0}{};

	Point(int n_x, int n_y): x{n_x}, y{n_y}{};

	Point(const Point& p): x{p.x}, y{p.y}{};
};

Point operator+(const Point& p1, const Point& p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}


Point move_waypoint(const Point& waypoint, char c, int m) {
	Point new_waypoint(waypoint);

	int iter = m / 90;

	switch(c) {
		case 'N':
			new_waypoint.y += m;
			break;
		case 'S':
			new_waypoint.y -= m;
			break;
		case 'E':
			new_waypoint.x += m;
			break;
		case 'W':
			new_waypoint.x -= m;
			break;
		case 'L':
			iter *= 3;
			// INTENTIONAL FALL THROUGH		
		case 'R':
			for(int i=0; i < iter; i++) {
				int tmp_x = new_waypoint.x;
				new_waypoint.x = new_waypoint.y;
				new_waypoint.y = -tmp_x;
			}
			break;
	}

	return new_waypoint;
}

int main() {

	Point ship;

	Point waypoint(10,1);

	fstream infile("input.txt", fstream::in);

	string command;
	char c;
	int m;
	
	while(infile >> command) {
		c = command[0];
		m = stoi(command.substr(1, string::npos));
		cout << "c: " << c << " m: " << m << endl;
	
		if(c == 'F') {
			for(int i=0; i < m; i++) {
				ship = ship + waypoint;
			}
		}else {
			waypoint = move_waypoint(waypoint, c, m);
		}
		cout << "ship x: " <<ship.x<<" ship.y: " <<ship.y<<endl;
		cout << "waypoint x: " <<waypoint.x<<" waypoint.y: " <<waypoint.y<<endl;
	}

	
	cout << "Manhattan distance from origin: " << abs(ship.x) + abs(ship.y) << endl;

	infile.close();
	return 0;
}
