#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream file("input.txt");
    //Dial are 0-->99 gives Mod 100
    //Start is 50

    int current_pos = 50;
    long long zero_hits = 0; 

    string instruction;
    
    while (getline(file, instruction)) {
        if (instruction.empty()) continue;

        char direction = instruction[0];
        int amount = stoi(instruction.substr(1));

        zero_hits += (amount / 100);

        int remainder = amount % 100;

        if (remainder > 0) {
            if (direction == 'R') {
                if (current_pos != 0 && remainder >= (100 - current_pos)) {
                    zero_hits++;
                }
                current_pos = (current_pos + remainder) % 100;
            } 
            else if (direction == 'L') {
                if (current_pos != 0 && remainder >= current_pos) {
                    zero_hits++;
                }
                current_pos = (current_pos - remainder);
                if (current_pos < 0) current_pos += 100;
            }
        }
    }

    cout << "Password " << zero_hits << endl;

    file.close();
    return 0;
}