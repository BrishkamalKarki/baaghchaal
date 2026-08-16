#pragma once
#include <vector>
#include <string>

class Engine;

class BoardEvaluator{
  public:
    int getValidMovesAt(int pos, std::string where = "none"); // GIVES THE VALID MOVES TO MOVE AROUND A POSITION
    std::string checkWinner();
    int checkBaaghTrapped(bool update_real_state = false);
    Engine* engine = nullptr;
    
    std::vector<int> valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
    std::vector<int> bgh_valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
    std::vector<int> temp_valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
    std::vector<std::pair<int, int>> temp_edible_valid_moves; 
    std::vector<int> virtual_valid_moves; 
    std::vector<std::pair<int, int>> edible_valid_moves; // STORES THE VALID TO EAT A GOAT 
    BoardEvaluator(Engine* eng);
}; 

