#include"menu.h"
#include"backtrack.h"

bool stopTimer = false; 
bool isfinished = false;

bool menu(MODE& mode,int& second, int& score,std::vector<User>&users,IMAGE &bkimg)
{
    // ��ť����
    MOUSEMSG mouseMsg;
    while (true)
    {
        putimage(0, 0, &bkimg);

        // ���ð�ť��ɫ
        setlinecolor(BLACK); // ���ð�ť�߿���ɫΪ��ɫ
        setfillcolor(RGB(0, 255, 255)); // ���ð�ť�����ɫΪ����ɫ

        // ����������ɫ�ʹ�С
        setbkmode(TRANSPARENT); // �������ֱ���ɫ͸��
        settextcolor(RGB(50, 50, 50)); // ����������ɫ����һ��
        settextstyle(20, 0, _T("����")); // ����������ʽΪ���壬��СΪ20

        // ���ư�ť
        // �����Ϸ��ť
        RECT designButtonRect = { 397, 166, 573, 216 };
        rectangle(designButtonRect.left, designButtonRect.top, designButtonRect.right, designButtonRect.bottom);
        floodfill((designButtonRect.left + designButtonRect.right) / 2, (designButtonRect.top + designButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((designButtonRect.left + designButtonRect.right - textwidth(_T("�����Ϸ"))) / 2, (designButtonRect.top + designButtonRect.bottom - textheight(_T("�����Ϸ"))) / 2, _T("�����Ϸ"));

        // ������а�ť
        RECT rankButtonRect = { 397, 266, 573, 316 };
        rectangle(rankButtonRect.left, rankButtonRect.top, rankButtonRect.right, rankButtonRect.bottom);
        floodfill((rankButtonRect.left + rankButtonRect.right) / 2, (rankButtonRect.top + rankButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((rankButtonRect.left + rankButtonRect.right - textwidth(_T("�������"))) / 2, (rankButtonRect.top + rankButtonRect.bottom - textheight(_T("�������"))) / 2, _T("�������"));

        // ��ʼ��Ϸ��ť
        RECT startButtonRect = { 397, 366, 573, 416 };
        rectangle(startButtonRect.left, startButtonRect.top, startButtonRect.right, startButtonRect.bottom);
        floodfill((startButtonRect.left + startButtonRect.right) / 2, (startButtonRect.top + startButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((startButtonRect.left + startButtonRect.right - textwidth(_T("��ʼ��Ϸ"))) / 2, (startButtonRect.top + startButtonRect.bottom - textheight(_T("��ʼ��Ϸ"))) / 2, _T("��ʼ��Ϸ"));

        // �رղ˵���ť
        RECT closeButtonRect = { 397, 466, 573, 516 };
        rectangle(closeButtonRect.left, closeButtonRect.top, closeButtonRect.right, closeButtonRect.bottom);
        floodfill((closeButtonRect.left + closeButtonRect.right) / 2, (closeButtonRect.top + closeButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((closeButtonRect.left + closeButtonRect.right - textwidth(_T("�رղ˵�"))) / 2, (closeButtonRect.top + closeButtonRect.bottom - textheight(_T("�رղ˵�"))) / 2, _T("�رղ˵�"));

        //��ⰴť
        IMAGE questionimg;
        loadimage(&questionimg, "question.png", 60, 60);
        putimage(930, 0, &questionimg);

        while (true)
        {
            mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) // ֻ�������������ʱ�ż���ִ��
                break;
            Sleep(1);
        }
        int mouseX = mouseMsg.x;
        int mouseY = mouseMsg.y;

        // ��Ϸ��ư�ť���
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= designButtonRect.left && mouseX <= designButtonRect.right && mouseY >= designButtonRect.top && mouseY <= designButtonRect.bottom)
        {
            design(mode, second,bkimg);
        }
        // ������а�ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= rankButtonRect.left && mouseX <= rankButtonRect.right && mouseY >= rankButtonRect.top && mouseY <= rankButtonRect.bottom)
        {
            rank(users);
        }
        // ��ʼ��Ϸ��ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= startButtonRect.left && mouseX <= startButtonRect.right && mouseY >= startButtonRect.top && mouseY <= startButtonRect.bottom)
        {
            //ѡ����Ϸģʽ
            if (gamemode(mode, bkimg))
            {
                if (mode == challenge)
                {
                    challengeMode(score, users, bkimg);
                    return true;
                }
                else
                {
                    Map map;
                    map.initMapnum();
                    map.mapfile();
                    map.draw(mode, 297, 66);
                    map.draw();

                    // ����ֹͣ��ʱ���ı�־λ
                    stopTimer = false;
                    second = 0;
                    isfinished = false;

                    // ���������̣߳��ֱ�ִ�� play �� timer ����
                    std::thread playThread(play, std::ref(map), std::ref(mode));
                    std::thread timerThread(timer, std::ref(second));

                    // �ȴ� playThread ִ�����
                    playThread.join();
                    stopTimer = true;

                    // �ȴ� timerThread ִ�����
                    timerThread.join();

                    if (isfinished)
                    {
                        second -= 1;
                        MessageBox(NULL, (std::to_string(second / 60) + "��" + std::to_string(second % 60) + "��").c_str(), "��ս����", MB_ICONINFORMATION);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                continue;
            }
        }
        // �رղ˵���ť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= closeButtonRect.left && mouseX <= closeButtonRect.right && mouseY >= closeButtonRect.top && mouseY <= closeButtonRect.bottom)
        {
            return false;
        }
        //��ⰴť���
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseX >= 930 && mouseX <= 990 && mouseY >= 0 && mouseY <= 60)
        {
            questionplay(mode,bkimg);
        }
    }
}

void design(MODE& mode, int& second,IMAGE &bkimg)
{
    //���ſ�ʼ��Ч
    mciSendString("close bgm4.mp3", NULL, 0, NULL);
    mciSendString("open bgm4.mp3", 0, 0, 0);
    mciSendString("play bgm4.mp3", 0, 0, 0);

    putimage(0, 0, &bkimg);
    IMAGE designimg;
    loadimage(&designimg, "design.png", 6 * IMGW, IMGW);
    putimage(297, 66, &designimg);
    IMAGE digit[10];
    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit[i], filename, IMGW, IMGW);
    }

    IMAGE bk;
    loadimage(&bk, "bk.png", IMGW, IMGW);
    for (int i = 2; i < 6; i++)
    {
        putimage(297 + i * IMGW, 66 + 7 * IMGW, &bk);
    }

    IMAGE close;
    loadimage(&close, "close.png", IMGW,IMGW);
    putimage(297, 66 + 7 * IMGW, &close);

    IMAGE save;
    loadimage(&save, "save.png", IMGW, IMGW);
    putimage(IMGW+297, 66 + 7 * IMGW, &save);

    MOUSEMSG mouseMsg;
    while (true)
    {
        Map map;
        for (int row = 0; row < ROW; row++)
        {
            for (int col = 0; col < COL; col++)
            {
                map.setMapnum(row, col, 0);
                map.draw(col * IMGW + 297, (row + 1) * IMGW + 66, digit + map.getMapnum(row, col));
            }
        }

        setlinecolor(BLUE);
        for (int i = 0; i <= 6 * IMGW; i += IMGW)
        {
            line(i + 297, IMGW + 66, i + 297, 8 * IMGW + 66);
        }
        for (int i = IMGW; i <= 8 * IMGW; i += IMGW)
        {
            line(0 + 297, i + 66, 6 * IMGW + 297, i + 66);
        }

        while (true)
        {
            mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
            if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= 6 * IMGW + 297 && mouseMsg.y >= IMGW + 66 && mouseMsg.y <= 7 * IMGW + 66)
            {
                //���ŵ����Ч
                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                mciSendString("open bgm2.mp3", 0, 0, 0);
                mciSendString("play bgm2.mp3", 0, 0, 0);

                int i, k;
                int mouseX = mouseMsg.x;
                int mouseY = mouseMsg.y;
                i = (mouseY - 66) / IMGW - 1;
                k = (mouseX - 297) / IMGW;
                char ch[21];
                int num;
                while (true)
                {
                    InputBox(ch, 20, "���������ϵ�0~4������õ�λ����Ӧ����ֲ��������");
                    num = atoi(ch);
                    if (num>=0&&num<=4)
                    {
                        break;  // ������Ч���˳�ѭ��
                    }
                    else
                    {
                        MessageBox(NULL, "������������ԣ�", "����", MB_ICONERROR);
                        continue;
                    }
                }
                map.setMapnum(i, k, num);
                map.draw(k * IMGW + 297, (i + 1) * IMGW + 66, digit+map.getMapnum(i,k));
                for (int i = 0; i <= 6 * IMGW; i += IMGW)
                {
                    line(i + 297, IMGW + 66, i + 297, 8 * IMGW + 66);
                }
                for (int i = IMGW; i <= 8 * IMGW; i += IMGW)
                {
                    line(0 + 297, i + 66, 6 * IMGW + 297, i + 66);
                }
            }
            else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
            {
                int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
                if (IDOK == result)
                {
                    return;
                }
            }
            else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= IMGW+297 && mouseMsg.x <= 2 * IMGW + 297 && mouseMsg.y >= 7*IMGW+66 && mouseMsg.y <= 8*IMGW + 66)
            {
                MessageBox(NULL, "�����ж���Ŀ�Ƿ��н⣬���Ե�", "��ʾ", MB_ICONINFORMATION);
                int key[6][6] = { 0 };
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        key[i][j] = map.getMapnum(i, j);
                    }
                }

                int mouseX = mouseMsg.x;
                int mouseY = mouseMsg.y;
                if (designcheck(key))
                {
                    //���������Ч
                    mciSendString("close bgm5.mp3", NULL, 0, NULL);
                    mciSendString("open bgm5.mp3", 0, 0, 0);
                    mciSendString("play bgm5.mp3", 0, 0, 0);

                    int result = MessageBox(NULL, "�����н⣬�Ƿ񱣴沢��ս���⣿", "�˳�", MB_OKCANCEL);
                    if (result == IDOK)
                    {
                        selectMode(mode);
                        map.mapfile();
                        map.draw(mode, 297, 66);
                        map.draw();

                        stopTimer = false;
                        second = 0;
                        isfinished = false;

                        std::thread playThread(play, std::ref(map), std::ref(mode));
                        std::thread timerThread(timer, std::ref(second));

                        playThread.join();

                        stopTimer = true;

                        timerThread.join();

                        if (isfinished)
                        {
                            second -= 1;
                            MessageBox(NULL, (std::to_string(second / 60) + "��" + std::to_string(second % 60) + "��").c_str(), "��ս����", MB_ICONINFORMATION);
                            return;
                        }
                        else
                        {
                            return;
                        }
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    int result = MessageBox(NULL, "�����޽⣡�Ƿ�������⣿", "�޽�", MB_OKCANCEL);
                    {
                        if (result == IDOK)
                        {
                            break;
                        }
                        else
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
}

void play(Map& map, MODE& mode)
{
    //���ſ�ʼ��Ч
    mciSendString("close bgm4.mp3", NULL, 0, NULL);
    mciSendString("open bgm4.mp3", 0, 0, 0);
    mciSendString("play bgm4.mp3", 0, 0, 0);

    IMAGE matrix[4];
    loadimage(matrix + 0, "matrix/1.png", IMGW, IMGW);
    loadimage(matrix + 1, "matrix/2.png", 2 * IMGW, 2 * IMGW);
    loadimage(matrix + 2, "matrix/3.png", 3 * IMGW, 3 * IMGW);
    loadimage(matrix + 3, "matrix/4.png", 4 * IMGW, 4 * IMGW);

    IMAGE bkimg;
    loadimage(&bkimg, "bkimg.png", 990, 660);

    IMAGE digit[10];
    for (int i = 0; i < 10; ++i) 
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit[i], filename, 15, 15);
    }
    refresh(348,66,348,66,map, digit,digit);

    std::stack<Map> historyStack; // ���ڱ�����ʷ������ջ
    historyStack.push(map);

    MOUSEMSG mouseMsg;
    while (true) 
    {
        int num;

        mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 2 * IMGW+297 && mouseMsg.x <= 6 * IMGW+297 && mouseMsg.y >= 7 * IMGW+66 && mouseMsg.y <= 8 * IMGW+66) 
        {
            num = (mouseMsg.x - 297) / IMGW - 1;
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONUP)
            {
                continue;
            }
            while (true)
            {
                mouseMsg = GetMouseMsg();
                if (mouseMsg.uMsg == WM_MOUSEMOVE)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        putimage(mouseMsg.x - num * IMGW / 2, mouseMsg.y - num * IMGW / 2, matrix + num - 1);
                    }

                    refresh(348, 66, 348, 66, map, digit, digit);

                    EndBatchDraw();
                }
                else if (mouseMsg.uMsg == WM_LBUTTONUP)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    EndBatchDraw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        int i = (mouseMsg.y - num * IMGW / 2 - 99) / IMGW;
                        int j = (mouseMsg.x - num * IMGW / 2 - 264) / IMGW;

                        map.setmatric(i, j, num);

                        historyStack.push(map);

                        refresh(348, 66, 348, 66, map, digit, digit);

                        //���ŵ����Ч
                        mciSendString("close bgm2.mp3", NULL, 0, NULL);
                        mciSendString("open bgm2.mp3", 0, 0, 0);
                        mciSendString("play bgm2.mp3", 0, 0, 0);

                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= IMGW+297 && mouseMsg.x <= 2 * IMGW+297 && mouseMsg.y >= 7 * IMGW+66 && mouseMsg.y <= 8 * IMGW+66 && historyStack.size() > 1) 
        {
            int result = MessageBox(NULL, "ȷ��������", "����", MB_OKCANCEL);
            if (IDOK == result) 
            {
                historyStack.pop(); // ����ջ��Ԫ�أ�����һ������

                map = historyStack.top(); // �ָ�����һ����ͼ״̬
                // ������ɺ�ˢ����ʾ
                refresh(348,66,348,66,map, digit,digit);
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= IMGW+297 && mouseMsg.y >= 7 * IMGW+66 && mouseMsg.y <= 8 * IMGW+66) 
        {
            int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
            if (IDOK == result) 
            {
                isfinished = false;
                return;
            }
        }
        if (map.finish(mode))
        {
            //���������Ч
            mciSendString("close bgm5.mp3", NULL, 0, NULL);
            mciSendString("open bgm5.mp3", 0, 0, 0);
            mciSendString("play bgm5.mp3", 0, 0, 0);

            MessageBox(NULL, "��ϲ�������ս��", "��ս����", MB_ICONINFORMATION);

            isfinished = true;

            return;
        }
    }
}

void timer(int& second) 
{
    // ��������ͼƬ
    IMAGE digit[10];

    //����ð��ͼƬ
    IMAGE colon;
    loadimage(&colon, "colon.png", IMGW, IMGW);
    putimage(3 * IMGW + 297, 66, &colon);

    //���ؼ�ʱ��ͼ��
    IMAGE clock;
    loadimage(&clock, "clock.png", IMGW, IMGW);
    putimage(297, 66, &clock);

    int seconds = 0;

    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i); // �����ļ������� 00.png��01.png��02.png
        loadimage(&digit[i], filename, IMGW, IMGW);
    }

    while (seconds >= 0) 
    {
        // ������Ӻ�����
        int minutes = seconds / 60;
        int remainingSeconds = seconds % 60;

        // ���Ʒ��Ӻ�������Ӧ������ͼƬ
        putimage(IMGW+297, 66, &digit[minutes / 10]); // ����ʮλ���ķ���
        putimage(2 * IMGW+297, 66, &digit[minutes % 10]); // ���Ƹ�λ���ķ���
        putimage(4 * IMGW+297, 66, &digit[remainingSeconds / 10]); // ����ʮλ��������
        putimage(5 * IMGW+297, 66, &digit[remainingSeconds % 10]); // ���Ƹ�λ��������
        putimage(3 * IMGW + 297, 66, &colon);
        putimage(297, 66, &clock);

        Sleep(1000);

        ++seconds;

        if (stopTimer) 
        {
            // ���¼�ʱʱ��
            second = seconds;
            return;
        }
    }
}

void refresh(int x1,int y1,int x2,int y2,Map& map,IMAGE *digit1,IMAGE *digit2)
{
    // ������ɺ�ˢ����ʾ
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COL; k++)
        {
            map.draw(x1 + k * IMGW, y1+(i+1) * IMGW, digit1 + map.getCellCovered(i, k));
        }
    }
    for (int j = 2; j < COL; j++)
    {
        map.draw(x2+j*IMGW,y2+7*IMGW, digit2 + map.getmatric(j - 1));
    }
}

