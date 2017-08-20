#pragma once

#include "MyScriptBaseVisitor.h"

class MyScriptVisitorImpl : public MyScriptBaseVisitor
{
public:
    MyScriptVisitorImpl();
    ~MyScriptVisitorImpl();
    antlrcpp::Any visitStart(MyScriptParser::StartContext* ctx) override;
    antlrcpp::Any visitExpr(MyScriptParser::ExprContext* ctx) override;
    antlrcpp::Any visitValue(MyScriptParser::ValueContext* ctx) override;
};

