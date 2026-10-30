#ifndef ANSI_H
#define ANSI_H

#include <ostream>
#include <string>
#include <string_view>

enum Foreground
{
  NONE = 0,
  BLACK = 30,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  DEFAULT = 39
};
enum class Background
{
  NONE = 0,
  BLACK = 40,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  DEFAULT = 49,
};
enum class Style
{
  RESET = 0,
  BOLD = 1,
  FAINT = 2,
  ITALIC = 3,
  UNDERLINE = 4,
  BLINK = 5,
  REVERSE = 7,
  STRIKE = 9,
};

class Print
{
public:
  Print(std::string_view text);
  Print &apply(int code);
  Print &black();
  Print &red();
  Print &green();
  Print &yellow();
  Print &blue();
  Print &magenta();
  Print &cyan();
  Print &white();

  Print &on_black();
  Print &on_red();
  Print &on_green();
  Print &on_yellow();
  Print &on_blue();
  Print &on_magenta();
  Print &on_cyan();
  Print &on_white();

  Print &bold();
  Print &reset();
  Print &faint();
  Print &italic();
  Print &strike();
  Print &underline();

  std::string str() const;
  void print() const;
  void println() const;
  friend std::ostream &operator<<(std::ostream &os, const Print &p);

private:
  std::string text_;

  Foreground fg_ = Foreground::NONE;
  Background bg_ = Background::NONE;

  bool bold_ = false;
  bool faint_ = false;
  bool italic_ = false;
  bool underline_ = false;
  bool strike_ = false;
};

#endif
