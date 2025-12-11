#include <bits/stdc++.h>
using namespace std;


int solve_machine(int n, const vector<unsigned long long>& rows, int m, unsigned long long target_mask) {
    vector<unsigned long long> mat = rows;
    vector<int> rhs(n);
    for (int i = 0; i < n; ++i) rhs[i] = ( (target_mask >> i) & 1ULL ) ? 1 : 0;

    vector<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i) {
            if ( (mat[i] >> col) & 1ULL ) { sel = i; break; }
        }
        if (sel == -1) continue;
        swap(mat[sel], mat[row]);
        swap(rhs[sel], rhs[row]);
        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row && ((mat[i] >> col) & 1ULL)) {
                mat[i] ^= mat[row];
                rhs[i] ^= rhs[row];
            }
        }
        ++row;
    }

    for (int i = row; i < n; ++i) {
        if (mat[i] == 0 && rhs[i]) return -1;
    }

    vector<int> free_cols;
    for (int j = 0; j < m; ++j) if (where[j] == -1) free_cols.push_back(j);
    int f = (int)free_cols.size();

    if (f > 60) {
        vector<int> x(m, 0);
        for (int col = 0; col < m; ++col) if (where[col] != -1) {
            int r = where[col];
            x[col] = rhs[r];
        }
        int w = 0; for (int i=0;i<m;++i) if (x[i]) ++w;
        return w; 
    }

    vector<unsigned long long> pivot_free_mask(m, 0ULL); 
    for (int col = 0; col < m; ++col) if (where[col] != -1) {
        int r = where[col];
        unsigned long long mask = 0ULL;
        for (int k = 0; k < f; ++k) {
            int fc = free_cols[k];
            if ((mat[r] >> fc) & 1ULL) mask |= (1ULL << k);
        }
        pivot_free_mask[col] = mask;
    }

    int best = INT_MAX;
    unsigned long long total_assign = (f == 0) ? 1ULL : (1ULL << f);
    for (unsigned long long assign = 0; assign < total_assign; ++assign) {
        int weight = __builtin_popcountll(assign); 

        for (int col = 0; col < m; ++col) if (where[col] != -1) {
            int r = where[col];
            unsigned long long mask = pivot_free_mask[col];
            int parity = __builtin_popcountll(mask & assign) & 1;
            int val = rhs[r] ^ parity;
            if (val) ++weight;

            if (weight >= best) break;
        }
        if (weight < best) best = weight;
    }

    return best;
}

int main() {
    ifstream file("input.txt");
    string line;
    long long total = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        size_t lbr = line.find('[');
        size_t rbr = line.find(']');
        if (lbr == string::npos || rbr == string::npos || rbr <= lbr) continue;
        string pattern = line.substr(lbr+1, rbr - lbr - 1);
        int n = (int)pattern.size();

        vector<vector<int>> buttons;
        size_t pos = rbr + 1;
        while (true) {
            size_t pstart = line.find('(', pos);
            size_t pcurly = line.find('{', pos);
            if (pstart == string::npos || (pcurly != string::npos && pstart > pcurly)) break;
            size_t pend = line.find(')', pstart);
            if (pend == string::npos) break;
            string inside = line.substr(pstart+1, pend - pstart - 1);
            vector<int> inds;
            stringstream ss(inside);
            string token;
            while (getline(ss, token, ',')) {
                if (token.empty()) continue;
                size_t a = token.find_first_not_of(" \t");
                size_t b = token.find_last_not_of(" \t");
                if (a==string::npos) continue;
                string tok = token.substr(a, b-a+1);
                inds.push_back(stoi(tok));
            }
            buttons.push_back(inds);
            pos = pend + 1;
        }

        int m = (int)buttons.size();

        vector<unsigned long long> rows(n, 0ULL);
        for (int j = 0; j < m; ++j) {
            for (int idx : buttons[j]) {
                if (idx >= 0 && idx < n) rows[idx] |= (1ULL << j);
            }
        }

        unsigned long long target = 0ULL;
        for (int i = 0; i < n; ++i) {
            if (pattern[i] == '#') target |= (1ULL << i);
        }

        int best = solve_machine(n, rows, m, target);
        total += best;
    }

    cout << "Total: " << total << endl;
    return 0;
}
