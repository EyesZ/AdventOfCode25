#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

bool isInvalidID(long long num) {
    string s = to_string(num);
    int len = s.length();
    
    if (len % 2 != 0) {
        return false;
    }
    
    return s.substr(0, len / 2) == s.substr(len / 2);
}

int main() {
    
    ifstream file("input.txt");

    string segment;
    long long totalSum = 0;
    
    while (getline(file, segment, ',')) {
        size_t dashPos = segment.find('-');
        
        if (dashPos != string::npos) {
            string startStr = segment.substr(0, dashPos);
            string endStr = segment.substr(dashPos + 1);
            
            long long start = stoll(startStr);
            long long end = stoll(endStr);
            
            for (long long i = start; i <= end; ++i) {
                if (isInvalidID(i)) {
                    totalSum += i;
                }
            }
        }
    }

    cout << "Sum: " << totalSum << endl;

    
    file.close();
    return 0;
}

