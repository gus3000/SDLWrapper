#include <iostream>

#include "libgraphique.hpp"

using std::cout;
using std::cerr;
using std::endl;

int main()
{
  const int WIDTH = 640;
  const int HEIGHT = 480;
  
  SDLManager manager(WIDTH, HEIGHT);

  int kittens = manager.addImage("kittens.jpeg");
  int speedX = 5, speedY = 5;
  //for(int i=0; i<200; ++i)
  while(manager.isRunning())
    {
      int x,y,w,h;
      manager.getImageInfo(kittens,x,y,w,h);

      if (x+w > WIDTH || x < 0)
	{
	  speedX = -speedX;
	}
      
      if(y+h > HEIGHT || y < 0)
	{
	  speedY = -speedY;
	}


      SDL_Event e;
      while(SDL_PollEvent(&e))
	{
	  if(e.type == SDL_QUIT)
	    {
	      cout << "salut" << endl;
	      return 0;
	    }
	  else if(e.type == SDL_KEYDOWN)
	    {
	      switch(e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		  cout << "droite" << endl;
		  break;
		case SDLK_LEFT:
		  cout << "gauche" << endl;
		  break;

		default:
		  cout << "J'ai pas compris la touche" << endl;
		}
	    }
	}
      
      x += speedX;
      y += speedY;

      manager.setImagePos(kittens, x, y);
      
      manager.draw();
      manager.sleep(10);
    }
}
