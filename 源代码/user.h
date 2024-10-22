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
    std::string username; // 用户名
    std::string password; // 密码
    int simpleModeTime;   // 简单模式时间
    int difficultModeTime;     // 困难模式时间
    int challengeModeScore; // 挑战模式得分

public:
    User(std::string uname = "xxx", std::string pwd = "000", int sTime = 0, int dTime = 0,int cScore=0 );
    std::string getUsername(); // 获取用户名的函数
    std::string getPassword(); // 获取密码的函数
    void setUsername(std::string name); // 设置用户名的函数
    void setPassword(std::string pass); // 设置密码的函数
    bool registerUser(std::vector<User>users); // 注册用户的函数
    bool loginUser(std::vector<User>users); // 登录的函数
    int getsimpleTime();// 简单模式时间的函数
    void setsimpleTime(int simpleTime); 
    int getdifficultTime();// 困难模式时间的函数
    void setdifficultTime(int difficultTime); 
    int getchallengeScore();
    void setchallengeScore(int challengeScore);
};
#endif USER_H
