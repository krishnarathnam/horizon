#include "ast.h"
#include "pdf_renderer.h"
#include "parser.tab.hh"
#include <FlexLexer.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

extern Node *get_root_node();

std::string get_output_filename(const std::string& input_file) {
  std::string output = input_file;
  
  size_t last_slash = output.find_last_of("/\\");
  if (last_slash != std::string::npos) {
    output = output.substr(last_slash + 1);
  }
  
  size_t dot_pos = output.find_last_of(".");
  if (dot_pos != std::string::npos && output.substr(dot_pos) == ".nh") {
    output = output.substr(0, dot_pos) + ".pdf";
  } else {
    output += ".pdf";
  }
  
  return output;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input.nh>" << std::endl;
    std::cerr << "Example: " << argv[0] << " document.nh" << std::endl;
    return 1;
  }

  std::string input_file = argv[1];
  
  size_t dot_pos = input_file.find_last_of(".");
  if (dot_pos == std::string::npos || input_file.substr(dot_pos) != ".nh") {
    std::cerr << "Error: Only .nh files are supported" << std::endl;
    std::cerr << "Usage: " << argv[0] << " <input.nh>" << std::endl;
    return 1;
  }
  
  std::ifstream file(input_file);
  if (!file) {
    std::cerr << "Error: Cannot open file '" << input_file << "'" << std::endl;
    return 1;
  }

  yyFlexLexer lexer(&file);
  horizon::parser parser(lexer);

  int result = parser.parse();
  file.close();

  if (result != 0) {
    std::cerr << "Parse failed" << std::endl;
    return result;
  }

  Node *root = get_root_node();
  if (!root) {
    std::cerr << "ERROR: No root node found" << std::endl;
    return 1;
  }

  std::string output_file = get_output_filename(input_file);
  
  if (!create_pdf_from_ast(root, output_file)) {
    return 1;
  }

  std::cout << "PDF generated: " << output_file << std::endl;
  return 0;
}
