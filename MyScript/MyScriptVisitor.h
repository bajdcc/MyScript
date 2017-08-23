
// Generated from E:\VSProjects\MyScript\MyScript\MyScript.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MyScriptParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MyScriptParser.
 */
class  MyScriptVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MyScriptParser.
   */
    virtual antlrcpp::Any visitStart(MyScriptParser::StartContext *context) = 0;

    virtual antlrcpp::Any visitExprs(MyScriptParser::ExprsContext *context) = 0;

    virtual antlrcpp::Any visitExpr(MyScriptParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitQuote(MyScriptParser::QuoteContext *context) = 0;

    virtual antlrcpp::Any visitList(MyScriptParser::ListContext *context) = 0;

    virtual antlrcpp::Any visitAtom(MyScriptParser::AtomContext *context) = 0;


};

