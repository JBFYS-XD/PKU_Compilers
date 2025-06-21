#include "ast.h"

// 全局输出运算符定义
std::ostream& operator<<(std::ostream& os, const BaseAST& ast) {
    ast.Dump(os);
    return os;
}

// CompUnitAST
void CompUnitAST::Dump(std::ostream& os) const {
    os << *func_def;
}

// FuncDefAST
void FuncDefAST::Dump(std::ostream& os) const {
    // os << "FuncDefAST { " << *func_type << ", " << *ident << ", " << *block << " }";
    if (*ident == "main") {
        os << "fun @" << (*ident) << "(): " << *func_type << " {\n" << *block << "\n}";
    } else {
        os << "fun %" << (*ident) << "(): " << *func_type << " {\n" << *block << "\n}";
    }
}

// FuncTypeAST
void FuncTypeAST::Dump(std::ostream& os) const {
    // os << "FuncTypeAST { " << *type << " }";
    if (*type == "int") {
        os << "i32";
    }
}

int BlockAST::entry_count = 0;

// BlockAST
void BlockAST::Dump(std::ostream& os) const {
    // os << "BlockAST { " << *stmt << " }";
    os << "%entry" << (entry_count ++) << ":\n  " << *stmt;
}

// StmtAST
void StmtAST::Dump(std::ostream& os) const {
    os << "ret " << *number;
}

// NumberAST
void NumberAST::Dump(std::ostream& os) const {
    os << *int_const;
}