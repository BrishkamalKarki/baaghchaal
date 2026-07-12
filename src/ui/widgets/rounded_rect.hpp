#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include <vector>

class RoundedRect{
private:
  int width, height;
  int corn_pnts = 0; // POINTS PER CORNER
  int flagx, flagy;
  float deg, PI;

public:
  RoundedRect(){}
  RoundedRect(float w, float h) : width(static_cast<int>(w)), height(static_cast<int>(h)){
    corn_pnts = static_cast<int>(((width>height?width:height)%100)+1)*7;
  }
  
  std::vector<SDL_Vertex> rounded_rect;
  std::vector<int> indices;
  void makeRoundRect(float x, float y, float rad, SDL_Color* col){
    rounded_rect.clear();
    flagx = 1;
    flagy = 1;
    deg = 0.f;
    int corner = 0, ttlp = 0;
    PI = 3.14159265358979323846f;

    SDL_Vertex center;
    center.position.x = x;
    center.position.y = y;
    center.color.a = col->a;
    center.color.b = col->b;
    center.color.r = col->r;
    center.color.g = col->g;
    // THIS IS THE CENTER OF THE RECT THAT WILL MAKE THE TRIANGLE WITH EACH PAIR POINT USED TO MAKE THE ROUNDED RECT
    rounded_rect.push_back(center); 
    
    for (int i=0; i<corn_pnts*4; i++){
      // MAKING EACH OF THE CORNER POINTS
      SDL_Vertex rr;
      rr.position.x = x + flagx * (width/2.f - rad) + rad * std::cos(deg * PI / 180.f);
      rr.position.y = y + flagy * (height/2.f - rad) + rad * std::sin(deg * PI / 180.f);
      rr.color.a = col->a;
      rr.color.b = col->b;
      rr.color.r = col->r;
      rr.color.g = col->g;
      ttlp++; // THIS IS TOTAL NUMBER OF POINTS
      if (ttlp % corn_pnts == 0) corner++;
      if (corner == 1){
        flagx = -1; flagy = 1;  
      }
      else if (corner == 2){
        flagx = -1; flagy = -1;
      }
      else if (corner == 3){
        flagx = 1; flagy = -1; 
      }
      if (ttlp%corn_pnts != 0) deg += 360.f/((corn_pnts-2)*4+4); 
      rounded_rect.push_back(rr); 

    }
    //  ADDING THE INDICES FOR EACH OF THE TRIANGLE TO BE MADE I.E CENTER P1 P2 MAKES ONE TRIANGLE, CENTER P2 P3 MAKES ANOTHOER AND SO ON ......
    for (int i=0; i<corn_pnts*4; i++){
      indices.push_back(0);
      indices.push_back(i+1);
      if (i == (corn_pnts*4)-1) indices.push_back(1);
      else indices.push_back(i+2);
    }
  }
};
