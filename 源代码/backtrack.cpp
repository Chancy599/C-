#include"backtrack.h"
void add(int map[][6], int y, int x, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (y + i < 6 && x + j < 6)
                map[y + i][x + j]++;
        }
    }
}

void remove(int map[][6], int y, int x, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (y + i < 6 && x + j < 6)
                map[y + i][x + j]--;
        }
    }
}

bool arraysEqual(int arr1[][6], int arr2[][6])
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if (arr1[i][j] != arr2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//»ØËÝËã·¨
bool backtrack(int map[][6], int key[][6], int shapes[][2], int index)
{
    if (index == 7)
    {
        return arraysEqual(map, key);
    }

    int size = shapes[index][0];
    for (int y = 0; y <= 6 - size; ++y)
    {
        for (int x = 0; x <= 6 - size; ++x)
        {
            add(map, y, x, size);
            if (backtrack(map, key, shapes, index + 1))
            {
                return true;
            }
            remove(map, y, x, size);
        }
    }
    return false;
}

bool isSolved(int key[][6])
{
    int map[6][6] = { 0 };
    int shapes[7][2] = { {4, 4}, {3, 3}, {3, 3}, {2, 2}, {2, 2}, {1, 1}, {1, 1} };
    return backtrack(map, key, shapes, 0);
}

bool designcheck(int key[][6])
{
    int n = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            n += key[i][j];
        }
    }
    if (n != 44)
    {
        return false;
    }
    else
    {
        if (!isSolved(key))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}