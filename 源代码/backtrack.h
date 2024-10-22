#ifndef BACKTRACK_H
#define BACKTRACK_H
void add(int map[][6], int y, int x, int n);
void remove(int map[][6], int y, int x, int n);
bool arraysEqual(int arr1[][6], int arr2[][6]);
bool backtrack(int map[][6], int key[][6], int shapes[][2], int index);
bool isSolved(int key[][6]);
bool designcheck(int key[][6]);
#endif BACKTRACK_H
