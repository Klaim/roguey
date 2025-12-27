--==================================================================================================
--  Roguey
--  Copyright : Joel FALCOU
--  SPDX-License-Identifier: MIT
--==================================================================================================

game_colors = {
--  {FG,BG,BOLD, "Name" }
    { 7, 0, false, "Default" }
  , { 8, 0, true, "Hidden" }
  , { 6, 0, false, "Player" }
  , { 1, 0, false, "Orc" }
  , { 7, 0, false, "Wall" }
  , { 4, 0, true , "Spell" }
  , { 3, 0, true , "Gold" }
  , { 5, 0, false, "Boss" }
  , { 0, 0, false, "Hidden" }
  , { 1, 0, true , "HP_Potion" }
  , { 5, 0, false, "STR_Potion" }
  , { 2, 0, false, "Forest" }
  , { 3, 2, true , "Slime" }
}

help_text = [[
  CONTROLS
  --------
  Arrow Keys : Move / Attack
  i          : Open Inventory
  c          : Character Stats
  f          : Cast Fireball
  ESC        : Open Help / Close Menus
  q          : Quit Game
]]

function get_start_config()
    return {
        start_level = "scripts/levels/forest.lua",
        start_depth = 1,
        initial_log_message = "Welcome adventurer !",
        window_width = 100,
        window_height = 48
    }
end
