#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<time.h>
#include<Windows.h>
#include "SudookuEngine.h"
#define SIZE_H 1920 // Разрешение окна по горизонтали
#define SIZE_V 1080 // Разрешение окна по вертикали

using namespace sf;

enum class GameState { MENU, GAME, END , DEVELOPER}; // Статусы игры

class SudokuGame
{
private: 
	Font font; // Шрифт
	GameState state; // Статус игры
	Texture backgroundTexture; // Текстура заднего плана
	Sprite background; // Спрайт для текстуры заднего плана
	void levels(); // Меню с выбором сложности
	void mainMenu(); // Главное меню
	void developer(); // Меню с разработчиком

public:
	SudokuGame(); // Конструктор
	~SudokuGame(); // Дестурктор
	void runGame(); // Запуск игры


};



