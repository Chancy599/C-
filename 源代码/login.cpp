#include"login.h"

bool isPlaying = false; // ���ڸ������ֵ�ǰ��״̬
bool isOpened = false; // ���ڸ�����Ƶ�ļ��Ƿ��Ѿ���
bool shouldTerminate = false; // ���ڱ���Ƿ���Ҫ��ֹ�߳�

void login(MODE& mode, int& second, int& score, std::vector<User>& users,IMAGE &bkimg)
{
    // ��ť����
    MOUSEMSG mouseMsg;

    loadUserInfoFromFile(users);

    while (true)
    {
        putimage(0, 0, &bkimg);
        bool loggedIn = false;

        //��Ϸ����
        IMAGE introimg;
        loadimage(&introimg, "introimg.png", 60, 60);
        putimage(930, 0, &introimg);

        // ���ð�ť��ɫ
        setlinecolor(BLACK); // ���ð�ť�߿���ɫΪ��ɫ
        setfillcolor(RGB(0, 255, 255)); // ���ð�ť�����ɫΪ����ɫ

        // ����������ɫ�ʹ�С
        setbkmode(TRANSPARENT); // �������ֱ���ɫ͸��
        settextcolor(RGB(50, 50, 50)); // ����������ɫ����һ��
        settextstyle(20, 0, _T("����")); // ����������ʽΪ���壬��СΪ20

        // ���ư�ť
        // ע�ᰴť
        RECT registerButtonRect = { 397, 166, 573, 216 };
        rectangle(registerButtonRect.left, registerButtonRect.top, registerButtonRect.right, registerButtonRect.bottom);
        floodfill((registerButtonRect.left + registerButtonRect.right) / 2, (registerButtonRect.top + registerButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((registerButtonRect.left + registerButtonRect.right - textwidth(_T("ע��"))) / 2, (registerButtonRect.top + registerButtonRect.bottom - textheight(_T("ע��"))) / 2, _T("ע��"));

        // ��¼��ť
        RECT loginButtonRect = { 397, 266, 573, 316 };
        rectangle(loginButtonRect.left, loginButtonRect.top, loginButtonRect.right, loginButtonRect.bottom);
        floodfill((loginButtonRect.left + loginButtonRect.right) / 2, (loginButtonRect.top + loginButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((loginButtonRect.left + loginButtonRect.right - textwidth(_T("��¼"))) / 2, (loginButtonRect.top + loginButtonRect.bottom - textheight(_T("��¼"))) / 2, _T("��¼"));

        // ˫����Ϸ��ť
        RECT coupleButtonRect = { 397, 366, 573, 416 };
        rectangle(coupleButtonRect.left, coupleButtonRect.top, coupleButtonRect.right, coupleButtonRect.bottom);
        floodfill((coupleButtonRect.left + coupleButtonRect.right) / 2, (coupleButtonRect.top + coupleButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((coupleButtonRect.left + coupleButtonRect.right - textwidth(_T("˫��"))) / 2, (coupleButtonRect.top + coupleButtonRect.bottom - textheight(_T("˫��"))) / 2, _T("˫��"));

        // �˳���Ϸ��ť
        RECT exitButtonRect = { 397, 466, 573, 516 };
        rectangle(exitButtonRect.left, exitButtonRect.top, exitButtonRect.right, exitButtonRect.bottom);
        floodfill((exitButtonRect.left + exitButtonRect.right) / 2, (exitButtonRect.top + exitButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((exitButtonRect.left + exitButtonRect.right - textwidth(_T("�˳�"))) / 2, (exitButtonRect.top + exitButtonRect.bottom - textheight(_T("�˳�"))) / 2, _T("�˳�"));

        while (true)
        {
            mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) // ֻ�������������ʱ�ż���ִ��
                break;
            Sleep(1); 
        }
        int mouseX = mouseMsg.x;
        int mouseY = mouseMsg.y;

        // ע�ᰴť���
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= registerButtonRect.left && mouseX <= registerButtonRect.right && mouseY >= registerButtonRect.top && mouseY <= registerButtonRect.bottom)
        {
            User user;
            if (user.registerUser(users))
            {
                MessageBox(NULL, "ע��ɹ���", "ע��", MB_ICONINFORMATION);
                users.push_back(user);
                saveUserInfoToFile(user);
            }
            else
            {
                MessageBox(NULL, "ע��ʧ�ܣ������ԣ�", "ע��", MB_ICONERROR);
            }
        }

        // ��¼��ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= loginButtonRect.left && mouseX <= loginButtonRect.right && mouseY >= loginButtonRect.top && mouseY <= loginButtonRect.bottom)
        {
            User user;
            if (user.loginUser(users))
            {
                MessageBox(NULL, "��¼�ɹ���", "��¼", MB_ICONINFORMATION);
                if (menu(mode, second, score, users, bkimg))
                {
                    modify(user, second, score, mode);
                }
                continue;
            }
            else
            {
                MessageBox(NULL, "��¼ʧ�ܣ������ԣ�", "��¼", MB_ICONERROR);
            }
        }

        // ˫����Ϸ��ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= coupleButtonRect.left && mouseX <= coupleButtonRect.right && mouseY >= coupleButtonRect.top && mouseY <= coupleButtonRect.bottom)
        {
            couplemode(mode, bkimg);
        }

        // ��Ϸ���ܵ��
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= 930 && mouseX <= 990 && mouseY >= 0 && mouseY <= 60)
        {
            intro();
        }

        // �˳���ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= exitButtonRect.left && mouseX <= exitButtonRect.right && mouseY >= exitButtonRect.top && mouseY <= exitButtonRect.bottom)
        {
            int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
            if (IDOK == result)
            {
                shouldTerminate = true;
                return;
            }
        }
    }
}

//��Ϸ����
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

    // ����������ɫ�ʹ�С
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 0, _T("����"));

    // ��ʾ��Ϸ�����ı�
    outtextxy(422, 91, _T("��Ϸ����")); // �޸�Ϊʵ�ʵ���Ϸ������Ϣ

    // ���ƹر���Ϸ��ť
    RECT closeButtonRect = { 432, 541, 558, 591 };
    setlinecolor(BLACK);
    setfillcolor(LIGHTBLUE);
    rectangle(closeButtonRect.left, closeButtonRect.top, closeButtonRect.right, closeButtonRect.bottom);
    floodfill((closeButtonRect.left + closeButtonRect.right) / 2, (closeButtonRect.top + closeButtonRect.bottom) / 2, BLACK);
    outtextxy((closeButtonRect.left + closeButtonRect.right - textwidth(_T("�رս���"))) / 2, (closeButtonRect.top + closeButtonRect.bottom - textheight(_T("�رս���"))) / 2, _T("�رս���"));

    while (true)
    {
        MOUSEMSG mouseMsg = GetMouseMsg();
        if (mouseMsg.uMsg == WM_LBUTTONDOWN)
        {
            int mouseX = mouseMsg.x;
            int mouseY = mouseMsg.y;
            // ����رս��ܰ�ť
            if (mouseX >= closeButtonRect.left && mouseX <= closeButtonRect.right &&
                mouseY >= closeButtonRect.top && mouseY <= closeButtonRect.bottom)
            {
                return;
            }
        }
    }
}

// �����û���Ϣ���ı��ļ�
void saveUserInfoToFile(User &user) 
{
    std::ofstream ofs;
    ofs.open("user.csv", std::ios::out | std::ios::app);
    std::string simpleTimeStr, difficultTimeStr ,challengeScoreStr; // ��ʱ�洢�ַ���
    simpleTimeStr = std::to_string(user.getsimpleTime());
    difficultTimeStr = std::to_string(user.getdifficultTime());
    challengeScoreStr = std::to_string(user.getchallengeScore());
    ofs << user.getUsername() << "," << user.getPassword() << "," << simpleTimeStr << "," << difficultTimeStr << "," << challengeScoreStr << ","<<std::endl;
    ofs.close();
}

// ���ı��ļ������û���Ϣ
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

//�����û��ɼ�
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
            row.pop_back(); // ȥ��ĩβ�Ķ���
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
    //���ż�����Ч
    mciSendString("open bgm3.mp3", 0, 0, 0);
    mciSendString("play bgm3.mp3", 0, 0, 0);

    IMAGE loadimg;
    loadimage(&loadimg, "load.png", 990, 660);
    putimage(0, 0, &loadimg);
    // ���ñ߿���ɫΪ��ɫ
    setcolor(WHITE);
    rectangle(345, 316, 645, 366);
    // �ھ����·�д��
    settextstyle(30, 0, _T("����")); // ���������СΪ30������Ϊ����
    setbkmode(TRANSPARENT); // ���ñ���͸��
    setcolor(WHITE); // ����������ɫΪ��ɫ
    outtextxy(395, 416, _T("��Ϸ�����С���")); // ��ָ��λ��д��
    settextstyle(80, 0, _T("�����п�")); // ���������СΪ80������Ϊ�����п�
    outtextxy(335, 166, _T("ֲ������")); // ��ָ��λ��д��

    // ��������
    for (int x = 345; x < 645; x += 3)
    { 
        // ÿ���ƶ�2������
        setfillcolor(WHITE); // ���������ɫΪ��ɫ
        solidrectangle(x, 316, x + 3, 366); // ���һ��ʵ�ľ���
        Sleep(30); // �ȴ�30���룬ʹ�þ���������
    }
    mciSendString("close bgm3.mp3", NULL, 0, NULL);
}

void couplemode(MODE& mode,IMAGE &bkimg)
{
    //���ſ�ʼ��Ч
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
            if ((GetAsyncKeyState('w') || GetAsyncKeyState('W')) && y1 > 3 * IMGW)//�ϼ�
            {
                putimage(x1 - 4, y1 - 4, &bk);
                y1 -= 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('s') || GetAsyncKeyState('S')) && y1 < 7 * IMGW)//�¼�
            {
                putimage(x1 - 4, y1 - 4, &bk);
                y1 += 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('a') || GetAsyncKeyState('A')) && x1 > 2 * IMGW)//���
            {
                putimage(x1 - 4, y1 - 4, &bk);
                x1 -= 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('d') || GetAsyncKeyState('D')) && x1 < 6 * IMGW)//�Ҽ�
            {
                putimage(x1 - 4, y1 - 4, &bk);
                x1 += 66;
                fillcircle(x1, y1, 5);
            }
            if ((GetAsyncKeyState('i') || GetAsyncKeyState('I')) && y2 > 3 * IMGW)//�ϼ�
            {
                putimage(x2 - 4, y2 - 4, &bk);
                y2 -= 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('k') || GetAsyncKeyState('K')) && y2 < 7 * IMGW)//�¼�
            {
                putimage(x2 - 4, y2 - 4, &bk);
                y2 += 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('j') || GetAsyncKeyState('J')) && x2 > 9 * IMGW)//���
            {
                putimage(x2 - 4, y2 - 4, &bk);
                x2 -= 66;
                fillcircle(x2, y2, 5);
            }
            if ((GetAsyncKeyState('l') || GetAsyncKeyState('L')) && x2 < 13 * IMGW)//�Ҽ�
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
                //���������Ч
                mciSendString("close bgm5.mp3", NULL, 0, NULL);
                mciSendString("open bgm5.mp3", 0, 0, 0);
                mciSendString("play bgm5.mp3", 0, 0, 0);

                int choose = MessageBox(NULL, "��Ҽ׻�ʤ���Ƿ������Ϸ", "PK����", MB_OKCANCEL);
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
                //���������Ч
                mciSendString("close bgm5.mp3", NULL, 0, NULL);
                mciSendString("open bgm5.mp3", 0, 0, 0);
                mciSendString("play bgm5.mp3", 0, 0, 0);

                int choose = MessageBox(NULL, "����һ�ʤ���Ƿ������Ϸ", "PK����", MB_OKCANCEL);
                if (IDOK == choose)
                {
                    break;
                }
                else
                {
                    return;
                }
            }
            if (GetAsyncKeyState(32))//����ո�����˳���Ϸ
            {
                return;
            }
            Sleep(300); // ��ִͣ�� 300 ����
        }
    }
}

