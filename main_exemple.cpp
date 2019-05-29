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
	 

      x += speedX;
      y += speedY;

      manager.setImagePos(kittens, x, y);
      
      manager.draw();
      manager.processInput();
      manager.sleep(10);
    }
}
