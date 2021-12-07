#include "raylib.h"

int main()
{
  // Game Variables
  const int windowHeight = 312;
  const int windowWidth = 400;

  //Create a Window
  InitWindow(windowWidth,windowHeight,"Dasher");


  //Character Properties---------------------------------------------------------
  Texture2D scarfy = LoadTexture("textures/scarfy.png");

  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;

  Vector2 scarfyPos;
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;
  //Character Properties---------------------------------------------------------


  //World Properity--------------------------------------------------------------
  int velocity{0};
  const int gravity{1'000};
  const int jumpValue{-600};
  bool isInAir{false};
  int frame{};
  const float updateTime{1.0 / 12.0};
  float runningTime{};
  //World Properity----------------------------------------------------------B----

  SetTargetFPS(60);


  while(!WindowShouldClose()) {

    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(WHITE);
    
    if(scarfyPos.y >= windowHeight - scarfyRec.height) {
      velocity = 0;
      isInAir = false;
    } else {
      //updating the velocity to the gravity for the PLAYER to go down
      velocity += gravity * dT;
      isInAir = true;
    }

    //creating a Delta Time that capture the FPS and use it to give players more frame in the game
    

    //Add Velocity on SPACE pressed
    if(IsKeyPressed(KEY_SPACE) && !isInAir) {
       velocity += jumpValue;
    }

    //Updating the velocity
    scarfyPos.y += velocity * dT;
    runningTime += dT;
    if(runningTime >= updateTime) {
      runningTime = 0.0;
      //updating the frame
      scarfyRec.x = frame * scarfyRec.width;
      frame++;
      if(frame > 5) {
        frame = 0;
      }
    }
    
    

    //Draw the character on the screen
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    EndDrawing();
  }
  UnloadTexture(scarfy);
  CloseWindow();
} 