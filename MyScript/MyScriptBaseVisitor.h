
// Generated from E:\VSProjects\MyScript\MyScript\MyScript.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MyScriptVisitor.h"


/**
 * This class provides an empty implementation of MyScriptVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MyScriptBaseVisitor : public MyScriptVisitor {
public:

  virtual antlrcpp::Any visitStart(MyScriptParser::StartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprs(MyScriptParser::ExprsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(MyScriptParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuote(MyScriptParser::QuoteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitList(MyScriptParser::ListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAtom(MyScriptParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }


};

