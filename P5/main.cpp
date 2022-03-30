#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>

using namespace sf;
using namespace std;



int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int w = 32;
    //vector<int, int> grid;
    //vector<int, int> sgrid;
    int grid[12][12];
    int sgrid[12][12]; //for showing

    Texture t;
    t.loadFromFile("C:/Users/tommi/source/repos/P5/P5/x64/Release/images/tiles.jpg");
    Sprite s(t);
    

    //create the inital board
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 10 == 0)  grid[i][j] = 9;
            else grid[i][j] = 0;
        }

    //counts number of bombs next to tile
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();


            if (e.type == Event::MouseButtonPressed)
                
                if (e.key.code == Mouse::Left) {
                    if (sgrid[x][y] == 11) ;
                    else {
                        sgrid[x][y] = grid[x][y];
                        if (sgrid[x][y] == 0) {
                            sgrid[x + 1][y] = grid[x + 1][y];
                            sgrid[x + 1][y + 1] = grid[x + 1][y + 1];
                            sgrid[x + 1][y - 1] = grid[x + 1][y - 1];
                            sgrid[x][y + 1] = grid[x][y + 1];
                            sgrid[x][y - 1] = grid[x][y - 1];
                            sgrid[x - 1][y] = grid[x - 1][y];
                            sgrid[x - 1][y + 1] = grid[x - 1][y + 1];
                            sgrid[x - 1][y - 1] = grid[x - 1][y - 1];
                        }
                    }
                }
                //flag tile or unflag
                else if (e.key.code == Mouse::Right) {
                    if (sgrid[x][y] == 10) {
                        sgrid[x][y] = 11;
                    }
                    else {
                        sgrid[x][y] = 10;
                    }
                    
                }
            
        }

        app.clear(Color::White);

        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                app.draw(s);
            }

        app.display();
    }

    return 0;
}
