#include"login.h"

bool isPlaying = false; // 用于跟踪音乐当前的状态
bool isOpened = false; // 用于跟踪音频文件是否已经打开
bool shouldTerminate = false; // 用于标记是否需要终止线程

void login(MODE& mode, int& second, int& score, std::vector<User>& users,IMAGE &bkimg)
{
    // 按钮交互
    MOUSEMSG mouseMsg;

    loadUserInfoFromFile(users);

    while (true)
    {
        putimage(0, 0, &bkimg);
        bool loggedIn = false;

        //游戏介绍
        IMAGE introimg;
        loadimage(&introimg, "introimg.png", 60, 60);
        putimage(930, 0, &introimg);

        // 设置按钮颜色
        setlinecolor(BLACK); // 设置按钮边框颜色为黑色
        setfillcolor(RGB(0, 255, 255)); // 设置按钮填充颜色为青绿色

        // 设置字体颜色和大小
        setbkmode(TRANSPARENT); // 设置文字背景色透明
        settextcolor(RGB(50, 50, 50)); // 设置字体颜色稍深一点
        settextstyle(20, 0, _T("宋体")); // 设置字体样式为宋体，大小为20

        // 绘制按钮
        // 注册按钮
        RECT registerButtonRect = { 397, 166, 573, 216 };
        rectangle(registerButtonRect.left, registerButtonRect.top, registerButtonRect.right, registerButtonRect.bottom);
        floodfill((registerButtonRect.left + registerButtonRect.right) / 2, (registerButtonRect.top + registerButtonRect.bottom) / 2, BLACK); // 填充按钮颜色
        outtextxy((registerButtonRect.left + registerButtonRect.right - textwidth(_T("注册"))) / 2, (registerButtonRect.top + registerButtonRect.bottom - textheight(_T("注册"))) / 2, _T("注册"));

        // 登录按钮
        RECT loginButtonRect = { 397, 266, 573, 316 };
        rectangle(loginButtonRect.left, loginButtonRect.top, loginButtonRect.right, loginButtonRect.bottom);
        floodfill((loginButtonRect.left + loginButtonRect.right) / 2, (loginButtonRect.top + loginButtonRect.bottom) / 2, BLACK); // 填充按钮颜色
        outtextxy((loginButtonRect.left + loginButtonRect.right - textwidth(_T("登录"))) / 2, (loginButtonRect.top + loginButtonRect.bottom - textheight(_T("登录"))) / 2, _T("登录"));

        // 双人游戏按钮
        RECT coupleButtonRect = { 397, 366, 573, 416 };
        rectangle(coupleButtonRect.left, coupleButtonRect.top, coupleButtonRect.right, coupleButtonRect.bottom);
        floodfill((coupleButtonRect.left + coupleButtonRect.right) / 2, (coupleButtonRect.top + coupleButtonRect.bottom) / 2, BLACK); // 填充按钮颜色
        outtextxy((coupleButtonRect.left + coupleButtonRect.right - textwidth(_T("双人"))) / 2, (coupleButtonRect.top + coupleButtonRect.bottom - textheight(_T("双人"))) / 2, _T("双人"));

        // 退出游戏按钮
        RECT exitButtonRect = { 397, 466, 573, 516 };
        rectangle(exitButtonRect.left, exitButtonRect.top, exitButtonRect.right, exitButtonRect.bottom);
        floodfill((exitButtonRect.left + exitButtonRect.right) / 2, (exitButtonRect.top + exitButtonRect.bottom) / 2, BLACK); // 填充按钮颜色
        outtextxy((exitButtonRect.left + exitButtonRect.right - textwidth(_T("退出"))) / 2, (exitButtonRect.top + exitButtonRect.bottom - textheight(_T("退出"))) / 2, _T("退出"));

        while (true)
        {
            mouseMsg = GetMouseMsg(); // 获取鼠标消息
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) // 只有在鼠标左键点击时才继续执行
                break;
            Sleep(1); 
        }
        int mouseX = mouseMsg.x;
        int mouseY = mouseMsg.y;

        // 注册按钮点击
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= registerButtonRect.left && mouseX <= registerButtonRect.right && mouseY >= registerButtonRect.top && mouseY <= registerButtonRect.bottom)
        {
            User user;
            if (user.registerUser(users))
            {
                MessageBox(NULL, "注册成功！", "注册", MB_ICONINFORMATION);
                users.push_back(user);
                saveUserInfoToFile(user);
            }
            else
            {
                MessageBox(NULL, "注册失败，请重试！", "注册", MB_ICONERROR);
            }
        }

        // 登录按钮点击
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= loginButtonRect.left && mouseX <= loginButtonRect.right && mouseY >= loginButtonRect.top && mouseY <= loginButtonRect.bottom)
        {
            User user;
            if (user.loginUser(users))
            {
                MessageBox(NULL, "登录成功！", "登录", MB_ICONINFORMATION);
                if (menu(mode, second, score, users, bkimg))
                {
                    modify(user, second, score, mode);
                }
                continue;
            }
            else
            {
                MessageBox(NULL, "登录失败，请重试！", "登录", MB_ICONERROR);
            }
        }

        // 双人游戏按钮点击
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= coupleButtonRect.left && mouseX <= coupleButtonRect.right && mouseY >= coupleButtonRect.top && mouseY <= coupleButtonRect.bottom)
        {
            couplemode(mode, bkimg);
        }

        // 游戏介绍点击
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= 930 && mouseX <= 990 && mouseY >= 0 && mouseY <= 60)
        {
            intro();
        }

        // 退出按钮点击
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= exitButtonRect.left && mouseX <= exitButtonRect.right && mouseY >= exitButtonRect.top && mouseY <= exitButtonRect.bottom)
        {
            int result = MessageBox(NULL, "确定退出？", "退出", MB_OKCANCEL);
            if (IDOK == result)
            {
                shouldTerminate = true;
                return;
            }
        }
    }
}

