#include <bits/stdc++.h>

using namespace std;

struct Range {
    long long start;
    long long end;
};

bool isFresh(long long id, const vector<Range>& ranges) {
    for (const auto& r : ranges) {
        if (id >= r.start && id <= r.end) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    vector<Range> ranges;
    string line;
    
    bool readingRanges = true;
    int sum = 0;

    while (getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        if (line.empty()) {
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            size_t dashPos = line.find('-');
            if (dashPos != string::npos) {
                long long start = stoll(line.substr(0, dashPos));
                long long end = stoll(line.substr(dashPos + 1));
                ranges.push_back({start, end});
            }
        } else {
            long long id = stoll(line);
            
            if (isFresh(id, ranges)) {
                sum++;
            }
        }
    }

    inputFile.close();

    cout << "Total: " << sum << endl;

    return 0;
}