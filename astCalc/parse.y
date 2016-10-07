//  Source code for "flex & bison", by John Levine
//  Declarations for an AST calculator fb3-1
//  Adapted by Brian Malloy
%{
#include <iostream>
#include "ast.h"
  extern int yylex();
  void yyerror(const char *s) { std::cout << s << std::endl; }
  void yyerror(const char *s, const char ch) {
    std::cout << s << ch << std::endl;
  }
%}

%union {
  Ast* ast;
  double d;
}

%token <d> NUMBER
%token EOL LPARAND RPARAND
%type <ast> expr

%left PLUS MINUS
%left MULT DIV
%right E
%nonassoc UMINUS

%%

calclist 
       : calclist expr EOL {
           std::cout << "= " << eval($2) << std::endl;
           makeGraph($2);
           treeFree($2);
           std::cout << "> ";

         }
       | calclist EOL // blank line or a comment
       | // empty
       ;

expr    : expr PLUS expr                { $$ = new AstNode('+', $1,$3);}
        | expr MINUS expr               { $$ = new AstNode('-', $1,$3); }
        | expr MULT expr                { $$ = new AstNode('*', $1,$3); }
        | expr DIV expr                 { $$ = new AstNode('/', $1,$3); }
        | expr E expr                   { $$ = new AstNode('E',$1,$3); }
        | LPARAND expr RPARAND          {$$ = $2;}
        | MINUS expr %prec UMINUS       { $$ = new AstNode('M', $2, NULL);}
        | NUMBER                        {$$ = new AstNumber('K', $1);   }
        ;


%%
