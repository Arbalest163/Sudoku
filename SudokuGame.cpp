#include "SudokuGame.h"


RenderWindow window(VideoMode(SIZE_H, SIZE_V), "Sudoku", Style::Close);


SudokuGame::SudokuGame()
{
	font.loadFromFile("Black-Acute.ttf");
	state = GameState::MENU;
	backgroundTexture.loadFromFile("Background.jpg");
	background.setTexture(backgroundTexture);
}
SudokuGame::~SudokuGame()
{
}
void SudokuGame::mainMenu()
{
	//window.setFramerateLimit(60);
	Text title(L"Судоку", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 60);
	const int numWords = 3;
	Text textMenu[numWords];
	textMenu[0].setString(L"Игра");
	textMenu[1].setString(L"Выход");
	textMenu[2].setString(L"Разработчик");
	for (int i = 0; i < numWords; i++)
	{
		textMenu[i].setFont(font);
		textMenu[i].setCharacterSize(65);
		textMenu[i].setPosition(SIZE_H / 2 - textMenu[i].getGlobalBounds().width / 2, 200 + i * 120);
	}
	while (state == GameState::MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		for (int i = 0; i < numWords; i++)
			if (textMenu[i].getGlobalBounds().contains(mouse))
				textMenu[i].setFillColor(Color::Red);
			else textMenu[i].setFillColor(Color::White);
		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < numWords; i++)
			window.draw(textMenu[i]);

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = GameState::END;
                
			for (int i{ 0 }; i < numWords; i++) 
			{
				if (textMenu[i].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					if(i == 0) state = GameState::GAME;
					if(i == 1) state = GameState::END;
					if(i == 2) state = GameState::DEVELOPER;
				}

			}
			// Проверить цикл выше и удалить лишнее снизу, если всё работает

			/*else if (textMenu[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::GAME;
			}
			else if (textMenu[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::END;
			}
			else if (textMenu[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GameState::DEVELOPER;
			}*/
		}
		window.display();
	}
}

void SudokuGame::developer()
{
	//window.setFramerateLimit(60);
	Text title(L"Разработчик", font, 80);
	title.setStyle(Text::Bold);
	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 60);
	const int numWords = 2;
	Text textMenu[numWords];
	textMenu[0].setString(L"Иван Гилязов");
	textMenu[1].setString(L"Вернуться");
	for (int i = 0; i < numWords; i++)
	{
		textMenu[i].setFont(font);
		textMenu[i].setCharacterSize(65);
		textMenu[i].setPosition(SIZE_H / 2 - textMenu[i].getGlobalBounds().width / 2, 200 + i * 120);
	}
	while (state == GameState::DEVELOPER)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		if (textMenu[1].getGlobalBounds().contains(mouse))
			textMenu[1].setFillColor(Color::Red);
		else textMenu[1].setFillColor(Color::White);
		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < numWords; i++)
			window.draw(textMenu[i]);

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				state = GameState::END;

			else if (textMenu[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased 
					&& event.key.code == Mouse::Left || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				state = GameState::MENU;
			}
		}
		window.display();
	}
}

void SudokuGame::levels()
{
	//window.setFramerateLimit(60); // Ограничение частоты кадров монитора
	SudokuEngine engine; // Создание движка игры
	Text title(L"Уровень сложности", font, 90); // Текст заголовка
	title.setStyle(Text::Bold); // Стиль заголовка
	title.setPosition(SIZE_H / 2 - title.getGlobalBounds().width / 2, 30); // Установка позиции заголовка
	const int numberWords = 4; // Количество слов меню
	Text text[numberWords]; // Массив текста меню
	text[0].setString(L"Лёгкий");
	text[1].setString(L"Средний");
	text[2].setString(L"Сложный");
	text[3].setString(L"Вернуться");
	for (int i = 0; i < numberWords; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setPosition(SIZE_H / 2 - text[i].getGlobalBounds().width / 2, 150 + i * 120);
	}
	// Цикл активен пока статус игры GAME
	while (state == GameState::GAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
	
		for (int i = 0; i < numberWords; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Red);
			else text[i].setFillColor(Color::White);
		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i < numberWords; i++) {
			window.draw(text[i]);
		}
		// Цикл отслеживания нажатий
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				state = GameState::END;
			}
			// Цикл выбора уровня сложности и запуск движка
			for (int i{ 0 }; i < numberWords; i++) {
				if ((i == numberWords - 1) && text[i].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased
					&& event.key.code == Mouse::Left || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					state = GameState::MENU;
				}
				else if (text[i].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					if (engine.runEngine(window, i)) // Запуск движка тут
						state = GameState::END;
					else
						state = GameState::MENU;
				}

			}
			// Проверить цикл выше и удалить лишнее, если все нормально

			/*if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 0))
					state = GameState::END;
				else
					state = GameState::MENU;
			}
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 1))
					state = GameState::END;
				else
					state = GameState::MENU;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (engine.runEngine(window, 2))
					state = GameState::END;
				else
					state = GameState::MENU;
			}
			else if (text[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased 
					&& event.key.code == Mouse::Left || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				state = GameState::MENU;
			}*/
		}
		window.display(); // Отображение всего, что было отрисовано в процессе работы цикла
	}
}

void SudokuGame::runGame()
{
	while (state != GameState::END)
	{
		switch (state)
		{
		case GameState::MENU:
			mainMenu();
			break;
		case GameState::GAME:
			levels();
			break;
		case GameState::DEVELOPER:
			developer();
			break;
		}
	}
}
