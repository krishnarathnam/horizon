#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

enum NodeKind {
  DOCUMENT_DOC,
  DOCUMENT_TITLE,
  DOCUMENT_HEADING,
  DOCUMENT_SUBHEADING,
  DOCUMENT_PARAGRAPH,
  DOCUMENT_TEXT,
  DOCUMENT_BOLD,
  DOCUMENT_ITALIC,
  DOCUMENT_BULLET,
};

struct Node {
  NodeKind kind;
  std::string value; // what comes inside ()
  std::vector<Node *>
      children; // paragraph this will be null for itaclic bullet and bold
};

Node *create_node(NodeKind kind, const std::string &v = "",
                  const std::vector<Node *> &children = {});

void print_tree(Node *node, const std::string &prefix = "", bool is_last = true, bool is_root = true);

#endif
