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

long long solve_block(const vector<string>& grid, int start_col, int end_col) {
    vector<long long> numbers;
    char operation = ' ';

    for (size_t r = 0; r < grid.size() - 1; ++r) {
        string line = grid[r];
        string num_str = "";

        if (start_col < line.length()) {
            int len = min((int)line.length(), end_col + 1) - start_col;
            if (len > 0) {
                num_str = line.substr(start_col, len);
            }
        }

        num_str.erase(remove(num_str.begin(), num_str.end(), ' '), num_str.end());

        if (!num_str.empty()) {
            numbers.push_back(stoll(num_str));
        }
    }

    string last_line = grid.back();
    for (int c = start_col; c <= end_col && c < last_line.length(); ++c) {
        if (last_line[c] == '+' || last_line[c] == '*') {
            operation = last_line[c];
            break;
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
        if (line.length() > max_width) {
            max_width = line.length();
        }
    }

    long long total = 0;
    int block_start = -1;

    for (int col = 0; col < max_width; ++col) {
        bool is_sep = is_separator_column(grid, col);

        if (!is_sep) {
            if (block_start == -1) {
                block_start = col;
            }
        } else {
            if (block_start != -1) {
                total += solve_block(grid, block_start, col - 1);
                block_start = -1;
            }
        }
    }
    if (block_start != -1) {
        total += solve_block(grid, block_start, max_width - 1);
    }

    cout << "Total: " << total << endl;

    return 0;
}