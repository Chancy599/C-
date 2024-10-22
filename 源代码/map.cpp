#include"map.h"

Map::Map()
{
	initMapcovered();
	initmatric();
}

void Map::mapfile()
{
	std::ofstream ofs;
	ofs.open("map.csv", std::ios::out | std::ios::app);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			ofs << std::to_string(map[i][j].num) << ",";
		}
	}
	ofs << std::endl;
	ofs.close();
}

void Map::setMapnum(int i, int j, int n)
{
	map[i][j].num = n;
}

int Map::getMapnum(int i, int j)
{
	return map[i][j].num;
}

void Map::initMapcovered()
{
	for (int i = 0; i < ROW; i++) 
	{
		for (int k = 0; k < COL; k++) 
		{
			// 初始化map[i][k].covered
			map[i][k].covered = 0; 
		}
	}
}

void Map::initmatric()
{
	matric.insert(std::make_pair(1, 2));
	matric.insert(std::make_pair(2, 2));
	matric.insert(std::make_pair(3, 2));
	matric.insert(std::make_pair(4, 1));
}

void Map::initMapnum()
{
	srand((unsigned int)time(NULL));
	// 用于标记地图是否符合要求
	bool mapIsValid = false; 

	while (!mapIsValid)
	{
		// 初始化地图为零
		for (int row = 0; row < ROW; row++)
		{
			for (int col = 0; col < COL; col++)
			{
				map[row][col].num = 0;
			}
		}

		// 随机设置地图中的数字
		int num4_x = rand() % 3;
		int num4_y = rand() % 3;
		for (int row = num4_y; row < num4_y+4; row++)
		{
			for (int col = num4_x; col < num4_x+4; col++)
			{
				map[row][col].num++;
			}
		}

		int num3_1_x = rand() % 4;
		int num3_1_y = rand() % 4;
		for (int row = num3_1_y; row < num3_1_y + 3; row++)
		{
			for (int col = num3_1_x; col < num3_1_x + 3; col++)
			{
				map[row][col].num++;
			}
		}

		int num3_2_x = rand() % 4;
		int num3_2_y = rand() % 4;
		for (int row = num3_2_y; row < num3_2_y + 3; row++)
		{
			for (int col = num3_2_x; col < num3_2_x + 3; col++)
			{
				map[row][col].num++;
			}
		}

		int num2_1_x = rand() % 5;
		int num2_1_y = rand() % 5;
		for (int row = num2_1_y; row < num2_1_y + 2; row++)
		{
			for (int col = num2_1_x; col < num2_1_x + 2; col++)
			{
				map[row][col].num++;
			}
		}

		int num2_2_x = rand() % 5;
		int num2_2_y = rand() % 5;
		for (int row = num2_2_y; row < num2_2_y + 2; row++)
		{
			for (int col = num2_2_x; col < num2_2_y + 2; col++)
			{
				map[row][col].num++;
			}
		}

		int num1_1_x = rand() % 6;
		int num1_1_y = rand() % 6;
		map[num1_1_y][num1_1_x].num++;

		int num1_2_x = rand() % 6;
		int num1_2_y = rand() % 6;
		map[num1_2_y][num1_2_x].num++;

		// 检查地图是否符合要求
		mapIsValid = checkMapnum();
	}
}

void Map::initMapnum(int)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			map[i][j].num = rand() % 5;
		}
	}
}

bool Map::checkMapnum()
{
	int count = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j].num > 4)
				return false;
			count += map[i][j].num;
		}
	}
	if (count != 44)
	{
		return false;
	}
	return true;
}


