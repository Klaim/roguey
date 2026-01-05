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
  ftxui::Element stats_state::render(game& g)
  {
    return g.renderer.render_stats(g.reg, g.reg.player_id, g.reg.player_name, g.log);
  }

  bool stats_state::on_event(game& g, ftxui::Event event)
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
