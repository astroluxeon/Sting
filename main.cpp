// PMSS Sting Algorithm by Zi Chen Cai

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>

void merge(std::vector<std::tuple<std::string, std::string, int>>& v, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<std::tuple<std::string, std::string, int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (std::get<0>(L[i]) <= std::get<0>(R[j])) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<std::tuple<std::string, std::string, int>>& v, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(v, l, m);
        merge_sort(v, m + 1, r);

        merge(v, l, m, r);
    }
}

std::vector<std::tuple<std::string, std::string, int>> txt_import(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::tuple<std::string, std::string, int>> people;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string person, target;
        int time;

        if (iss >> person >> target >> time) {
            people.emplace_back(person, target, time);
        }
    }

    file.close();
    return people;
}

void txt_export(const std::vector<std::tuple<std::string, std::string, int>>& list, const std::string& filename) {
    std::ofstream file(filename);

    for (const auto& [person, target, time] : list) {
        file << person << " " << target << " " << time << std::endl;
    }

    file.close();
}

void initialize() {
    auto file = std::ifstream("..\\initial.txt");
    std::vector<std::string> people;
    std::string line;

    while (std::getline(file, line)) {
        people.push_back(line);
    }

    file.close();

    if (people.empty()) {
        std::cout << "No names found" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::ranges::shuffle(people, g);
    std::vector<std::tuple<std::string, std::string, int>> sting_list;

    for (size_t i = 0; i < people.size(); ++i) {
        std::string person = people[i];
        std::string target = people[(i + 1) % people.size()];
        sting_list.emplace_back(person, target, 30);
    }

    merge_sort(sting_list, 0, sting_list.size() - 1);

    txt_export(sting_list, "..\\sting_list.txt");

    std::cout << "Initialization Done" << std::endl;
}

void search() {
    std::vector<std::tuple<std::string, std::string, int>> people = txt_import("..\\sting_list.txt");
    std::string candidate;

    while (true) {
        std::cout << "Enter Candidate to Search For:" << std::endl;
        std::getline(std::cin, candidate);

        if (candidate.empty()) {
            break;
        }

        auto it = std::ranges::find_if(people, [candidate](const auto& t) {
            return std::get<0>(t) == candidate;
        });

        if (it != people.end()) {
            std::cout << "Name: " << std::get<0>(*it) << std::endl;
            std::cout << "Target: " << std::get<1>(*it) << std::endl;
            std::cout << "Time Left: " << std::get<2>(*it) << " Days" << std::endl;
        } else {
            std::cout << "Candidate Not Found" << std::endl;
        }
    }
}

void assign(const std::vector<std::tuple<std::string, std::string, int>> &people) {
    std::vector<std::tuple<std::string, std::string, int>> sting_list;

    for (const auto& [person, target, time] : people) {
        sting_list.emplace_back(person, target, time);
    }

    merge_sort(sting_list, 0, sting_list.size() - 1);

    txt_export(sting_list, "..\\sting_list.txt");
}

void eliminate() {
    std::vector<std::tuple<std::string, std::string, int>> people = txt_import("..\\sting_list.txt");
    std::string candidate;

    while (true) {
        std::cout << "Enter Candidate to Eliminate:" << std::endl;
        std::getline(std::cin, candidate);

        if (candidate.empty()) {
            break;
        }

        auto it = std::ranges::find_if(people, [candidate](const auto& t) {
            return std::get<0>(t) == candidate;
        });

        if (it != people.end()) {
            std::string x = std::get<0>(*it);
            std::cout << std::get<0>(*it) << " Has Been Eliminated" << std::endl;

            auto it0 = std::ranges::find_if(people, [x](const auto& u) {
                return std::get<1>(u) == x;
            });

            std::get<1>(*it0) = std::get<1>(*it);
            std::get<2>(*it0) = 30;
            std::cout << std::get<0>(*it0) << "'s new target is: " << std::get<1>(*it0) << std::endl;

            people.erase(it);
        } else {
            std::cout << "Candidate Not Found" << std::endl;
        }
    }

    assign(people);
}

void time_decrease() {
    std::vector<std::tuple<std::string, std::string, int>> people = txt_import("..\\sting_list.txt");

    for (auto& it : people) {
        std::get<2>(it) = std::get<2>(it) - 1;
    }

    assign(people);
}

int main() {
    std::string input;

    while (true) {
        std::cout << "\nEnter 0 for candidate search, 1 for time decrease, 2 for candidate elimination, 10 for initialization, or anything else to quit:" << std::endl;
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