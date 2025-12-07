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
    long long total = 0;
    set<int> currentBeams;
    
    if (startCol != -1) {
        currentBeams.insert(startCol);
    }

    for (int r = 0; r < height; ++r) {
        set<int> nextBeams; 

        for (int col : currentBeams) {
            char cell = grid[r][col];

            if (cell == '^') {
                total++;

                if (col - 1 >= 0) nextBeams.insert(col - 1);
                if (col + 1 < width) nextBeams.insert(col + 1);

            } else {
                if (col >= 0 && col < width) {
                    nextBeams.insert(col);
                }
            }
        }

        currentBeams = nextBeams;

        if (currentBeams.empty()) break;
    }

    cout << "Total: " << total << endl;

    return 0;
}