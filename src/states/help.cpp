//==================================================================================================
/*
  Roguey
  Copyright : Joel FALCOU
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
module roguey.states;

import roguey.game;

namespace roguey
{
  ftxui::Element help_state::render(game& g)
  {
    std::string txt = g.scripts.lua["help_text"].get_or<std::string>("No help text defined.");
    return g.renderer.render_help(g.log, txt);
  }

  bool help_state::on_event(game& g, ftxui::Event event)
  {
    if (g.menu_lock > 0) return true;
    if (event == ftxui::Event::Escape || event == ftxui::Event::Character('c'))
    {
      g.set_state(dungeon_state{});
      return true;
    }
    return true;
  }
}
