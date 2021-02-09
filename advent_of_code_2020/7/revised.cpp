#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <queue>
#include <unordered_set>

using namespace std;

typedef unordered_map<string, vector<pair<string, int>>> graph;

graph make_graph(string filepath, bool outer_to_inner) {
	ifstream infile(filepath, fstream::in);


	graph g;

	string line;
	
	while(getline(infile, line)) {
		stringstream line_stream(line);
		string line_item;
		vector<string> line_items;
		while(line_stream >> line_item) {
			line_items.push_back(line_item);
		}

		string src = line_items[0] + " " + line_items[1];

		int idx = 4;

		if (line_items[idx] == "no") {
			g[src] = {};
		} else {
			while(idx+3 < line_items.size()) {
				int count = stoi(line_items[idx]);
				string dst = line_items[idx+1] + " " + line_items[idx+2];
				if(outer_to_inner){
					g[dst].push_back({src, count});
				} else {
					g[src].push_back({dst, count});

				}
				idx += 4;
			}
		}
		// for(auto e : g) {
		// 	cout << e.first << " [";
		// 	for(auto adj : e.second) {
		// 		cout << "(" << adj.first << ", " << adj.second << "),";
		// 	}
		// 	cout <<"]\n";
		// }
	}


	infile.close();
	return g;
}


int count_bfs(graph g) {
	queue<string> q;
	q.push("shiny gold");
	

	unordered_set<string> visited;

	while(q.size() > 0) {
		string node = q.front();
		q.pop();
		visited.insert(node);

		for(auto adj : g[node]) {
			if(!visited.count(adj.first)) {
				q.push(adj.first);
			}
		}
	}
	return visited.size() - 1;
}

int count_dfs(graph g, string node) {
	if(!g.count(node)) {
		return 0;
	}

	int count = 0;

	for(auto e : g[node]) {
		count += e.second + (e.second * count_dfs(g, e.first));
	}

	return count;

}

int main() {
	graph g = make_graph("input.txt", true);
	
	cout << count_bfs(g)<<endl;

	g = make_graph("input.txt", false);

	cout << count_dfs(g, "shiny gold")<<endl;

	return 0;
}