// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 7 "parser.y"

#include <iostream>
#include <string>
#include <vector>
#include <FlexLexer.h>

#line 48 "parser.tab.c"


#include "parser.tab.h"


// Unqualified %code blocks.
#line 53 "parser.y"

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

#line 83 "parser.tab.c"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 3 "parser.y"
namespace  horizon  {
#line 157 "parser.tab.c"

  /// Build a parser object.
   parser :: parser  (yyFlexLexer& lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

   parser ::~ parser  ()
  {}

   parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
   parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
   parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
   parser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
   parser ::symbol_kind_type
   parser ::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
   parser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
   parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
   parser ::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
   parser ::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

   parser ::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

   parser ::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
   parser ::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
   parser ::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

   parser ::symbol_kind_type
   parser ::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


   parser ::symbol_kind_type
   parser ::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
   parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   parser ::symbol_kind_type
   parser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   parser ::stack_symbol_type::stack_symbol_type ()
  {}

   parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   parser ::stack_symbol_type&
   parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

   parser ::stack_symbol_type&
   parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
   parser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   parser ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   parser ::debug_level_type
   parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   parser ::state_type
   parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   parser ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   parser ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   parser ::operator() ()
  {
    return parse ();
  }

  int
   parser ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, lexer));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // document: title_opt heading_list
#line 87 "parser.y"
      { 
        std::vector<Node*> children = *(yystack_[0].value.list);
        if ((yystack_[1].value.node)) {
          children.insert(children.begin(), (yystack_[1].value.node));
        }
        (yylhs.value.node) = create_node(DOCUMENT_DOC, "", children);
        g_root_node = (yylhs.value.node);
      }
#line 621 "parser.tab.c"
    break;

  case 3: // title_opt: title
#line 98 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 627 "parser.tab.c"
    break;

  case 4: // title_opt: %empty
#line 100 "parser.y"
    { (yylhs.value.node) = nullptr; }
#line 633 "parser.tab.c"
    break;

  case 5: // title: TOKEN_TITLE TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN
#line 105 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_TITLE, *(yystack_[1].value.str)); }
#line 639 "parser.tab.c"
    break;

  case 6: // heading_list: heading_list heading
#line 110 "parser.y"
      { (yystack_[1].value.list)->push_back((yystack_[0].value.node)); (yylhs.value.list) = (yystack_[1].value.list); }
#line 645 "parser.tab.c"
    break;

  case 7: // heading_list: heading
#line 112 "parser.y"
      { (yylhs.value.list) = new std::vector<Node*>{ (yystack_[0].value.node) }; }
#line 651 "parser.tab.c"
    break;

  case 8: // heading: TOKEN_HEADING TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN TOKEN_LBRAC heading_content_list TOKEN_RBRAC
#line 118 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_HEADING, *(yystack_[4].value.str), *(yystack_[1].value.list)); }
#line 657 "parser.tab.c"
    break;

  case 9: // heading_content_list: heading_content_list heading_content
#line 123 "parser.y"
      { (yystack_[1].value.list)->push_back((yystack_[0].value.node)); (yylhs.value.list) = (yystack_[1].value.list); }
#line 663 "parser.tab.c"
    break;

  case 10: // heading_content_list: heading_content
#line 125 "parser.y"
      { (yylhs.value.list) = new std::vector<Node*>{ (yystack_[0].value.node) }; }
#line 669 "parser.tab.c"
    break;

  case 11: // heading_content: paragraph
#line 129 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 675 "parser.tab.c"
    break;

  case 12: // heading_content: bullet
#line 130 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 681 "parser.tab.c"
    break;

  case 13: // heading_content: subheading
#line 131 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 687 "parser.tab.c"
    break;

  case 14: // subheading: TOKEN_SUBHEADING TOKEN_LPAREN TOKEN_TEXT TOKEN_RPAREN TOKEN_LBRAC subheading_content_list TOKEN_RBRAC
#line 137 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_SUBHEADING, *(yystack_[4].value.str), *(yystack_[1].value.list)); }
#line 693 "parser.tab.c"
    break;

  case 15: // subheading_content_list: subheading_content_list subheading_content
#line 142 "parser.y"
      { (yystack_[1].value.list)->push_back((yystack_[0].value.node)); (yylhs.value.list) = (yystack_[1].value.list); }
