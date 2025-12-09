#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x;
    long long y;
};

int main() {
    ifstream file("input.txt"); 
    vector<Point> points;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        replace(line.begin(), line.end(), ',', ' ');

        long long x, y;
        if (sscanf(line.c_str(), "%lld %lld", &x, &y) == 2) {
            points.push_back({x, y});
        }
    }
    file.close();

    long long max_area = 0;
    size_t n = points.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            
            long long width = abs(points[i].x - points[j].x) + 1;
            long long height = abs(points[i].y - points[j].y) + 1;

            long long area = width * height;

            if (area > max_area) {
                max_area = area;
            }
        }
    }

    cout << "Area: " << max_area << endl;

    return 0;
}