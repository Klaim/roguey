--==================================================================================================
--  Roguey
--  Copyright : Joel FALCOU
--  SPDX-License-Identifier: MIT
--==================================================================================================

function get_init_stats()
    return { archetype = "Rogue", hp = 90, mp = 15, damage = 10, delay = 2 }
end

function level_up(stats)
    return {
        hp = stats.hp + 15,
        mp = stats.mp + 5,
        damage = stats.damage + 3,
        delay = stats.delay
    }
end