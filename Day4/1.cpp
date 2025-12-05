#include <bits/stdc++.h>

using namespace std;

const int dr[] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dc[] = {-1,  0,  1, -1,  1, -1,  0,  1};

int countRolls(const std::vector<std::string>& grid) {
    if (grid.empty()) return 0;
    
    int rows = grid.size();
    int cols = grid[0].size();
    int accessibleCount = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            
            if (grid[r][c] == '@') {
                int neighbors = 0;

                for (int i = 0; i < 8; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        if (grid[nr][nc] == '@') {
                            neighbors++;
                        }
                    }
                }
                if (neighbors < 4) {
                    accessibleCount++;
                }
            }
        }
    }
    return accessibleCount;
}

int main() {
    // Open the file
    std::ifstream inputFile("input.txt");
    std::vector<std::string> grid;
    std::string line;

    while (inputFile >> line) {
        grid.push_back(line);
    }

    inputFile.close();

    int result = countRolls(grid);
    std::cout << "Rolls: " << result << std::endl;

    return 0;
}   