// TODO: Create a constructor for Tile object 
//       16:44
#include <raylib.h>
#include <iostream>
#include <deque>
#include <raymath.h>

using namespace std;

float cellSize = 24;
float cellCount = 24;

double lastUpdate = 0;
double interval = 0.1;

const Vector2 UP = {0,-1};
const Vector2 DOWN = {0,1};
const Vector2 LEFT = {-1,0};
const Vector2 RIGHT = {1,0};


bool eventTriggered(double interval) {

    double currentTime = GetTime();

    if(currentTime - lastUpdate >= interval) {
        lastUpdate = currentTime;
        return true;
    }
    return false;
}

class Snake {

    public: 
        deque<Vector2> body = {Vector2{7,7}, Vector2{6,7}, Vector2{5,7}};
        Vector2 direction = {1,0};

        void Draw() {
            for(unsigned int i = 0; i < body.size(); i++) {
                float x = body[i].x;
                float y = body[i].y;
                Rectangle segment = Rectangle{x*cellSize, y*cellSize, cellSize, cellSize};
                DrawRectangleRounded(segment, 0.5, 6, GREEN);
            }
        }

        void Update() {
            body.pop_back();
            body.push_front(Vector2Add(body[0], direction));
        }

};

class Food {

    public:
        Vector2 position; 
        Texture2D texture;

        Food() {
            Image image = LoadImage("graphics/burger.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = RandomPos();
        }

        ~Food() {
            UnloadTexture(texture);
        }


        void Draw() {
            DrawTextureEx(texture, {(position.x * cellSize), (position.y * cellSize)}, 0, 0.03, WHITE);
        }

        Vector2 RandomPos() {
            float x = GetRandomValue(0, cellCount - 1);
            float y = GetRandomValue(0, cellCount - 1);
            return Vector2{x, y};
        }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        snake.Update();
        CheckCollisionWithFood();
    }

    void CheckCollisionWithFood() {
        if (Vector2Equals(snake.body[0], food.position)) {
            cout << "Nom Nom Nom" << endl;
        }
    }
};


int main () {

    cout<<"Starting game..."<< endl;
    InitWindow(cellSize * cellCount, cellSize * cellCount,"Snake");
    SetTargetFPS(60);

    Game game = Game();

    while(WindowShouldClose() == false) { // if esc or X is pressed on window

        BeginDrawing();

        if(eventTriggered(interval)) {
            game.Update();
        }

        if(IsKeyPressed(KEY_W) & game.snake.direction != DOWN) {
            game.snake.direction = UP;
        }

        if(IsKeyPressed(KEY_S) & game.snake.direction != UP) {
            game.snake.direction = DOWN;
        }

        if(IsKeyPressed(KEY_A) & game.snake.direction != RIGHT) {
            game.snake.direction = LEFT;
        }

        if(IsKeyPressed(KEY_D)& game.snake.direction != LEFT) {
            game.snake.direction = RIGHT; 
        }

        ClearBackground(BLACK);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
