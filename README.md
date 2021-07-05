# Sudoku
#include <iostream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#define RED "\x1b[31m"
#define WHITE "\x1b[0m"
#define YELOW "\x1b[33m"
#define CURSOR "\x1b[463m"
#define SIZE 9
#define UP 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define DOWN 's'


using namespace std;
class Sudoku {
	int sudokuLogic[SIZE][SIZE]{ 0 };
	int sudokuGrid[SIZE][SIZE]{ 0 };
	int posX{ 0 };
	int posY{ 0 };
public:
	vector<int> vector{ 1,2,3,4,5,6,7,8,9 };
	Sudoku();
	void transposing();
	void swapColumn();
	void swapRow();
	void gameRandom();
	void flipGorizontaly();
	void flipVerticaly();
	void Move(char ch);
	bool CheckStep();
	int CheckSolve();
	void setNumber(int num);
	void FillUserField();
	friend ostream& operator<<(ostream& out, Sudoku& _sudoku);
};
Sudoku::Sudoku(){
	for (int i{ 0 }; i < SIZE; ++i) {
		if (i == 1) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 2) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 3) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 4) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 5) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 6) rotate(vector.begin(), vector.begin() + 4, vector.end());
		if (i == 7) rotate(vector.begin(), vector.begin() + 3, vector.end());
		if (i == 8) rotate(vector.begin(), vector.begin() + 3, vector.end());
		for (int j{ 0 }; j < SIZE; j++) {
			sudokuLogic[i][j] = vector[j];
		}
	}
}
ostream& operator<<(ostream& out, Sudoku& _sudoku) {
	out << RED << "  -----------------------" << WHITE << endl;
	for (int i{ 0 }; i < SIZE; ++i) {
		for (int j{ 0 }; j < SIZE; j++) {
			!(j % 3) ? out << RED << " | " << WHITE : out << " ";
			if (_sudoku.posX == i && _sudoku.posY == j) out << CURSOR;
			if (_sudoku.sudokuGrid[i][j] == 0) out << " ";
			else out << YELOW <<_sudoku.sudokuGrid[i][j] << WHITE;
		}
		out << RED << " |" <<  endl;
		!((i + 1)%3) ? out << "  -----------------------" << WHITE << endl : out << "";
	}
	return out;
}
void Sudoku::transposing() {
	Sudoku tmp;
	for (int i{ 0 }; i < SIZE; ++i) {
		for (int j{ 0 }; j < SIZE; j++) {
			sudokuLogic[i][j] = tmp.sudokuLogic[j][i];
		}
	}
}
void Sudoku::swapColumn() {
	int x = rand()%9;
	int y{ 0 };
	x == 0 || x == 3 || x == 6 ? y = x + (rand()%2 + 1) : y = x - 1;
	for (int i{ 0 }; i < 9; ++i) {
		swap(sudokuLogic[i][x], sudokuLogic[i][y]);
	}
}
void Sudoku::swapRow() {
	int x = rand() % 9;
	int y{ 0 };
	x == 0 || x == 3 || x == 6 ? y = x + 1 : y = x - 1;
	for (int i{ 0 }; i < SIZE; ++i) {
		swap(sudokuLogic[x][i], sudokuLogic[y][i]);
	}
}
void Sudoku::flipGorizontaly() {
	
	for (int i{ 0 }, k{ SIZE - 1 }; i < SIZE/2; ++i, k--) {
		for (int j{ 0 }; j < SIZE; j++) {
			swap(sudokuLogic[i][j], sudokuLogic[k][j]);
		}
	}
}
void Sudoku::flipVerticaly() {

	for (int i{ 0 }; i < SIZE; ++i) {
		for (int j{ 0 }, k{ SIZE - 1 }; j < SIZE / 2; j++, k--) {
			swap(sudokuLogic[i][j], sudokuLogic[i][k]);
		}
	}
}
void Sudoku::gameRandom() {
	for (int random_value{ rand() % 100 }; random_value > 0; random_value--) {
		transposing();
		flipGorizontaly();
		flipVerticaly();
		swapColumn();
		swapRow();
	}
}
void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void Sudoku::Move(char ch) {
	switch (ch) {
	case LEFT:
		if (posX > 0) posX--;
		break;
	case RIGHT:
		if (posX < 8) posX++;
		break;
	case UP:
		if (posY > 0) posY--;
		break;
	case DOWN:
		if (posY < 8) posY++;
		break;
	}
}
bool Sudoku::CheckStep() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (sudokuGrid[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}
int Sudoku::CheckSolve() {
	int countFail = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (sudokuGrid[i][j] != sudokuLogic[i][j]) {
				countFail++;
			}
		}
	}
	return countFail;
}
void Sudoku::setNumber(int num) {
	if (!sudokuLogic[posX][posY]) {
		sudokuGrid[posX][posY] = num;
	}
}
void Sudoku::FillUserField() {
	int r = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (r % 3) {
				sudokuGrid[i][j] = sudokuLogic[i][j];
			}
			r++;
		}
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	Sudoku sudoku;
	sudoku.FillUserField();
	hideCursor();
	while (true) {
		char key = _getch();
		if (key == LEFT || key == RIGHT ||
			key == UP || key == DOWN) {
			sudoku.Move(key);
		}
		else if (key > 48 && key < 58) {
			sudoku.setNumber(key = 48);
		}
		else if (key == 27) cout << "EXIT.";
		
		system("cls");
		//cout << "\033[2J\033[1;1H";
		if (!sudoku.CheckStep()) {
			int countFail = sudoku.CheckSolve();
			if (countFail) {
				cout << "Допущено ошибок: " << countFail << endl;
			}
			else {
				cout << "ПОЗДРАВЛЯЕМ! ВСЁ ВЕРНО!\n";
				cout << sudoku;
				break;
			}
		}
		cout << sudoku;
	}

}
