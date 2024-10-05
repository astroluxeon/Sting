// PMSS Sting Algorithm by Zi Chen Cai

#include <iostream>
#include <fstream>
#include <string>
#include "game.h"

int main() {
    std::string input;

    for (;;) {
        std::cout << "\nEnter 0 for player search, 1 for time decrease, 2 for player elimination,\n5 for target shuffle, 10 for player initialization, or anything else to quit:" << std::endl;
        std::getline(std::cin, input);

        if (input.empty()) {
            break;
        }

        int k = std::stoi(input);

        switch (k) {
            case 0:
                search();
                break;
            case 1:
                time_decrease();
                break;
            case 2:
                eliminate();
                break;
            case 5:
                shuffle_setup();
                break;
            case 10:
                initialize();
                break;
            default:
                goto end;
        }
    }

    end:;
    return 0;
}