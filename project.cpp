/*
Project:-Pong Game
made with an external library
*/
#include<iostream>
#include<raylib.h>
using namespace std;
//in order to pause game
bool pause = false;
//This will be holding score of players 
  int L_score, R_score = 0;//Let P1 be Left and P2 be right
//this will decide our screen resolution
  const int Width = 800;
  const int Height = 600;
//this will be our circle shape
  const float ball_radius = 10.0;
  float ball_posx = 1.0*(Width/2);
  float ball_posy = 1.0*(Height/2);
  float speed_x = 5;
  float speed_y = 5;
//now for rackets
  const float racket_width = 10.0; //as each racket shall have same width
  const float racket_height = 120.0; //as each racket shall have same height
//left racket
  const float left_racket_posx = 30.0;
  //please note that the racket does not move in x axis thus position in x-axis the x cordinate is constant and in y will be variable as it moves up and down 
  float left_racket_posy = Height/2.0;
  float Lracket_speed = 10.0;//since the racket moves up and down so its speed will be in y axis only
//right racket
  const float right_racket_posx = Width-50.0;
  float right_racket_posy = Height/2.0;
  float Rracket_speed = 10.0; //same logic as in line 24
    
    void DRAW()//new window
    {
    InitWindow (Width,Height,"RESULT");
    SetTargetFPS(60);
    while(WindowShouldClose() == false)
    {
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("IT'S A DRAW :|\n", 70+Width/4, Height/2, 30, WHITE);
      EndDrawing();
    }
    CloseWindow();
    }
    
    void L_WIN()
    { //new window
    InitWindow (Width,Height,"RESULT");
    SetTargetFPS(60);//this will set frames per seconds
    while(WindowShouldClose() == false)//this is a built-in function of raylib.h(can only be terminated when press Esc)
    {
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("Player 1 WINS :D\n", 70+Width/4, Height/2, 30, WHITE);
      DrawText("(Better Luck Next Time Player 2)", Width/4, Height/1.75, 25, WHITE); 
      EndDrawing();
    }
    CloseWindow();
    }
    
    void R_WIN()
    {
    InitWindow (Width,Height,"RESULT");
    SetTargetFPS(60);//this will set frames per seconds
    while(WindowShouldClose() == false)//this is a built-in function of raylib.h(can only be terminated when press Esc)
    {//new window
      BeginDrawing();
      ClearBackground(BLACK);
      DrawText("Player 2 WINS :D\n", 70+Width/4, 15+Height/2, 30, WHITE);
      DrawText("(Better Luck Next Time Player 1)", Width/4, Height/1.75, 25, WHITE);
      EndDrawing();
    }
    CloseWindow();
    }
   
   //this will see the score related scenario
  void Score() 
  { 
    if(ball_posx + ball_radius > Width)//if ball reaches right end of screen 
      {//increment the score
        L_score++;
        //reset position of ball
        speed_x=5;
        ball_posx = GetScreenWidth()/2.0;
        ball_posy = GetScreenHeight()/2.0;
        //make it move randomly
        //this will be giving random direction to value
        int random_direction[] = {-1, 1};
        speed_x*= random_direction[GetRandomValue(0, 1)];
        speed_y*= random_direction[GetRandomValue(0, 1)];
      }
//if ball reaches left end of screen
    if (ball_posx - ball_radius < 0) 
      {//increment score
        R_score++;
        //reset position of ball
        speed_x=5;
        ball_posx = GetScreenWidth()/2;
        ball_posy = GetScreenHeight()/2;
        //move it in random direction
        //this will be giving random direction to value
        int random_direction[] = {-1, 1};
        speed_x*= random_direction[GetRandomValue(0, 1)];
        speed_y*= random_direction[GetRandomValue(0, 1)];
      }
    }

