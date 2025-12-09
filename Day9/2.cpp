#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x;
    long long y;
};

bool is_between(double v, double min_v, double max_v) {
    return v > min_v && v < max_v;
}

bool intervals_overlap(double a1, double a2, double b1, double b2) {
    return max(a1, b1) < min(a2, b2);
}

bool is_point_in_polygon(double px, double py, const vector<Point>& poly) {
    bool inside = false;
    size_t n = poly.size();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        if (((poly[i].y > py) != (poly[j].y > py)) &&
            (px < (poly[j].x - poly[i].x) * (py - poly[i].y) / (double)(poly[j].y - poly[i].y) + poly[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}

bool is_on_boundary(double px, double py, const vector<Point>& poly) {
    size_t n = poly.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;

        if (poly[i].x == poly[j].x && abs(px - poly[i].x) < 0.001) {
            double min_y = min(poly[i].y, poly[j].y);
            double max_y = max(poly[i].y, poly[j].y);
            if (py >= min_y && py <= max_y) return true;
        }
        else if (poly[i].y == poly[j].y && abs(py - poly[i].y) < 0.001) {
            double min_x = min(poly[i].x, poly[j].x);
            double max_x = max(poly[i].x, poly[j].x);
            if (px >= min_x && px <= max_x) return true;
        }
    }
    return false;
}

int main() {
    ifstream file("input.txt");
    vector<Point> poly;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        replace(line.begin(), line.end(), ',', ' ');
        long long x, y;
        if (sscanf(line.c_str(), "%lld %lld", &x, &y) == 2) {
            poly.push_back({x, y});
        }
    }
    file.close();

    size_t n = poly.size();
    long long max_area = 0;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            
            long long left = min(poly[i].x, poly[j].x);
            long long right = max(poly[i].x, poly[j].x);
            long long top = min(poly[i].y, poly[j].y);
            long long bottom = max(poly[i].y, poly[j].y);

            long long width = (right - left) + 1;
            long long height = (bottom - top) + 1;
            long long area = width * height;

            if (area <= max_area) continue;
          
            bool is_valid = true;

            for (size_t k = 0; k < n; ++k) {
                size_t next_k = (k + 1) % n;
                Point p1 = poly[k];
                Point p2 = poly[next_k];

                if (p1.x == p2.x) {
                    if (p1.x > left && p1.x < right) {
                        if (intervals_overlap(min(p1.y, p2.y), max(p1.y, p2.y), top, bottom)) {
                            is_valid = false;
                            break;
                        }
                    }
                }
                else if (p1.y == p2.y) {
                    if (p1.y > top && p1.y < bottom) {
                        if (intervals_overlap(min(p1.x, p2.x), max(p1.x, p2.x), left, right)) {
                            is_valid = false;
                            break;
                        }
                    }
                }
            }

            if (!is_valid) continue;

            double center_x = (left + right) / 2.0;
            double center_y = (top + bottom) / 2.0;

            bool center_inside = is_point_in_polygon(center_x, center_y, poly);
            
            if (!center_inside) {
                if (!is_on_boundary(center_x, center_y, poly)) {
                    is_valid = false;
                }
            }

            if (is_valid) {
                max_area = area;
            }
        }
    }

    cout << "Area: " << max_area << endl;

    return 0;
}