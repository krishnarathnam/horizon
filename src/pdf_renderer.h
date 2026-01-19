#ifndef PDF_RENDERER_H
#define PDF_RENDERER_H

#include "ast.h"
#include "hpdf.h"
#include <string>

// PDF rendering state
struct PDFState {
  HPDF_Doc pdf;
  HPDF_Page page;
  float y_pos;
  float left_margin;
  float right_margin;
  float top_margin;
  float bottom_margin;
  float page_height;
  float page_width;
  HPDF_Font font_normal;
  HPDF_Font font_bold;
  HPDF_Font font_italic;
  float font_size_title;
  float font_size_heading;
  float font_size_subheading;
  float font_size_normal;
};

// Error handler for libhpdf
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

// Initialize PDF state with default settings
bool init_pdf_state(PDFState& state, HPDF_Doc pdf);

// Render AST node to PDF
void render_node_to_pdf(PDFState& state, Node* node);

// Create PDF from AST root node and save to file
bool create_pdf_from_ast(Node* root, const std::string& output_path);

#endif // PDF_RENDERER_H
