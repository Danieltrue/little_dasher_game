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

  const int length = 3;

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

  float finishLine{nebulea[length - 1].pos.x};
  //Nebula Properties------------------------------------------------------------
  bool collision{};


  //Nebula animation data
  int NebulaVelocity{-300};

  Texture2D background = LoadTexture("textures/far-buildings.png");
  float bgX{};
  Texture2D midground = LoadTexture("textures/back-buildings.png");
  float mgX{};
  Texture2D foreground = LoadTexture("textures/foreground.png");
  float fgX{};

  SetTargetFPS(60);


  while(!WindowShouldClose()) {

    const float dT{GetFrameTime()};

    BeginDrawing();

    ClearBackground(BLACK);

    //update background moving position
    bgX -= 20 * dT;  
    if(bgX <= -background.width * 2 + 100) {
      bgX = 0;
    }
    mgX -= 60 * dT;
    if(mgX <= -midground.width * 2 + 100) {
      mgX = 0;
    }
    fgX -= 80 * dT;
    if(fgX <= -foreground.width * 2 + 100) {
      fgX = 0;
    }

    //Draw Background
    Vector2 bg1Pos{bgX,0.0};
    DrawTextureEx(background,bg1Pos,0.0,2.0,WHITE);
    Vector2 bg2Pos{bgX + background.width * 2,0.0};
    DrawTextureEx(background,bg2Pos,0.0,2.0,WHITE);
    //Draw Background
    Vector2 mg1Pos{mgX,0.0};
    DrawTextureEx(midground,mg1Pos,0.0,2.0,WHITE);
    Vector2 mg2Pos{mgX + midground.width * 2,0.0};
    DrawTextureEx(midground,mg2Pos,0.0,2.0,WHITE);
    //Draw Background
    Vector2 fg1Pos{fgX,0.0};
    DrawTextureEx(foreground,fg1Pos,0.0,2.0,WHITE);
    Vector2 fg2Pos{fgX + foreground.width * 2,0.0};
    DrawTextureEx(foreground,fg2Pos,0.0,2.0,WHITE);
    
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
    // update the finish line

    finishLine = NebulaVelocity * dT;
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
    for (AnimData nebula: nebulea) {
    float pad{20};
    Rectangle nebRec {
      nebula.pos.x + pad,
      nebula.pos.y + pad,
      nebula.rec.width - 2*pad,
      nebula.rec.height - 2*pad
    };

    Rectangle scarfyRec {
      scarfyData.pos.y,
      scarfyData.pos.x,
      scarfyData.rec.width,
      scarfyData.rec.height
    };

    if (CheckCollisionRecs(nebRec, scarfyRec)) {
      collision = true;
    }
  }

    //Draw the character on the screen
    if(collision) {
      DrawText("GAME OVER", windowDimension[0] / 2 - 50, windowDimension[1] / 2 - 50, 20, WHITE);
    } else {
      DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos,WHITE);
      for (int i = 0; i < length; i++) {
        DrawTextureRec(nebula, nebulea[i].rec, nebulea[i].pos, WHITE);
      }
    }
    

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  UnloadTexture(background);
  UnloadTexture(midground);
  UnloadTexture(foreground);
  CloseWindow();
} 