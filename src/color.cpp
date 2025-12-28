//==================================================================================================
/*
  Roguey
  Copyright : Joel FALCOU
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <ftxui/screen/color.hpp>

#include <cstdint>
#include <ftxui/dom/elements.hpp>
#include <sstream>
#include <string>

namespace roguey
{
  std::string hex_to_ansi(std::string const& hex)
  {
    if (hex.size() < 7 || hex[0] != '#') return "\033[37m"; // Fallback to white

    int r = std::stoi(hex.substr(1, 2), nullptr, 16);
    int g = std::stoi(hex.substr(3, 2), nullptr, 16);
    int b = std::stoi(hex.substr(5, 2), nullptr, 16);
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
  }

  ftxui::Color parse_hex_color(std::string const& hex)
  {
    if (hex.size() < 7) return ftxui::Color::White;
    int r = std::stoi(hex.substr(1, 2), nullptr, 16);
    int g = std::stoi(hex.substr(3, 2), nullptr, 16);
    int b = std::stoi(hex.substr(5, 2), nullptr, 16);
    return ftxui::Color::RGB(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
  }
}
