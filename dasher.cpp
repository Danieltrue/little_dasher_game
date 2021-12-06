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
  const int jumpValue{10};
  //World Properity--------------------------------------------------------------

  while(!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(WHITE);
    
    scarfyPos.y += velocity;

    //Add Velocity on SPACE pressed
    if(IsKeyPressed(KEY_SPACE)) {
       velocity -= jumpValue;
    }

    //Draw the character on the screen
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    EndDrawing();
  }
  CloseWindow();
} 