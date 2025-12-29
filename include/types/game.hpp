//==================================================================================================
/*
  Roguey
  Copyright : Joel FALCOU
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace roguey
{
  enum class game_state
  {
    Dungeon,
    Inventory,
    Stats,
    Help,
    GameOver,
    Victory,
    Animating
  };

  struct SpeedThreshold
  {
    int limit;
    std::string label;
    std::string color;
  };

}
