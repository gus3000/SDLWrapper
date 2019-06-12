#ifndef LIB_GRAPHIQUE_HPP
#define LIB_GRAPHIQUE_HPP

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::ofstream;

class Image
{
private:
  SDL_Texture* texture;
  SDL_Rect* rect;
public:
  Image(SDL_Texture* texture, int x=0, int y=0, int width=0, int height=0) : texture(texture)
  {
    this->rect = new SDL_Rect();
    this->rect->x = x;
    this->rect->y = y;

    if(width == 0 && height == 0)
      SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
    this->rect->w = width;
    this->rect->h = height;
  }

  ~Image()
  {
    //cout << "Image destructor" << endl;
    //SDL_DestroyTexture(this->texture);
  }

  SDL_Texture* getTexture()
  {
    return this->texture;
  }

  SDL_Rect* getRect()
  {
    return this->rect;
  }
  
  void setXY(int x, int y)
  {
    this->rect->x = x;
    this->rect->y = y;
  }

  void setWH(int w, int h)
  {
    this->rect->w = w;
    this->rect->h = h;
  }
};

const string RESSOURCE_DIR = "img/";

class SDLManager
{
private:
  SDL_Window *win;
  SDL_Renderer* ren;
  //vector<SDL_Texture*> textures;
  vector<Image> images;

  bool running;
  const bool debug;
  ofstream debugFile;

  void log(const string& msg)
  {
    ostream& output = this->debug ? cout : debugFile;
    output << msg << endl;
  }
  
  void logError(const string& msg)
  {
    ostream& output = this->debug ? cerr : debugFile;
    
    output << msg << " : " << SDL_GetError() << endl;
  }
  
public:
     SDLManager(const int WIDTH=640, const int HEIGHT=480, string titre="Sans Titre", bool debug=true) : debug(debug)
  {
    this->running = true;
    
    if(!debug)
      {
	debugFile.open("debug.log");
      }
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
      logError("Erreur SDL_Init");
      return;
    }
    
    this->win = SDL_CreateWindow(titre.c_str(), 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr){
      logError("Erreur création fenêtre");
      SDL_Quit();
      return;
    }

    int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if ((IMG_Init(flags) & flags) != flags){
      logError("Erreur init SDL_image");
      SDL_Quit();
      return;
    }
    
    this->ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
      SDL_DestroyWindow(win);
      logError("Erreur création renderer");
      SDL_Quit();
      return;
    }
  }

  ~SDLManager()
  {

    if(debugFile.is_open())
      debugFile.close();

    for(auto it = this->images.begin(); it != this->images.end(); ++it)
      {
	SDL_DestroyTexture((*it).getTexture());
      }
    
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
  }

  int addImage(string path, int x=0, int y=0, int w=0, int h=0)
  {
    path = SDL_GetBasePath() + RESSOURCE_DIR + path;

    SDL_Texture* tex = IMG_LoadTexture(this->ren, path.c_str());
    if(tex == nullptr)
      {
	logError("Erreur lors du chargement de l'image");
	return -1;
      }
    Image img(tex,x,y,w,h);
    images.push_back(img);

    return images.size() - 1;
  }

  bool moveImage(int indice, int dx, int dy)
  {
    SDL_Rect* rect =  images[indice].getRect();
    images[indice].setXY(rect->x + dx, rect->y + dy);

    return true; //TODO
  }
  
  void setImagePos(int indice, int x, int y)
  {
    images[indice].setXY(x,y);
  }

  void getImagePos(int indice, int& x, int& y)
  {
    SDL_Rect* rect =  images[indice].getRect();
    x = rect->x;
    y = rect->y;
  }

  void setImageSize(int indice, int w, int h)
  {
    images[indice].setWH(w,h);
  }

  void getImageSize(int indice, int& w, int& h)
  {
    SDL_Rect* rect =  images[indice].getRect();
    w = rect->w;
    h = rect->h;
  }

  void getImageInfo(int indice, int& x, int& y, int& w, int& h)
  {
    SDL_Rect* rect =  images[indice].getRect();
    x = rect->x;
    y = rect->y;
    w = rect->w;
    h = rect->h;
  }
  
  void draw()
  {
    //cout << "drawing " << images.size() << " images." << endl;
    SDL_RenderClear(this->ren);
    for(auto it = this->images.begin(); it != this->images.end(); ++it)
      {
        SDL_RenderCopy(this->ren, (*it).getTexture(), NULL, (*it).getRect());
      }
    SDL_RenderPresent(this->ren);
  }

  vector<SDL_Event> processInput()
  {
    vector<SDL_Event> v;
    SDL_Event e;
    
    while(SDL_PollEvent(&e))
      {
	if(e.type == SDL_QUIT)
	  {
	    this->stop();
	  }
	else
	  {
	    v.push_back(e);
	  }
      }
  }

  bool isRunning()
  {
    return this->running;
  }

  void stop()
  {
    this->running = false;
  }
  
  void sleep(int ms)
  {
    SDL_Delay(ms);
  }
};

#endif
