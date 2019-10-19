
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <time.h>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define HEIGHT 30
#define WIDTH 20
#define SIZE 16


int LENGTH = 5;
int dir = DOWN;
int score = 0;
struct Snake
{
	int x;
	int y;
} snake[100];

struct Fruit
{
	int x;
	int y;
}fruit;

void Tick()
{
	for (int i = LENGTH; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (dir == LEFT) snake[0].x -= 1;
	if (dir == RIGHT) snake[0].x += 1;
	if (dir == UP) snake[0].y -= 1;
	if (dir == DOWN) snake[0].y += 1;


	if (snake[0].x == fruit.x && snake[0].y == fruit.y)
	{
		score++;
		std::cout << score << std::endl;

		fruit.x = rand() % WIDTH;
		fruit.y = rand() % HEIGHT;

		LENGTH++;
	}

	if (snake[0].x > WIDTH) snake[0].x = 0;
	if (snake[0].x < 0) snake[0].x = WIDTH;
	if (snake[0].y > HEIGHT) snake[0].y = 0;
	if (snake[0].y < 0) snake[0].y = HEIGHT;

	for (int i = 1; i < LENGTH; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			LENGTH /= 2;
		}
	}
}

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WIDTH * SIZE, HEIGHT * SIZE), "Snake");
	
	sf::RectangleShape fruitImage(sf::Vector2f(SIZE, SIZE));
	sf::Texture snakeTexture;
	snakeTexture.loadFromFile("images/snake.jpg");
	sf::Sprite snakeImage(snakeTexture);
	snakeImage.setTextureRect(sf::IntRect(0, 0, SIZE, SIZE));

	sf::Texture grid;
	grid.loadFromFile("images/background.png");
	sf::Sprite background(grid);

	fruitImage.setFillColor(sf::Color::Red);

	fruit.x = 10;
	fruit.y = 10;
	
	sf::Clock clock;
	float timer = 0;
	float delay = 0.1;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		timer += time;
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				dir = LEFT;
				break;
			case sf::Keyboard::Right:
				dir = RIGHT;
				break;
			case sf::Keyboard::Up:
				dir = UP;
				break;
			case sf::Keyboard::Down:
				dir = DOWN;
				break;
			}
			
		}

		if (timer > delay)
		{
			timer = 0;
			Tick();
		}

		window.clear();
		
		window.draw(background);

		for (int i = 0; i < LENGTH; i++)
		{
			snakeImage.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
			window.draw(snakeImage);
		}
		fruitImage.setPosition(fruit.x * SIZE, fruit.y * SIZE);
		window.draw(fruitImage);
		window.display();
	}
	return 0;
}
