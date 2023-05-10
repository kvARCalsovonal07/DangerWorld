#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

float CameraX = 0;
float CameraY = 0;

class Objects : public sf::Drawable {

public:
	int x = 0;
	int y = 0;
	int ScaleX = 32;
	int ScaleY = 32;

	void update() {
		rect.setPosition(x - CameraX, y - CameraY);
		rect.setSize(sf::Vector2f(ScaleX, ScaleY));
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(rect, states);
	}

private:
	sf::RectangleShape rect;
};

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer");
	window.setFramerateLimit(60);

    sf::Event event;

	sf::RectangleShape Player;
	Player.setSize(sf::Vector2f(32, 32));

	float RectX = 400;
	float RectY = 300;
	float DelayX = 400;
	float DelayY = 300;

	Objects Ground1;
	Ground1.ScaleX = 800;
	Ground1.ScaleY = 32;
	Ground1.x = 0;
	Ground1.y = (600 - 32);

	float xVelocity = 3;
	float yVelocity = 0;
	float Gravity = 0;

	sf::FloatRect PlayerBounds = Player.getGlobalBounds();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			
			if (xVelocity < 10)
			{
				xVelocity += 0.5;
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				
				if (xVelocity > -10)
				{
					xVelocity -= 0.5;
				}
			}
			else
			{
				if (xVelocity > 0)
				{
					xVelocity -= 0.5;
				}
				if (xVelocity < 0)
				{
					xVelocity += 0.5;
				}
			}
		}

		RectX += xVelocity;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && RectY > Ground1.y - Ground1.ScaleY)
		{
			yVelocity = 15;
			Gravity = 0;
		}

		if (yVelocity > 0)
		{
			yVelocity -= 0.1;
			RectY -= yVelocity;
		}

		if (RectY > Ground1.y - Ground1.ScaleY)
		{
			RectY -= Gravity;
			Gravity = 0;
			yVelocity = 0;
		}
		else
		{
			if (Gravity < 20)
			{
				Gravity += 0.4;
			}
		}

		RectY += Gravity;

		// Rendering

		CameraX = CameraX + 0.1 * ((RectX - DelayX) - CameraX);
		CameraY = CameraY + 0.1 * ((RectY - DelayY) - CameraY);

		window.clear();

		Ground1.update();
		window.draw(Ground1);
		Player.setPosition(RectX-CameraX, RectY-CameraY);
		window.draw(Player);

		window.display();


	}
}