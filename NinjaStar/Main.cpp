#include "Game.h"

int main()
{
	RenderWindow window(VideoMode(1366, 768), "NinjaStar", Style::Fullscreen | Style::Close);
	Game game(&window);
	Menu menu(&window);
	Score scores(&window);
	float deltaTime = 0.0f;
	Clock clock;
	vector<Event> textEnter;

	while (window.isOpen())
	{
		
		textEnter.clear();
		deltaTime = clock.restart().asSeconds();
		/*	if (deltaTime > 1.0f / 60.0f)
			{
				deltaTime = 1.0f / 60.0f;
			}*/

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
					window.close();
				break;
			case Event::TextEntered:
				textEnter.push_back(event);
				break;
			default:
				break;
			}
		}
		int state = menu.getState();
		if (state == 0)
		{
			menu.update();
			menu.draw();
			game.resetState();
		}
		if (state == 1)
		{
			menu.updateInput(textEnter);
			menu.inputMenu();
		}
		if (state == 2)
		{
			game.setPlayerName(menu.getPlayerName());
			game.Update(deltaTime);
			game.Draw();
			if (game.getCheckState())
			{
				menu.setActionToZero();
				menu.ResetName();
				game.GameReset();
			}
		}
		if (state == 3)
		{
			scores.update();
			scores.draw();
			if (scores.getCheckState())
			{
				menu.setActionToZero();
				scores.resetState();
			}
		}
	}
	return 0;
}