//游戏介绍
void intro()
{
    IMAGE introImage;
    loadimage(&introImage, "intro.png", COL * IMGW, (ROW + 2) * IMGW);
    putimage(297, 66, &introImage);
    IMAGE cell[4];
    loadimage(cell + 0, "cell/0.jpg", 23, 23);
    loadimage(cell + 1, "cell/1.jpg", 23, 23);
    loadimage(cell + 2, "cell/2.jpg", 23, 23);
    loadimage(cell + 3, "cell/3.jpg", 23, 23);

    putimage(327, 129, cell + 0);
    putimage(327, 177, cell + 2);
    putimage(327, 225, cell + 1);
    putimage(327, 273, cell + 3);

    // 设置文字颜色和大小
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 0, _T("宋体"));

    // 显示游戏介绍文本
    outtextxy(422, 91, _T("游戏介绍")); // 修改为实际的游戏介绍信息

    // 绘制关闭游戏按钮
    RECT closeButtonRect = { 432, 541, 558, 591 };
    setlinecolor(BLACK);
    setfillcolor(LIGHTBLUE);
    rectangle(closeButtonRect.left, closeButtonRect.top, closeButtonRect.right, closeButtonRect.bottom);
    floodfill((closeButtonRect.left + closeButtonRect.right) / 2, (closeButtonRect.top + closeButtonRect.bottom) / 2, BLACK);
    outtextxy((closeButtonRect.left + closeButtonRect.right - textwidth(_T("关闭介绍"))) / 2, (closeButtonRect.top + closeButtonRect.bottom - textheight(_T("关闭介绍"))) / 2, _T("关闭介绍"));

    while (true)
    {
        MOUSEMSG mouseMsg = GetMouseMsg();
        if (mouseMsg.uMsg == WM_LBUTTONDOWN)
        {
            int mouseX = mouseMsg.x;
            int mouseY = mouseMsg.y;
            // 点击关闭介绍按钮
            if (mouseX >= closeButtonRect.left && mouseX <= closeButtonRect.right &&
                mouseY >= closeButtonRect.top && mouseY <= closeButtonRect.bottom)
            {
                return;
            }
        }
    }
}

