# ansi-term

A small C++17 header/source library for building ANSI escape sequences without
writing the codes by hand. Chain color and style calls on a `Print` object and
send the result to any `std::ostream`.

## Features

- Foreground colors: `black red green yellow blue magenta cyan white`
- Background colors: `on_black on_red on_green on_yellow on_blue on_magenta on_cyan on_white`
- Styles: `bold faint italic underline strike`
- `reset()` clears every color and style on the object
- `apply(int)` sets a raw SGR code (30-39 foreground, 40-49 background, styles)
- `str()`, `print()`, `println()`, and `operator<<`

## Usage

```cpp
#include "ansi.h"

int main()
{
  Print("error: something failed\n").red().bold().print();
  Print("warning\n").yellow().on_black().println();

  Print msg("done\n");
  msg.green().italic();
  std::cout << msg;
}
```

## Building

Compile `ansi.cpp` together with your own sources (c++17 or greater is required):

```sh
g++ -std=c++20 -Wall -Wextra main.cpp ansi.cpp -o app
```

Or include it as an object in your build system of choice. The library itself
has no dependencies beyond the C++ standard library.

## Notes

- The output always ends the styled text with `\033[0m`, so styles do not leak
  into surrounding text.
- `reset()` affects only the `Print` instance, not previously printed output.

## License

MIT