void pauseBGM() 
{
    mciSendString("pause BGM", 0, 0, 0);
    isPlaying = false; // ����״̬Ϊ��ͣ
}

void resumeBGM() 
{
    mciSendString("resume BGM", 0, 0, 0);
    isPlaying = true; // ����״̬Ϊ���ڲ���
}

void BGM()
{
    if (!isOpened)
    {
        mciSendString("open bgm1.mp3 alias BGM", 0, 0, 0);
        isOpened = true;
    }

    mciSendString("play BGM repeat", 0, 0, 0);
    isPlaying = true; // ����״̬Ϊ���ڲ���

    bool keyPressed = false; // ����Ƿ��Ѿ�������Esc ��

    // ��������Ϣ
    while (!shouldTerminate)
    {
        // ����Ƿ�����Esc��������ȷ��ֻ����һ�ΰ����¼�
        if (GetAsyncKeyState(VK_ESCAPE) && !keyPressed)
        {
            // �л�����״̬
            if (isPlaying)
            {
                pauseBGM();
            }
            else
            {
                resumeBGM();
            }
            // ��ǰ����Ѵ���
            keyPressed = true;
        }
        else if (!GetAsyncKeyState(VK_ESCAPE))
        {
            // ���û�а���Esc���������ñ�־
            keyPressed = false;
        }
        Sleep(100);
    }
    mciSendString("close BGM", 0, 0, 0);
    return;
}