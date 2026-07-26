#include <unordered_set>
#include "game_state.hpp"

GameState::GameState(){
  std::unordered_set<int> baagh_pos = {1, 5, 21, 25};  
  for (int pos = 1; pos <= 25; pos++){
    if (baagh_pos.find(pos) != baagh_pos.end()) board_state.push_back({pos, 'T'});
    else board_state.push_back({pos, ' '});
  }
}