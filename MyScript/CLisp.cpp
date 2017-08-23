#include "CLisp.h"
#include <cassert>

#include "antlr4-runtime.h"
#include "MyScriptLexer.h"
#include "MyScriptParser.h"

using namespace antlr4;
using namespace antlr4::tree;
using namespace antlrcpp;

CLisp::CLisp()
{
    init();
}

CLisp::~CLisp()
{
}

void CLisp::init()
{
    _S_t = intern("t");
    _S_quote = intern("quote");
    _S_qquote = intern("quasiquote");
    _S_uquote = intern("unquote");
    _S_uquotes = intern("unquote-splicing");
    globals = cell_cons(cell_cons(intern("t"), _S_t), globals);
    init_fsubr("define", &CLisp::defineFsubr);
    init_fsubr("lambda", &CLisp::lambdaFsubr);
    init_fsubr("flambda", &CLisp::flambdaFsubr);
    init_fsubr("let", &CLisp::letFsubr);
    init_fsubr("if", &CLisp::ifFsubr);
    init_fsubr("while", &CLisp::whileFsubr);
    init_fsubr("setq", &CLisp::setqFsubr);
    init_subr("cons", &CLisp::consSubr);
    init_subr("rplaca", &CLisp::rplacaSubr);
    init_subr("rplacd", &CLisp::rplacdSubr);
    init_subr("car", &CLisp::carSubr);
    init_subr("cdr", &CLisp::cdrSubr);
    init_subr("eval", &CLisp::evalSubr);
    init_subr("apply", &CLisp::applySubr);
    init_subr("map", &CLisp::mapSubr);
    init_subr("assq", &CLisp::assqSubr);
    init_subr("print", &CLisp::printSubr);
    init_subr("println", &CLisp::printlnSubr);
    init_subr("+", &CLisp::addSubr);
    init_subr("-", &CLisp::subtractSubr);
    init_subr("*", &CLisp::multiplySubr);
    init_subr("/", &CLisp::divideSubr);
    init_subr("%", &CLisp::modulusSubr);
    init_subr("<", &CLisp::lessSubr);
    init_subr("<=", &CLisp::lessEqualSubr);
    init_subr("==", &CLisp::equalSubr);
    init_subr("!=", &CLisp::notEqualSubr);
    init_subr(">=", &CLisp::greaterEqualSubr);
    init_subr(">", &CLisp::greaterSubr);
    init_subr("println", &CLisp::printlnSubr);
    globals = cell_cons((syntaxTable = cell_cons(intern("*syntax-table*"), nullptr)), globals);
}

void CLisp::init_fsubr(const char *str, Subr_t fn)
{
    globals = cell_cons(cell_cons(intern(str), cell_fsubr(fn)), globals);
}

void CLisp::init_subr(const char *str, Subr_t fn)
{
    globals = cell_cons(cell_cons(intern(str), cell_subr(fn)), globals);
}

const char* CLisp::__strdup(const char* str)
{
    auto len = strlen(str);
    auto s = strings.alloc_array<char>(len + 1);
    strcpy_s(s, len + 1, str);
    return s;
}

void CLisp::mark(Cell* cell)
{
    gc.mark(cell);
    if (cell->tag == Cons || cell->tag == Expr || cell->tag == Fexpr)
    {
        if (cell->cons.a) gc.mark(cell->cons.a);
        if (cell->cons.d) gc.mark(cell->cons.d);
    }
}

void CLisp::unmark(Cell* cell)
{
    gc.unmark(cell);
}

void CLisp::fatal(const char* str)
{
    std::cerr << str << std::endl;
    exit(0);
}

CLisp::Cell* CLisp::cell()
{
    return gc.alloc<Cell>();
}

CLisp::Cell* CLisp::cell_num(int n)
{
    Cell* self = cell();
    self->tag = Number;
    self->number = n;
    return self;
}

CLisp::Cell* CLisp::cell_str(const char* s)
{
    Cell* self = cell();
    self->tag = String;
    self->string = __strdup(s);
    return self;
}