#line 699 "parser.tab.c"
    break;

  case 16: // subheading_content_list: subheading_content
#line 144 "parser.y"
      { (yylhs.value.list) = new std::vector<Node*>{ (yystack_[0].value.node) }; }
#line 705 "parser.tab.c"
    break;

  case 17: // subheading_content: paragraph
#line 148 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 711 "parser.tab.c"
    break;

  case 18: // subheading_content: bullet
#line 149 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 717 "parser.tab.c"
    break;

  case 19: // paragraph: paragraph_items
#line 154 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_PARAGRAPH, "", *(yystack_[0].value.list)); }
#line 723 "parser.tab.c"
    break;

  case 20: // paragraph_items: paragraph_items paragraph_item
#line 159 "parser.y"
      { (yystack_[1].value.list)->push_back((yystack_[0].value.node)); (yylhs.value.list) = (yystack_[1].value.list); }
#line 729 "parser.tab.c"
    break;

  case 21: // paragraph_items: paragraph_item
#line 161 "parser.y"
      { (yylhs.value.list) = new std::vector<Node*>{ (yystack_[0].value.node) }; }
#line 735 "parser.tab.c"
    break;

  case 22: // paragraph_item: TOKEN_TEXT
#line 166 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_TEXT, *(yystack_[0].value.str)); }
#line 741 "parser.tab.c"
    break;

  case 23: // paragraph_item: bold
#line 167 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 747 "parser.tab.c"
    break;

  case 24: // paragraph_item: italic
#line 168 "parser.y"
      { (yylhs.value.node) = (yystack_[0].value.node); }
#line 753 "parser.tab.c"
    break;

  case 25: // bullet: TOKEN_BULLET TOKEN_LBRAC bullet_text_items TOKEN_RBRAC
#line 173 "parser.y"
      { 
        // Concatenate all text tokens
        std::string combined;
        for (Node* item : *(yystack_[1].value.list)) {
            if (item->kind == DOCUMENT_TEXT) {
                combined += item->value;
            }
        }
        (yylhs.value.node) = create_node(DOCUMENT_BULLET, combined);
        // Clean up the list items
        for (Node* item : *(yystack_[1].value.list)) {
            delete item;
        }
        delete (yystack_[1].value.list);
      }
#line 773 "parser.tab.c"
    break;

  case 26: // bullet_text_items: bullet_text_items TOKEN_TEXT
#line 192 "parser.y"
      { 
        (yystack_[1].value.list)->push_back(create_node(DOCUMENT_TEXT, *(yystack_[0].value.str)));
        (yylhs.value.list) = (yystack_[1].value.list);
      }
#line 782 "parser.tab.c"
    break;

  case 27: // bullet_text_items: TOKEN_TEXT
#line 197 "parser.y"
      { (yylhs.value.list) = new std::vector<Node*>{ create_node(DOCUMENT_TEXT, *(yystack_[0].value.str)) }; }
#line 788 "parser.tab.c"
    break;

  case 28: // bold: TOKEN_BOLD TOKEN_LBRAC TOKEN_TEXT TOKEN_RBRAC
#line 202 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_BOLD, *(yystack_[1].value.str)); }
#line 794 "parser.tab.c"
    break;

  case 29: // italic: TOKEN_ITALIC TOKEN_LBRAC TOKEN_TEXT TOKEN_RBRAC
#line 207 "parser.y"
      { (yylhs.value.node) = create_node(DOCUMENT_ITALIC, *(yystack_[1].value.str)); }
#line 800 "parser.tab.c"
    break;


