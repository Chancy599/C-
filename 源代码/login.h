#ifndef LOGIN_H
#define LOGIN_H
#include<graphics.h>
#include<fstream>
#include<vector>
#include<string>
#include"user.h"
#include"menu.h"
#include<sstream>
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
void couplemode(MODE& mode,IMAGE &bkimg);
void login(MODE& mode, int& second,int&score,std::vector<User>& users,IMAGE &bkimg);
void intro();
void saveUserInfoToFile(User &user);//�����û���Ϣ���ı��ļ�
void loadUserInfoFromFile(std::vector<User>&users);//���ı��ļ������û���Ϣ
void modify(User& user, int& newTime,int& score, MODE& mode);
void load();
void pauseBGM();
void resumeBGM();
void BGM();
#endif LOGIN_H


