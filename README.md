# sdlwrapper
Un wrapper objet sur SDL, légèrement plus facile à prendre en main pour les débutants en C++

## Fonctions :

- `int addImage(string path, int x=0, int y=0, int w=0, int h=0)`
- `bool moveImage(int indice, int dx, int dy)`
- `void setImagePos(int indice, int x, int y)`
- `void getImagePos(int indice, int& x, int& y)`
- `void setImageSize(int indice, int w, int h)`
- `void getImageSize(int indice, int& w, int& h)`
- `void getImageInfo(int indice, int& x, int& y, int& w, int& h)`
- `void draw()`
- `bool isRunning()`
- `void stop()`
- `void sleep(int ms)`
