#include "user.h"

User::User(std::string uname, std::string pwd, int sTime, int dTime,int cScore)
    : username(uname), password(pwd), simpleModeTime(sTime), difficultModeTime(dTime),challengeModeScore(cScore) {}


// 获取用户名的函数的实现
std::string User::getUsername() 
{
    return username;
}

// 获取密码的函数的实现
std::string User::getPassword() 
{
    return password;
}

// 设置用户名的函数的实现
void User::setUsername(std::string name) 
{
    username = name;
}

//设置密码的函数的实现
void User::setPassword(std::string pass)
{
    password = pass;
}

// 注册用户的函数的实现
bool User::registerUser(std::vector<User>users)
{
    // 获取用户名
    char n[21];
    InputBox(n, 20, "请输入用户名(1~20个字符)");
    std::string name(n);

    // 检查用户名是否已经存在
    for (User& user : users)
    {
        if (user.getUsername() == name || name.empty() || name.length() > 20)
        {
            return false; // 用户名已存在，注册失败
        }
    }

    // 获取密码
    char p[21];
    InputBox(p, 20, "请输入密码(1~20个字符)");
    std::string pass(p);

    // 创建新用户并添加到用户容器中
    this->setUsername(name);
    this->setPassword(pass);

    return true; // 注册成功
}

// 登录的函数的实现
bool User::loginUser(std::vector<User>users)
{
    // 获取用户名
    char n[21];
    InputBox(n, 20, "请输入用户名(1~20个字符)");
    std::string name(n);

    // 获取密码
    char p[21];
    InputBox(p, 20, "请输入密码(1~20个字符)");
    std::string pass(p);

    // 检查用户是否存在并且密码正确
    for (User& user : users)
    {
        if (user.getUsername() == name && user.getPassword() == pass && pass.length()>0 && pass.length() <21)
        {
            *this = user;
            return true; // 登录成功
        }
    }
    return false; // 登录失败
}

// 挑战时间的函数
int User::getsimpleTime()
{
    return simpleModeTime;
}

void User::setsimpleTime(int simpleTime)
{
    if ((simpleTime!=0&&simpleTime < simpleModeTime) || simpleModeTime == 0)
    {
        simpleModeTime = simpleTime;
    }
}

int User::getdifficultTime()
{
    return difficultModeTime;
}

void User::setdifficultTime(int difficultTime)
{
    if ((difficultTime!=0&&difficultTime < difficultModeTime) || difficultModeTime == 0)
    {
        difficultModeTime = difficultTime;
    }
}

int User::getchallengeScore()
{
    return challengeModeScore;
}

void User::setchallengeScore(int challengeScore)
{
    if (challengeScore > challengeModeScore)
    {
        challengeModeScore = challengeScore;
    }
}




