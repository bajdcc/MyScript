
// Generated from E:\VSProjects\MyScript\MyScript\MyScript.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MyScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by MyScriptParser.
 */
class  MyScriptListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(MyScriptParser::StartContext *ctx) = 0;
  virtual void exitStart(MyScriptParser::StartContext *ctx) = 0;

  virtual void enterExprs(MyScriptParser::ExprsContext *ctx) = 0;
  virtual void exitExprs(MyScriptParser::ExprsContext *ctx) = 0;

  virtual void enterExpr(MyScriptParser::ExprContext *ctx) = 0;
  virtual void exitExpr(MyScriptParser::ExprContext *ctx) = 0;

  virtual void enterQuote(MyScriptParser::QuoteContext *ctx) = 0;
  virtual void exitQuote(MyScriptParser::QuoteContext *ctx) = 0;

  virtual void enterList(MyScriptParser::ListContext *ctx) = 0;
  virtual void exitList(MyScriptParser::ListContext *ctx) = 0;

  virtual void enterAtom(MyScriptParser::AtomContext *ctx) = 0;
  virtual void exitAtom(MyScriptParser::AtomContext *ctx) = 0;


};

