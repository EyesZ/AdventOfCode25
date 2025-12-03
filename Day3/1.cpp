#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int getMaxJoltage(const string& bank) {
    int maxVal = 0;
    int n = bank.length();

    // can be faster
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            
            int digit1 = bank[i] - '0'; 
            int digit2 = bank[j] - '0';
            
            int currentVal = (digit1 * 10) + digit2;
            
            if (currentVal > maxVal) {
                maxVal = currentVal;
            }
        }
    }
    return maxVal;
}

int main() {
    
    ifstream file("input.txt");

    string line;
    long long totalJoltage = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            int bankMax = getMaxJoltage(line);
            totalJoltage += bankMax;
        }
    }

    cout << "Sum: " << totalJoltage << endl;

    return 0;
}