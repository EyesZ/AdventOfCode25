#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

long long getMaxJoltage(const std::string& bank) {
    int n = bank.length();
    if (n < 12) return 0;

    std::string result = "";
    int currentPos = 0; 
    int digitsToFind = 12;

    while (digitsToFind > 0) {
        
        int searchLimit = n - digitsToFind;
        
        char maxDigit = -1;
        int maxIndex = -1;

        for (int i = currentPos; i <= searchLimit; ++i) {
            if (bank[i] > maxDigit) {
                maxDigit = bank[i];
                maxIndex = i;
                if (maxDigit == '9') break;
            }
        }
        result += maxDigit;
        
        currentPos = maxIndex + 1;
        digitsToFind--;
    }

    return std::stoll(result);
}

int main() {
    
    ifstream file("input.txt");

    string line;
    long long totalJoltage = 0;

    while (getline(file, line)) {
        if (!line.empty()) {
            long long  bankMax = getMaxJoltage(line);
            totalJoltage += bankMax;
        }
    }

    cout << "Sum: " << totalJoltage << endl;

    return 0;
}