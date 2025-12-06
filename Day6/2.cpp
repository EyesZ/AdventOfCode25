#include <bits/stdc++.h>

using namespace std;

bool is_separator_column(const vector<string>& grid, int col_idx) {
    for (const auto& row : grid) {
        if (col_idx < row.length()) {
            if (row[col_idx] != ' ') {
                return false;
            }
        }
    }
    return true;
}

long long solve_vertical_block(const vector<string>& grid, int start_col, int end_col) {
    vector<long long> numbers;
    char operation = ' ';
    int height = grid.size();

    if (height > 0) {
        const string& last_row = grid[height - 1];
        for (int c = start_col; c <= end_col; ++c) {
            if (c < last_row.length()) {
                char ch = last_row[c];
                if (ch == '+' || ch == '*') {
                    operation = ch;
                    break; 
                }
            }
        }
    }

    for (int c = start_col; c <= end_col; ++c) {
        string num_str = "";
        
        for (int r = 0; r < height - 1; ++r) {
            if (c < grid[r].length()) {
                char ch = grid[r][c];
                if (isdigit(ch)) {
                    num_str += ch;
                }
            }
        }

        if (!num_str.empty()) {
            try {
                numbers.push_back(stoll(num_str));
            } catch (...) {}
        }
    }

    if (numbers.empty()) return 0;
    
    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (operation == '+') {
            result += numbers[i];
        } else if (operation == '*') {
            result *= numbers[i];
        }
    }

    return result;
}

int main() {
    ifstream file("input.txt");
    vector<string> grid;
    string line;
    size_t max_width = 0;

    while (getline(file, line)) {
        grid.push_back(line);
        if (line.length() > max_width) max_width = line.length();
    }

    for (auto& row : grid) {
        row.resize(max_width, ' ');
    }

    long long total = 0;
    int block_start = -1;

    for (int col = 0; col < max_width; ++col) {
        bool is_sep = is_separator_column(grid, col);

        if (!is_sep) {
            if (block_start == -1) block_start = col;
        } else {
            if (block_start != -1) {
                total += solve_vertical_block(grid, block_start, col - 1);
                block_start = -1;
            }
        }
    }
    if (block_start != -1) {
        total += solve_vertical_block(grid, block_start, max_width - 1);
    }

    cout << "Total: " << total << endl;

    return 0;
}