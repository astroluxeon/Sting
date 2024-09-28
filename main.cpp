// PMSS Sting Algorithm by Zi Chen Cai

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include "candidate.h"

std::vector<Candidate> txt_import(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Candidate> list;
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

void txt_export(const std::vector<Candidate>& list, const std::string& filename) {
    std::ofstream file(filename);

    for (const auto& c : list) {
        file << c.fname() << " " << c.lname() << " " << c.tfname() << " " << c.tlname() << " " << c.time() << std::endl;
    }

    file.close();
}

void search() {
    std::vector<Candidate> candidates = txt_import("..\\sting_list.txt");
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

        auto it = std::ranges::find_if(candidates, [fname, lname](const Candidate& c) {
            return c.fname() == fname && c.lname() == lname;
        });

        if (it != candidates.end()) {
            std::cout << "Name: " << it->fname() << " " << it->lname() << std::endl;
            std::cout << "Target: " << it->tfname() << " " << it->tlname() << std::endl;
            std::cout << "Time Left: " << it->time() << " Days" << std::endl;
        } else {
            std::cout << "Candidate Not Found" << std::endl;
        }
    }
}

std::vector<Candidate> shuffle(std::vector<std::tuple<std::string, std::string>> people) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::ranges::shuffle(people, g);
    std::vector<Candidate> sting_list;

    for (size_t i = 0; i < people.size(); ++i) {
        std::string fname = std::get<0>(people[i]);
        std::string lname = std::get<1>(people[i]);
        std::string tfname = std::get<0>(people[(i + 1) % people.size()]);
        std::string tlname = std::get<1>(people[(i + 1) % people.size()]);
        sting_list.emplace_back(fname, lname, tfname, tlname, 30);
    }

    return sting_list;
}

void initialize() {
    auto file = std::ifstream("..\\initial.txt");
    std::vector<std::tuple<std::string, std::string>> people;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fname, lname;

        if (iss >> fname >> lname) {
            people.emplace_back(fname, lname);
        }
    }

    file.close();

    if (people.empty()) {
        std::cout << "\nNo names found." << std::endl;
        return;
    }

    txt_export(shuffle(people), "..\\sting_list.txt");

    std::cout << "\nInitialization Done" << std::endl;
}

void eliminate() {
    std::vector<Candidate> candidates = txt_import("..\\sting_list.txt");
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

        auto it1 = std::ranges::find_if(candidates, [fname1, lname1](const Candidate& c1) {
            return c1.fname() == fname1 && c1.lname() == lname1;
        });

        if (it1 != candidates.end()) {
            std::string fname2 = it1->fname();
            std::string lname2 = it1->lname();
            std::cout << it1->fname() << " " << it1->lname() << " has been eliminated." << std::endl;

            auto it2 = std::ranges::find_if(candidates, [fname2, lname2](const Candidate& c2) {
                return c2.tfname() == fname2 && c2.tlname() == lname2;
            });

            it2->set_target(it1->tfname(), it1->tlname());
            it2->set_time(30);
            std::cout << it2->fname() << " " << it2->lname() << "'s new target is: " << it2->tfname() << " " << it2->tlname() << std::endl;

            candidates.erase(it1);
        } else {
            std::cout << "Candidate not found." << std::endl;
        }
    }

    if (candidates.size() == 1) {
        std::cout << candidates[0].fname() << " " << candidates[0].lname() << " is the winner!" << std::endl;
    }

    txt_export(candidates, "..\\sting_list.txt");
}

void time_decrease() {
    std::vector<Candidate> candidates = txt_import("..\\sting_list.txt");

    for (auto& c : candidates) {
        c.set_time(c.time() - 1);
    }

    std::cout << std::endl;

    for (const auto& c : candidates) {
        if (c.time() <= 0) {
            std::cout << c.fname() << " " << c.lname() << " has run out of time." << std::endl;

            std::string fname1 = c.fname(), lname1 = c.lname();

            auto it1 = std::ranges::find_if(candidates, [fname1, lname1](const Candidate& c1) {
                return c1.fname() == fname1 && c1.lname() == lname1;
            });

            if (it1 != candidates.end()) {
                std::string fname2 = it1->fname();
                std::string lname2 = it1->lname();
                std::cout << it1->fname() << " " << it1->lname() << " has been eliminated." << std::endl;

                auto it2 = std::ranges::find_if(candidates, [fname2, lname2](const Candidate& c2) {
                    return c2.tfname() == fname2 && c2.tlname() == lname2;
                });

                it2->set_target(it1->tfname(), it1->tlname());
                it2->set_time(30);
                std::cout << it2->fname() << " " << it2->lname() << "'s new target is: " << it2->tfname() << " " << it2->tlname() << std::endl;

                candidates.erase(it1);
            } else {
                std::cout << "Candidate not found." << std::endl;
            }
        }
    }

    if (candidates.size() == 1) {
        std::cout << candidates[0].fname() << " " << candidates[0].lname() << " is the winner!" << std::endl;
    }

    txt_export(candidates, "..\\sting_list.txt");

    std::cout << "Time Decreased by 1 Day" << std::endl;
}

void shuffle_setup() {
    std::vector<Candidate> candidates = txt_import("..\\sting_list.txt");
    std::vector<std::tuple<std::string, std::string>> people;

    for (const auto& c : candidates) {
        people.emplace_back(c.fname(), c.lname());
    }

    txt_export(shuffle(people), "..\\sting_list.txt");

    std::cout << "\nShuffle Done" << std::endl;
}

int main() {
    std::string input;

    while (true) {
        std::cout << "\nEnter 0 for candidate search, 1 for time decrease, 2 for candidate elimination,\n5 for target shuffle, 10 for candidate initialization, or anything else to quit:" << std::endl;
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