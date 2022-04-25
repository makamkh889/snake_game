#include <cstring>
#include <vector>
#include <stdio.h>
#include <bitset>
#include<ctime>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include<sstream>
#include <iomanip>
#include<conio.h>
#include<utility>
#include<Windows.h>
#include <iostream>
#define ll long long
double pi = 3.14159;
using namespace std;
void shift_rigth(ll arr[], ll size) {
	for (int i = size - 2; i >= 0; i--) {
		arr[i + 1] = arr[i];
	}
}
enum Direction{top=1,down,rigth,Laft};
struct map { ll wight, heigth, fruit_x, fruit_y; };
struct snake { ll Headx, Heady, tail_N,tailx[50],taily[50]; Direction Dir; };
struct player { ll score; bool loose; };
map map1; snake snake1; player player1;
void generate_fruit(){
	srand(time(NULL));
	map1.fruit_x = rand() % (map1.wight - 2) + 1;
	map1.fruit_y = rand() % (map1.heigth - 2) + 1;
}
void generate_snake() {
	snake1.Headx = map1.wight / 2;
	snake1.Heady = map1.heigth / 2;
	snake1.tail_N = 0;
}
void genarate_player() {
	player1.score = 0;
	player1.loose = false;
}
void Draw() {
	system("cls");
	for (int i = 0; i < map1.heigth; i++) {
		for (int j = 0; j < map1.wight; j++) {
			if (i == 0 || i == map1.heigth - 1) cout << "*";
			else if (j == 0 || j == map1.wight - 1) cout << "*";
			else if (i == snake1.Heady && j == snake1.Headx) cout << "O";
			else if (i == map1.fruit_y && j == map1.fruit_x) cout << "$";
			else {
				for (int z = 0; z < snake1.tail_N; z++) {
					if (snake1.tailx[z] == snake1.Headx && snake1.taily[z] == snake1.Heady) {
						player1.loose = true;
						exit(0);
						break;
					}
				}
				bool print = false;
				for (int z = 0; z < snake1.tail_N; z++) {
					if (snake1.tailx[z] == j && snake1.taily[z] == i) {
						cout << "o";
						print = true;
						break;
					}
				}
				if(!print)cout << " ";
			}
		}
		cout << "\n";
	}
	cout << "player score : " << player1.score << "\n";
}
void Input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c) {
		case'w':snake1.Dir = top; break;
		case's':snake1.Dir = down; break;
		case'd':snake1.Dir = rigth; break;
		case'a':snake1.Dir = Laft; break;
		case'x':exit(0); break;
		}
	}

}
void satup() {
	map1.wight = 40;
	map1.heigth = 20;
	generate_fruit();
	generate_snake();
	genarate_player();
}
void move() {
	shift_rigth(snake1.tailx, 50);
	shift_rigth(snake1.taily, 50);
	snake1.tailx[0] = snake1.Headx;
	snake1.taily[0] = snake1.Heady;
	switch (snake1.Dir)
	{
	case top:snake1.Heady--; break;
	case down:snake1.Heady++; break;
	case rigth:snake1.Headx++; break;
	case Laft:snake1.Headx--; break;
	}
	if (snake1.Heady >= map1.heigth || snake1.Heady <= 0 || snake1.Headx >= map1.wight || snake1.Headx <= 0)
		player1.loose = true;
	if (snake1.Headx == map1.fruit_x && snake1.Heady == map1.fruit_y) {
		generate_fruit();
		player1.score++;
		snake1.tail_N++;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	satup();
	while (!player1.loose) {
		Draw();
		Input();
		move();
		Sleep(50);
	}

	system("pause");
	
}
