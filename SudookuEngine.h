#pragma once
#include<vector>
#include "SudokuGame.h"
#include<string>
#define SIZE 9 // Размер поля
using namespace sf;

enum class EngineState {GAME, GAMEOVER, WIN}; // Статусы игры

class SudokuEngine {
private:
	int** sudokuLogic; // Логическое поле
	int** sudokuView; // Отображаемое поле
	bool** sudokuPlayer; // Поле на основе отображаемого поля для задания цвета цифр
	int** numberCursorMouse; // Для координат курсора мыши
	std::vector<int> vector{ 1,2,3,4,5,6,7,8,9 }; // дя создания поля
	int positionCursor; // Позиция курсора на поле
	Vector2i posMouse; // Координаты курсора мыши
	Font font; // Шрифт
	EngineState engineState; // Статусы игры
	int cellSize; // Размер ячейки поля
	int fontSize; // Размер шрифта ячейки поля
	Texture backgroundTexture; // Текстура заднего плана
	Sprite background; //  Спрайт для тектуры заднего плана
public:
	SudokuEngine(); // Конструктор поля
	~SudokuEngine(); // Деструктор поля
	bool CheckWin(); // Проверка победы
	bool checkFull();// Проверка заполненсти поля
	void setDifficulty(int difficulty); // установка сложности игры
	bool runEngine(RenderWindow& window, int difficulty); // Запуск движка игры
	void drawSquare(RenderWindow& window); // Отрисовка поля
	void selectCell(); // Выбор ячейки и ввод цифр
	bool checkRow(int row, int value); // проверка строки
	bool checkColumn(int col, int value); // проверка колонки
	bool checkSquare(int row, int col, int value); // проверка квадрата
	bool checkCorrectInput(int row, int col, int value); // Проверка корректности воода
private:
	void transposing(); // транспонирование поля
	void swapColumn(); // смена колонок в пределах одной группы
	void swapRow(); // Смена строк в пределах одной группы
	void gameRandom(); // Перемешивание поля
	void flipGorizontaly(); // Отажение по горизонтали
	void flipVerticaly(); // Отражение по вертикали
	void drawCheckFullField(RenderWindow& window); // Отрисовка бокса проверки поля
	bool gameOver(RenderWindow& window);
	bool gameWin(RenderWindow& window);
};

