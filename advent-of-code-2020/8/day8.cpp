#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

typedef unordered_map<int, unordered_set<int>> graph;
typedef vector<pair<string, int>> program;

program read_program(string filepath);
int run_program(const program& p);

int find_error(const program& p);
bool repair_error(program& p, int error);

unordered_set<int> find_dst_comp(const program& p);
graph make_graph(const program& p);


int main() {

	program p = read_program("input.txt");

	int error = find_error(p);
	
	if(error >= 0) {
		cout << "error in node: " << error << endl;
		if(!repair_error(p, error)) {
			cout << "error conducting repair." << endl;
		}
	}
	
	int acc = run_program(p);
	
	cout << "Final acc value: " << acc << endl;

	return 0;
}


program read_program(string filepath) {
	fstream infile("input.txt", fstream::in);

	program p;
	string op;
	int val;
	
	while(infile >> op >> val) {	
		p.push_back({op, val});
	}

	infile.close();
	return p;
}


int run_program(const program& p) {
	// stops if a cycle is detected or if end node is reached
	
	int acc = 0;
	unordered_set<int> visited;
	int pc = 0;

	while(!(visited.count(pc)) & pc != p.size()) {
		
		visited.insert(pc);

		if(p[pc].first == "jmp") {
			pc += p[pc].second;
		
		} else if(p[pc].first == "acc") {
			acc += p[pc].second;
			pc += 1;
		
		} else {
			pc += 1;
		}
	}

	return acc;
}


int find_error(const program& p) {
	// Returns the first error if an error exists, else -1
	// An error is the id of a node such that:
		// the node is either 'jmp' or 'nop'
		// next(flipped(node)) is in destination_component
		// where flipped(node) changes the op from 'jmp' to 'nop' or vice-versa

	unordered_set<int> dst_comp = find_dst_comp(p);

	// start by preempting the problem of no error

	int pc = 0;

	if(dst_comp.count(pc)) {
		// The start node is in the destination set -> no error.
		return -1;
	}

	unordered_set<int> visited;

	// Loop as long as it hasn't visited this node already
	while(!(visited.count(pc))) {

		visited.insert(pc);

		// Get the alternate next, if this node's op were flipped
		// Return this node's id if the alternate next is in dst_comp
		if(p[pc].first == "jmp") {
			int alt = pc+1;
			if(dst_comp.count(alt)) {
				return pc;
			}
			pc += p[pc].second;
		
		} else if(p[pc].first == "acc") {
			pc += 1;
		} else {
			int alt = pc + p[pc].second;
			if(dst_comp.count(alt)) {
				return pc;
			}
			pc += 1;
		}

	}

	return -1;
}

bool repair_error(program& p, int error) {
	// Flips jmp<->nop of node 'error'

	if(p[error].first == "jmp") {
		p[error] = {"nop", p[error].second};
		return true;
	} else if(p[error].first == "nop") {
		p[error] = {"jmp", p[error].second};
		return true;
	}

	return false;
}


unordered_set<int> find_dst_comp(const program& p) {
	// Find the component that includes the destination node
	// plain vanilla BFS

	graph g = make_graph(p);
	unordered_set<int> dst_comp;

	queue<int> q;

	q.push(g.size()-1); // The id of the 'end' node; 

	while(q.size() > 0) {
		int node = q.front();
		q.pop();

		dst_comp.insert(node);

		for(int adj : g[node]) {
			if(!dst_comp.count(adj)) {
				q.push(adj);
			}
		}
	}
	
	return dst_comp;
}


graph make_graph(const program& p) {
	// Builds an undirected graph representing the program input 
	// The graph leaves out the accumulator values
	// since the graph is only used for BFS and not execution

	// Note it will insert an 'end' node as the 'next' node after the last in program
	graph g;

	for(int i=0; i < p.size(); i++) {
		if(p[i].first == "jmp") {
			int adj = i + p[i].second;
			g[i].insert(adj);
			g[adj].insert(i);
		} else {
			g[i].insert(i + 1);
			g[i+1].insert(i);
		}
	}
	
	return g;
}


