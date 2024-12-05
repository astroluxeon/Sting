#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include <cctype>
#include "player.h"
#include "game.h"

std::string firstUpper(std::string s) {
    if (!s.empty()) {
        s[0] = std::toupper(s[0]);
    }
    return s;
}

std::vector<Player> txtImport() {
    std::ifstream file(txtFile);
    std::vector<Player> players;
    std::vector<std::tuple<std::string, std::string, std::string, int>> list;

    for (std::string line; std::getline(file, line); ) {
        std::istringstream iss(line);
        std::string fname, lname, instagram;
        int time;

        if (iss >> fname >> lname >> instagram >> time) {
            list.emplace_back(fname, lname, instagram, time);
        }
    }

    file.close();

    for (size_t i = 0; i < list.size(); ++i) {
        const auto& [fname, lname, instagram, time] = list[i];
        const auto& [tfname, tlname, tinstagram, _] = list[(i + 1) % list.size()];
        players.emplace_back(fname, lname, tfname, tlname, instagram, tinstagram, time);
    }

    return players;
}

void txtExport(const std::vector<Player>& list) {
    std::ofstream file(txtFile);

    for (const auto& p : list) {
        file << p.fname() << " " << p.lname() << " " << p.instagram() << " " << p.time() << std::endl;
    }

    file.close();
}

void txtExportf(std::vector<Player>& list) {
    std::ranges::sort(list, [](const Player& p1, const Player& p2) {
        return p1.fname() < p2.fname();
    });

    std::ofstream file(txtFilef);

    for (const auto& p : list) {
        file << firstUpper(p.fname()) << " " << firstUpper(p.lname()) << "'s target is " << firstUpper(p.tfname()) << " " << firstUpper(p.tlname()) << " (Instagram: " << p.instagram() << ", Target Instagram: " << p.tinstagram() << ", Time Remaining: " << p.time() << " Days)" << std::endl;
    }

    file.close();
}

void updateListf() {
    auto players = txtImport();
    txtExportf(players);

    std::cout << "\nList Updated" << std::endl;
}

void search() {
    auto players = txtImport();
    std::string fname, lname;

    for (;;) {
        std::cout << "\nEnter Player's First Name:" << std::endl;
        std::getline(std::cin, fname);

        if (fname.empty()) {
            break;
        }

        std::cout << "Enter Player's Last Name:" << std::endl;
        std::getline(std::cin, lname);

        if (lname.empty()) {
            break;
        }

        auto it = std::ranges::find_if(players, [fname, lname](const Player& p) {
            return p.fname() == fname && p.lname() == lname;
        });

        if (it != players.end()) {
            std::cout << "Name: " << firstUpper(it->fname()) << " " << firstUpper(it->lname()) << std::endl;
            std::cout << "Instagram: " << it->instagram() << std::endl;
            std::cout << "Target: " << firstUpper(it->tfname()) << " " << firstUpper(it->tlname()) << std::endl;
            std::cout << "Target Instagram: " << it->tinstagram() << std::endl;
            std::cout << "Time Left: " << it->time() << " Days" << std::endl;
        } else {
            std::cout << "Player Not Found" << std::endl;
        }
    }
}

std::vector<Player> shuffle(std::vector<std::tuple<std::string, std::string, std::string, int>> list) {
    std::ranges::shuffle(list, std::mt19937{std::random_device{}()});
    std::vector<Player> players;

    for (size_t i = 0; i < list.size(); ++i) {
        const auto& [fname, lname, instagram, time] = list[i];
        const auto& [tfname, tlname, tinstagram, _] = list[(i + 1) % list.size()];
        players.emplace_back(fname, lname, tfname, tlname, instagram, tinstagram, time);
    }

    return players;
}

void shuffleSetup() {
    auto players = txtImport();
    std::vector<std::tuple<std::string, std::string, std::string, int>> people;

    for (const auto& p : players) {
        people.emplace_back(p.fname(), p.lname(), p.instagram(), p.time());
    }

    auto list = shuffle(people);

    txtExport(list);
    txtExportf(list);

    std::cout << "\nShuffle Done" << std::endl;
}

