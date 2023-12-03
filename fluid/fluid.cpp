#include "../sim/parser.hpp"
#include "../sim/progargs.hpp"

#include <iostream>
#include <span>

int main(int argc, char **argv) {
  // arguments
  std::span const args_view{argv, static_cast<std::size_t>(argc)};
  std::vector<std::string> const arguments{args_view.begin() + 1,
                                           args_view.end()};

  if (progargs(argc, arguments) == 0) {
    parser(arguments);
  }

  return 0;
}
