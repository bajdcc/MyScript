#pragma once

#include "MyScriptBaseVisitor.h"

class MyScriptVisitorImpl : public MyScriptBaseVisitor
{
public:
    MyScriptVisitorImpl();
    ~MyScriptVisitorImpl();
    antlrcpp::Any visitStart(MyScriptParser::StartContext* ctx) override;
    antlrcpp::Any visitExprs(MyScriptParser::ExprsContext* ctx) override;
    antlrcpp::Any visitExpr(MyScriptParser::ExprContext* ctx) override;
    antlrcpp::Any visitList(MyScriptParser::ListContext* ctx) override;
    antlrcpp::Any visitAtom(MyScriptParser::AtomContext* ctx) override;
};

