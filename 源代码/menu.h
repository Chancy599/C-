#ifndef MENU_H
#define MENU_H
#include<graphics.h>
#include<conio.h>
#include"map.h"
#include"user.h"
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//º”‘ÿæ≤Ã¨ø‚
#include<thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include<vector>
#include<map>
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>

bool menu(MODE& mode,int& second, int&score,std::vector<User>& users,IMAGE &bkimg);
void design(MODE& mode, int& second, IMAGE& bkimg);
void play(Map& map,MODE& mode);
void timer(int& second);
void refresh(int x1, int y1, int x2, int y2, Map& map, IMAGE* digit1, IMAGE* digit2);
void refresh(int x, int y, Map& map, IMAGE* digit);
bool gamemode(MODE& mode,IMAGE &bkimg);
void rank(std::vector<User>& users);
void drawchart(MODE mode,IMAGE* a, IMAGE* b, IMAGE* c,IMAGE* ranking, std::multimap<int,std::string>& v);
void challengeMode(int& score, std::vector<User>& users,IMAGE &bkimg);
void loadMapFile(int n, Map& map, std::string filename);
bool challengeplay(int& score, int& n);
void questionplay(MODE &mode,IMAGE &bkimg);
int sumMapFile(std::string filename);
void selectMode(MODE& mode);
void innovate(MODE& mode,IMAGE &bkimg);
#endif MENU_H