void refresh(int x, int y, Map& map, IMAGE* digit)
{
    // ������ɺ�ˢ����ʾ
    for (int i = 0; i < ROW; i++)
    {
        for (int k = 0; k < COL; k++)
        {
            map.draw(x + k * IMGW, y + (i + 1) * IMGW, digit + map.getCellCovered(i, k));
        }
    }
}

bool gamemode(MODE& mode,IMAGE &bkimg)
{
    putimage(0, 0, &bkimg);

    // ���ð�ť��ɫ
    setlinecolor(BLACK); // ���ð�ť�߿���ɫΪ��ɫ
    setfillcolor(RGB(0, 255, 255)); // ���ð�ť�����ɫΪ����ɫ

    // ����������ɫ�ʹ�С
    setbkmode(TRANSPARENT); // �������ֱ���ɫ͸��
    settextcolor(RGB(50, 50, 50)); // ����������ɫ����һ��
    settextstyle(20, 0, _T("����")); // ����������ʽΪ���壬��СΪ20

    // ���ư�ť
    //����ģʽ
    IMAGE more;
    loadimage(&more, "more.png", 60, 60);
    putimage(930, 0,&more);

    // ��ģʽ��ť
    RECT simpleButtonRect = { 397, 166, 573, 216 };
    rectangle(simpleButtonRect.left, simpleButtonRect.top, simpleButtonRect.right, simpleButtonRect.bottom);
    floodfill((simpleButtonRect.left + simpleButtonRect.right) / 2, (simpleButtonRect.top + simpleButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
    outtextxy((simpleButtonRect.left + simpleButtonRect.right - textwidth(_T("��ģʽ"))) / 2, (simpleButtonRect.top + simpleButtonRect.bottom - textheight(_T("��ģʽ"))) / 2, _T("��ģʽ"));

    // ����ģʽ��ť
    RECT difficultButtonRect = { 397, 266, 573, 316 };
    rectangle(difficultButtonRect.left, difficultButtonRect.top, difficultButtonRect.right, difficultButtonRect.bottom);
    floodfill((difficultButtonRect.left + difficultButtonRect.right) / 2, (difficultButtonRect.top + difficultButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
    outtextxy((difficultButtonRect.left + difficultButtonRect.right - textwidth(_T("����ģʽ"))) / 2, (difficultButtonRect.top + difficultButtonRect.bottom - textheight(_T("����ģʽ"))) / 2, _T("����ģʽ"));

    // ��սģʽ��ť
    RECT challengeButtonRect = { 397, 366, 573, 416 };
    rectangle(challengeButtonRect.left, challengeButtonRect.top, challengeButtonRect.right, challengeButtonRect.bottom);
    floodfill((challengeButtonRect.left + challengeButtonRect.right) / 2, (challengeButtonRect.top + challengeButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
    outtextxy((challengeButtonRect.left + challengeButtonRect.right - textwidth(_T("��սģʽ"))) / 2, (challengeButtonRect.top + challengeButtonRect.bottom - textheight(_T("��սģʽ"))) / 2, _T("��սģʽ"));

    // ���ز˵���ť
    RECT returnButtonRect = { 397, 466, 573, 516 };
    rectangle(returnButtonRect.left, returnButtonRect.top, returnButtonRect.right, returnButtonRect.bottom);
    floodfill((returnButtonRect.left + returnButtonRect.right) / 2, (returnButtonRect.top + returnButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
    outtextxy((returnButtonRect.left + returnButtonRect.right - textwidth(_T("���ز˵�"))) / 2, (returnButtonRect.top + returnButtonRect.bottom - textheight(_T("���ز˵�"))) / 2, _T("���ز˵�"));

    // ��ť����
    MOUSEMSG mouseMsg;
    while (true)
    {
        mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
        if (mouseMsg.uMsg == WM_LBUTTONDOWN) // �������������
        {
            int mouseX = mouseMsg.x;
            int mouseY = mouseMsg.y;

            // ��ģʽ��ť���
            if (mouseX >= simpleButtonRect.left && mouseX <= simpleButtonRect.right && mouseY >= simpleButtonRect.top && mouseY <= simpleButtonRect.bottom)
            {
                mode = simple;
                return true;
            }
            // ����ģʽ��ť���
            else if (mouseX >= difficultButtonRect.left && mouseX <= difficultButtonRect.right && mouseY >= difficultButtonRect.top && mouseY <= difficultButtonRect.bottom)
            {
                mode = difficult;
                return true;
            }
            //��սģʽ��ť���
            else if (mouseX >= challengeButtonRect.left && mouseX <= challengeButtonRect.right && mouseY >= challengeButtonRect.top && mouseY <= challengeButtonRect.bottom)
            {
                mode = challenge;
                return true;
            }
            //����ģʽ��ť���
            else if (mouseX > 930 && mouseX < 990 && mouseY>0 && mouseY < 60)
            {
                innovate(mode, bkimg);
                return false;
            }
            //���ذ�ť���
            else if (mouseX >= returnButtonRect.left && mouseX <= returnButtonRect.right && mouseY >= returnButtonRect.top && mouseY <= returnButtonRect.bottom)
            {
                return false;
            }
        }
    }
}

void rank(std::vector<User>& users)
{
    //�ֱ𴴽���ż�ģʽ��ʱ������ģʽ��ʱ����սģʽ�÷ֵ�����
    std::multimap<int,std::string> v1;
    std::multimap<int,std::string> v2;
    std::multimap<int,std::string> v3;

    for (auto& user : users) 
    {
        if (user.getsimpleTime() != 0)
        {
            v1.insert({ user.getsimpleTime(),user.getUsername() });
        }
        if (user.getdifficultTime() != 0)
        {
            v2.insert({ user.getdifficultTime(),user.getUsername() });
        }
        if (user.getchallengeScore() != 0)
        {
            v3.insert({ user.getchallengeScore(),user.getUsername() });
        }
    }
    IMAGE chart;
    IMAGE close;
    loadimage(&chart, "chart.png", COL * IMGW, (ROW + 2) * IMGW);
    loadimage(&close, "close.png", 30, 30);
    putimage(297, 66, &chart);
    putimage(663, 66, &close);

    IMAGE modeimg[6];
    IMAGE ranking[6];
    loadimage(modeimg + 0, "mode/s1.png", 100, 40);
    loadimage(modeimg + 1, "mode/s2.png", 100, 40);
    loadimage(modeimg + 2, "mode/d1.png", 100, 40);
    loadimage(modeimg + 3, "mode/d2.png", 100, 40);
    loadimage(modeimg + 4, "mode/c1.png", 100, 40);
    loadimage(modeimg + 5, "mode/c2.png", 100, 40);

    for (int i = 0; i < 6; ++i) 
    {
        char filename[20];
        sprintf_s(filename, "ranking/%d.png", i+1); 
        loadimage(ranking+i, filename, 380, 60);
    }

    //Ĭ�ϳ�ʼ״̬Ϊ��ģʽ��ʱ����
    drawchart(simple,modeimg + 0, modeimg + 3,modeimg+5, ranking,v1);

    MOUSEMSG mouseMsg;
    while (true)
    {
        mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
        if (mouseMsg.uMsg == WM_LBUTTONDOWN) // �������������
        {
            int mouseX = mouseMsg.x;
            int mouseY = mouseMsg.y;
            if (mouseX >= 321 && mouseX <= 421 && mouseY >= 186 && mouseY <= 226)
            {
                drawchart(simple,modeimg + 0, modeimg + 3,modeimg+5, ranking, v1);
            }
            else if (mouseX >= 445 && mouseX <= 545 && mouseY >= 186 && mouseY <= 226)
            {
                drawchart(difficult, modeimg + 1, modeimg + 2, modeimg + 5, ranking, v2);
            }
            else if (mouseX >= 569 && mouseX <= 669 && mouseY >= 186 && mouseY <= 226)
            {
                drawchart(challenge,modeimg + 1, modeimg + 3, modeimg + 4, ranking, v3);
            }
            else if (mouseX >= 663 && mouseX <= 763 && mouseY >= 0 && mouseY <= 330)
            {
                return;
            }
        }
    }
}

void drawchart(MODE mode,IMAGE *a,IMAGE *b,IMAGE* c,IMAGE *ranking, std::multimap<int,std::string>& v)
{
    putimage(321, 186, a);
    putimage(445, 186, b);
    putimage(569, 186, c);
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(30, 0, _T("����"));
    if (v.size() >= 5)
    {
        for (int i = 0; i < 5; ++i)
        {
            putimage(305, 246 + 65 * i, ranking + i);
        }
        int count = 0;
        if (mode == challenge)
        {
            for (auto it = v.rbegin(); count < 5; ++it, ++count)
            {
                outtextxy(617, 256 + 65 * count, (std::to_string(it->first) + "��").c_str());
                outtextxy(313, 256 + 65 * count, (std::to_string(count + 1) + "  " + it->second.c_str()).c_str());
            }
        }
        else
        {
            for (auto it = v.begin(); count < 5; ++it, ++count)
            {
                outtextxy(567, 256 + 65 * count, (std::to_string(it->first / 60) + "��" + std::to_string(it->first % 60) + "��").c_str());
                outtextxy(313, 256 + 65 * count, (std::to_string(count + 1) + "  " + it->second.c_str()).c_str());
            }
        }
    }
    else
    {
        for (int i = 0; i < v.size(); i++)
        {
            putimage(305, 246 + 65 * i, ranking + i);
        }
        for (int i = v.size(); i < 5; i++)
        {
            putimage(305, 246 + 65 * i, ranking + 5);
        }
        int count = 0;
        if (mode == challenge)
        {
            for (auto it = v.rbegin(); it != v.rend(); ++it, ++count)
            {
                outtextxy(617, 256 + 65 * count, (std::to_string(it->first) + "��").c_str());
                outtextxy(313, 256 + 65 * count, (std::to_string(count + 1) + "  " + it->second.c_str()).c_str());
            }
        }
        else
        {
            for (auto it = v.begin(); it != v.end(); ++it, ++count)
            {
                outtextxy(567, 256 + 65 * count, (std::to_string(it->first / 60) + "��" + std::to_string(it->first % 60) + "��").c_str());
                outtextxy(313, 256 + 65 * count, (std::to_string(count + 1) + "  " + it->second.c_str()).c_str());
            }
        }
    }
}

void challengeMode(int& score, std::vector<User>& users, IMAGE &bkimg)
{
    score = 0;
    std::vector<int> v; // ����ѱ���ս�Ĺؿ�
    IMAGE digit1[10];
    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit1[i], filename, 96, 96);
    }

    IMAGE digit2[10];
    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit2[i], filename, 30, 30);
    }

    IMAGE tick;
    loadimage(&tick, "tick.png", 20, 20);

    while (true)
    {
        putimage(0, 0, &bkimg);
        if (score >= 10)
        {
            putimage(497, 76, digit2 + score / 10);
            putimage(527, 76, digit2 + score % 10);
        }
        else
        {
            putimage(497, 76, digit2 + score % 10);
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                putimage(125 * j + 324, 123 * i + 145, digit1 + 3 * i + j + 1);
            }
        }

        if (!v.empty())
        { // ��� v ��Ϊ��
            for (size_t i = 0; i < v.size(); i++)
            {
                putimage(125 * ((v[i] - 1) % 3) + 400, 123 * ((v[i] - 1) / 3) + 221, &tick);
            }
        }

        // ���ð�ť��ɫ
        setlinecolor(BLACK); // ���ð�ť�߿���ɫΪ��ɫ
        setfillcolor(RGB(0, 255, 255)); // ���ð�ť�����ɫΪ����ɫ

        // ����������ɫ�ʹ�С
        setbkmode(TRANSPARENT); // �������ֱ���ɫ͸��
        settextcolor(RGB(0, 0, 0)); // ����������ɫ����һ��
        settextstyle(30, 0, _T("����")); // ����������ʽΪ���壬��СΪ20
        outtextxy(307, 76, "��ĵ�ǰ�÷֣�");

        // ���沢�˳���ť
        RECT saveButtonRect = { 407, 520, 583, 570 };
        rectangle(saveButtonRect.left, saveButtonRect.top, saveButtonRect.right, saveButtonRect.bottom);
        floodfill((saveButtonRect.left + saveButtonRect.right) / 2, (saveButtonRect.top + saveButtonRect.bottom) / 2, BLACK); // ��䰴ť��ɫ
        outtextxy((saveButtonRect.left + saveButtonRect.right - textwidth(_T("���沢�˳�"))) / 2, (saveButtonRect.top + saveButtonRect.bottom - textheight(_T("���沢�˳�"))) / 2, _T("���沢�˳�"));

        MOUSEMSG mouseMsg;
        while (true)
        {
            mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) // ֻ�������������ʱ�ż���ִ��
                break;
            Sleep(1);
        }
        if (mouseMsg.uMsg == WM_LBUTTONDOWN)
        {
            if (mouseMsg.y >= 520 && mouseMsg.y <= 570 && mouseMsg.x >= 407 && mouseMsg.x <= 583)
            {
                int result = MessageBox(NULL, "ȷ�����沢�˳���", "�˳�", MB_OKCANCEL);
                if (IDOK == result)
                {
                    MessageBox(NULL, ("������ս�÷�Ϊ��" + std::to_string(score) + "��").c_str(), "��ս����", MB_ICONINFORMATION);
                    return;
                }
            }
            int n = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if ((mouseMsg.y - 66) >= 123 * i + 29 + 50 && (mouseMsg.y - 66) <= 123 * (i + 1) + 50 && (mouseMsg.x - 297) >= 125 * j + 27 && (mouseMsg.x - 297) <= 125 * (j + 1))
                    {
                        n = 3 * i + j + 1;
                        break; // �ҵ��˱�����Ĺؿ����˳��ڲ�ѭ��
                    }
                }
            }
            // ����Ƿ�����ս���ùؿ�
            bool challenged = false;
            if (!v.empty()&&n!=0)
            { 
                // ��� v ��Ϊ��
                for (size_t i = 0; i < v.size(); ++i)
                {
                    if (v[i] == n)
                    {
                        MessageBox(NULL, "�ùؿ��Ѿ���ս���������ٴ���ս��", "����", MB_ICONERROR);
                        challenged = true;
                        break; // ������ǰѭ��
                    }
                }
            }
            if (!challenged)
            {
                if (challengeplay(score, n))
                {
                    v.push_back(n);
                    continue;
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void loadMapFile(int n, Map& map, std::string filename)
{
    std::ifstream file(filename);
    std::string line;

    // ����ǰ n-1 ��
    for (int i = 0; i < n - 1; ++i)
    {
        getline(file, line);
    }

    // ��ȡ�� n ��
    getline(file, line);

    // ���������ݰ����ŷָ���洢�� vector ��
    std::vector<int> data;
    std::stringstream ss(line);
    std::string value;
    while (getline(ss, value, ','))
    {
        data.push_back(std::stoi(value));
    }

    // ���������õ���ͼ������
    int index = 0;
    for (int i = 0; i < 6; ++i) 
    {
        for (int j = 0; j < 6; ++j) 
        {
            map.setMapnum(i, j, data[index++]);
        }
    }
}

bool challengeplay(int& score,int& n)
{
    //���ſ�ʼ��Ч
    mciSendString("close bgm4.mp3", NULL, 0, NULL);
    mciSendString("open bgm4.mp3", 0, 0, 0);
    mciSendString("play bgm4.mp3", 0, 0, 0);

    IMAGE matrix[4];
    loadimage(matrix + 0, "matrix/1.png", IMGW, IMGW);
    loadimage(matrix + 1, "matrix/2.png", 2 * IMGW, 2 * IMGW);
    loadimage(matrix + 2, "matrix/3.png", 3 * IMGW, 3 * IMGW);
    loadimage(matrix + 3, "matrix/4.png", 4 * IMGW, 4 * IMGW);

    Map map;
    MODE mode;
    loadMapFile(n, map, "challenge_map.csv");

    if (n >= 1 && n <= 6)
    {
        mode = simple;
        map.draw(mode,297,66);
    }
    else if (n >= 7 && n <= 9)
    {
        mode = difficult;
        map.draw(mode,297,66);
    }
    map.draw();

    std::stack<Map> historyStack; // ���ڱ�����ʷ������ջ
    IMAGE challenge2;
    loadimage(&challenge2, "challenge2.png", 396, 66);
    putimage(297, 66, &challenge2);
    IMAGE digit[10];

    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit[i], filename, 15, 15);
    }

    refresh(348, 66, 348, 66, map, digit, digit);

    historyStack.push(map);

    MOUSEMSG mouseMsg;
    while (true)
    {
        int num;

        mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 2 * IMGW + 297 && mouseMsg.x <= 6 * IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
        {
            num = (mouseMsg.x - 297) / IMGW - 1;
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONUP)
            {
                continue;
            }
            while (true)
            {
                mouseMsg = GetMouseMsg();
                if (mouseMsg.uMsg == WM_MOUSEMOVE)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        putimage(mouseMsg.x - num * IMGW / 2, mouseMsg.y - num * IMGW / 2, matrix + num - 1);
                    }

                    refresh(348, 66, 348, 66, map, digit, digit);

                    EndBatchDraw();
                }
                else if (mouseMsg.uMsg == WM_LBUTTONUP)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    EndBatchDraw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        int i = (mouseMsg.y - num * IMGW / 2 - 99) / IMGW;
                        int j = (mouseMsg.x - num * IMGW / 2 - 264) / IMGW;

                        map.setmatric(i, j, num);

                        historyStack.push(map);

                        refresh(348, 66, 348, 66, map, digit, digit);

                        //���ŵ����Ч
                        mciSendString("close bgm2.mp3", NULL, 0, NULL);
                        mciSendString("open bgm2.mp3", 0, 0, 0);
                        mciSendString("play bgm2.mp3", 0, 0, 0);

                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= IMGW+297 && mouseMsg.x <= 2 * IMGW+297 && mouseMsg.y >= 7 * IMGW+66 && mouseMsg.y <= 8 * IMGW+66 && historyStack.size() > 1)
        {
            int result = MessageBox(NULL, "ȷ��������", "����", MB_OKCANCEL);
            if (IDOK == result)
            {
                historyStack.pop(); // ����ջ��Ԫ�أ�����һ������

                map = historyStack.top(); // �ָ�����һ����ͼ״̬
                // ������ɺ�ˢ����ʾ
                refresh(348, 66, 348, 66, map, digit, digit);
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= IMGW+297 && mouseMsg.y >= 7 * IMGW+66 && mouseMsg.y <= 8 * IMGW+66)
        {
            int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
            if (IDOK == result)
            {
                return false;
            }
        }
        if (map.finish(mode))
        {
            //���������Ч
            mciSendString("close bgm5.mp3", NULL, 0, NULL);
            mciSendString("open bgm5.mp3", 0, 0, 0);
            mciSendString("play bgm5.mp3", 0, 0, 0);

            if (mode == simple)
            {
                score += 1;
            }
            else if(mode==difficult)
            {
                score += 3;
            }
            MessageBox(NULL, "��ϲ����ɱ�����ս��", "��ս����", MB_ICONINFORMATION);
            return true;
        }
    }
}

void questionplay(MODE &mode,IMAGE &bkimg)
{
    putimage(0, 0, &bkimg);
    IMAGE matrix[4];
    loadimage(matrix + 0, "matrix/1.png", IMGW, IMGW);
    loadimage(matrix + 1, "matrix/2.png", 2 * IMGW, 2 * IMGW);
    loadimage(matrix + 2, "matrix/3.png", 3 * IMGW, 3 * IMGW);
    loadimage(matrix + 3, "matrix/4.png", 4 * IMGW, 4 * IMGW);
    IMAGE digit[10];
    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit[i], filename, 15, 15);
    }

    int n = sumMapFile("map.csv");

    while (true)
    {
        char qn[21];
        InputBox(qn, 20, ("����ڹ���" + std::to_string(n) + "����Ŀ����������Ҫ��ս����Ŀ���").c_str());
        std::string questionnum(qn);

        Map map;
        if (std::stoi(questionnum) <= n)
        {
            while (true)
            {
                char m[21];
                InputBox(m, 20, "��������սģʽ(simple��difficult)");
                std::string m_mode(m);
                loadMapFile(std::stoi(questionnum), map, "map.csv");
                if (m_mode == "simple")
                {
                    mode = simple;
                    map.draw(mode, 297, 66);
                    break;
                }
                else if (m_mode == "difficult")
                {
                    mode = difficult;
                    map.draw(mode, 297, 66);
                    break;
                }
                else
                {
                    MessageBox(NULL, "������������ԣ�", "ģʽ", MB_ICONINFORMATION);
                    continue;
                }
            }
            map.draw();
            std::stack<Map> historyStack; // ���ڱ�����ʷ������ջ
            refresh(348, 66, 348, 66, map, digit, digit);
            historyStack.push(map);
            mciSendString("close bgm4.mp3", NULL, 0, NULL);
            mciSendString("open bgm4.mp3", 0, 0, 0);
            mciSendString("play bgm4.mp3", 0, 0, 0);

            MOUSEMSG mouseMsg;
            while (true)
            {
                int num;

                mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
                if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 2 * IMGW + 297 && mouseMsg.x <= 6 * IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
                {
                    num = (mouseMsg.x - 297) / IMGW - 1;
                    mouseMsg = GetMouseMsg();
                    if (mouseMsg.uMsg == WM_LBUTTONUP)
                    {
                        continue;
                    }
                    while (true)
                    {
                        mouseMsg = GetMouseMsg();
                        if (mouseMsg.uMsg == WM_MOUSEMOVE)
                        {
                            BeginBatchDraw();

                            map.draw(mode, 297, 66);
                            map.draw();

                            if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                            {
                                putimage(mouseMsg.x - num * IMGW / 2, mouseMsg.y - num * IMGW / 2, matrix + num - 1);
                            }

                            refresh(348, 66, 348, 66, map, digit, digit);

                            EndBatchDraw();
                        }
                        else if (mouseMsg.uMsg == WM_LBUTTONUP)
                        {
                            BeginBatchDraw();

                            map.draw(mode, 297, 66);
                            map.draw();

                            EndBatchDraw();

                            if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                            {
                                int i = (mouseMsg.y - num * IMGW / 2 - 99) / IMGW;
                                int j = (mouseMsg.x - num * IMGW / 2 - 264) / IMGW;

                                map.setmatric(i, j, num);

                                historyStack.push(map);

                                refresh(348, 66, 348, 66, map, digit, digit);

                                //���ŵ����Ч
                                mciSendString("close bgm2.mp3", NULL, 0, NULL);
                                mciSendString("open bgm2.mp3", 0, 0, 0);
                                mciSendString("play bgm2.mp3", 0, 0, 0);

                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                }
                else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= IMGW + 297 && mouseMsg.x <= 2 * IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66 && historyStack.size() > 1)
                {
                    int result = MessageBox(NULL, "ȷ��������", "����", MB_OKCANCEL);
                    if (IDOK == result)
                    {
                        historyStack.pop(); // ����ջ��Ԫ�أ�����һ������

                        map = historyStack.top(); // �ָ�����һ����ͼ״̬
                        // ������ɺ�ˢ����ʾ
                        refresh(348, 66, 348, 66, map, digit, digit);
                    }
                }
                else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
                {
                    int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
                    if (IDOK == result)
                    {
                        return;
                    }
                }
                if (map.finish(mode))
                {
                    mciSendString("close bgm5.mp3", NULL, 0, NULL);
                    mciSendString("open bgm5.mp3", 0, 0, 0);
                    mciSendString("play bgm5.mp3", 0, 0, 0);

                    int result = MessageBox(NULL, "��ս�������Ƿ������ս��", "��ս����", MB_OKCANCEL);
                    if (IDOK == result)
                    {
                        break;
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }
        else
        {
            MessageBox(NULL, "�����������ѳ�����������������ٴ�������ţ�", "���", MB_ICONINFORMATION);
            continue;
        }
    }
}

int sumMapFile(std::string filename)
{
    int n = 0;
    std::ifstream file(filename);
    std::string line;
    while (true)
    {
        if (getline(file, line))
        {
            n++;
        }
        else
        {
            return n;
        }
    }
}


void selectMode(MODE& mode)
{
    while (true)
    {
        char m[21];
        // �����Ի����ȡģʽ����
        InputBox(m, 20, "������ģʽ(simple��difficult)");
        std::string m_mode(m);
        if (m_mode == "simple")
        {
            mode = simple;
            return;
        }
        else if (m_mode == "difficult")
        {
            mode = difficult;
            return;
        }
        else
        {
            MessageBox(NULL, "��ʽ�������������룡", "����", MB_ICONERROR);
        }
    }
}

void innovate(MODE& mode,IMAGE &bkimg)
{
    //���ſ�ʼ��Ч
    mciSendString("close bgm4.mp3", NULL, 0, NULL);
    mciSendString("open bgm4.mp3", 0, 0, 0);
    mciSendString("play bgm4.mp3", 0, 0, 0);

    putimage(0, 0, &bkimg);
    selectMode(mode);
    IMAGE innovateimg;
    loadimage(&innovateimg, "innovate.png", 6* IMGW, IMGW);
    putimage(297, 66, &innovateimg);
    Map map;
    map.initMapnum(0);
    map.draw(mode, 297, 66);
    map.draw();

    IMAGE matrix[4];
    loadimage(matrix + 0, "matrix/1.png", IMGW, IMGW);
    loadimage(matrix + 1, "matrix/2.png", 2 * IMGW, 2 * IMGW);
    loadimage(matrix + 2, "matrix/3.png", 3 * IMGW, 3 * IMGW);
    loadimage(matrix + 3, "matrix/4.png", 4 * IMGW, 4 * IMGW);

    IMAGE digit[10];
    for (int i = 0; i < 10; ++i)
    {
        char filename[20];
        sprintf_s(filename, "digit/%02d.png", i);
        loadimage(&digit[i], filename, 15, 15);
    }
    refresh(348, 66, map, digit);

    std::stack<Map> historyStack; // ���ڱ�����ʷ������ջ
    historyStack.push(map);

    MOUSEMSG mouseMsg;
    while (true)
    {
        int num;

        mouseMsg = GetMouseMsg(); // ��ȡ�����Ϣ
        if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 2 * IMGW + 297 && mouseMsg.x <= 6 * IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
        {
            num = (mouseMsg.x - 297) / IMGW - 1;
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONUP)
            {
                continue;
            }
            while (true)
            {
                mouseMsg = GetMouseMsg();
                if (mouseMsg.uMsg == WM_MOUSEMOVE)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        putimage(mouseMsg.x - num * IMGW / 2, mouseMsg.y - num * IMGW / 2, matrix + num - 1);
                    }

                    refresh(348, 66, map, digit);

                    EndBatchDraw();
                }
                else if (mouseMsg.uMsg == WM_LBUTTONUP)
                {
                    BeginBatchDraw();

                    map.draw(mode, 297, 66);
                    map.draw();

                    EndBatchDraw();

                    if (mouseMsg.x > 297 + num * IMGW / 2 && mouseMsg.x < 297 + 6 * IMGW - num * IMGW / 2 && mouseMsg.y>132 + num * IMGW / 2 && mouseMsg.y < 132 + 6 * IMGW - num * IMGW / 2)
                    {
                        int i = (mouseMsg.y - num * IMGW / 2 - 99) / IMGW;
                        int j = (mouseMsg.x - num * IMGW / 2 - 264) / IMGW;

                        map.setmatric(i, j, num,0,0);

                        historyStack.push(map);

                        refresh(348, 66, map, digit);

                        //���ŵ����Ч
                        mciSendString("close bgm2.mp3", NULL, 0, NULL);
                        mciSendString("open bgm2.mp3", 0, 0, 0);
                        mciSendString("play bgm2.mp3", 0, 0, 0);

                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= IMGW + 297 && mouseMsg.x <= 2 * IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66 && historyStack.size() > 1)
        {
            int result = MessageBox(NULL, "ȷ��������", "����", MB_OKCANCEL);
            if (IDOK == result)
            {
                historyStack.pop(); // ����ջ��Ԫ�أ�����һ������

                map = historyStack.top(); // �ָ�����һ����ͼ״̬
                // ������ɺ�ˢ����ʾ
                refresh(348, 66, map, digit);
            }
        }
        else if (mouseMsg.uMsg == WM_LBUTTONDOWN && mouseMsg.x >= 297 && mouseMsg.x <= IMGW + 297 && mouseMsg.y >= 7 * IMGW + 66 && mouseMsg.y <= 8 * IMGW + 66)
        {
            int result = MessageBox(NULL, "ȷ���˳���", "�˳�", MB_OKCANCEL);
            if (IDOK == result)
            {
                return;
            }
        }
        if (map.finish(mode))
        {
            //���������Ч
            mciSendString("close bgm5.mp3", NULL, 0, NULL);
            mciSendString("open bgm5.mp3", 0, 0, 0);
            mciSendString("play bgm5.mp3", 0, 0, 0);

            MessageBox(NULL, "��ϲ�������ս��", "��ս����", MB_ICONINFORMATION);

            return;
        }
    }
}

