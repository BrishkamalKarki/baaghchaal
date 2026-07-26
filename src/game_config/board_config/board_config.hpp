#pragma once
#include <vector>

class BoardConfig
{
private:
public:
  BoardConfig();
  // CONFIGURATIONS HERE ARE FOR THE INITIAL DEFAULT SCREEN SIZE - 1600 x 900
  float board_width, board_height;
  float win_x, win_y; // FOR EACH INTERSECTION POINTS
  float hrect_hg, vrect_hg, hrect_wid, vrect_wid, rad, rect_x, rect_y, rect_diag_wid, rect_diag_hg;  // FOR THE LINES - ROUNDED RECTS
  float factor;
  std::vector<std::vector<std::pair<int, std::pair<float, float>>>> points;
  std::vector<std::vector<std::pair<float, float>>> lines;
  std::vector<std::pair<int, int>> points_info; // STORING WHICH ROW AND THE COLUMN THE POINTS LIES IN
  // THIS STORES THE COORDINATES OF EACH POINTS (25 POINTS) FOR THE BOARD
  void makePoints();
};