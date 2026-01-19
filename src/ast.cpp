#include "ast.h"
#include <iostream>
#include <string>
#include <cctype>

Node *create_node(NodeKind kind, const std::string &value,
                  const std::vector<Node *> &children) {
  Node *n = new Node;
  n->kind = kind;
  n->value = value;
  n->children = children;
  return n;
}

Node *create_node(NodeKind kind, const std::string &value) {
  Node *n = new Node;
  n->kind = kind;
  n->value = value;
  return n;
}

std::string node_kind_to_string(NodeKind kind) {
  switch (kind) {
    case DOCUMENT_DOC: return "DOCUMENT";
    case DOCUMENT_TITLE: return "TITLE";
    case DOCUMENT_HEADING: return "HEADING";
    case DOCUMENT_SUBHEADING: return "SUBHEADING";
    case DOCUMENT_PARAGRAPH: return "PARAGRAPH";
    case DOCUMENT_BOLD: return "BOLD";
    case DOCUMENT_ITALIC: return "ITALIC";
    case DOCUMENT_BULLET: return "BULLET";
    case DOCUMENT_TEXT: return "TEXT";
    default: return "UNKNOWN";
  }
}

void print_tree(Node *node, const std::string &prefix, bool is_last, bool is_root) {
  if (!node) return;

  // Convert to lowercase for display
  std::string kind_str = node_kind_to_string(node->kind);
  for (char& c : kind_str) {
    c = std::tolower(c);
  }
  
  // Print current node
  std::cout << prefix;
  // Add tree characters if not the root
  if (!is_root) {
    std::cout << (is_last ? "└─ " : "├─ ");
  }
  std::cout << kind_str;
  
  if (!node->value.empty()) {
    std::cout << " (" << node->value << ")";
  }
  std::cout << std::endl;

  // Print children
  if (!node->children.empty()) {
    std::string child_prefix;
    if (is_root) {
      // Root's children: start with empty prefix (they'll add ├─ or └─ themselves)
      child_prefix = "";
    } else {
      // Nested children: add vertical line continuation: │  for non-last, spaces for last
      child_prefix = prefix + (is_last ? "   " : "│  ");
    }
    
    for (size_t i = 0; i < node->children.size(); ++i) {
      bool is_last_child = (i == node->children.size() - 1);
      print_tree(node->children[i], child_prefix, is_last_child, false);
    }
  }
}
