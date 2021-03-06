#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <sstream>

using namespace sf;
using namespace std;

int grid[12][12];
int sgrid[12][12];
bool DISPLAY = true;
bool LOSE = false;
int BOMBS = 15;
int TILES = 10 * 10;
int w = 32;



void opentile(int x, int y) {
    if (sgrid[x][y] == 10) {
        TILES--;
        sgrid[x][y] = grid[x][y];
        if (sgrid[x][y] == 0) {
            opentile((x + 1), y);
            opentile((x + 1), (y + 1));
            opentile((x + 1),(y - 1));
            opentile(x, y + 1);
            opentile(x, y - 1);
            opentile((x - 1), y);
            opentile((x - 1),(y + 1));
            opentile((x - 1),(y - 1));
        }
    }
}


void make_grid() {
    //create the inital board and add bombs

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            grid[i][j] = 0;
        }
    }


    int added_bombs = 0;
    do{
        int x = (rand() % 10)+ 1;
        int y = (rand() % 10) + 1;
        if (grid[x][y] != 9) {
            grid[x][y] = 9;
            added_bombs++;
            if (grid[x + 1][y] != 9) grid[x + 1][y]++;
            if (grid[x][y + 1] != 9) grid[x][y + 1]++;
            if (grid[x - 1][y] != 9) grid[x - 1][y]++;
            if (grid[x][y - 1] != 9) grid[x][y - 1]++;
            if (grid[x + 1][y + 1] != 9) grid[x + 1][y + 1]++;
            if (grid[x - 1][y - 1] != 9) grid[x - 1][y - 1]++;
            if (grid[x - 1][y + 1] != 9) grid[x - 1][y + 1]++;
            if (grid[x + 1][y - 1] != 9) grid[x + 1][y - 1]++;
        }

    } while (BOMBS > added_bombs);
}


Sprite game_display(int x, int y, Sprite s, int i , int j) {
    if (LOSE) sgrid[i][j] = grid[i][j];
    if ((x == i && y == j) && (sgrid[x][y] == 10|| sgrid[x][y] == 9)) {
        s.setTextureRect(IntRect(sgrid[x][y] * w, 0, w, w));
        s.setColor(Color(211, 211, 211));
        if (LOSE)s.setColor(Color::Red);;
        s.setPosition(x * w, y * w);
    }
    else {
        s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
        s.setColor(Color::White);
        s.setPosition(i * w, j * w);
    }
    return s;
}


int main()
{
    srand(time(0));

    Clock clock;

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");


    Texture t;
    t.loadFromFile("../images/tiles.jpg");
    Sprite s(t);
    make_grid();

    while (app.isOpen())
    {   

        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;
        
        
        Event e;
        while (app.pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
                app.close();
            case  Event::MouseButtonPressed:
                if (e.key.code == Mouse::Left) {
                    if (sgrid[x][y] != 11) opentile(x, y);

                    if (sgrid[x][y] == 9) {
                        LOSE = true;
                        
                        for (int i = 1; i <= 10; i++)
                            for (int j = 1; j <= 10; j++) {
                                app.draw(game_display(x, y, s, i, j));
                            }
                    if (DISPLAY) app.display();
                    DISPLAY = false;
                    }
                    
                        
                        
                        
                }
                else if (e.key.code == Mouse::Right) {
                    if (sgrid[x][y] == 10) {
                        sgrid[x][y] = 11;
                    }
                    else {
                        sgrid[x][y] = 10;
                    }

                }


            default:
                if (DISPLAY) {
                    app.clear(Color::White);
                    for (int i = 1; i <= 10; i++)
                        for (int j = 1; j <= 10; j++) {
                            //game_display(x, y, s, i, j);
                            app.draw(game_display(x, y, s, i, j));
                        }
                    
                    app.display();
                }
                
                if (BOMBS == TILES && DISPLAY) {
                    DISPLAY = false;
                    Time elapsed1 = clock.getElapsedTime();
                    cout << "Congrats you won in " << elapsed1.asSeconds() << " secounds!" << endl;
                    cout << "press R to restart" << endl;
                }

                if ((e.key.code == Keyboard::R)) {
                    TILES = 100;
                    make_grid();
                    clock.restart();
                    DISPLAY = true;
                    LOSE = false;
                }
            }
        }
    }

    return 0;
}
