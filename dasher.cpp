#include "raylib.h"

int main()
{
  //Assign the window variable
  const int windowWidth{512};
  const int windowHeight{380};

  //Rectangle Dimensions
  const int width{50};
  const int height{49};
  int posY{windowHeight - height};
  const int posX{300};
  //Velocity // Gravity // Acceleration
  int velocity{0};
  const int jumpValue{-10};
  bool isInAir{false};
  //Acceleration due to gravity
  const int gravity{1};
  //Create the window
  InitWindow(windowWidth,windowHeight,"Dasher");

  //Setting the game FPS
  SetTargetFPS(60);
  while(!WindowShouldClose()) {
    // ...
    BeginDrawing();
    // Clearing the white background
    ClearBackground(WHITE);
   
    //Drawing the rectangle
    DrawRectangle(windowWidth/2 , posY, width, height, BLUE);
    

    //Ground Height
    if(posY >= windowHeight - height) {
      velocity = 0;
      isInAir = false;
    } else {
      //updating gravity
      velocity += gravity;
      isInAir = true;
    }

   
      //Make the Ke
    if(IsKeyPressed(KEY_SPACE) && !isInAir) {
      velocity += jumpValue;
    }

   //Updating the velocity for every frame per sec
    posY += velocity;
    //End the Canvas Frame Draw
    EndDrawing();
  }
  //This is a raylib function that closes the window correctly;
  CloseWindow();
}