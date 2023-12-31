// Cross_and_zeroes.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

class Game {
	char Board[3][3];   //Доска 3 на 3
	char X;             //Символ X или Y, типа игрока
	void swapX();       //Смена игрока
	bool EmptySquare(char); //Проверка клетки на занятость
	void Check();       //Проверка победы
public:
	void ShowBoard();  //Показывает доску
	void GetCoord();   //Получает координату клетки для записив неё X(O)
	int Result;        //Какой игрок победил
	int NewGame();     //Начинает новую игру
};

void Game::ShowBoard() {
	system("CLS");
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			cout << "|" << Board[i][j] << "|";
		}   cout << "\n";
	}
	Check();  //Проверяем победил ли кто-нибудь
}

void Game::swapX() {
	if (X == 'X') X = 'O';
	else X = 'X';
}

void Game::GetCoord() {
	char ch = '1';
	cout << "Input COORD(" << X << "): ";

	cin >> ch;

	while (!EmptySquare(ch)) {   //Пока клетка занята, получаем новую координату
		cout << "Input COORD(" << X << "): ";
		cin >> ch;
	}

	Board[0][ch - '0' - 1] = X;  //Записываем по координате X или O
	swapX(); //Ходит другой игрок
	ShowBoard();
}

bool Game::EmptySquare(char x) {
	return (Board[0][x - '0' - 1] == x);
}

//Проверка на победу
void Game::Check() {
	int temp = 0;

	for (int i = 0; i<3; i++) {
		temp = 0;
		for (int j = 0; j<3; j++) {
			temp += Board[j][i];
		}
		if (temp == 'O' * 3) Result = 2;  //Победил игрок, ходящий O
		if (temp == 'X' * 3) Result = 1;  //Победил игрок, ходящий X
	}

	if (Result) return;

	//Обход строк
	for (int i = 0; i<3; i++) {
		temp = 0;
		for (int j = 0; j<3; j++) {
			temp += Board[i][j];
		}
		if (temp == 'O' * 3) Result = 2;  //Победил игрок, ходящий O
		if (temp == 'X' * 3) Result = 1;  //Победил игрок, ходящий X
	}
	if (Result) return;

	//проверка диагоналей
	if ((Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2])
		|| (Board[0][2] == Board[1][1] && Board[0][2] == Board[2][0])) {
		if (Board[1][1] == 'O') Result = 2;  //Победил игрок, ходящий O
		else Result = 1;                    //Победил игрок, ходящий X
	}
	if (Result) return;

	//НИЧЬЯ, Result=0
}

int Game::NewGame() {
	Result = 0;  //сброс результатов прошлой игры
	char z = '1'; //символ для записи в поле
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			Board[i][j] = z++;  //заполняем поле 1,2,3...9
		}
	}
	ShowBoard();

	srand(time(NULL)); if (rand() % 2) X = 'O'; else   X = 'X';  //Случайный выбор кто первый ходит
	for (int i = 0; i<9; i++) {
		GetCoord();            //Получаем 9 координат
		if (Result) break;     //Если кто-то победил, выходим досрочно
	}

	cin.get();
	return Result;  //ВОзвращаем кто победил
}

int main() {
	Game Play;

	char reply = 'y';
	int Statistica[3] = { 0 };   //Массив для подсчета статистики

	while (reply == 'y') {
		Play.NewGame();

		Statistica[(Play.Result)]++;
		cout << "X win  ==\t" << Statistica[1] << "\n";
		cout << "O win ==\t" << Statistica[2] << "\n";
		cout << "friendly ==\t" << Statistica[0] << "\n";

		cout << "Game again? y/n\n";
		cin >> reply;
		cin.get();

	}
}