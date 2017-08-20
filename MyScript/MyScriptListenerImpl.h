#pragma once

#include "MyScriptBaseListener.h"

class MyScriptListenerImpl : public MyScriptBaseListener
{
public:
    MyScriptListenerImpl();
    ~MyScriptListenerImpl();
    void enterStart(MyScriptParser::StartContext*) override;
    void exitStart(MyScriptParser::StartContext*) override;
    void enterExpr(MyScriptParser::ExprContext*) override;
    void exitExpr(MyScriptParser::ExprContext*) override;
    void enterValue(MyScriptParser::ValueContext*) override;
    void exitValue(MyScriptParser::ValueContext*) override;
};

