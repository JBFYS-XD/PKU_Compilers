#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <ast.h>
#include "/opt/include/koopa.h"

using namespace std;

extern FILE *yyin, *yyout;
extern int yyparse(unique_ptr<BaseAST> &ast);

extern int yy_flex_debug;

int main(int argc, const char *argv[]) {
    assert(argc == 5);
    auto mode = argv[1];
    auto input = argv[2];
    auto output = argv[4];

    yyin = fopen(input, "r");
    assert(yyin);

    yy_flex_debug = 1;

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);

    std::ofstream result(output);
    result << *ast << endl;
    return 0;
}