#include "BoardView.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace console_ui {

std::string BoardView::body() {
  performAction();
  const std::string seperator = "---------------------------------\n";
  std::string body;
  for (const auto& row : board) {
    body += seperator + "| ";
    for (const auto value : row) {
      std::ostringstream oss;
      oss << std::setw(5) << value;
      body += (value != 0 ? oss.str() : "     ") + " | ";
    }
    body += "\n";
  }
  body += seperator + "\n";
  return body;
}

}  // namespace console_ui
