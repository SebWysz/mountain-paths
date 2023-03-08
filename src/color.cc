#include "color.hpp"
#include <stdexcept>
#include <string>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (Color::kColorValueMin > r || Color::kColorValueMax < r) {
    throw std::runtime_error("Invalid Red color: " + std::to_string(r));
  }
  if (Color::kColorValueMin > g || Color::kColorValueMax < g) {
    throw std::runtime_error("Invalid Green color");
  }
  if (Color::kColorValueMin > b || Color::kColorValueMax < b) {
    throw std::runtime_error("Invalid Blue color");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}