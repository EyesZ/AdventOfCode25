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
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
        }
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
    int limit = min((int)edges.size(), 1000);
    for (int i = 0; i < limit; ++i) {
        dsu.unite(edges[i].u, edges[i].v);
    }

    vector<long long> sizes;
    for(int i=0; i<n; ++i) {
        if(dsu.parent[i] == i) {
            sizes.push_back(dsu.size[i]);
        }
    }

    sort(sizes.rbegin(), sizes.rend());

    long long ans = 1;
    for(int i=0; i<min((int)sizes.size(), 3); ++i) {
        ans *= sizes[i];
    }

    cout << ans << endl;

    return 0;
}
