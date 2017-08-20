
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

  virtual void enterExpr(MyScriptParser::ExprContext *ctx) = 0;
  virtual void exitExpr(MyScriptParser::ExprContext *ctx) = 0;

  virtual void enterValue(MyScriptParser::ValueContext *ctx) = 0;
  virtual void exitValue(MyScriptParser::ValueContext *ctx) = 0;


};

