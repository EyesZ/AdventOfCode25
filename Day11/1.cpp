#include <bits/stdc++.h>
using namespace std;

unsigned long long dfs_count(const string &node,
							 unordered_map<string, vector<string>> &g,
							 unordered_map<string, unsigned long long> &memo,
							 unordered_set<string> &vis) {
	if (node == "out") return 1ULL;
	auto itm = memo.find(node);
	if (itm != memo.end()) return itm->second;
	if (vis.count(node)) {
		return 0ULL;
	}
	vis.insert(node);
	unsigned long long total = 0ULL;
	auto it = g.find(node);
	if (it != g.end()) {
		for (const string &nx : it->second) {
			total += dfs_count(nx, g, memo, vis);
		}
	}
	vis.erase(node);
	memo[node] = total;
	return total;
}

int main() {
	ifstream file("input.txt");
	if (!file) {
		cerr << "input.txt not found" << endl;
		return 1;
	}

	unordered_map<string, vector<string>> graph;
	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;
		size_t p = line.find(':');
		if (p == string::npos) continue;
		string name = line.substr(0, p);
		auto trim = [](string &s){
			size_t a = s.find_first_not_of(" \t\r\n");
			if (a == string::npos) { s.clear(); return; }
			size_t b = s.find_last_not_of(" \t\r\n");
			s = s.substr(a, b-a+1);
		};
		trim(name);

		string rest = (p+1 < line.size()) ? line.substr(p+1) : string();
		trim(rest);
		vector<string> outs;
		if (!rest.empty()) {
			stringstream ss(rest);
			string tok;
			while (ss >> tok) {
				trim(tok);
				if (!tok.empty()) outs.push_back(tok);
			}
		}
		graph[name] = outs;
	}
	file.close();

	unordered_map<string, unsigned long long> memo;
	unordered_set<string> visiting;
	unsigned long long paths = dfs_count("you", graph, memo, visiting);

	cout << "Paths: " << paths << endl;
	return 0;
}