//Ball Collision Detection
void DetectCollision()
{//Please note here CheckCollision is a built-in fn of Raylib Library
  if(CheckCollisionCircleRec(Vector2{ball_posx, ball_posy}, ball_radius, {left_racket_posx, left_racket_posy, racket_width, racket_height})) 
        if(speed_x<0)
            speed_x*= -1.005;
  if(CheckCollisionCircleRec(Vector2{ball_posx, ball_posy}, ball_radius,{right_racket_posx, right_racket_posy, racket_width, racket_height}))
        if(speed_x>0)
            speed_x *= -1.005;
}

//this fn to move rackets

void Rackets_Movement()
{ //in order to move left racket up
  if(IsKeyDown(KEY_W))
  left_racket_posy-=Lracket_speed;
  if(IsKeyDown(KEY_S))//in order to make left racket move down
  left_racket_posy+=Lracket_speed;
  if(IsKeyDown(KEY_UP))
  right_racket_posy-=Rracket_speed;//in order to make right racket move up
  if(IsKeyDown(KEY_DOWN))
  right_racket_posy+=Rracket_speed;//in order to make right racket move down
  
}

void Rackets_Endpoints()
{//in order to make the rackets stay on the screen following conds were made
  if(left_racket_posy<0)
  left_racket_posy=0;
  if(left_racket_posy>=Height)
  left_racket_posy=GetScreenHeight()-Height;
  if(right_racket_posy<0)
  right_racket_posy=0;
  if(right_racket_posy>=Height)
  right_racket_posy=GetScreenHeight()-Height;
}


//this is the function that will move the ball

void Ball_Movement()
 {
  //accelerate the ball
  ball_posx+= speed_x;
  ball_posy+= speed_y;
  if(ball_posy - ball_radius < 0 || ball_posy + ball_radius > GetScreenHeight())//this Condition shall detect collisions wrt Height Up and Down
   speed_y*= -1.0000;//make ball move in opp dir.
  if(ball_posx - ball_radius < 0 || ball_posx + ball_radius > GetScreenWidth())//this condition shall detect collisions wrt Width Left or Right
   speed_x*= -1.0000;//make ball move in opp dir.
 }

//this fn to draw the shapes of the objects
 void Draw_Fn()
 {
  DrawCircle (ball_posx, ball_posy, ball_radius, WHITE);//drawing a ball
  DrawRectangle (right_racket_posx, right_racket_posy, racket_width, racket_height, WHITE);//drawing rackets
  DrawRectangle (left_racket_posx, left_racket_posy, racket_width, racket_height, WHITE);
  DrawLine (Width/2,0,Width/2,Height,WHITE);//drawing a line at the middle
  DrawText( TextFormat("%i", L_score), Width / 4 - 20, 10, 60, WHITE);//displaying scores
  DrawText( TextFormat("%i", R_score), 3 * Width / 4 - 20, 10, 60, WHITE);
 }

int main(void)
 {  
    InitWindow (Width,Height,"PONG By Hmmmmm");//function used to create a window
    SetTargetFPS(60);//this will set frames per seconds
    while(WindowShouldClose() == false)//this is a built-in function of raylib.h(can only be terminated when press Esc)
    {
      if(IsKeyPressed(KEY_SPACE))//this condition will be quite handy in changing the game state
      pause= !pause;//on first press the pause becomes true
      BeginDrawing();
      ClearBackground(BLACK);
       Draw_Fn();
      if(pause == false)//if pause is not pressed
      {
      Ball_Movement();
      Rackets_Movement();
      DetectCollision();
      Rackets_Endpoints();
      Score();
      }
      if(pause)//if pause is pressed 
      DrawText("Paused",-50+Width/2,Height/2,30,WHITE);
      if(L_score==10||R_score==10)//if score reaches max limit
      break;
      EndDrawing();
    }
      CloseWindow();
      //this will be an interesting feature I hope so.
      if(L_score==10||L_score>R_score)//in case if someone quites while one player had a lead 
      {
        L_WIN();
      }
      if(R_score==10||R_score>L_score)
      {
        R_WIN();
      }
      if(L_score==R_score)//in case in someone quites and both players have same score
      {
        DRAW();
      }
 }
