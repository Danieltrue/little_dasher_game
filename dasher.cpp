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
  int windowDimension[2];
  windowDimension[0] = 612;
  windowDimension[1] = 312;

  //Create a Window
  InitWindow(windowDimension[0],windowDimension[1],"Dasher");


  //Character Properties---------------------------------------------------------
  Texture2D scarfy = LoadTexture("textures/scarfy.png");

  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowDimension[0] / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowDimension[1] - scarfyData.rec.height;
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

  const int length = 20;

  AnimData nebulea[length]{};

  for (int i = 0; i < length; i++) {
    // ... // ... // ...
    nebulea[i].rec.width = nebula.width / 8;
    nebulea[i].rec.height = nebula.height / 8;
    nebulea[i].rec.x = 0;
    nebulea[i].rec.y = 0;
    nebulea[i].pos.y = windowDimension[1] - nebulea[i].rec.height;
    nebulea[i].frame = 0;
    nebulea[i].updateTime = 1.0 / 12.0;
    nebulea[i].runningTime = 0.0;
  }
  for (int i = 0; i < length; i++) {
    nebulea[i].pos.x = windowDimension[0] - nebulea[i].rec.width + i * 900;
  }
  //Nebula Properties------------------------------------------------------------

  //Nebula animation data
  int NebulaVelocity{-300};

  SetTargetFPS(60);


  while(!WindowShouldClose()) {

    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(BLACK);
    
    if(scarfyData.pos.y >= windowDimension[1] - scarfyData.rec.height) {
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
    for (int i = 0; i < length; i++) {
      nebulea[i].pos.x += NebulaVelocity * dT;
    }
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

    for (int i = 0; i < length; i++) {
      //Nebula TWO
      nebulea[i].runningTime += dT;
      if(nebulea[i].runningTime > nebulea[i].updateTime) {
        nebulea[i].runningTime = 0.0;
        //updating the frame
        nebulea[i].rec.x = nebulea[i].frame * nebulea[i].rec.width;
        nebulea[i].frame++;
        if(nebulea[i].frame > 7) {
          nebulea[i].frame = 0;
        }
      }
    }
     

    //Draw the character on the screen
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos,WHITE);
    for (int i = 0; i < length; i++) {
      DrawTextureRec(nebula, nebulea[i].rec, nebulea[i].pos, WHITE);
    }

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
} 