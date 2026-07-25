#include "board_config.hpp"
#include <iostream>
#include <cmath>

BoardConfig::BoardConfig()
{
  board_height = 800.f;
  board_width = 800.f;
  // CENTER X AND Y OF THE WINDOW
  win_x = 800.f; 
  win_y = 450.f;
  vrect_wid = 10.f;
  vrect_hg = 640.f + 10.f;
  hrect_hg = vrect_wid;
  hrect_wid = vrect_hg;
  rect_diag_wid = std::sqrt((std::pow(vrect_hg-10.f, 2) + std::pow(vrect_hg-10.f, 2)));
  rect_diag_hg = 10.f;
  rad = 5.f;
  factor = 100.f;
}

void BoardConfig::makePoints(){
  // TOP LEFTEST POINT
  float pnt_st_x = win_x - board_height/2 + 80;
  float pnt_st_y = win_y - board_width/2 + 80;
  int temp_fac = factor;

  int pos = 1;
  for (int col=0; col<5; col++){ // FOR EACH COLUMN
    std::vector<std::pair<int, std::pair<float, float>>> b_row;
    for (int row=0; row<5; row++){ // FOR EACH ROW
      if (row <= 3) factor = -temp_fac;
      else factor = temp_fac;
      b_row.push_back({pos, {pnt_st_x + 160*col, pnt_st_y + 160*row}});
      // std::cout << pnt_st_x + 160*row << " " << pnt_st_y + 160*col << std::endl;
      if (pos == 1 || pos == 5 || pos == 21 || pos == 25)
        baagh_ini.push_back({pnt_st_x + 160*col, pnt_st_y + 160*row});
      pos++;
    }
    
    points.push_back(b_row);
  }

  // STARTING CENTER POINTS FOR THE ROUNDED RECTS (HORIZONTAL AND VERTICAL) TO BE PUT
  float vline_st_x = points[2][0].second.first;
  float vline_st_y = points[2][0].second.second;
  float hline_st_x = points[0][2].second.first;
  float hline_st_y = points[0][2].second.second;

  for (int turn=0; turn<2; turn++){ 
    std::vector<std::pair<float, float>> line;
    for (int ln=0; ln<5; ln++){ // FOR EACH LINE
      turn == 0 ? line.push_back({hline_st_x + 160*ln, hline_st_y}):line.push_back({vline_st_x, vline_st_y + 160*ln});
      // std::cout << hline_st_x + 160*ln << " " << hline_st_y + 160*ln << std::endl;
    }
    lines.push_back(line);
  }
}