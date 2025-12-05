#include <bits/stdc++.h>

using namespace std;

struct Range {
    long long start;
    long long end;
};

bool comparator(const Range& a, const Range& b) {
    return a.start < b.start;
}

int main() {
    ifstream inputFile("input.txt");
    vector<Range> ranges;
    string line;

    while (getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.empty()) {
            break;
        }

        size_t dashPos = line.find('-');
        if (dashPos != string::npos) {
            long long start = stoll(line.substr(0, dashPos));
            long long end = stoll(line.substr(dashPos + 1));
            ranges.push_back({start, end});
        }
    }
    inputFile.close();

    sort(ranges.begin(), ranges.end(), comparator);

    long long sum = 0;
    
    long long currentStart = ranges[0].start;
    long long currentEnd = ranges[0].end;

    for (size_t i = 1; i < ranges.size(); ++i) {
        if (ranges[i].start <= currentEnd + 1) {
            if (ranges[i].end > currentEnd) {
                currentEnd = ranges[i].end;
            }
        } else {
            sum += (currentEnd - currentStart + 1);

            currentStart = ranges[i].start;
            currentEnd = ranges[i].end;
        }
    }

    sum += (currentEnd - currentStart + 1);

    cout << "Total: " << sum << endl;

    return 0;
}