%skeleton "lalr1.cc"
%require "3.0"
%define api.namespace { horizon }
%define api.parser.class { parser }
%define parse.assert

%{
#include <iostream>
#include <string>
#include <vector>
#include <FlexLexer.h>
%}

%code requires {
  class yyFlexLexer;
  #include "ast.h"
}


%union{
  std::string* str;
  Node* node;
  std::vector<Node*>* list;
}

%parse-param { yyFlexLexer& lexer }
%lex-param { yyFlexLexer& lexer }

%token TOKEN_TITLE
%token TOKEN_HEADING
%token TOKEN_SUBHEADING
%token TOKEN_BULLET
%token TOKEN_BOLD
%token TOKEN_ITALIC
%token <str> TOKEN_TEXT

%token TOKEN_LBRAC
%token TOKEN_RBRAC
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_ERROR

%type <node> document title title_opt heading subheading
%type <node> paragraph bullet bold italic
%type <node> heading_content subheading_content

%type <list> heading_list
%type <list> heading_content_list
%type <list> subheading_content_list
%type <list> paragraph_items
%type <list> bullet_text_items
%type <node> paragraph_item
%code {
#include <FlexLexer.h>

// Global lexer pointer for error recovery
static yyFlexLexer* g_lexer = nullptr;
// Global root node
static Node* g_root_node = nullptr;

Node* get_root_node() {
    return g_root_node;
}

    int yylex(horizon::parser::semantic_type* yylval,
            yyFlexLexer& lexer)
    {
        int tok = lexer.yylex();
        static int token_count = 0;
        token_count++;

        if (tok == horizon::parser::token::TOKEN_TEXT) {
            yylval->str = new std::string(lexer.YYText());
        }


        return tok;
    }
}

%start document

%%

document
    : title_opt heading_list
      { 
        std::vector<Node*> children = *$2;
        if ($1) {
          children.insert(children.begin(), $1);
        }
        $$ = create_node(DOCUMENT_DOC, "", children);
        g_root_node = $$;
      }
    ;

title_opt
    : title
    | /* empty */
    { $$ = nullptr; }
    ;

title
    : TOKEN_TITLE TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN
      { $$ = create_node(DOCUMENT_TITLE, *$3); }
    ;

heading_list
    : heading_list heading
      { $1->push_back($2); $$ = $1; }
    | heading
      { $$ = new std::vector<Node*>{ $1 }; }
    ;

heading
    : TOKEN_HEADING TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN
      TOKEN_LBRAC heading_content_list TOKEN_RBRAC
      { $$ = create_node(DOCUMENT_HEADING, *$3, *$6); }
    ;

heading_content_list
    : heading_content_list heading_content
      { $1->push_back($2); $$ = $1; }
    | heading_content
      { $$ = new std::vector<Node*>{ $1 }; }
    ;

heading_content
    : paragraph
    | bullet
    | subheading
    ;

subheading
    : TOKEN_SUBHEADING TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN
      TOKEN_LBRAC subheading_content_list TOKEN_RBRAC
      { $$ = create_node(DOCUMENT_SUBHEADING, *$3, *$6); }
    ;

subheading_content_list
    : subheading_content_list subheading_content
      { $1->push_back($2); $$ = $1; }
    | subheading_content
      { $$ = new std::vector<Node*>{ $1 }; }
    ;

subheading_content
    : paragraph
    | bullet
    ;

paragraph
    : paragraph_items
      { $$ = create_node(DOCUMENT_PARAGRAPH, "", *$1); }
    ;

paragraph_items
    : paragraph_items paragraph_item
      { $1->push_back($2); $$ = $1; }
    | paragraph_item
      { $$ = new std::vector<Node*>{ $1 }; }
    ;

paragraph_item
    : TOKEN_TEXT
      { $$ = create_node(DOCUMENT_TEXT, *$1); }
    | bold
    | italic
    ;

bullet
    : TOKEN_BULLET TOKEN_LBRAC bullet_text_items TOKEN_RBRAC
      { 
        // Concatenate all text tokens
        std::string combined;
        for (Node* item : *$3) {
            if (item->kind == DOCUMENT_TEXT) {
                combined += item->value;
            }
        }
        $$ = create_node(DOCUMENT_BULLET, combined);
        // Clean up the list items
        for (Node* item : *$3) {
            delete item;
        }
        delete $3;
      }
    ;

bullet_text_items
    : bullet_text_items TOKEN_TEXT
      { 
        $1->push_back(create_node(DOCUMENT_TEXT, *$2));
        $$ = $1;
      }
    | TOKEN_TEXT
      { $$ = new std::vector<Node*>{ create_node(DOCUMENT_TEXT, *$1) }; }
    ;

bold
    : TOKEN_BOLD TOKEN_LBRAC TOKEN_TEXT TOKEN_RBRAC
      { $$ = create_node(DOCUMENT_BOLD, *$3); }
    ;

italic
    : TOKEN_ITALIC TOKEN_LBRAC TOKEN_TEXT TOKEN_RBRAC
      { $$ = create_node(DOCUMENT_ITALIC, *$3); }
    ;

%%


void horizon::parser::error(const std::string& msg)
{
    std::cerr << "Parse error: " << msg << std::endl;
    std::cerr << "Unexpected token encountered" << std::endl;
}
