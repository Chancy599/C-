#include"communicate.h"
#include"login.h"
int main()
{
	initgraph(990,660);
	load();
	IMAGE bkimg;
	loadimage(&bkimg,"bkimg.png", 990,660);
	std::vector<User>users;
	MODE mode = simple;
	int second = 0;
	int score = 0;

	// ʹ�� std::thread ���������������̣߳��ֱ����� login �� BGM ����
	std::thread login_thread(login, std::ref(mode), std::ref(second), std::ref(score), std::ref(users), std::ref(bkimg));
	std::thread bgm_thread(BGM);
	std::thread communicate_thread(communicate);

	// ���̵߳ȴ� login �̺߳� BGM �߳����
	login_thread.join();
	bgm_thread.join();
	communicate_thread.join();

	closegraph();
	system("pause");
	return 0;
}














