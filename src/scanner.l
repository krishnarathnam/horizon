%option noyywrap
%option c++

%{
#include <cstring>
#include <cstdlib>
#include <string>
#include "parser.tab.hh"
#include "token.h"
%}


%%
"@title"/([ \t]*\()    { return horizon::parser::token::TOKEN_TITLE; }
"@heading"/([ \t]*\()  { return horizon::parser::token::TOKEN_HEADING; }
"@subheading"/([ \t]*\() { return horizon::parser::token::TOKEN_SUBHEADING; }
"@bold"/([ \t]*\{)     { return horizon::parser::token::TOKEN_BOLD; }
"@italic"/([ \t]*\{)   { return horizon::parser::token::TOKEN_ITALIC; }
"@bullet"/([ \t]*\{)   { return horizon::parser::token::TOKEN_BULLET; }

"{"                     { return horizon::parser::token::TOKEN_LBRAC; }
"}"                     { return horizon::parser::token::TOKEN_RBRAC; }
"("                     { return horizon::parser::token::TOKEN_LPAREN; }
")"                     { return horizon::parser::token::TOKEN_RPAREN; }

[ \t]+                  ;   // skip spaces and tabs (but not newlines)

[\r\n][ \t]*[\r\n]+     ;   // blank lines (two+ newlines) - these separate paragraphs

[^@{}()\r\n]+|@[^@{}()\r\n]+ { return horizon::parser::token::TOKEN_TEXT; }

[\r\n]                  ;   // single newlines are part of text content, skip them here

<<EOF>>                 { return 0; }
%%