CLisp::Cell* CLisp::cell_sym(const char* s)
{
    Cell* self = cell();
    self->tag = Symbol;
    self->symbol = s;
    return self;
}

CLisp::Cell* CLisp::cell_cons(Cell* a, Cell* d)
{
    Cell* self = cell();
    self->tag = Cons;
    self->cons.a = a;
    self->cons.d = d;
    return self;
}

CLisp::Cell* CLisp::cell_subr(Subr_t fn)
{
    Cell* self = cell();
    self->tag = Subr;
    self->subr = fn;
    return self;
}

CLisp::Cell* CLisp::cell_fsubr(Subr_t fn)
{
    Cell* self = cell();
    self->tag = Fsubr;
    self->subr = fn;
    return self;
}

CLisp::Cell* CLisp::cell_expr(Cell* x, Cell* e)
{
    Cell* self = cell();
    self->tag = Expr;
    self->expr.expr = x;
    self->expr.env = e;
    return self;
}

CLisp::Cell* CLisp::cell_fexpr(Cell* x, Cell* e)
{
    Cell* self = cell();
    self->tag = Fexpr;
    self->expr.expr = x;
    self->expr.env = e;
    return self;
}

int CLisp::nilP(Cell* self)
{
    return !self;
}

int CLisp::numberP(Cell* self)
{
    return self && self->tag == Number;
}

int CLisp::stringP(Cell* self)
{
    return self && self->tag == String;
}

int CLisp::symbolP(Cell* self)
{
    return self && self->tag == Symbol;
}

int CLisp::consP(Cell* self)
{
    return self && self->tag == Cons;
}

int CLisp::subrP(Cell* self)
{
    return self && self->tag == Subr;
}

int CLisp::fsubrP(Cell* self)
{
    return self && self->tag == Fsubr;
}

int CLisp::exprP(Cell* self)
{
    return self && self->tag == Expr;
}

int CLisp::fexprP(Cell* self)
{
    return self && self->tag == Fexpr;
}

int CLisp::number(Cell* self)
{
    assert(numberP(self));
    return self->number;
}

const char* CLisp::string(Cell* self)
{
    assert(stringP(self));
    return self->string;
}

const char* CLisp::symbol(Cell* self)
{
    assert(symbolP(self));
    return self->symbol;
}

CLisp::Subr_t CLisp::subr(Cell* self)
{
    assert(subrP(self));
    return self->subr;
}

CLisp::Subr_t CLisp::fsubr(Cell* self)
{
    assert(fsubrP(self));
    return self->subr;
}

CLisp::Cell* CLisp::expr(Cell* self)
{
    assert(exprP(self));
    return self->expr.expr;
}

CLisp::Cell* CLisp::exprenv(Cell* self)
{
    assert(exprP(self));
    return self->expr.env;
}

CLisp::Cell* CLisp::fexpr(Cell* self)
{
    assert(fexprP(self));
    return self->expr.expr;
}

CLisp::Cell* CLisp::fexprenv(Cell* self)
{
    assert(fexprP(self));
    return self->expr.env;
}

CLisp::Cell* CLisp::car(Cell* self)
{
    assert(!self || consP(self));
    return self ? self->cons.a : 0;
}

CLisp::Cell* CLisp::cdr(Cell* self)
{
    assert(!self || consP(self));
    return self ? self->cons.d : 0;
}

CLisp::Cell* CLisp::rplaca(Cell* self, Cell* c)
{
    assert(!self || consP(self));
    return self ? self->cons.a = c : c;
}

CLisp::Cell* CLisp::rplacd(Cell* self, Cell* c)
{
    assert(!self || consP(self));
    return self ? self->cons.d = c : c;
}

CLisp::Cell* CLisp::caar(Cell* self)
{
    return car(car(self));
}

CLisp::Cell* CLisp::cadr(Cell* self)
{
    return car(cdr(self));
}

