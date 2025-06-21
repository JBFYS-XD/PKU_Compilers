#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <iostream>

class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual void Dump(std::ostream& os) const = 0;
};

// 全局输出运算符声明
std::ostream& operator<<(std::ostream& os, const BaseAST& ast);

class CompUnitAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_def;
    void Dump(std::ostream& os) const override;
};

class FuncDefAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_type;
    std::unique_ptr<std::string> ident;
    std::unique_ptr<BaseAST> block;
    void Dump(std::ostream& os) const override;
};

class FuncTypeAST : public BaseAST {
public:
    std::unique_ptr<std::string> type;
    void Dump(std::ostream& os) const override;
};

class BlockAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> stmt;
    static int entry_count;
    void Dump(std::ostream& os) const override;
};

class StmtAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> number;
    void Dump(std::ostream& os) const override;
};

class NumberAST : public BaseAST {
public:
    std::unique_ptr<std::string> int_const;
    void Dump(std::ostream& os) const override;
};

#endif // AST_H