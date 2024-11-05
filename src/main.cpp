#include <raylib.h>
#include <iostream>

int cpuScore = 0;
int playerScore = 0;

class Ball
{
public:
    float x, y;
    int speedx, speedy;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, RED); // Bola
    }

    void Update()
    {
        x += speedx;
        y += speedy;

        if (x + radius >= GetScreenWidth()) {
            x = GetScreenWidth() / 2;
            y = GetScreenHeight() / 2;
            cpuScore++;
        }
        if (x - radius <= 0){
            x = GetScreenWidth() / 2;
            y = GetScreenHeight() / 2;
            playerScore++;
        }

        if (y + radius >= GetScreenHeight() or y - radius <= 0)
        {
            speedy *= -1;
        }
    }
};

class Player 
{
public:
    float y;
    int speed;
    float x = 10;
    float width = 20;
    float height = 200;

    void Draw ()
    {
        DrawRectangle(x, y, width, height, WHITE); // Player 1
    }

    void Update() 
    {
        if (IsKeyDown(KEY_W) and y > 0) {
            y -= speed;
        }
        if (IsKeyDown(KEY_S) and (y + height) < GetScreenHeight()) {
            y += speed;
        }
    }
};

class CPU
{
public:
    float x, y;
    int speed;
    float width = 20;
    float height = 200;

    void Draw ()
    {
        DrawRectangle(x, y, width, height, WHITE); // Player 2
    }

    void Update (int ballY) {
        if (ballY > y + 100)
        {y += speed;}
        if (ballY < y + 100 and y + 200 <= GetScreenHeight())
        {y -= speed;}

        if (y < 0)
        {y = 0;}
        if (y + 200 > GetScreenHeight())
        {y = GetScreenHeight() - 200;}
    }
};

Ball ball;
Player player;
CPU cpu;

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Simple Pong - RayLib");
    SetTargetFPS(60);

    ball.x = (GetScreenWidth() / 2);
    ball.y = (GetScreenHeight() / 2);
    ball.radius = 20;
    ball.speedx = 7;
    ball.speedy = 7;

    player.y = GetScreenHeight() / 2 - 100;
    player.x = 10;
    player.speed = 6;

    cpu.x = GetScreenWidth() - 30;
    cpu.y = GetScreenHeight() / 2 - 100;
    cpu.speed = 6;

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), GRAY);

        ball.Draw();
        ball.Update();

        player.Draw();
        player.Update();

        cpu.Draw();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speedx *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speedx *= -1;
        }

        DrawText(TextFormat("%i", cpuScore), GetScreenWidth() / 2 - 25, 10, 30, GRAY);
        DrawText(TextFormat("%i", playerScore), GetScreenWidth() / 2 + 10, 10, 30, GRAY);
        
        EndDrawing();
    }

    CloseWindow();
}