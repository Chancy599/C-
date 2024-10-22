#ifndef MAP_H
#define MAP_H
#include<graphics.h>
#include <fstream>
#include<cstdlib>
#include<random>
#include<ctime>
#include<string>
#include<stack>
#include<map>
#define ROW 6
#define COL 6
#define IMGW 66

enum MODE { simple, difficult,challenge };

struct cell
{
	int num;
	int covered;
};

class Map
{
public:
	Map();
	void mapfile();
	int getCellCovered(int i,int k);
	void setmatric(int row, int col,int num);
	void setmatric(int row, int col, int num,int);
	void setmatric(int row, int col, int num, int, int);
	void setMapnum(int i, int j, int n);
	int getMapnum(int i, int j);
	void initMapcovered();
	void initMapnum();
	void initMapnum(int);
	bool checkMapnum();
	void draw(MODE mode,int x,int y);
	void draw(int x, int y, IMAGE* digit);
	void draw();
	bool finish(MODE mode);
	void initmatric();
	int getmatric(int i);
	int NumtoImg(int num, MODE mode);

private:
	cell map[ROW][COL];
	std::map<int, int> matric;
};
#endif MAP_H