void eliminate() {
    auto players = txtImport();
    std::string fname1, lname1;

    for (;;) {
        std::cout << "\nEnter Player's First Name:" << std::endl;
        std::getline(std::cin, fname1);

        if (fname1.empty()) {
            break;
        }

        std::cout << "Enter Player's Last Name:" << std::endl;
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
            std::cout << firstUpper(it1->fname()) << " " << firstUpper(it1->lname()) << " (Instagram: " << it1->instagram() << ") has been eliminated." << std::endl;

            auto it2 = std::ranges::find_if(players, [fname2, lname2](const Player& p2) {
                return p2.tfname() == fname2 && p2.tlname() == lname2;
            });

            it2->setTarget(it1->tfname(), it1->tlname(), it1->tinstagram());
            it2->setTime(it2->time() + timeLimit);
            std::cout << firstUpper(it2->fname()) << " " << firstUpper(it2->lname()) << "'s new target is: " << firstUpper(it2->tfname()) << " " << firstUpper(it2->tlname()) << std::endl;

            players.erase(it1);
        } else {
            std::cout << "Player Not Found" << std::endl;
        }
    }

    if (players.size() == 1) {
        std::cout << firstUpper(players[0].fname()) << " " << firstUpper(players[0].lname()) << " (Instagram: " << players[0].instagram() << ") is the winner!" << std::endl;
    }

    txtExport(players);
    txtExportf(players);
}

void timeDecrease() {
    auto players = txtImport();

    for (auto& p : players) {
        p.setTime(p.time() - 1);
    }

    std::cout << "Time Decreased by 1 Day" << std::endl;

    for (auto it = players.begin(); it != players.end(); ) {
        if (it->time() <= 0) {
            std::cout << firstUpper(it->fname()) << " " << firstUpper(it->lname()) << " (Instagram: " << it->instagram() << ") has run out of time." << std::endl;

            std::string fname1 = it->fname(), lname1 = it->lname();

            auto it1 = std::ranges::find_if(players, [fname1, lname1](const Player& p1) {
                return p1.fname() == fname1 && p1.lname() == lname1;
            });

            std::string fname2 = it1->fname();
            std::string lname2 = it1->lname();
            std::cout << firstUpper(it1->fname()) << " " << firstUpper(it1->lname()) << " (Instagram: " << it1->instagram() << ") has been eliminated." << std::endl;

            auto it2 = std::ranges::find_if(players, [fname2, lname2](const Player& p2) {
                return p2.tfname() == fname2 && p2.tlname() == lname2;
            });

            it2->setTarget(it1->tfname(), it1->tlname(), it1->tinstagram());
            it2->setTime(it2->time() + timeLimit);
            std::cout << firstUpper(it2->fname()) << " " << firstUpper(it2->lname()) << "'s new target is: " << firstUpper(it2->tfname()) << " " << firstUpper(it2->tlname()) << std::endl;

            players.erase(it1);
        } else {
            ++it;
        }
    }

    if (players.size() == 1) {
        std::cout << firstUpper(players[0].fname()) << " " << firstUpper(players[0].lname()) << " (Instagram: " << players[0].instagram() << ") is the winner!" << std::endl;
    }

    txtExport(players);
    txtExportf(players);

    std::cout << std::endl;
}

void initialize() {
    auto file = std::ifstream(txtInitial);
    std::vector<std::tuple<std::string, std::string, std::string, int>> players;

    for (std::string line; std::getline(file, line); ) {
        std::istringstream iss(line);
        std::string fname, lname, instagram;

        if (iss >> fname >> lname >> instagram) {
            players.emplace_back(fname, lname, instagram, timeLimit);
        }
    }

    file.close();

    if (players.empty()) {
        std::cout << "\nNo Names Found" << std::endl;
        return;
    }

    auto list = shuffle(players);

    txtExport(list);
    txtExportf(list);

    std::cout << "\nInitialization Done" << std::endl;
}
