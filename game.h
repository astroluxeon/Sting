#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <tuple>
#include "player.h"

inline const std::string txtFile = "list.txt";
inline const std::string txtFilef = "listf.txt";
inline const std::string txtInitial = "initial.txt";
inline const int timeLimit = 28;

std::vector<Player> txtImport();
void txtExport(const std::vector<Player>& list);
void txtExportf(std::vector<Player>& list);

void updateListf();
void search();
std::vector<Player> shuffle(std::vector<std::tuple<std::string, std::string, std::string>> list);
void shuffleSetup();
void eliminate();
void timeDecrease();
void initialize();

#endif
