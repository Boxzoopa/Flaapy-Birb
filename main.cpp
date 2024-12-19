#include "raylib.h"
#include <iostream>
#include <vector>

#include "rng.h"
#include "sprite.h"
#include "bird.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Flaapy Birb");
    SetTargetFPS(60);                // Set our game to run at 60 frames-per-second
    float deltaTime = 0;
    Image logo = LoadImage("resources/bird.ico");
    SetWindowIcon(logo);

    // Load Objects
    Bird bird("resources/bird.png", 300, 300);

    std::vector<Sprite> pipes;
    pipes.push_back(Sprite("resources/pipe.png", 500, randint(-16, 616)));
    pipes.push_back(Sprite("resources/pipe.png", 800, randint(-16, 616)));
    pipes.push_back(Sprite("resources/pipe.png", 1100, randint(-16, 616)));

    bool die = false;
    bool exit_game = false;
    int score = 0;

    std::vector<bool> passedPipe(pipes.size(), false); // Flags for each pipe

    // Main game loop
    while (!WindowShouldClose() && !exit_game)
    {
        // Update
        deltaTime = GetFrameTime();

        if (!die) {
            bird.update(deltaTime);

            for (size_t i = 0; i < pipes.size(); ++i) {
                pipes[i].move({ -1, 0 }, deltaTime, 120);
                if (pipes[i].position.x <= 0 - (32 * 3)) {
                    pipes[i].position.x = 800 + (32 * 3);
                    pipes[i].position.y = randint(-16, 616);
                    passedPipe[i] = false;
                }

                if (bird.checkCollision(pipes[i], 3) || bird.position.y <= 0 || bird.position.y >= 600) {
                    std::cout << "Game Over!" << std::endl;
                    die = true; // Set die flag to true when collision happens
                }

                // Increment score when the bird crosses the pipe
                if (bird.position.x > pipes[i].position.x && !passedPipe[i]) {
                    passedPipe[i] = true;
                    score += 1;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Draw pipes
        for (size_t i = 0; i < pipes.size(); ++i) {
            pipes[i].draw(3);
        }

        if (!die)
        {
            // Draw the bird
            bird.draw(3);
        }

        // Draw score (Center it horizontally)
        const char* scoreText = TextFormat("Score: %i", score);
        int textWidth = MeasureText(scoreText, 20);
        DrawText(scoreText, (screenWidth - textWidth) / 2, 10, 20, BLACK);

        // If the game is over, show the game over screen
        if (die) {
            // Center text horizontally for game over screen
            const char* gameOverText = "Game Over";
            const char* scoreGameOverText = TextFormat("Score: %i", score);
            const char* pressToQuitText = "Press ESC to Quit";

            int gameOverWidth = MeasureText(gameOverText, 40);
            int scoreGameOverWidth = MeasureText(scoreGameOverText, 20);
            int pressToQuitWidth = MeasureText(pressToQuitText, 20);

            ClearBackground(BLACK);
            DrawText(gameOverText, (screenWidth - gameOverWidth) / 2, 255, 40, BLACK);
            DrawText(gameOverText, (screenWidth - gameOverWidth) / 2, 250, 40, WHITE);

            DrawText(scoreGameOverText, (screenWidth - scoreGameOverWidth) / 2, 305, 20, BLACK);
            DrawText(scoreGameOverText, (screenWidth - scoreGameOverWidth) / 2, 300, 20, WHITE);
           
            DrawText(pressToQuitText, (screenWidth - pressToQuitWidth) / 2, 355, 20, BLACK);
            DrawText(pressToQuitText, (screenWidth - pressToQuitWidth) / 2, 350, 20, WHITE);

            // Wait for ESC to quit
            if (IsKeyDown(KEY_ESCAPE)) {
                exit_game = true;
            }
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
