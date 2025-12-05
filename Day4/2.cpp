#include <bits/stdc++.h>

using namespace std;


const int dr[] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dc[] = {-1,  0,  1, -1,  1, -1,  0,  1};

int countNeighbors(const std::vector<std::string>& grid, int r, int c) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (grid[nr][nc] == '@') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    std::ifstream inputFile("input.txt");

    std::vector<std::string> grid;
    std::string line;
    while (inputFile >> line) {
        grid.push_back(line);
    }
    inputFile.close();

    int totalRemoved = 0;
    bool changed = true;
    int rows = grid.size();
    int cols = grid[0].size();

    while (changed) {
        changed = false;
        std::vector<std::pair<int, int>> toRemove;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '@') {
                    if (countNeighbors(grid, r, c) < 4) {
                        toRemove.push_back({r, c});
                    }
                }
            }
        }

        if (!toRemove.empty()) {
            changed = true;
            totalRemoved += toRemove.size();
            
            for (const auto& pos : toRemove) {
                grid[pos.first][pos.second] = '.'; 
            }
        }
    }

    std::cout << "Rolls: " << totalRemoved << std::endl;

    return 0;
}