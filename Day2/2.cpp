#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

bool isInvalidID(long long num) {
    string s = to_string(num);
    int len = s.length();
    
    for (int subLen = 1; subLen <= len / 2; ++subLen) {
        
        if (len % subLen == 0) {
            string pattern = s.substr(0, subLen);
            string constructed = "";
            
            int repeats = len / subLen;
            for (int k = 0; k < repeats; ++k) {
                constructed += pattern;
            }
            
            if (constructed == s) {
                return true;
            }
        }
    }
    
    return false;
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

