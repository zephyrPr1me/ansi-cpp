#include "ansi.h"
#include <iostream>
#include <string>
Print::Print(std::string_view text) : text_(text) {}

Print &Print::apply(int code)
{
  if (code >= static_cast<int>(Foreground::BLACK) &&
      code <= static_cast<int>(Foreground::DEFAULT))
    fg_ = static_cast<Foreground>(code);
  else if (code >= static_cast<int>(Background::BLACK) &&
           code <= static_cast<int>(Background::DEFAULT))
    bg_ = static_cast<Background>(code);
  else
    switch (code)
    {
    case static_cast<int>(Style::RESET):
      return reset();
    case static_cast<int>(Style::BOLD):
      bold_ = true;
      break;
    case static_cast<int>(Style::FAINT):
      faint_ = true;
      break;
    case static_cast<int>(Style::ITALIC):
      italic_ = true;
      break;
    case static_cast<int>(Style::UNDERLINE):
      underline_ = true;
      break;
    case static_cast<int>(Style::STRIKE):
      strike_ = true;
      break;
    }
  return *this;
}

Print &Print::black()
{
  fg_ = Foreground::BLACK;
  return *this;
}
Print &Print::red()
{
  fg_ = Foreground::RED;
  return *this;
}
Print &Print::green()
{
  fg_ = Foreground::GREEN;
  return *this;
}
Print &Print::yellow()
{
  fg_ = Foreground::YELLOW;
  return *this;
}
Print &Print::blue()
{
  fg_ = Foreground::BLUE;
  return *this;
}
Print &Print::magenta()
{
  fg_ = Foreground::MAGENTA;
  return *this;
}
Print &Print::cyan()
{
  fg_ = Foreground::CYAN;
  return *this;
}
Print &Print::white()
{
  fg_ = Foreground::WHITE;
  return *this;
}

Print &Print::on_black()
{
  bg_ = Background::BLACK;
  return *this;
}
Print &Print::on_red()
{
  bg_ = Background::RED;
  return *this;
}
Print &Print::on_green()
{
  bg_ = Background::GREEN;
  return *this;
}
Print &Print::on_yellow()
{
  bg_ = Background::YELLOW;
  return *this;
}
Print &Print::on_blue()
{
  bg_ = Background::BLUE;
  return *this;
}
Print &Print::on_magenta()
{
  bg_ = Background::MAGENTA;
  return *this;
}
Print &Print::on_cyan()
{
  bg_ = Background::CYAN;
  return *this;
}
Print &Print::on_white()
{
  bg_ = Background::WHITE;
  return *this;
}

Print &Print::bold()
{
  bold_ = true;
  return *this;
}
Print &Print::faint()
{
  faint_ = true;
  return *this;
}
Print &Print::italic()
{
  italic_ = true;
  return *this;
}
Print &Print::underline()
{
  underline_ = true;
  return *this;
}
Print &Print::strike()
{
  strike_ = true;
  return *this;
}

Print &Print::reset()
{
  fg_ = Foreground::NONE;
  bg_ = Background::NONE;
  bold_ = faint_ = italic_ = underline_ = strike_ = false;
  return *this;
}

std::string Print::str() const
{
  std::string codes;
  auto add = [&](int c)
  { codes += std::to_string(c) + ";"; };

  if (bold_)
    add(static_cast<int>(Style::BOLD));
  if (faint_)
    add(static_cast<int>(Style::FAINT));
  if (italic_)
    add(static_cast<int>(Style::ITALIC));
  if (underline_)
    add(static_cast<int>(Style::UNDERLINE));
  if (strike_)
    add(static_cast<int>(Style::STRIKE));
  if (bg_ != Background::NONE)
    add(static_cast<int>(bg_));
  if (fg_ != Foreground::NONE)
    add(static_cast<int>(fg_));

  if (codes.empty())
    return text_;

  codes.back() = 'm'; // replace the trailing ';' with 'm'
  return "\033[" + codes + text_ + "\033[0m";
}

void Print::print() const { std::cout << str(); }
void Print::println() const { std::cout << str() << '\n'; }

std::ostream &operator<<(std::ostream &os, const Print &p)
{
  return os << p.str();
}
