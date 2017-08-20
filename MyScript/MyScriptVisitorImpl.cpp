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

antlrcpp::Any MyScriptVisitorImpl::visitExpr(MyScriptParser::ExprContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any MyScriptVisitorImpl::visitValue(MyScriptParser::ValueContext* ctx)
{
    return visitChildren(ctx);
}
