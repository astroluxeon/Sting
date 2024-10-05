#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <tuple>
#include "player.h"

inline const std::string txt_file = "list.txt";
inline const std::string txt_filef = "listf.txt";
inline const std::string txt_initial = "initial.txt";
inline const int time_limit = 28;

std::vector<Player> txt_import();
void txt_export(const std::vector<Player>& list);
void txt_exportf(std::vector<Player>& list);

void search();
std::vector<Player> shuffle(std::vector<std::tuple<std::string, std::string>> people);
void shuffle_setup();
void eliminate();
void time_decrease();
void initialize();

#endif
