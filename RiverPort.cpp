#include <SFML/Graphics.hpp>
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 300
int main()
{
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello");
  sf::RectangleShape rect(sf::Vector2f(10, 20));
  rect.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20 - 20));
  rect.setFillColor(sf::Color::Magenta);


  sf::RectangleShape background(sf::Vector2f(SCREEN_WIDTH, 20));
  background.setFillColor(sf::Color::Green);
  background.setPosition(sf::Vector2f(0, SCREEN_HEIGHT - 20));

  sf::Clock clock;
  float time = 0, delay = 0.1;

  int x = SCREEN_WIDTH / 2, y = SCREEN_HEIGHT - 20 - 20;
  int count = 0;
  while (window.isOpen())
  {
    time += clock.getElapsedTime().asSeconds();
    clock.restart();

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
      {
        switch (event.key.code)
        {
        case sf::Keyboard::Right:
          x += 5;
          break;
          
        case sf::Keyboard::Left:
          x -= 5;
          break;

        case sf::Keyboard::Space:
          y -= 30;
          break;
        }
      }
    }

    if (time > delay)
    {
      time = 0;
       
      if (y < SCREEN_HEIGHT - 40)
        y += 5;
    }


    window.clear();

    rect.setPosition(sf::Vector2f(x, y));
    window.draw(rect);
    window.draw(background);
    window.display();
  }
}