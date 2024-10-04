// PMSS Sting Algorithm by Zi Chen Cai

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include "player.h"

std::vector<Player> txt_import() {
    std::ifstream file(txt_file);
    std::vector<Player> list;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fname, lname, tfname, tlname;
        int time;

        if (iss >> fname >> lname >> tfname >> tlname >> time) {
            list.emplace_back(fname, lname, tfname, tlname, time);
        }
    }

    file.close();
    return list;
}

void txt_export(const std::vector<Player>& list) {
    std::ofstream file(txt_file);

    for (const auto& p : list) {
        file << p.fname() << " " << p.lname() << " " << p.tfname() << " " << p.tlname() << " " << p.time() << std::endl;
    }

    file.close();
}

void txt_exportf(std::vector<Player>& list) {
    std::ranges::sort(list, [](const Player& p1, const Player& p2) {
        return p1.fname() < p2.fname();
    });

    std::ofstream file(txt_filef);

    for (const auto& p : list) {
        file << p.fname() << " " << p.lname() << "'s target is " << p.tfname() << " " << p.tlname() << " (Time Remaining: " << p.time() << " Days)" << std::endl;
    }

    file.close();
}

void search() {
    std::vector<Player> players = txt_import();
    std::string fname, lname;

    while (true) {
        std::cout << "\nEnter Candidate's First Name:" << std::endl;
        std::getline(std::cin, fname);

        if (fname.empty()) {
            break;
        }

        std::cout << "Enter Candidate's Last Name:" << std::endl;
        std::getline(std::cin, lname);

        if (lname.empty()) {
            break;
        }

        auto it = std::ranges::find_if(players, [fname, lname](const Player& p) {
            return p.fname() == fname && p.lname() == lname;
        });

        if (it != players.end()) {
            std::cout << "Name: " << it->fname() << " " << it->lname() << std::endl;
            std::cout << "Target: " << it->tfname() << " " << it->tlname() << std::endl;
            std::cout << "Time Left: " << it->time() << " Days" << std::endl;
        } else {
            std::cout << "Candidate Not Found" << std::endl;
        }
    }
}

std::vector<Player> shuffle(std::vector<std::tuple<std::string, std::string>> people) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::ranges::shuffle(people, g);
    std::vector<Player> players;

    for (size_t i = 0; i < people.size(); ++i) {
        std::string fname = std::get<0>(people[i]);
        std::string lname = std::get<1>(people[i]);
        std::string tfname = std::get<0>(people[(i + 1) % people.size()]);
        std::string tlname = std::get<1>(people[(i + 1) % people.size()]);
        players.emplace_back(fname, lname, tfname, tlname, time_limit);
    }

    return players;
}

void initialize() {
    auto file = std::ifstream("initial.txt");
    std::vector<std::tuple<std::string, std::string>> players;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fname, lname;

        if (iss >> fname >> lname) {
            players.emplace_back(fname, lname);
        }
    }

    file.close();

    if (players.empty()) {
        std::cout << "\nNo names found." << std::endl;
        return;
    }

    auto list = shuffle(players);

    txt_export(list);
    txt_exportf(list);

    std::cout << "\nInitialization Done" << std::endl;
}

void eliminate() {
    std::vector<Player> players = txt_import();
    std::string fname1, lname1;

    while (true) {
        std::cout << "\nEnter Candidate's First Name:" << std::endl;
        std::getline(std::cin, fname1);

        if (fname1.empty()) {
            break;
        }

        std::cout << "Enter Candidate's Last Name:" << std::endl;
        std::getline(std::cin, lname1);

        if (lname1.empty()) {
            break;
        }

        auto it1 = std::ranges::find_if(players, [fname1, lname1](const Player& p1) {
            return p1.fname() == fname1 && p1.lname() == lname1;
        });

        if (it1 != players.end()) {
            std::string fname2 = it1->fname();
            std::string lname2 = it1->lname();
            std::cout << it1->fname() << " " << it1->lname() << " has been eliminated." << std::endl;

            auto it2 = std::ranges::find_if(players, [fname2, lname2](const Player& p2) {
                return p2.tfname() == fname2 && p2.tlname() == lname2;
            });

            it2->set_target(it1->tfname(), it1->tlname());
            it2->set_time(time_limit);
            std::cout << it2->fname() << " " << it2->lname() << "'s new target is: " << it2->tfname() << " " << it2->tlname() << std::endl;

            players.erase(it1);
        } else {
            std::cout << "Candidate not found." << std::endl;
        }
    }

    if (players.size() == 1) {
        std::cout << players[0].fname() << " " << players[0].lname() << " is the winner!" << std::endl;
    }

    txt_export(players);
    txt_exportf(players);
}

void time_decrease() {
    std::vector<Player> players = txt_import();

    for (auto& p : players) {
        p.set_time(p.time() - 1);
    }

    std::cout << std::endl;

    for (const auto& p : players) {
        if (p.time() <= 0) {
            std::cout << p.fname() << " " << p.lname() << " has run out of time." << std::endl;

            std::string fname1 = p.fname(), lname1 = p.lname();

            auto it1 = std::ranges::find_if(players, [fname1, lname1](const Player& p1) {
                return p1.fname() == fname1 && p1.lname() == lname1;
            });

            if (it1 != players.end()) {
                std::string fname2 = it1->fname();
                std::string lname2 = it1->lname();
                std::cout << it1->fname() << " " << it1->lname() << " has been eliminated." << std::endl;

                auto it2 = std::ranges::find_if(players, [fname2, lname2](const Player& p2) {
                    return p2.tfname() == fname2 && p2.tlname() == lname2;
                });

                it2->set_target(it1->tfname(), it1->tlname());
                it2->set_time(time_limit);
                std::cout << it2->fname() << " " << it2->lname() << "'s new target is: " << it2->tfname() << " " << it2->tlname() << std::endl;

                players.erase(it1);
            } else {
                std::cout << "Candidate not found." << std::endl;
            }
        }
    }

    if (players.size() == 1) {
        std::cout << players[0].fname() << " " << players[0].lname() << " is the winner!" << std::endl;
    }

    txt_export(players);
    txt_exportf(players);

    std::cout << "Time Decreased by 1 Day" << std::endl;
}

void shuffle_setup() {
    std::vector<Player> players = txt_import();
    std::vector<std::tuple<std::string, std::string>> people;

    for (const auto& p : players) {
        people.emplace_back(p.fname(), p.lname());
    }

    auto list = shuffle(people);

    txt_export(list);
    txt_exportf(list);

    std::cout << "\nShuffle Done" << std::endl;
}

int main() {
    std::string input;

    while (true) {
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