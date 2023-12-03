#include "progargs.hpp"

bool isNumeric(const std::string &str) {
  // Check if the string is empty or contains only whitespace
  if (str.empty() || std::all_of(str.begin(), str.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
      })) {
    return false;
  }

  // Check if the string represents a numeric value (positive or negative)
  auto itr = str.begin();
  if (*itr == '-' || *itr == '+') {
    ++itr; // Skip the optional sign
  }

  return std::all_of(itr, str.end(), [](char c) {
    return std::isdigit(static_cast<unsigned char>(c));
  });
}

int progargs(int argc, std::vector<std::string> arguments) {
  if (argc != 4) {
    std::cerr << "Error: Invalid number of arguments: " << argc - 1 << ".\n";
    return -1;
  }
  if (!isNumeric(arguments[0])) {
    std::cout << "Error: Time steps must be numeric." << '\n';
    return -1;
  }
  if (std::stoi(arguments[0]) < 0) {
    std::cout << "Error: Invalid number of time steps." << '\n';
    return -2;
  }
  auto checkFile = [](const char *filename, const char *mode, int errorCode) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error: Cannot open " << filename << " for " << mode << "\n";
      return errorCode;
    }
    return 0;
  };
  return checkFile(arguments[1].c_str(), "reading", -3) +
         checkFile(arguments[2].c_str(), "writing", -4);
}