CLisp::Cell* CLisp::cdar(Cell* self)
{
    return cdr(car(self));
}

CLisp::Cell* CLisp::caddr(Cell* self)
{
    return car(cdr(cdr(self)));
}

CLisp::Cell* CLisp::cadar(Cell* self)
{
    return car(cdr(car(self)));
}

CLisp::Cell* CLisp::intern(const char* s)
{
    Cell* cell = nullptr;
    for (cell = interns; cell; cell = cdr(cell))
        if (!strcmp(symbol(car(cell)), s))
            return car(cell);
    cell = cell_sym(__strdup(s));
    mark(cell);
    interns = cell_cons(cell, interns);
    unmark(cell);
    return car(interns);
}

CLisp::Cell* CLisp::assq(Cell* key, Cell* list)
{
    for (; list; list = cdr(list))
        if (key == caar(list)) return car(list);
    return nullptr;
}

CLisp::Cell* CLisp::undefined(Cell* sym)
{
    std::cerr << "undefined symbol: " << symbol(sym) << std::endl;
    return nullptr;
}

CLisp::Cell* CLisp::evargs(Cell* self, Cell* env)
{
    if (self)
    {
        Cell *head, *tail;
        head = eval(car(self), env);
        if (head)
            mark(head);
        tail = evargs(cdr(self), env);
        if (tail)
            mark(tail);
        head = cell_cons(head, tail);
        unmark(head);
        return head;
    }
    return nullptr;
}

CLisp::Cell* CLisp::evbind(Cell* expr, Cell* args, Cell* env)
{
    Cell* cell = nullptr;
    mark(env);
    if (cell)
        mark(cell);
    if (consP(expr))
        for (; expr; expr = cdr(expr) , args = cdr(args))
        {
            cell = cell_cons(car(expr), car(args));
            env = cell_cons(cell, env);
        }
    else
    {
        cell = cell_cons(expr, args);
        env = cell_cons(cell, env);
    }
    unmark(env);
    return env;
}

CLisp::Cell* CLisp::evlist(Cell* expr, Cell* env)
{
    Cell* result = nullptr;
    mark(expr);
    mark(env);
    for (; expr; expr = cdr(expr))
    {
        result = eval(car(expr), env);
    }
    unmark(expr);
    if (result)
        mark(result);
    return result;
}

CLisp::Cell* CLisp::apply(Cell* fn, Cell* args, Cell* env)
{
    mark(fn);
    if (args)
        mark(args);
    mark(env);
    if (fn)
    {
        switch (fn->tag)
        {
        case Subr: return (this->*subr(fn))(evargs(args, env), env);
        case Fsubr: return (this->*fsubr(fn))(args, env);
        case Expr:
        {
            Cell* eva = evargs(args, env);
            if (eva)
                mark(eva);
            eva = evlist(cdr(expr(fn)), evbind(car(expr(fn)), eva, exprenv(fn)));
            unmark(fn);
            return eva;
        }
        case Fexpr:
        {
            Cell* eva = cell_cons(env, nullptr);
            if (eva)
                mark(eva);
            eva = cell_cons(args, eva);
            eva = evlist(cdr(fexpr(fn)), evbind(car(fexpr(fn)), eva, fexprenv(fn)));
            unmark(fn);
            return eva;
        }
        default: break;
        }
    }
    return args;
}

CLisp::Cell* CLisp::eval(Cell* expr, Cell* env)
{
    if (!expr) return nullptr;
    switch (expr->tag)
    {
    case Number: case String: case Subr: case Fsubr: case Expr:
        {
            return expr;
        }
    case Symbol:
        {
            Cell* cell = assq(expr, env);
            if (!cell) return undefined(expr);
            return cdr(cell);
        }
    case Cons:
        {
            Cell* cell;
            mark(expr);
            mark(env);
            cell = eval(car(expr), env);
            if (!cell) return nullptr;
            mark(cell);
            cell = apply(cell, cdr(expr), env);
            unmark(expr);
            return cell;
        }
    default:
        fatal("unknown tag");
    }
    return nullptr;
}

