#include "MyScriptVisitorImpl.h"



MyScriptVisitorImpl::MyScriptVisitorImpl()
{
}


MyScriptVisitorImpl::~MyScriptVisitorImpl()
{
}

antlrcpp::Any MyScriptVisitorImpl::visitStart(MyScriptParser::StartContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any MyScriptVisitorImpl::visitExprs(MyScriptParser::ExprsContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any MyScriptVisitorImpl::visitExpr(MyScriptParser::ExprContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any MyScriptVisitorImpl::visitList(MyScriptParser::ListContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any MyScriptVisitorImpl::visitAtom(MyScriptParser::AtomContext* ctx)
{
    return visitChildren(ctx);
}
