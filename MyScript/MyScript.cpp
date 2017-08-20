// MyScript.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>

#include "antlr4-runtime.h"
#include "MyScriptLexer.h"
#include "MyScriptParser.h"
#include "MyScriptListenerImpl.h"
#include "MyScriptVisitorImpl.h"

using namespace antlr4;
using namespace antlr4::tree;
using namespace antlrcpp;
using namespace std;

int main()
{
    for (;;)
    {
        cout << ">> ";
        string in;
        getline(cin, in);
        if (in.empty())
            break;
        ANTLRInputStream input(in);
        MyScriptLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        MyScriptParser parser(&tokens);
        ParseTree *tree = parser.start();
        cout << tree->toStringTree(&parser) << endl;
        MyScriptListenerImpl listener;
        ParseTreeWalker::DEFAULT.walk(&listener, tree);
        MyScriptVisitorImpl visitor;
        auto ast = visitor.visit(tree);
        cout << endl;
    }
    return 0;
}

