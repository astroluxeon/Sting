#include <iostream>
#include <string>
#include "game.h"

int main() {
    std::string input;

    for (;;) {
        std::cout << "\nEnter 0 for player search, 1 for time decrease, 2 for player elimination, 3 for formatted list update,\n10 for target shuffle, 50 for player initialization, or anything else to quit:" << std::endl;
        std::getline(std::cin, input);

        if (input.empty() || !std::all_of(input.begin(), input.end(), ::isdigit)) {
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
            case 3:
                update_listf();
                break;
            case 10:
                shuffle_setup();
                break;
            case 50:
                initialize();
                break;
            default:
                goto end;
        }
    }

    end:;
    return 0;
}