CLisp::Cell* CLisp::defineFsubr(Cell* args, Cell* env)
{
    Cell* cell = nullptr;
    mark(args);
    mark(env);
    if (args)
    {
        cell = cell_cons(car(args), nullptr);
        mark(cell);
        rplacd(globals, cell_cons(cell, cdr(globals)));
        cell = rplacd(cell, eval(cadr(args), env));
    }
    unmark(args);
    return cell;
}

CLisp::Cell* CLisp::setqFsubr(Cell* args, Cell* env)
{
    Cell *key, *value = nullptr;
    mark(args);
    mark(env);
    key = car(args);
    if (symbolP(key))
    {
        Cell* cell;
        value = eval(cadr(args), env);
        mark(value);
        cell = assq(key, env);
        if (!cell)
        {
            unmark(args);
            return undefined(key);
        }
        rplacd(cell, value);
    }
    unmark(args);
    return value;
}

CLisp::Cell* CLisp::lambdaFsubr(Cell* args, Cell* env)
{
    return cell_expr(args, env);
}

CLisp::Cell* CLisp::flambdaFsubr(Cell* args, Cell* env)
{
    return cell_fexpr(args, env);
}

CLisp::Cell* CLisp::letFsubr(Cell* args, Cell* env)
{
    Cell *cell;
    mark(args);
    mark(env);
    for (cell = car(args); cell; cell = cdr(cell))
    {
        auto tmp = eval(cadar(cell), env);
        mark(tmp);
        tmp = cell_cons(caar(cell), tmp);
        env = cell_cons(tmp, env);
    }
    unmark(args);
    return evlist(cdr(args), env);
}

CLisp::Cell* CLisp::orFsubr(Cell* args, Cell* env)
{
    Cell* value;
    mark(args);
    mark(env);
    for (value = nullptr; args && !value; args = cdr(args))
        value = eval(car(args), env);
    unmark(args);
    return value;
}

CLisp::Cell* CLisp::andFsubr(Cell* args, Cell* env)
{
    Cell* value;
    mark(args);
    mark(env);
    for (value = _S_t; args && value; args = cdr(args))
        value = eval(car(args), env);
    unmark(args);
    return value;
}

CLisp::Cell* CLisp::ifFsubr(Cell* args, Cell* env)
{
    Cell* cell;
    mark(args);
    mark(env);
    cell = (eval(car(args), env) ? eval(cadr(args), env) : eval(caddr(args), env));
    unmark(args);
    return cell;
}

CLisp::Cell* CLisp::whileFsubr(Cell* args, Cell* env)
{
    Cell* result = nullptr;
    mark(args);
    mark(env);
    while (eval(car(args), env))
    {
        result = evlist(cdr(args), env);
        if (result)
            mark(result);
    }
    unmark(args);
    return result;
}

CLisp::Cell* CLisp::mapArgs(Cell* args)
{
    Cell *arg, *tail;
    if (!args) return nullptr;
    arg = caar(args);
    mark(args);
    mark(arg);
    rplaca(args, cdar(args));
    tail = mapArgs(cdr(args));
    arg = cell_cons(arg, tail);
    unmark(args);
    return arg;
}

CLisp::Cell* CLisp::mapSubr(Cell* args, Cell* env)
{
    Cell *fn = car(args), *head, *tail, *cell = nullptr;
    mark(args);
    mark(env);
    mark(cell);
    tail = head = cell_cons(nullptr, nullptr);
    args = cdr(args);
    while (car(args))
    {
        cell = mapArgs(args);
        cell = apply(fn, cell, env);
        tail = rplacd(tail, cell_cons(cell, nullptr));
    }
    unmark(args);
    return cdr(head);
}