#line 804 "parser.tab.c"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
   parser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char  parser ::yypact_ninf_ = -21;

  const signed char  parser ::yytable_ninf_ = -1;

  const signed char
   parser ::yypact_[] =
  {
       2,    -1,    26,    28,   -21,    24,   -21,    22,    28,   -21,
      23,    29,   -21,   -21,    27,    25,     8,    30,    31,    33,
      34,   -21,    -5,   -21,   -21,   -21,    15,   -21,   -21,   -21,
     -21,    36,    37,    38,    39,   -21,   -21,   -21,    40,   -21,
      16,    41,    43,    45,   -21,   -21,   -21,   -21,    12,     1,
     -21,   -21,   -21,   -21,   -21
  };

  const signed char
   parser ::yydefact_[] =
  {
       4,     0,     0,     0,     3,     0,     1,     0,     2,     7,
       0,     0,     6,     5,     0,     0,     0,     0,     0,     0,
       0,    22,     0,    10,    13,    11,    19,    21,    12,    23,
      24,     0,     0,     0,     0,     8,     9,    20,     0,    27,
       0,     0,     0,     0,    26,    25,    28,    29,     0,     0,
      16,    17,    18,    14,    15
  };

  const signed char
   parser ::yypgoto_[] =
  {
     -21,   -21,   -21,   -21,   -21,    42,   -21,    17,   -21,   -21,
     -12,   -20,   -21,    32,   -18,   -21,   -21,   -21
  };

  const signed char
   parser ::yydefgoto_[] =
  {
       0,     2,     3,     4,     8,     9,    22,    23,    24,    49,
      50,    25,    26,    27,    28,    40,    29,    30
  };

  const signed char
   parser ::yytable_[] =
  {
      17,    18,    19,    20,    21,     1,    35,    18,    19,    20,
      21,     5,    53,    17,    18,    19,    20,    21,    18,    19,
      20,    21,    19,    20,    21,    44,     6,    45,    51,    51,
      52,    52,     7,    10,    11,    16,    13,    54,    14,    36,
      15,    32,    31,    33,    34,    38,    39,    41,    42,     0,
      12,     0,    46,    43,    47,    48,     0,     0,    37
  };

  const signed char
   parser ::yycheck_[] =
  {
       5,     6,     7,     8,     9,     3,    11,     6,     7,     8,
       9,    12,    11,     5,     6,     7,     8,     9,     6,     7,
       8,     9,     7,     8,     9,     9,     0,    11,    48,    49,
      48,    49,     4,     9,    12,    10,    13,    49,     9,    22,
      13,    10,    12,    10,    10,     9,     9,     9,     9,    -1,
       8,    -1,    11,    13,    11,    10,    -1,    -1,    26
  };

  const signed char
   parser ::yystos_[] =
  {
       0,     3,    16,    17,    18,    12,     0,     4,    19,    20,
       9,    12,    20,    13,     9,    13,    10,     5,     6,     7,
       8,     9,    21,    22,    23,    26,    27,    28,    29,    31,
      32,    12,    10,    10,    10,    11,    22,    28,     9,     9,
      30,     9,     9,    13,     9,    11,    11,    11,    10,    24,
      25,    26,    29,    11,    25
  };

  const signed char
   parser ::yyr1_[] =
  {
       0,    15,    16,    17,    17,    18,    19,    19,    20,    21,
      21,    22,    22,    22,    23,    24,    24,    25,    25,    26,
      27,    27,    28,    28,    28,    29,    30,    30,    31,    32
  };

  const signed char
   parser ::yyr2_[] =
  {
       0,     2,     2,     1,     0,     4,     2,     1,     7,     2,
       1,     1,     1,     1,     7,     2,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     4,     2,     1,     4,     4
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  parser ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_TITLE",
  "TOKEN_HEADING", "TOKEN_SUBHEADING", "TOKEN_BULLET", "TOKEN_BOLD",
  "TOKEN_ITALIC", "TOKEN_TEXT", "TOKEN_LBRAC", "TOKEN_RBRAC",
  "TOKEN_LPAREN", "TOKEN_RPAREN", "TOKEN_ERROR", "$accept", "document",
  "title_opt", "title", "heading_list", "heading", "heading_content_list",
  "heading_content", "subheading", "subheading_content_list",
  "subheading_content", "paragraph", "paragraph_items", "paragraph_item",
  "bullet", "bullet_text_items", "bold", "italic", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   parser ::yyrline_[] =
  {
       0,    86,    86,    98,   100,   104,   109,   111,   116,   122,
     124,   129,   130,   131,   135,   141,   143,   148,   149,   153,
     158,   160,   165,   167,   168,   172,   191,   196,   201,   206
  };

  void
   parser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   parser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

   parser ::symbol_kind_type
   parser ::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
    };
    // Last valid token kind.
    const int code_max = 269;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 3 "parser.y"
} //  horizon 
#line 1187 "parser.tab.c"

#line 210 "parser.y"



void horizon::parser::error(const std::string& msg)
{
    std::cerr << "Parse error: " << msg << std::endl;
    std::cerr << "Unexpected token encountered" << std::endl;
}
