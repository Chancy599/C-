#include "user.h"

User::User(std::string uname, std::string pwd, int sTime, int dTime,int cScore)
    : username(uname), password(pwd), simpleModeTime(sTime), difficultModeTime(dTime),challengeModeScore(cScore) {}


// ��ȡ�û����ĺ�����ʵ��
std::string User::getUsername() 
{
    return username;
}

// ��ȡ����ĺ�����ʵ��
std::string User::getPassword() 
{
    return password;
}

// �����û����ĺ�����ʵ��
void User::setUsername(std::string name) 
{
    username = name;
}

//��������ĺ�����ʵ��
void User::setPassword(std::string pass)
{
    password = pass;
}

// ע���û��ĺ�����ʵ��
bool User::registerUser(std::vector<User>users)
{
    // ��ȡ�û���
    char n[21];
    InputBox(n, 20, "�������û���(1~20���ַ�)");
    std::string name(n);

    // ����û����Ƿ��Ѿ�����
    for (User& user : users)
    {
        if (user.getUsername() == name || name.empty() || name.length() > 20)
        {
            return false; // �û����Ѵ��ڣ�ע��ʧ��
        }
    }

    // ��ȡ����
    char p[21];
    InputBox(p, 20, "����������(1~20���ַ�)");
    std::string pass(p);

    // �������û�����ӵ��û�������
    this->setUsername(name);
    this->setPassword(pass);

    return true; // ע��ɹ�
}

// ��¼�ĺ�����ʵ��
bool User::loginUser(std::vector<User>users)
{
    // ��ȡ�û���
    char n[21];
    InputBox(n, 20, "�������û���(1~20���ַ�)");
    std::string name(n);

    // ��ȡ����
    char p[21];
    InputBox(p, 20, "����������(1~20���ַ�)");
    std::string pass(p);

    // ����û��Ƿ���ڲ���������ȷ
    for (User& user : users)
    {
        if (user.getUsername() == name && user.getPassword() == pass && pass.length()>0 && pass.length() <21)
        {
            *this = user;
            return true; // ��¼�ɹ�
        }
    }
    return false; // ��¼ʧ��
}

// ��սʱ��ĺ���
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




