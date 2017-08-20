#pragma once

#include "MyScriptBaseListener.h"

class MyScriptListenerImpl : public MyScriptBaseListener
{
public:
    MyScriptListenerImpl();
    ~MyScriptListenerImpl();
    void enterStart(MyScriptParser::StartContext*) override;
    void exitStart(MyScriptParser::StartContext*) override;
    void enterExprs(MyScriptParser::ExprsContext*) override;
    void exitExprs(MyScriptParser::ExprsContext*) override;
    void enterExpr(MyScriptParser::ExprContext*) override;
    void exitExpr(MyScriptParser::ExprContext*) override;
    void enterList(MyScriptParser::ListContext*) override;
    void exitList(MyScriptParser::ListContext*) override;
    void enterAtom(MyScriptParser::AtomContext*) override;
    void exitAtom(MyScriptParser::AtomContext*) override;
};

