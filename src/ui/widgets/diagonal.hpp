// #pragma once
// #include <SDL3/SDL.h>
// #include <cmath>
// #include <vector>

// class Diagonal{
// private:
//   int width, height;
//   float ang, PI;
//   int flag1, flag2;

// public:
//   Diagonal(){}
//   Diagonal(float w, float h) : width(static_cast<int>(w)), height(static_cast<int>(h)){}
  
//   std::vector<SDL_Vertex> diags;
//   std::vector<int> indices;
//   void makeDiagonal(float x, float y, float deg, SDL_Color* col){
//     diags.clear();
//     float PI = 3.1415f;
//     ang = deg * PI / 180.f;

//     SDL_Vertex center;
//     center.position.x = x;
//     center.position.y = y;
//     center.color.a = col->a;
//     center.color.b = col->b;
//     center.color.r = col->r;
//     center.color.g = col->g;
//     // THIS IS THE CENTER OF THE RECT THAT WILL MAKE THE TRIANGLE WITH EACH PAIR POINT USED TO MAKE THE ROUNDED RECT
//     diags.push_back(center); 

//     flag1 = (deg>90.f)?1:-1;
//     flag2 = (deg<90.f)?-1:1;

//     std::vector<std::pair<float, float>> pre_corners;
//     pre_corners.push_back(std::make_pair(x-height/2, y-width/2));
//     pre_corners.push_back(std::make_pair(x+height/2, y-width/2));
//     pre_corners.push_back(std::make_pair(x+height/2, y+width/2));
//     pre_corners.push_back(std::make_pair(x-height/2, y+width/2));

//     std::vector<std::pair<float, float>> corners;
//     for (auto& [corn_x, corn_y] : pre_corners){
//       corners.push_back({x+(corn_x-x)*std::cos(ang)-(corn_y-y)*std::sin(ang), y+(corn_y-y)*std::sin(ang)+(corn_y-y)*std::cos(ang)});
//       SDL_
//       center.position.x = x;
//       center.position.y = y;
//       center.color.a = col->a;
//       center.color.b = col->b;
//       center.color.r = col->r;
//       center.color.g = col->g;
//     }
    
//     //  ADDING THE INDICES FOR EACH OF THE TRIANGLE TO BE MADE I.E CENTER P1 P2 MAKES ONE TRIANGLE, CENTER P2 P3 MAKES ANOTHOER AND SO ON ......
//     for (int i=0; i<4; i++){  
//       indices.push_back(0);
//       indices.push_back(i+1);
//       if (i == (4)-1) indices.push_back(1);
//       else indices.push_back(i+2);
//     }
//   }
// };