CLisp::Cell* CLisp::evalSubr(Cell* args, Cell* env)
{
    Cell* evalArg = car(args);
    Cell* evalEnv = cadr(args);
    mark(args);
    mark(env);
    evalArg = eval(evalArg, evalEnv ? evalEnv : env);
    unmark(args);
    return evalArg;
}

CLisp::Cell* CLisp::applySubr(Cell* args, Cell* env)
{
    return apply(car(args), cdr(args), env);
}

CLisp::Cell* CLisp::consSubr(Cell* args, Cell* env)
{
    return cell_cons(car(args), cadr(args));
}

CLisp::Cell* CLisp::rplacaSubr(Cell* args, Cell* env)
{
    return rplaca(car(args), cadr(args));
}

CLisp::Cell* CLisp::rplacdSubr(Cell* args, Cell* env)
{
    return rplacd(car(args), cadr(args));
}

CLisp::Cell* CLisp::carSubr(Cell* args, Cell* env)
{
    return caar(args);
}

CLisp::Cell* CLisp::cdrSubr(Cell* args, Cell* env)
{
    return cdar(args);
}

CLisp::Cell* CLisp::assqSubr(Cell* args, Cell* env)
{
    return assq(car(args), cadr(args));
}

CLisp::Cell* CLisp::printSubr(Cell* args, Cell* env)
{
    for (; args; args = cdr(args))
    {
        print(car(args), std::cout);
        if (cdr(args)) std::cout << ' ';
    }
    return nullptr;
}

CLisp::Cell* CLisp::printlnSubr(Cell* args, Cell* env)
{
    printSubr(args, env);
    std::cout << std::endl;
    return nullptr;
}

CLisp::Cell* CLisp::addSubr(Cell* args, Cell* env)
{
    if (cdr(args))
    {
        long n = number(car(args));
        for (args = cdr(args); args; args = cdr(args))
            n += number(car(args));
        return cell_num(n);
    }
    return cell_num(number(car(args)));
}

CLisp::Cell* CLisp::subtractSubr(Cell* args, Cell* env)
{
    if (cdr(args))
    {
        long n = number(car(args));
        for (args = cdr(args); args; args = cdr(args))
            n -= number(car(args));
        return cell_num(n);
    }
    return cell_num(number(car(args)));
}

CLisp::Cell* CLisp::multiplySubr(Cell* args, Cell* env)
{
    if (cdr(args))
    {
        long n = number(car(args));
        for (args = cdr(args); args; args = cdr(args))
            n *= number(car(args));
        return cell_num(n);
    }
    return cell_num(number(car(args)));
}

CLisp::Cell* CLisp::divideSubr(Cell* args, Cell* env)
{
    if (cdr(args))
    {
        long n = number(car(args));
        for (args = cdr(args); args; args = cdr(args))
            n /= number(car(args));
        return cell_num(n);
    }
    return cell_num(number(car(args)));
}

CLisp::Cell* CLisp::modulusSubr(Cell* args, Cell* env)
{
    if (cdr(args))
    {
        long n = number(car(args));
        for (args = cdr(args); args; args = cdr(args))
            n %= number(car(args));
        return cell_num(n);
    }
    return cell_num(number(car(args)));
}

CLisp::Cell* CLisp::lessSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) < number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::lessEqualSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) <= number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::equalSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) == number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::notEqualSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) != number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::greaterEqualSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) >= number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::greaterSubr(Cell* args, Cell* env)
{
    for (auto numbers = args; cdr(numbers); numbers = cdr(numbers))
        if (!(number(car(numbers)) > number(cadr(numbers))))
            return nullptr;
    return args;
}

CLisp::Cell* CLisp::run(std::string str)
{
    ANTLRInputStream input(str);
    MyScriptLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    MyScriptParser parser(&tokens);
    ParseTree *tree = parser.start();
    Cell *cell = visit(tree);
    if (cell)
        return repl(cell);
    return nullptr;
}

CLisp::Cell* CLisp::repl(Cell* expr)
{
    Cell *value = nullptr;
    mark(expr);
    while (expr)
    {
        auto tmp = cdr(expr);
        value = eval(car(expr), globals);
        expr = tmp;
    }
    unmark(expr);
    return value;
}

