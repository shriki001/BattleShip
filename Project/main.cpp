#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include <SFML/Graphics.hpp>
#include "E_includes/Execute.h"
#include "Game.h"


int main()
{
	sf::Thread video([&]()
	{
		RunProcess("data\\vi.bat"); 
	}
	);
	video.launch();
	Game game;
	video.wait();
	game.run();

	return EXIT_SUCCESS;
}