// 保存用户信息到文本文件
void saveUserInfoToFile(User &user) 
{
    std::ofstream ofs;
    ofs.open("user.csv", std::ios::out | std::ios::app);
    std::string simpleTimeStr, difficultTimeStr ,challengeScoreStr; // 临时存储字符串
    simpleTimeStr = std::to_string(user.getsimpleTime());
    difficultTimeStr = std::to_string(user.getdifficultTime());
    challengeScoreStr = std::to_string(user.getchallengeScore());
    ofs << user.getUsername() << "," << user.getPassword() << "," << simpleTimeStr << "," << difficultTimeStr << "," << challengeScoreStr << ","<<std::endl;
    ofs.close();
}

// 从文本文件加载用户信息
void loadUserInfoFromFile(std::vector<User>& users) 
{
    std::ifstream ifs("user.csv");

    std::string line;
    while (std::getline(ifs, line))
    {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        if (tokens.size() == 5)
        {
            users.emplace_back(tokens[0], tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
        }
    }
    ifs.close();
}

//更新用户成绩
void modify(User& user,int& newTime,int& score,MODE& mode) 
{
    std::ifstream file("user.csv");

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line)) 
    {
        lines.push_back(line);
    }

    file.close();

    for (auto& row : lines) 
    {
        std::stringstream ss(row);
        std::vector<std::string> fields;
        std::string field;
        while (getline(ss, field, ',')) 
        {
            fields.push_back(field);
        }

        if (fields.size() >= 5 && fields[0] == user.getUsername()) 
        {
            if (mode == simple)
            {
                user.setsimpleTime(newTime);
                fields[2] = std::to_string(user.getsimpleTime());
                
            }
            else if(mode==difficult)
            {
                user.setdifficultTime(newTime);
                fields[3] = std::to_string(user.getdifficultTime());
                
            }
            else if (mode == challenge)
            {
                user.setchallengeScore(score);
                fields[4] = std::to_string(user.getchallengeScore());
            }
            row.clear();
            for (const auto& field : fields) 
            {
                row += field + ",";
            }
            row.pop_back(); // 去掉末尾的逗号
            break;
        }
    }
    std::ofstream outFile("user.csv");
    for (const auto& line : lines) 
    {
        outFile << line << std::endl;
    }
    outFile.close();
}

void load()
{
    //播放加载音效
    mciSendString("open bgm3.mp3", 0, 0, 0);
    mciSendString("play bgm3.mp3", 0, 0, 0);

    IMAGE loadimg;
    loadimage(&loadimg, "load.png", 990, 660);
    putimage(0, 0, &loadimg);
    // 设置边框颜色为白色
    setcolor(WHITE);
    rectangle(345, 316, 645, 366);
    // 在矩形下方写字
    settextstyle(30, 0, _T("宋体")); // 设置字体大小为30，字体为宋体
    setbkmode(TRANSPARENT); // 设置背景透明
    setcolor(WHITE); // 设置字体颜色为白色
    outtextxy(395, 416, _T("游戏加载中……")); // 在指定位置写字
    settextstyle(80, 0, _T("华文行楷")); // 设置字体大小为80，字体为华文行楷
    outtextxy(335, 166, _T("植此青绿")); // 在指定位置写字

    // 逐步填充矩形
    for (int x = 345; x < 645; x += 3)
    { 
        // 每次移动2个像素
        setfillcolor(WHITE); // 设置填充颜色为白色
        solidrectangle(x, 316, x + 3, 366); // 填充一个实心矩形
        Sleep(30); // 等待30毫秒，使得矩形逐渐增加
    }
    mciSendString("close bgm3.mp3", NULL, 0, NULL);
}

