#pragma once

#include <raylib.h>
#include <cstdio> // Include the header file that declares the 'FormatText' function
#include <raylib.h> // Include the header file that declares the 'FormatText' function
#include <cmath> // Include the header file that declares the 'sqrtf' function

#include "../Scene.hpp"

struct Ball; // Forward declaration of Ball, getting an error on Game struct

typedef enum Action { // Enum for player and AI actions to separate input from update logic
    UP,
    DOWN,
    NONE
};

typedef enum BallType
{
    NORMAL, // Default ball
    HOT_POTATO, // Accelerates until it scores
    BLINK_BALL, // Teleports to a random location
    TABLE_FLIP, // Changes Sides of the player and AI
    CAMMO_BALL // Changes color struct of the ball to match the background
} BallType;

typedef enum AiType
{
    MANUAL, // Player controls the AI
    CONSTANT_SPEED, // Moves up and down at a constant speed
    MIRROR, // Mirrors the player's movement
    EASY, // Follows the ball but with a delay
    MEDIUM, // Follows the ball
    HARD  // Follows the ball and predicts the ball's position
} AiType;

typedef struct Ball
{
    Vector2 position; // Current position
    Vector2 direction = {1, 1}; // Direction of the ball
    Vector2 velocity = {0, 0}; //Next frame position
    Vector2 maxVelocity = {10, 10}; // Speed of the ball
    Vector2 acceleration = {0, 0}; //Unused 
    float radius;
    Color color;
    BallType type;
} Ball;

typedef struct Paddle
{
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Color color;
} Paddle;

typedef struct Score
{
    int player;
    int ai;
} Score;

typedef struct Game
{
    Ball ball;
    Paddle player;
    Paddle ai;
    Score score;
    Action playerAction;
    Action aiAction;
    AiType aiType;
} Game;

Vector2 NormalizeVector2(Vector2 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    if (length != 0) {
        v.x /= length;
        v.y /= length;
    }
    return v;
}

class Pong : public Scene
{
    public:
        Pong() {
            this->screenHeight = GetScreenHeight();
        };
        Pong(AiType aiMode)
        {
            game.aiType = aiMode;
        };

        virtual ~Pong() {};

    protected: // Can only be accessed through the Scene Manager via Update() per frame

        bool isBallCollidingWithPaddle(Ball ball, Paddle paddle) {
            return CheckCollisionCircleRec(ball.position, ball.radius, {paddle.position.x - paddle.size.x / 2, paddle.position.y - paddle.size.y / 2, paddle.size.x, paddle.size.y});
        }

        void init() override {
            // Initialize game variables

            // Ball initialization
            game.ball.position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
            
            game.ball.velocity = {500.0f, 500.0f};
            game.ball.radius = 10;
            game.ball.color = RED;

            game.player.position = {20, (float)GetScreenHeight() / 2};
            game.player.speed = {0, 10.0f};
            game.player.size = {20, 100};
            game.player.color = BLUE;

            game.ai.position = {(float)GetScreenWidth() - 40, (float)GetScreenHeight() / 2};
            game.ai.speed = {0, 5.0f};
            game.ai.size = {20, 100};
            game.ai.color = GREEN;

            game.score.player = 0;
            game.score.ai = 0;

            game.aiType = EASY;

            float angle = PI / 4;

            game.ball.direction = (Vector2){ cosf(angle), sinf(angle) };
            game.ball.direction = NormalizeVector2(game.ball.direction);

            #ifdef DEBUG
                TraceLog(LOG_INFO, "Game initialized");
                TraceLog(LOG_INFO, "Ball position: %f, %f", game.ball.position.x, game.ball.position.y);
                TraceLog(LOG_INFO, "Player position: %f, %f", game.player.position.x, game.player.position.y);
                TraceLog(LOG_INFO, "AI position: %f, %f", game.ai.position.x, game.ai.position.y);
                TraceLog(LOG_INFO, "AI Type: %d", game.aiType);

            #endif
        };

