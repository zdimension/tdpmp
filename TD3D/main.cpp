#include "Application.hpp"

int main()
{
    atexit(SDL_Quit);

    Application app;
    app.run();
    return 0;
}