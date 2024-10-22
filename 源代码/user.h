#ifndef USER_H
#define USER_H
#include<string>
#include <vector>
#include<graphics.h>
#include<conio.h>
#include<fstream>

class User 
{
private:
    std::string username; // �û���
    std::string password; // ����
    int simpleModeTime;   // ��ģʽʱ��
    int difficultModeTime;     // ����ģʽʱ��
    int challengeModeScore; // ��սģʽ�÷�

public:
    User(std::string uname = "xxx", std::string pwd = "000", int sTime = 0, int dTime = 0,int cScore=0 );
    std::string getUsername(); // ��ȡ�û����ĺ���
    std::string getPassword(); // ��ȡ����ĺ���
    void setUsername(std::string name); // �����û����ĺ���
    void setPassword(std::string pass); // ��������ĺ���
    bool registerUser(std::vector<User>users); // ע���û��ĺ���
    bool loginUser(std::vector<User>users); // ��¼�ĺ���
    int getsimpleTime();// ��ģʽʱ��ĺ���
    void setsimpleTime(int simpleTime); 
    int getdifficultTime();// ����ģʽʱ��ĺ���
    void setdifficultTime(int difficultTime); 
    int getchallengeScore();
    void setchallengeScore(int challengeScore);
};
#endif USER_H
