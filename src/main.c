#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "room.h"
#include "window.h"
#include "entity.h"
#include "sample.h"
#include "game.h"

int main(int argc, char **argv)
{
    Room first;
    
    ResourceManager rm;
    
    Window window;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = new_Window("a test window", 640, 480, SDL_WINDOW_RESIZABLE);
    rm = new_ResourceManager();
    
    first = new_Room(rm, window, "bg.png", NULL);

    currentRoom = &first;
    while (1)
    {
	List events = new_List(0);
	SDL_Event *e = malloc(sizeof(SDL_Event));
	while(SDL_PollEvent(e))
	{
	    switch (e->type)
	    {
	    case SDL_QUIT:
		Room_kill(currentRoom, GAME_KILLED);
		SDL_Quit();
		exit(0);
		break;
	    case SDL_WINDOWEVENT:
		if (e->window.event == SDL_WINDOWEVENT_RESIZED)
		{
		    Window_resizedCB(window);
		    break;
		}
		// INTENTIONAL FALLTHROUGH
	    default:
		NULL;
//		List_enqueue(events, e);
	    }
	    
	}
	Room_update(*currentRoom);
	Room_react(*currentRoom);
	Room_draw(*currentRoom);

	free(events);
    }

    return 0;
}
