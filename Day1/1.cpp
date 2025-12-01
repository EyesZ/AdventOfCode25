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
    int zero_hits = 0;
    
    string instruction;
    
    while (getline(file, instruction)) {
        if (instruction.empty()) continue;

        char direction = instruction[0];
        int amount = stoi(instruction.substr(1));

        if (direction == 'R') {
            current_pos = (current_pos + amount) % 100;
        } else if (direction == 'L') {
            current_pos = (current_pos - amount) % 100;
            // wrap around if neg    
            if (current_pos < 0) {
                current_pos += 100;
            }
        }

        if (current_pos == 0) {
            zero_hits++;
        }
    }

    cout << "Password " << zero_hits << endl;

    file.close();
    return 0;
}