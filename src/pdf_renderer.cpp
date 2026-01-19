#include "pdf_renderer.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

// Helper function to trim whitespace from both ends
static std::string trim(const std::string& str) {
  size_t first = str.find_first_not_of(" \t\n\r");
  if (first == std::string::npos) return "";
  size_t last = str.find_last_not_of(" \t\n\r");
  return str.substr(first, (last - first + 1));
}

// Error handler for libhpdf
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
  std::cerr << "ERROR: error_no=" << std::hex << error_no 
            << ", detail_no=" << detail_no << std::dec << std::endl;
}

// Create a new page if needed
static HPDF_Page ensure_page(PDFState& state) {
  if (state.y_pos < state.bottom_margin) {
    state.page = HPDF_AddPage(state.pdf);
    if (!state.page) {
      std::cerr << "ERROR: Cannot create new page" << std::endl;
      return nullptr;
    }
    HPDF_Page_SetSize(state.page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    state.y_pos = state.page_height - state.top_margin;
    // Set default font on new page
    HPDF_Page_SetFontAndSize(state.page, state.font_normal, state.font_size_normal);
  }
  return state.page;
}

// Render centered text with word wrapping
static void render_text_centered(PDFState& state, const std::string& text, float& y,
                                 float font_size, HPDF_Font font) {
  ensure_page(state);
  
  std::string trimmed_text = trim(text);
  if (trimmed_text.empty()) return;
  
  HPDF_Page_SetFontAndSize(state.page, font, font_size);
  float max_width = state.page_width - state.left_margin - state.right_margin;
  float line_height = font_size * 1.2;
  std::string remaining = trimmed_text;
  
  while (!remaining.empty()) {
    if (y < state.bottom_margin) {
      state.page = HPDF_AddPage(state.pdf);
      HPDF_Page_SetSize(state.page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
      y = state.page_height - state.top_margin;
      HPDF_Page_SetFontAndSize(state.page, font, font_size);
    }
    
    // Find how much text fits on this line
    std::string line;
    std::string word;
    std::istringstream iss(remaining);
    
    HPDF_Page_SetFontAndSize(state.page, font, font_size);
    
    while (iss >> word) {
      std::string test_line = line.empty() ? word : line + " " + word;
      float text_width = HPDF_Page_TextWidth(state.page, test_line.c_str());
      
      if (text_width <= max_width || line.empty()) {
        line = test_line;
      } else {
        break;
      }
    }
    
    if (line.empty() && !remaining.empty()) {
      line = remaining;
      remaining.clear();
    } else {
      if (remaining.size() >= line.size()) {
        remaining = remaining.substr(line.size());
        while (!remaining.empty() && (remaining[0] == ' ' || remaining[0] == '\t')) {
          remaining = remaining.substr(1);
        }
      } else {
        remaining.clear();
      }
    }
    
    // Center this line
    HPDF_Page_SetFontAndSize(state.page, font, font_size);
    float line_width = HPDF_Page_TextWidth(state.page, line.c_str());
    float center_x = (state.page_width - line_width) / 2.0f;
    
    HPDF_Page_BeginText(state.page);
    HPDF_Page_TextOut(state.page, center_x, y, line.c_str());
    HPDF_Page_EndText(state.page);
    
    y -= line_height;
  }
}

// Render text with word wrapping
static void render_text(PDFState& state, const std::string& text, float x, float& y, 
                 float max_width, HPDF_Font font, float font_size) {
  ensure_page(state);
  
  // Set font before any text operations
  HPDF_Page_SetFontAndSize(state.page, font, font_size);
  
  // Trim and clean the text
  std::string remaining = trim(text);
  float line_height = font_size * 1.2;
  
  while (!remaining.empty()) {
    if (y < state.bottom_margin) {
      state.page = HPDF_AddPage(state.pdf);
      HPDF_Page_SetSize(state.page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
      y = state.page_height - state.top_margin;
      // Must set font again after creating new page
      HPDF_Page_SetFontAndSize(state.page, font, font_size);
    }
    
    // Find how much text fits on this line
    std::string line;
    std::string word;
    std::istringstream iss(remaining);
    
    // Ensure font is set before calling TextWidth
    HPDF_Page_SetFontAndSize(state.page, font, font_size);
    
    while (iss >> word) {
      std::string test_line = line.empty() ? word : line + " " + word;
      float text_width = HPDF_Page_TextWidth(state.page, test_line.c_str());
      
      if (text_width <= max_width || line.empty()) {
        line = test_line;
      } else {
        break;
      }
    }
    
    if (line.empty() && !remaining.empty()) {
      // Single word is too long, just use it
      line = remaining;
      remaining.clear();
    } else {
      // Remove the line from remaining
      if (remaining.size() >= line.size()) {
        remaining = remaining.substr(line.size());
        // Skip leading whitespace
        while (!remaining.empty() && (remaining[0] == ' ' || remaining[0] == '\t')) {
          remaining = remaining.substr(1);
        }
      } else {
        remaining.clear();
      }
    }
    
    // Ensure font is set before rendering
    HPDF_Page_SetFontAndSize(state.page, font, font_size);
    HPDF_Page_BeginText(state.page);
    HPDF_Page_TextOut(state.page, x, y, line.c_str());
    HPDF_Page_EndText(state.page);
    
    y -= line_height;
  }
}

// Render a node and its children recursively
void render_node_to_pdf(PDFState& state, Node* node) {
  if (!node) return;
  
  ensure_page(state);
  
  switch (node->kind) {
    case DOCUMENT_DOC: {
      // Render all children (title and headings)
      for (Node* child : node->children) {
        render_node_to_pdf(state, child);
      }
      break;
    }
    
    case DOCUMENT_TITLE: {
      // Title should be at the top of the first page, centered
      if (state.y_pos > state.page_height - state.top_margin - 50) {
        // We're near the top, use current position
        state.y_pos = state.page_height - state.top_margin;
      }
      ensure_page(state);
      float title_y = state.y_pos;
      render_text_centered(state, node->value, title_y, state.font_size_title, state.font_bold);
      state.y_pos = title_y - 20; // Extra space after title
      break;
    }
    
    case DOCUMENT_HEADING: {
      state.y_pos -= 20; // Space before heading
      ensure_page(state);
      float heading_y = state.y_pos;
      std::string heading_text = trim(node->value);
      render_text(state, heading_text, state.left_margin, heading_y,
                  state.page_width - state.left_margin - state.right_margin,
                  state.font_bold, state.font_size_heading);
      state.y_pos = heading_y - 15; // Space after heading
      
      // Render heading content
      for (Node* child : node->children) {
        render_node_to_pdf(state, child);
      }
      break;
    }
    
    case DOCUMENT_SUBHEADING: {
      state.y_pos -= 15; // Space before subheading
      ensure_page(state);
      float subheading_y = state.y_pos;
      std::string subheading_text = trim(node->value);
      // Subheadings aligned with left margin, same as headings
      render_text(state, subheading_text, state.left_margin, subheading_y,
                  state.page_width - state.left_margin - state.right_margin,
                  state.font_bold, state.font_size_subheading);
      state.y_pos = subheading_y - 10; // Space after subheading
      
      // Render subheading content
      for (Node* child : node->children) {
        render_node_to_pdf(state, child);
      }
      break;
    }
    
    case DOCUMENT_PARAGRAPH: {
      state.y_pos -= 10; // Space before paragraph
      ensure_page(state);
      float para_y = state.y_pos;
      float para_x = state.left_margin;
      float max_width = state.page_width - state.left_margin - state.right_margin;
      float current_x = para_x;
      float line_height = state.font_size_normal * 1.2;
      
      // Render paragraph with inline formatting
      for (Node* child : node->children) {
        HPDF_Font font = state.font_normal;
        if (child->kind == DOCUMENT_BOLD) {
          font = state.font_bold;
        } else if (child->kind == DOCUMENT_ITALIC) {
          font = state.font_italic;
        }
        
        std::string text = trim(child->value);
        if (child->kind != DOCUMENT_TEXT && !text.empty() && text.back() != ' ') {
          text += " ";
        }
        
        // Simple word wrapping for this segment
        std::istringstream iss(text);
        std::string word;
        while (iss >> word) {
          // Check if we need a new line before processing this word
          HPDF_Page_SetFontAndSize(state.page, font, state.font_size_normal);
          float word_width = HPDF_Page_TextWidth(state.page, (word + " ").c_str());
          
          if (current_x + word_width > para_x + max_width && current_x > para_x) {
            // Need new line
            para_y -= line_height;
            if (para_y < state.bottom_margin) {
              state.page = HPDF_AddPage(state.pdf);
              HPDF_Page_SetSize(state.page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
              para_y = state.page_height - state.top_margin;
              // Set font after creating new page
              HPDF_Page_SetFontAndSize(state.page, font, state.font_size_normal);
            }
            current_x = para_x;
          }
          
          // Render the word
          HPDF_Page_SetFontAndSize(state.page, font, state.font_size_normal);
          HPDF_Page_BeginText(state.page);
          HPDF_Page_TextOut(state.page, current_x, para_y, word.c_str());
          HPDF_Page_EndText(state.page);
          
          // Update position using the same font
          current_x += word_width;
        }
      }
      
      state.y_pos = para_y - line_height;
      break;
    }
    
    case DOCUMENT_BULLET: {
      state.y_pos -= 8; // Space before bullet
      ensure_page(state);
      float bullet_y = state.y_pos;
      
      // Draw bullet point using a simple character that works in all fonts
      HPDF_Page_SetFontAndSize(state.page, state.font_normal, state.font_size_normal);
      HPDF_Page_BeginText(state.page);
      HPDF_Page_TextOut(state.page, state.left_margin, bullet_y, "-");
      HPDF_Page_EndText(state.page);
      
      // Render bullet text (trimmed)
      std::string bullet_text = trim(node->value);
      float text_x = state.left_margin + 15;
      render_text(state, bullet_text, text_x, bullet_y,
                  state.page_width - text_x - state.right_margin,
                  state.font_normal, state.font_size_normal);
      state.y_pos = bullet_y;
      break;
    }
    
    case DOCUMENT_TEXT:
    case DOCUMENT_BOLD:
    case DOCUMENT_ITALIC:
      // These are handled within paragraphs
      break;
  }
}

// Initialize PDF state with default settings
bool init_pdf_state(PDFState& state, HPDF_Doc pdf) {
  if (!pdf) {
    return false;
  }

  state.pdf = pdf;
  state.left_margin = 50;
  state.right_margin = 50;
  state.top_margin = 50;
  state.bottom_margin = 50;
  state.page_width = 595.276; // A4 width in points
  state.page_height = 841.890; // A4 height in points
  state.font_size_title = 24;
  state.font_size_heading = 18;
  state.font_size_subheading = 14;
  state.font_size_normal = 12;

  // Get fonts
  state.font_normal = HPDF_GetFont(pdf, "Helvetica", nullptr);
  state.font_bold = HPDF_GetFont(pdf, "Helvetica-Bold", nullptr);
  state.font_italic = HPDF_GetFont(pdf, "Helvetica-Oblique", nullptr);
  
  if (!state.font_normal || !state.font_bold || !state.font_italic) {
    std::cerr << "ERROR: Cannot load fonts" << std::endl;
    return false;
  }

  // Create first page
  state.page = HPDF_AddPage(pdf);
  if (!state.page) {
    std::cerr << "ERROR: Cannot create first page" << std::endl;
    return false;
  }
  
  HPDF_Page_SetSize(state.page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
  state.y_pos = state.page_height - state.top_margin;

  return true;
}

// Create PDF from AST root node and save to file
bool create_pdf_from_ast(Node* root, const std::string& output_path) {
  if (!root) {
    std::cerr << "ERROR: No root node provided" << std::endl;
    return false;
  }

  // Create PDF document
  HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
  if (!pdf) {
    std::cerr << "ERROR: Cannot create PDF object" << std::endl;
    return false;
  }

  // Initialize PDF state
  PDFState state;
  if (!init_pdf_state(state, pdf)) {
    HPDF_Free(pdf);
    return false;
  }

  // Render the AST starting from root
  render_node_to_pdf(state, root);

  // Save PDF to file
  HPDF_STATUS save_status = HPDF_SaveToFile(pdf, output_path.c_str());
  if (save_status != HPDF_OK) {
    std::cerr << "ERROR: Failed to save PDF file. Error code: " << save_status << std::endl;
    HPDF_Free(pdf);
    return false;
  }

  HPDF_Free(pdf);
  return true;
}
