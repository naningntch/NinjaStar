#include "Game.h"

int main()
{
	RenderWindow window(VideoMode(1366, 768), "NinjaStar", Style::Fullscreen | Style::Close);
		Game game(&window);

	float deltaTime = 0.0f;
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 60.0f)
		{
			deltaTime = 1.0f / 60.0f;
		}

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					window.close();
				break;
			default:
				break;
			}
		}
		game.Update(deltaTime);
		game.Draw();
	}
	return 0;
}