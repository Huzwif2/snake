// TODO: Create a constructor for Tile object 
//       16:44
#include <raylib.h>
#include <iostream>

using namespace std;

int cellSize = 67;
int cellCount = 9;

class Tile {

public:
    Vector2 position = {5,6};

    void Draw() 
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, DARKGRAY);
    }
};



int main () {
    
    cout<<"Starting game..."<< endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount,"Minesweeper");
    SetTargetFPS(60);

    Tile tile = Tile();

    while(WindowShouldClose() == false) { // if esc or X is pressed on window

        BeginDrawing();

        ClearBackground(BLACK);

        tile.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
