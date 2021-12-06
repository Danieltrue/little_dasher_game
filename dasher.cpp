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
  int velocity{0};
  //Create the window
  InitWindow(windowWidth,windowHeight,"Dasher");

  //Setting the game FPS
  SetTargetFPS(60);
  while(!WindowShouldClose()) {
    // ...
    BeginDrawing();

    ClearBackground(WHITE);
   
    //Drawing the rectangle
    DrawRectangle(windowWidth/2 , posY, width, height, BLUE);
    //Make the Ke
    if(IsKeyPressed(KEY_SPACE)) {
      velocity -= 10;
    }
   //Updating the velocity for every frame per sec
    posY += velocity;
    //End the Canvas Frame Draw
    EndDrawing();
  }
  //This is a raylib function that closes the window correctly;
  CloseWindow();
}