CLisp::Cell* CLisp::print(Cell* self, std::ostream& stream)
{
    if (!self) stream << "nil";
    else
    {
        switch (self->tag)
        {
        case Number:
            stream << number(self);
            break;
        case String:
            stream << string(self);
            break;
        case Symbol:
            stream << symbol(self);
            break;
        case Subr: 
            stream << "subr<" << self->number << ">";
            break;
        case Fsubr:
            stream << "fsubr<" << self->number << ">";
            break;
        case Expr: 
            stream << "(lambda " << print(expr(self), stream) << ")";
            break;
        case Fexpr: 
            stream << "(flambda " << print(fexpr(self), stream) << ")";
            break;
        case Cons:
        {
            stream << "(";
            while (self && consP(self))
            {
                print(car(self), stream);
                if ((self = cdr(self))) stream << ' ';
            }
            if (self)
            {
                stream << ". ";
                print(self, stream);
            }
            stream << ")";
            break;
        }
        default:
            stream << "?" << self;
            break;
        }
    }
    return self;
}

CLisp::Cell* CLisp::println(Cell* self, std::ostream& stream)
{
    print(self, stream);
    stream << std::endl;
    return self;
}

antlrcpp::Any CLisp::visitStart(MyScriptParser::StartContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any CLisp::visitExprs(MyScriptParser::ExprsContext* ctx)
{
    Cell *head, *tail;
    tail = head = cell_cons(nullptr, nullptr);
    mark(head);
    for (auto expr : ctx->expr())
    {
        Cell *cell = visit(expr);
        if (cell)
            mark(cell);
        tail = rplacd(tail, cell_cons(cell, nullptr));
    }
    head = cdr(head);
    if (head && symbolP(car(head))) {
        Cell *syntax = assq(car(head), cdr(syntaxTable));
        if (syntax) head = apply(cdr(syntax), cdr(head), globals);
        if (!head) {
            unmark(head);
            return nullptr;
        }
    }
    unmark(head);
    return head ? head : nullptr;
}

antlrcpp::Any CLisp::visitExpr(MyScriptParser::ExprContext* ctx)
{
    return visitChildren(ctx);
}

antlrcpp::Any CLisp::visitQuote(MyScriptParser::QuoteContext* ctx)
{
    Cell *cell = visitChildren(ctx);
    if (!cell)
        fatal("EOF in quoted literal");
    mark(cell);
    cell = cell_cons(cell, nullptr);
    cell = cell_cons(_S_quote, cell);
    unmark(cell);
    return cell;
}

antlrcpp::Any CLisp::visitList(MyScriptParser::ListContext* ctx)
{
    Cell *head, *tail;
    tail = head = cell_cons(nullptr, nullptr);
    mark(head);
    auto node = ctx->exprs();
    if (node)
        for (auto expr : node->expr())
        {
            Cell *cell = visit(expr);
            if (cell)
                mark(cell);
            tail = rplacd(tail, cell_cons(cell, nullptr));
        }
    head = cdr(head);
    if (head && symbolP(car(head))) {
        Cell *syntax = assq(car(head), cdr(syntaxTable));
        if (syntax) head = apply(cdr(syntax), cdr(head), globals);
        if (!head) {
            unmark(head);
            return nullptr;
        }
    }
    unmark(head);
    return head ? head : nullptr;
}

antlrcpp::Any CLisp::visitAtom(MyScriptParser::AtomContext* ctx)
{
    auto node = ctx->ID();
    if (node)
        return intern(node->getText().c_str());
    node = ctx->NUM();
    if (node)
        return cell_num(atoi(node->getText().c_str()));
    node = ctx->STRING();
    if (node)
    {
        auto str = node->getText();
        str.erase(str.length() - 1);
        return cell_str(str.c_str() + 1);
    }
    return nullptr;
}
