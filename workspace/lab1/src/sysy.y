%code requires {
    #include <memory>
    #include <string>
    #include <ast.h>
}

%{

    #pragma one
    #include <iostream>
    #include <memory>
    #include <string>
    #include <ast.h>

    int yylex();
    void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

    using namespace std;

%}

%parse-param { std::unique_ptr<BaseAST> &ast }


%union {
    std::string *str_val;
    int int_val;
    BaseAST *ast_val;
}


%token INT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST


%type <ast_val> FuncDef FuncType Block Stmt Number
/* %type <int_val> Number */


%%

CompUnit
    : FuncDef {
        auto comp_unit = make_unique<CompUnitAST>();
        comp_unit->func_def = unique_ptr<BaseAST>($1);
        ast = std::move(comp_unit);
    }
    ;

FuncDef
    : FuncType IDENT '(' ')' Block {
        auto ast = make_unique<FuncDefAST>();
        ast->func_type = unique_ptr<BaseAST>($1);
        ast->ident = unique_ptr<string>($2);
        ast->block = unique_ptr<BaseAST>($5);
        $$ = ast.release();
    }
    ;

FuncType
    : INT {
        auto ast = make_unique<FuncTypeAST>();
        ast->type = make_unique<string>("int");
        $$ = ast.release();
    }
    ;

Block
    : '{' Stmt '}' {
        auto ast = make_unique<BlockAST>();
        ast->stmt = unique_ptr<BaseAST>($2);
        $$ = ast.release();
    }
    ;

Stmt
    : RETURN Number ';' {
        auto ast = make_unique<StmtAST>();
        ast->number = unique_ptr<BaseAST>($2);
        $$ = ast.release();
    }
    ;

Number
    : INT_CONST {
        auto ast = make_unique<NumberAST>();
        ast->int_const = make_unique<string>(to_string($1));
        $$ = ast.release();
    }
    ;

%%

void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
    cerr << "error: " << s << endl;
}