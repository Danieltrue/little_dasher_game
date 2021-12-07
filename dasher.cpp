#include "raylib.h"

struct AnimData 
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{
  // Game Variables
  const int windowHeight = 312;
  const int windowWidth = 700;

  //Create a Window
  InitWindow(windowWidth,windowHeight,"Dasher");


  //Character Properties---------------------------------------------------------
  Texture2D scarfy = LoadTexture("textures/scarfy.png");

  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowHeight - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.runningTime = 0.0;
  scarfyData.updateTime = 1.0 / 12.0;
  //Character Properties---------------------------------------------------------


  //World Properity--------------------------------------------------------------
  int velocity{0};
  const int gravity{1'000};
  const int jumpValue{-600};
  bool isInAir{false};
  //World Properity--------------------------------------------------------------

  //Nebula Properties------------------------------------------------------------
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  // ... // ... // ...
  AnimData  nebulaData;
  AnimData  nebula2Data;
  // ... // ... // ...
  nebulaData.rec.width = nebula.width / 8;
  nebulaData.rec.height = nebula.height / 8;
  nebulaData.rec.x = 0;
  nebulaData.rec.y = 0;
  nebulaData.pos.x = windowWidth - nebulaData.rec.width;
  nebulaData.pos.y = windowHeight - nebulaData.rec.height;
  nebulaData.frame = 0;
  nebulaData.updateTime = 1.0 / 12.0;
  nebulaData.runningTime = 0.0;

  nebula2Data.rec.width = nebula.width / 8;
  nebula2Data.rec.height = nebula.height / 8;
  nebula2Data.rec.x = 0;
  nebula2Data.rec.y = 0;
  nebula2Data.pos.x = windowWidth + 400;
  nebula2Data.pos.y = windowHeight - nebula2Data.rec.height;
  nebula2Data.frame = 0;
  nebula2Data.updateTime = 1.0 / 16.0;
  nebula2Data.runningTime = 0.0;
  //Nebula Properties------------------------------------------------------------

  //Nebula animation data
  int NebulaVelocity{-600};

  SetTargetFPS(60);


  while(!WindowShouldClose()) {

    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(BLACK);
    
    if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height) {
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

    //upadting nebula velocity to move to the left
    nebulaData.pos.x += NebulaVelocity * dT;
    nebula2Data.pos.x += NebulaVelocity * dT;
    //Updating the velocity
    scarfyData.pos.y += velocity * dT;

  //checking if the scarfy is in air and stoping his animation if true
    if(!isInAir) {
      scarfyData.runningTime += dT;
      if(scarfyData.runningTime >= scarfyData.updateTime) {
        scarfyData.runningTime = 0.0;
        //updating the frame
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if(scarfyData.frame > 5) {
          scarfyData.frame = 0;
        }
      }

    }

  
    //Nebula ONE
    nebulaData.runningTime += dT;
    if(nebulaData.runningTime > nebulaData.updateTime) {
      nebulaData.runningTime = 0.0;
      //updating the frame
      nebulaData.rec.x = nebulaData.frame * nebulaData.rec.width;
      nebulaData.frame++;
      if(nebulaData.frame > 7) {
        nebulaData.frame = 0;
      }
    }

    //Nebula TWO
    nebula2Data.runningTime += dT;
    if(nebula2Data.runningTime > nebula2Data.updateTime) {
      nebula2Data.runningTime = 0.0;
      //updating the frame
      nebula2Data.rec.x = nebula2Data.frame * nebula2Data.rec.width;
      nebula2Data.frame++;
      if(nebula2Data.frame > 7) {
        nebula2Data.frame = 0;
      }
    }
     

    //Draw the character on the screen
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos,WHITE);
    DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
    DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos,RED);

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
} 