        void input() override {
        
            if(IsKeyDown(KEY_W))
            {
                #ifdef DEBUG
                    TraceLog(LOG_INFO, "Player Input: UP");
                #endif

                game.playerAction = UP;
            }
            else if(IsKeyDown(KEY_S))
            {
                #ifdef DEBUG
                    TraceLog(LOG_INFO, "Player Input: DOWN");
                #endif

                game.playerAction = DOWN;
            }
            else
            {
                #ifdef DEBUG_INCLUDE_IDLE // Debugging Idle Input: Unconfigured until step by step debugging is needed
                    TraceLog(LOG_INFO, "Player Input: NONE"); // Commented out to reduce log spam
                #endif

                game.playerAction = NONE;
            }
        }
        void update() override {

            float deltaTime = GetFrameTime();
            framesCounter++;


            #ifdef DEBUG_ITERATIONS // Debugging Iterations: Unconfigured until step by step debugging is needed
                // TraceLog(LOG_INFO, "Scene starts update loop");
            #endif

            if(this->screenHeight != GetScreenHeight()) {
                // TODO: Write for changing screen height and width mid-game
            };


            switch (game.playerAction)
            {
                if(game.aiType == MANUAL) 
                {
                    
                }
                case UP:
                    #ifdef DEBUG
                        TraceLog(LOG_INFO, "Player Update: UP");
                    #endif
                    if(game.player.position.y >= 0) // Prevents paddle from going off screen
                    {
                        #ifdef DEBUG
                            TraceLog(LOG_INFO, "Player position.y: %f", game.player.position.y);
                        #endif

                        game.player.position.y -= game.player.speed.y; // Moves paddle up top left is 0,0
                        break;
                    }
                    #ifdef DEBUG
                        TraceLog(LOG_INFO, "Player prevented from going off top of the screen");
                    #endif
                
                    break;
                    
                case DOWN:
                    #ifdef DEBUG
                        TraceLog(LOG_INFO, "Player Update: Down");
                    #endif
                    if(game.player.position.y + game.player.size.y <= GetScreenHeight()) // Prevents paddle from going off screen
                    {
                        #ifdef DEBUG
                            TraceLog(LOG_INFO, "Player position.y: %f", game.player.position.y);
                        #endif
                        game.player.position.y += game.player.speed.y; // Moves paddle down

                        break;
                    }
                    #ifdef DEBUG
                        TraceLog(LOG_INFO, "Player prevented from going off top of the screen");
                    #endif
                
                    break;

                default:
                    break;
            }

            // Ball movement
            Vector2 nextPosition = game.ball.position;
            Vector2 nextVelocity = game.ball.direction;

            if(game.ball.type == HOT_POTATO) // Requires factoring in acceleration in next position
            {
                game.ball.velocity.x += game.ball.acceleration.y * deltaTime;
                game.ball.velocity.y += game.ball.acceleration.y * deltaTime;
            }

            // Paddles are updated first but the ball's next position for the AI is calculated first
            game.ball.position.x += (game.ball.direction.x * game.ball.velocity.x * deltaTime);
            game.ball.position.y += (game.ball.direction.y * game.ball.velocity.y * deltaTime);

            #ifdef DEBUG_INCLUDE_NEXT_POSITION // Debugging Next Position: Unconfigured until step by step debugging is needed
                TraceLog(LOG_INFO, "Ball next position: %f, %f", nextPosition.x, nextPosition.y);
            #endif

            switch (game.aiType)
            {
                case MANUAL:
                    switch (game.aiAction)
                    {
                        case UP:
                            #ifdef DEBUG
                                TraceLog(LOG_INFO, "AI Update: UP");
                            #endif
                            game.ai.position.y -= game.ai.speed.y;
                            break;

                        case DOWN:
                            #ifdef DEBUG
                                TraceLog(LOG_INFO, "AI Update: DOWN");
                            #endif
                            game.ai.position.y += game.ai.speed.y;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                case CONSTANT_SPEED:
                    if(game.ball.position.y < game.ai.position.y)
                    {
                        game.ai.position.y -= game.ai.speed.y;
                    }
                    else if(game.ball.position.y > game.ai.position.y + game.ai.size.y)
                    {
                        game.ai.position.y += game.ai.speed.y;
                    }
                    break;
                case MIRROR:
                    game.ai.position.y = game.player.position.y;
                    break;
                case EASY:
                    if(game.ball.position.y < game.ai.position.y)
                    {
                        game.ai.position.y -= game.ai.speed.y;
                    }
                    else if(game.ball.position.y > game.ai.position.y + game.ai.size.y)
                    {
                        game.ai.position.y += game.ai.speed.y;
                    }
                    break;
                case MEDIUM:
                    if(game.ball.position.y < game.ai.position.y)
                    {
                        game.ai.position.y -= game.ai.speed.y;
                    }
                    else if(game.ball.position.y > game.ai.position.y + game.ai.size.y)
                    {
                        game.ai.position.y += game.ai.speed.y;
                    }
                    break;
                case HARD:
                    if(framesCounter % 5 == 0) // AI recalculates every 5 frames
                    if(game.ball.position.y < game.ai.position.y)
                    {
                        game.ai.position.y -= game.ai.speed.y;
                    }
                    else if(game.ball.position.y > game.ai.position.y + game.ai.size.y)
                    {
                        game.ai.position.y += game.ai.speed.y;
                    }
                    break;
                default:
                    break;
            }

            // Ball collision with walls
            if (game.ball.position.y - game.ball.radius <= 0) {
                game.ball.position.y = game.ball.radius;
                game.ball.direction.y *= -1;
            } else if (game.ball.position.y + game.ball.radius >= GetScreenHeight()) {
                game.ball.position.y = GetScreenHeight() - game.ball.radius;
                game.ball.direction.y *= -1;
            }

            if (game.ball.position.x - game.ball.radius <= 0) {
                // Player scores
                game.score.player++;

                float angle = PI / 4;

                game.ball.direction = (Vector2){ cosf(angle), sinf(angle) };
                game.ball.direction = NormalizeVector2(game.ball.direction);


                game.ball.position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
                game.ball.direction.x *= -1;
            } else if (game.ball.position.x + game.ball.radius >= GetScreenWidth()) {
                // AI scores
                game.score.ai++;

                float angle = PI / 4;

                game.ball.direction = (Vector2){ cosf(angle), sinf(angle) };
                game.ball.direction = NormalizeVector2(game.ball.direction);

                game.ball.position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
                game.ball.direction.x *= -1;
            }

            // Ball collision with paddles
            if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, (Rectangle){game.player.position.x, game.player.position.y, game.player.size.x, game.player.size.y})) {
                game.ball.position.x = game.player.position.x + game.player.size.x + game.ball.radius; // Adjust position
                game.ball.direction.x *= -1;

                // Reflect based on paddle hit position
                float offset = (game.ball.position.y - game.player.position.y) / game.player.size.y;
                game.ball.direction.y = offset - 0.5f; // Reflect angle adjustment
                game.ball.direction = NormalizeVector2(game.ball.direction);
            } else if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, (Rectangle){game.ai.position.x, game.ai.position.y, game.ai.size.x, game.ai.size.y})) {
                game.ball.position.x = game.ai.position.x - game.ball.radius; // Adjust position
                game.ball.direction.x *= -1;

                // Reflect based on paddle hit position
                float offset = (game.ball.position.y - game.ai.position.y) / game.ai.size.y;
                game.ball.direction.y = offset - 0.5f; // Reflect angle adjustment
                game.ball.direction = NormalizeVector2(game.ball.direction);
            }
        }

        void render() override {
            char scoreTextPlayer[20]; 
            char scoreTextAI[20];

            sprintf(scoreTextPlayer, "%i", game.score.player);
            sprintf(scoreTextAI, "%i", game.score.ai);

            DrawText(scoreTextPlayer, GetScreenWidth() / 2 - 50, 20, 20, BLACK);
            DrawText(scoreTextAI, GetScreenWidth() / 2 + 50, 20, 20, BLACK);

            DrawCircleV(game.ball.position, game.ball.radius, game.ball.color);
            DrawRectangleV(game.player.position, game.player.size, game.player.color);
            DrawRectangleV(game.ai.position, game.ai.size, game.ai.color);
        }

        void deInit() override { }

    private:
        Game game;
        bool isGameOver = false;
        bool isGamePaused = false;
        int screenHeight = 0;
        int screenWidth = 0;
        int framesCounter = 0; // Used so AI doesn't recalculate every frame (e.g. framesCounter % 5 == 0)
};