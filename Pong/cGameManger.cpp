#include "cBall.cpp"
#include "cPaddle.cpp"
#include <time.h>
#include <conio.h>
#include <thread>
#include <mutex>
#include <condition_variable>

class cGameManger
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall* ball;
	cPaddle* player1;
	cPaddle* player2;

public:
	cGameManger(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}
	~cGameManger()
	{
		delete ball, player1, player2;
	}
	void ScoreUp(cPaddle* player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0)
					cout << "\xB2";

				if (ballx == j && bally == i)
					cout << "O"; //ball
				else if (player1x == j && player1y == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y == i)
					cout << "\xDB"; //player2

				else if (player1x == j && player1y + 1 == i)
					cout << "\xDB"; //player1
				else if (player1x == j && player1y + 2 == i)
					cout << "\xDB"; //player1
				else if (player1x == j && player1y + 3 == i)
					cout << "\xDB"; //player1

				else if (player2x == j && player2y + 1 == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y + 2 == i)
					cout << "\xDB"; //player1
				else if (player2x == j && player2y + 3 == i)
					cout << "\xDB"; //player1
				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
	}
	void Logic()
	{
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		//left paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player1x + 1)
				if (bally == player1y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		//right paddle
		for (int i = 0; i < 4; i++)
			if (ballx == player2x - 1)
				if (bally == player2y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		//bottom wall
		if (bally == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall
		if (bally == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 2)
			ScoreUp(player1);
		//left wall
		if (ballx == 1)
			ScoreUp(player2);
	}
	void Run()
	{
		std::mutex mut;
		std::condition_variable cvPlayer, cvBall;

		std::thread threadPlayer1(&cGameManger::player1Function, this, &mut, &cvPlayer, &cvBall);
		std::thread threadPlayer2(&cGameManger::player2Function, this, &mut, &cvPlayer, &cvBall);
		std::thread threadBall(&cGameManger::ballFunction, this, &mut, &cvPlayer, &cvBall);

		threadBall.join();
		threadPlayer1.join();
		threadPlayer2.join();
	}

	void player1Function(std::mutex* mut, std::condition_variable* cvPlayer, std::condition_variable* cvBall) {
		std::unique_lock<std::mutex> lock(*mut);
		while (quit == false) {
			(*cvBall).notify_one();
			(*cvPlayer).wait(lock);
			if (_kbhit()) {
				
				char current = _getch();
				if (current == up1)
					if (player1->getY() > 0) {
						player1->moveUp();
						Draw();
					}
				if (current == down1)
					if (player1->getY() + 4 < height) {
						player1->moveDown();
						Draw();
					}
				
				if (current == 'q')
					quit = true;
				
			}
			
		}
	}

	void player2Function(std::mutex* mut, std::condition_variable* cvPlayer, std::condition_variable* cvBall) {
		std::unique_lock<std::mutex> lock(*mut);
		while (quit == false) {
			(*cvBall).notify_one();
			(*cvPlayer).wait(lock);
			if (_kbhit()) {
				
				char current = _getch();
				if (current == up2)
					if (player2->getY() > 0) {
						player2->moveUp();
						Draw();
					}
				if (current == down2)
					if (player2->getY() + 4 < height) {
						player2->moveDown();
						Draw();
					}
				
				if (current == 'q')
					quit = true;
				
			}
			
		}
	}

	void ballFunction(std::mutex* mut, std::condition_variable* cvPlayer, std::condition_variable* cvBall) {
		std::unique_lock<std::mutex> lock(*mut);
		std::cout << "test1";
		while (quit == false) {
			(*cvBall).wait(lock);
			std::cout << "test2";
			ball->Move();
			Draw();
			(*cvPlayer).notify_all();
			std::cout << "test3";
			if (ball->getDirection() == STOP)
				ball->randomDirection();
			Logic();
			std::this_thread::sleep_for(0.5s);
		}
	}
};