void Map::draw(MODE mode,int x,int y)
{
	IMAGE cell[4];
	loadimage(cell + 0, "cell/0.jpg", IMGW, IMGW);
	loadimage(cell + 1, "cell/1.jpg", IMGW, IMGW);
	loadimage(cell + 2, "cell/2.jpg", IMGW, IMGW);
	loadimage(cell + 3, "cell/3.jpg", IMGW, IMGW);

	for (int i = 0; i < ROW; i++)
	{
		for (int k = 0; k < COL; k++)
		{
			putimage(x+k * IMGW, y+(i + 1) * IMGW, cell + NumtoImg(map[i][k].num,mode));
		}
	}

	IMAGE matrix[4];
	loadimage(matrix + 0, "matric/0.jpg", IMGW, IMGW);
	loadimage(matrix + 1, "matric/1.jpg", IMGW, IMGW);
	loadimage(matrix + 2, "matric/2.jpg", IMGW, IMGW);
	loadimage(matrix + 3, "matric/3.jpg", IMGW, IMGW);

	for (int i = 0; i < 4; i++)
	{
		putimage(x+(i + 2) * IMGW, y+7 * IMGW, matrix + i);
	}
}

void Map::draw(int x, int y,IMAGE* digit)
{
	putimage(x, y, digit);
}

void Map::draw()
{
	IMAGE img[2];
	loadimage(img + 0, "close.png", IMGW, IMGW);
	loadimage(img + 1, "back.jpg", IMGW, IMGW);

	putimage(297, 7 * IMGW+66, img + 0);
	putimage(IMGW+297, 7 * IMGW+66, img + 1);
	setlinecolor(BLUE);

	for (int i = 0; i <= 6 * IMGW; i += IMGW)
	{
		line(i+297, IMGW+66, i+297, 8 * IMGW+66);
	}
	for (int i = IMGW; i <= 8 * IMGW; i += IMGW)
	{
		line(0+297, i+66, 6 * IMGW+297, i+66);
	}
}

int Map::getCellCovered(int i,int k)
{
	return map[i][k].covered;
}

void Map::setmatric(int row, int col, int num)
{
	if (row >= 0 && row + num <= ROW && col >= 0 && col + num <= COL && matric[num] > 0)
	{
		for (int i = 0; i < num; i++)
		{
			for (int k = 0; k < num; k++)
			{
				if (map[row + i][col + k].num == 0 || map[row + i][col + k].covered == 4)
				{
					MessageBox(NULL, "存在区域不可再进行种植", "提示", MB_ICONERROR);
				}
				map[row + i][col + k].covered++;
			}
		}
		matric[num]--;
	}
	else
	{
		MessageBox(NULL, "无法种植，请重试！", "错误", MB_ICONERROR);
	}
}

void Map::setmatric(int row, int col, int num, int)
{
	if (row >= 0 && row + num <= ROW && col >= 0 && col + num <= COL && matric[num] > 0)
	{
		for (int i = 0; i < num; i++)
		{
			for (int k = 0; k < num; k++)
			{
				map[row + i][col + k].covered++;
			}
		}
		matric[num]--;
	}
}

void Map::setmatric(int row, int col, int num, int,int)
{
	if (row >= 0 && row + num <= ROW && col >= 0 && col + num <= COL)
	{
		for (int i = 0; i < num; i++)
		{
			for (int k = 0; k < num; k++)
			{
				if (map[row + i][col + k].num == 0 || map[row + i][col + k].covered == 4)
				{
					MessageBox(NULL, "存在区域不可再进行种植", "提示", MB_ICONERROR);
				}
				map[row + i][col + k].covered++;
			}
		}
	}
	else
	{
		MessageBox(NULL, "无法种植，请重试！", "错误", MB_ICONERROR);
	}
}

bool Map::finish(MODE mode)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (NumtoImg(map[i][j].num, mode) != NumtoImg(map[i][j].covered, mode))
			{
				return false;
			}
		}
	}
	return true;
}

int Map::NumtoImg(int num,MODE mode)
{
	if (num % 2 == 1)
	{
		return 2;
	}
	else if (num == 2)
	{
		return 1;
	}
	else if (num == 0)
	{
		if (mode == simple)
		{
			return 0;
		}
		else if(mode==difficult)
		{
			return 1;
		}
	}
	else if (num == 4)
	{
		return 3;
	}
}

int Map::getmatric(int i)
{
	return matric[i];
}



