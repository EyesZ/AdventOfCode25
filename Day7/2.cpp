#include <bits/stdc++.h>

using namespace std;

int main() {

    ifstream inputFile("input.txt");
    vector<string> grid;
    string line;
    int startCol = -1;

    while (inputFile >> line) {
        grid.push_back(line);
        if (startCol == -1) {
            size_t found = line.find('S');
            if (found != string::npos) {
                startCol = static_cast<int>(found);
            }
        }
    }
    inputFile.close();

    int height = grid.size();
    int width = grid[0].size();
    vector<unsigned long long> currentCounts(width, 0);

    if (startCol != -1) {
        currentCounts[startCol] = 1;
    }

    for (int r = 0; r < height; ++r) {
        vector<unsigned long long> nextCounts(width, 0);

        for (int c = 0; c < width; ++c) {
            if (currentCounts[c] > 0) {
                char cell = grid[r][c];

                if (cell == '^') {
                    if (c - 1 >= 0) {
                        nextCounts[c - 1] += currentCounts[c];
                    }
                    
                    if (c + 1 < width) {
                        nextCounts[c + 1] += currentCounts[c];
                    }
                } else {
                    nextCounts[c] += currentCounts[c];
                }
            }
        }

        currentCounts = nextCounts;
    }

    unsigned long long total = 0;
    for (unsigned long long count : currentCounts) {
        total += count;
    }

    cout << "Total: " << total << endl;

    return 0;
}