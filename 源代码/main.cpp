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

	// 使用 std::thread 创建并启动两个线程，分别运行 login 和 BGM 函数
	std::thread login_thread(login, std::ref(mode), std::ref(second), std::ref(score), std::ref(users), std::ref(bkimg));
	std::thread bgm_thread(BGM);
	std::thread communicate_thread(communicate);

	// 主线程等待 login 线程和 BGM 线程完成
	login_thread.join();
	bgm_thread.join();
	communicate_thread.join();

	closegraph();
	system("pause");
	return 0;
}














