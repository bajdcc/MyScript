
// Generated from E:\VSProjects\MyScript\MyScript\MyScript.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MyScriptListener.h"


/**
 * This class provides an empty implementation of MyScriptListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MyScriptBaseListener : public MyScriptListener {
public:

  virtual void enterStart(MyScriptParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(MyScriptParser::StartContext * /*ctx*/) override { }

  virtual void enterExprs(MyScriptParser::ExprsContext * /*ctx*/) override { }
  virtual void exitExprs(MyScriptParser::ExprsContext * /*ctx*/) override { }

  virtual void enterExpr(MyScriptParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(MyScriptParser::ExprContext * /*ctx*/) override { }

  virtual void enterList(MyScriptParser::ListContext * /*ctx*/) override { }
  virtual void exitList(MyScriptParser::ListContext * /*ctx*/) override { }

  virtual void enterAtom(MyScriptParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(MyScriptParser::AtomContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

