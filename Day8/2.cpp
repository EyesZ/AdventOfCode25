#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y, z;
    int id;
};

long long distSq(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

struct Edge {
    int u, v;
    long long d;
    bool operator<(const Edge& other) const {
        return d < other.d;
    }
};

struct DSU {
    vector<int> parent;
    vector<long long> size;
    int num_components;

    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
        num_components = n;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            num_components--;
            return true;
        }
        return false;
    }
};

int main() {
    ifstream cin("input.txt");
    string line;
    vector<Point> points;
    int id = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        for (char &c : line) if (c == ',') c = ' ';
        stringstream ss(line);
        long long x, y, z;
        ss >> x >> y >> z;
        points.push_back({x, y, z, id++});
    }

    vector<Edge> edges;
    int n = points.size();
    edges.reserve((long long)n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({i, j, distSq(points[i], points[j])});
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            if (dsu.num_components == 1) {
                cout << points[edge.u].x * points[edge.v].x << endl;
                break;
            }
        }
    }

    return 0;
}