void couplemode(MODE& mode,IMAGE &bkimg)
{
    //播放开始音效
    mciSendString("close bgm4.mp3", NULL, 0, NULL);
    mciSendString("open bgm4.mp3", 0, 0, 0);
    mciSendString("play bgm4.mp3", 0, 0, 0);

    putimage(0, 0, &bkimg);

    selectMode(mode);

    IMAGE player[2];
    loadimage(player + 0, "player1.png", 6 * IMGW, IMGW);
    loadimage(player + 1, "player2.png", 6 * IMGW, IMGW);
    putimage(IMGW, IMGW, player + 0);
    putimage(8 * IMGW, IMGW, player + 1);
    IMAGE bk;
    loadimage(&bk, "bk.png", IMGW, IMGW);
    
    while (true)
    {
        Map m1;
        Map	m2;
        m1.initMapnum();
        m2.initMapnum();
        m1.draw(mode, 66, 66);
        m2.draw(mode, 528, 66);
        
        putimage(IMGW, 8 * IMGW, &bk);
        putimage(8 * IMGW, 8 * IMGW, &bk);
        putimage(2 * IMGW, 8 * IMGW, &bk);
        putimage(9 * IMGW, 8 * IMGW, &bk);

        setlinecolor(BLUE);
        for (int i = 0; i < 8; i++)
        {
            line(IMGW, (i + 2) * IMGW, 7 * IMGW, (i + 2) * IMGW);
            line(8 * IMGW, (i + 2) * IMGW, 14 * IMGW, (i + 2) * IMGW);
            line((i + 1) * IMGW, 2 * IMGW, (i + 1) * IMGW, 9 * IMGW);
            line((i + 8) * IMGW, 2 * IMGW, (i + 8) * IMGW, 9 * IMGW);
        }
        int x1 = IMGW + 5;
        int y1 = 2 * IMGW + 5;
        int x2 = 8 * IMGW + 5;
        int y2 = 2 * IMGW + 5;
        std::stack<Map> historyStack1;
        std::stack<Map> historyStack2;
        historyStack1.push(m1);
        historyStack2.push(m2);
        IMAGE digit[10];
        for (int i = 0; i < 10; ++i)
        {
            char filename[20];
            sprintf_s(filename, "digit/%02d.png", i);
            loadimage(&digit[i], filename, 15, 15);
        }

        refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
        refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
        IMAGE bk;
        loadimage(&bk, "bk.png", 10, 10);
        setfillcolor(YELLOW);
        fillcircle(x1, y1, 5);
        fillcircle(x2, y2, 5);
        while (true)
        {
            if ((GetAsyncKeyState('w') || GetAsyncKeyState('W')) && y1 > 3 * IMGW)//上键
            {
                putimage(x1 - 4, y1 - 4, &bk);
                y1 -= 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('s') || GetAsyncKeyState('S')) && y1 < 7 * IMGW)//下键
            {
                putimage(x1 - 4, y1 - 4, &bk);
                y1 += 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('a') || GetAsyncKeyState('A')) && x1 > 2 * IMGW)//左键
            {
                putimage(x1 - 4, y1 - 4, &bk);
                x1 -= 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('d') || GetAsyncKeyState('D')) && x1 < 6 * IMGW)//右键
            {
                putimage(x1 - 4, y1 - 4, &bk);
                x1 += 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('i') || GetAsyncKeyState('I')) && y2 > 3 * IMGW)//上键
            {
                putimage(x2 - 4, y2 - 4, &bk);
                y2 -= 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('k') || GetAsyncKeyState('K')) && y2 < 7 * IMGW)//下键
            {
                putimage(x2 - 4, y2 - 4, &bk);
                y2 += 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('j') || GetAsyncKeyState('J')) && x2 > 9 * IMGW)//左键
            {
                putimage(x2 - 4, y2 - 4, &bk);
                x2 -= 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('l') || GetAsyncKeyState('L')) && x2 < 13 * IMGW)//右键
            {
                putimage(x2 - 4, y2 - 4, &bk);
                x2 += 66;
                fillcircle(x2, y2, 5);
            }
            if (GetAsyncKeyState('1'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m1.setmatric((y1 - 2 * IMGW) / IMGW, (x1 - IMGW) / IMGW, 1,0);
                historyStack1.push(m1);
                refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
            }
            if (GetAsyncKeyState('2'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m1.setmatric((y1 - 2 * IMGW) / IMGW, (x1 - IMGW) / IMGW, 2,0);
                historyStack1.push(m1);
                refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
            }
            if (GetAsyncKeyState('3'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m1.setmatric((y1 - 2 * IMGW) / IMGW, (x1 - IMGW) / IMGW, 3,0);
                historyStack1.push(m1);
                refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
            }
            if (GetAsyncKeyState('4'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m1.setmatric((y1 - 2 * IMGW) / IMGW, (x1 - IMGW) / IMGW, 4,0);
                historyStack1.push(m1);
                refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
            }
            if (GetAsyncKeyState('7'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m2.setmatric((y2 - 2 * IMGW) / IMGW, (x2 - 8 * IMGW) / IMGW, 1,0);
                historyStack2.push(m2);
                refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
            }
            if (GetAsyncKeyState('8'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m2.setmatric((y2 - 2 * IMGW) / IMGW, (x2 - 8 * IMGW) / IMGW, 2,0);
                historyStack2.push(m2);
                refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
            }
            if (GetAsyncKeyState('9'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m2.setmatric((y2 - 2 * IMGW) / IMGW, (x2 - 8 * IMGW) / IMGW, 3,0);
                historyStack2.push(m2);
                refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
            }
            if (GetAsyncKeyState('0'))
            {
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                m2.setmatric((y2 - 2 * IMGW) / IMGW, (x2 - 8 * IMGW) / IMGW, 4,0);
                historyStack2.push(m2);
                refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
            }
            if ((GetAsyncKeyState('z') || GetAsyncKeyState('Z')) && historyStack1.size() > 1)
            {
                historyStack1.pop();
                m1 = historyStack1.top();
                refresh(IMGW + 51, IMGW, IMGW + 51, IMGW, m1, digit, digit);
            }
            if ((GetAsyncKeyState('m') || GetAsyncKeyState('M')) && historyStack2.size() > 1)
            {
                historyStack2.pop();
                m2 = historyStack2.top();
                refresh(8 * IMGW + 51, IMGW, 8 * IMGW + 51, IMGW, m2, digit, digit);
            }
            if (m1.finish(mode))
            {
                //播放完成音效
                mciSendString("close bgm5.mp3", NULL, 0, NULL);
                mciSendString("open bgm5.mp3", 0, 0, 0);
                mciSendString("play bgm5.mp3", 0, 0, 0);

                int choose = MessageBox(NULL, "玩家甲获胜！是否继续游戏", "PK结束", MB_OKCANCEL);
                if (IDOK == choose)
                {
                    break;
                }
                else
                {
                    return;
                }
            }
            if (m2.finish(mode))
            {
                //播放完成音效
                mciSendString("close bgm5.mp3", NULL, 0, NULL);
                mciSendString("open bgm5.mp3", 0, 0, 0);
                mciSendString("play bgm5.mp3", 0, 0, 0);

                int choose = MessageBox(NULL, "玩家乙获胜！是否继续游戏", "PK结束", MB_OKCANCEL);
                if (IDOK == choose)
                {
                    break;
                }
                else
                {
                    return;
                }
            }
            if (GetAsyncKeyState(32))//点击空格键，退出游戏
            {
                return;
            }
            Sleep(300); // 暂停执行 300 毫秒
        }
    }
}

void pauseBGM() 
{
    mciSendString("pause BGM", 0, 0, 0);
    isPlaying = false; // 设置状态为暂停
}

void resumeBGM() 
{
    mciSendString("resume BGM", 0, 0, 0);
    isPlaying = true; // 设置状态为正在播放
}

void BGM()
{
    if (!isOpened)
    {
        mciSendString("open bgm1.mp3 alias BGM", 0, 0, 0);
        isOpened = true;
    }

    mciSendString("play BGM repeat", 0, 0, 0);
    isPlaying = true; // 设置状态为正在播放

    bool keyPressed = false; // 标记是否已经按下了Esc 键

    // 处理按键消息
    while (!shouldTerminate)
    {
        // 检查是否按下了Esc键，并且确保只处理一次按键事件
        if (GetAsyncKeyState(VK_ESCAPE) && !keyPressed)
        {
            // 切换播放状态
            if (isPlaying)
            {
                pauseBGM();
            }
            else
            {
                resumeBGM();
            }
            // 标记按键已处理
            keyPressed = true;
        }
        else if (!GetAsyncKeyState(VK_ESCAPE))
        {
            // 如果没有按下Esc键，则重置标志
            keyPressed = false;
        }
        Sleep(100);
    }
    mciSendString("close BGM", 0, 0, 0);
    return;
}