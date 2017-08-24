#pragma once
#include "clib_memory.h"
#include "MyScriptBaseVisitor.h"

// Refer: http://piumarta.com/software/lysp/lysp-1.1/lysp.c

class CLisp : public MyScriptBaseVisitor
{
public:
    CLisp();
    ~CLisp();

public:
    typedef enum
    {
        None,
        Number,
        String,
        Symbol,
        Cons,
        Subr,
        Fsubr,
        Expr,
        Fexpr
    } Tag;

    // 由于需要GC，那么所有的对象就表为Cell同一结构
    struct Cell
    {
        Tag tag;
        union {
            int number;
            const char *string;
            const char *symbol;
            struct {
                Cell *a;
                Cell *d;
            } cons;
            struct {
                Cell *expr;
                Cell *env;
            } expr;
            typedef Cell *(CLisp::*subr_t)(Cell *args, Cell *env);
            subr_t subr;
        };
    };
    using Subr_t = Cell *(CLisp::*)(Cell *args, Cell *env);

private:
    clib::memory::memory_pool<> gc;
    clib::memory::memory_pool<> strings;

    const char *__strdup(const char *);
    void mark(Cell *);
    void unmark(Cell *);
    static void fatal(const char *);

    void init();
    void init_fsubr(const char *, Subr_t);
    void init_subr(const char *, Subr_t);

    Cell *_S_t = nullptr;
    Cell *_S_quote = nullptr;
    Cell *_S_qquote = nullptr;
    Cell *_S_uquote = nullptr;
    Cell *_S_uquotes = nullptr;
    Cell *syntaxTable = nullptr;
    Cell* interns = nullptr;
    Cell *globals = nullptr;
    using apply_t = void(*)(void);
    using arglist_t = union { char *argp; } *;

    Cell* cell();
    Cell* cell_num(int n);
    Cell* cell_str(const char* s);
    Cell* cell_sym(const char* s);
    Cell* cell_cons(Cell* a, Cell* d);
    Cell* cell_subr(Subr_t fn);
    Cell* cell_fsubr(Subr_t fn);
    Cell* cell_expr(Cell* x, Cell* e);
    Cell* cell_fexpr(Cell* x, Cell* e);
    int nilP(Cell* self);
    int numberP(Cell* self);
    int stringP(Cell* self);
    int symbolP(Cell* self);
    int consP(Cell* self);
    int subrP(Cell* self);
    int fsubrP(Cell* self);
    int exprP(Cell* self);
    int fexprP(Cell* self);
    int number(Cell* self);
    const char* string(Cell* self);
    const char* symbol(Cell* self);
    Subr_t subr(Cell* self);
    Subr_t fsubr(Cell* self);
    Cell* expr(Cell* self);
    Cell* exprenv(Cell* self);
    Cell* fexpr(Cell* self);
    Cell* fexprenv(Cell* self);
    Cell* car(Cell* self);
    Cell* cdr(Cell* self);
    Cell* rplaca(Cell* self, Cell* c);
    Cell* rplacd(Cell* self, Cell* c);
    Cell* caar(Cell* self);
    Cell* cadr(Cell* self);
    Cell* cdar(Cell* self);
    Cell* caddr(Cell* self);
    Cell* cadar(Cell* self);
    Cell* intern(const char* s);
    Cell* assq(Cell* key, Cell* list);
    Cell* undefined(Cell* sym);
    Cell* evargs(Cell* self, Cell* env);
    Cell* evbind(Cell* expr, Cell* args, Cell* env);
    Cell* evlist(Cell* expr, Cell* env);
    Cell* apply(Cell* fn, Cell* args, Cell* env);
    Cell* eval(Cell* expr, Cell* env);
    Cell* defineFsubr(Cell* args, Cell* env);
    Cell* setqFsubr(Cell* args, Cell* env);
    Cell* lambdaFsubr(Cell* args, Cell* env);
    Cell* flambdaFsubr(Cell* args, Cell* env);
    Cell* letFsubr(Cell* args, Cell* env);
    Cell* orFsubr(Cell* args, Cell* env);
    Cell* andFsubr(Cell* args, Cell* env);
    Cell* ifFsubr(Cell* args, Cell* env);
    Cell* whileFsubr(Cell* args, Cell* env);
    Cell* mapArgs(Cell* args);
    Cell* mapSubr(Cell* args, Cell* env);
    Cell* evalSubr(Cell* args, Cell* env);
    Cell* applySubr(Cell* args, Cell* env);
    Cell* consSubr(Cell* args, Cell* env);
    Cell* rplacaSubr(Cell* args, Cell* env);
    Cell* rplacdSubr(Cell* args, Cell* env);
    Cell* carSubr(Cell* args, Cell* env);
    Cell* cdrSubr(Cell* args, Cell* env);
    Cell* assqSubr(Cell* args, Cell* env);
    Cell* printSubr(Cell* args, Cell* env);
    Cell* printlnSubr(Cell* args, Cell* env);
    Cell* addSubr(Cell* args, Cell* env);
    Cell* subtractSubr(Cell* args, Cell* env);
    Cell* multiplySubr(Cell* args, Cell* env);
    Cell* divideSubr(Cell* args, Cell* env);
    Cell* modulusSubr(Cell* args, Cell* env);
    Cell* lessSubr(Cell* args, Cell* env);
    Cell* lessEqualSubr(Cell* args, Cell* env);
    Cell* equalSubr(Cell* args, Cell* env);
    Cell* notEqualSubr(Cell* args, Cell* env);
    Cell* greaterEqualSubr(Cell* args, Cell* env);
    Cell* greaterSubr(Cell* args, Cell* env);

public:
    Cell* run(std::string str);
    Cell* repl(Cell* expr);
    Cell* print(Cell* self, std::ostream& stream);
    Cell* println(Cell* self, std::ostream& stream);

    antlrcpp::Any visitStart(MyScriptParser::StartContext* ctx) override;
    antlrcpp::Any visitExprs(MyScriptParser::ExprsContext* ctx) override;
    antlrcpp::Any visitExpr(MyScriptParser::ExprContext* ctx) override;
    antlrcpp::Any visitQuote(MyScriptParser::QuoteContext* ctx) override;
    antlrcpp::Any visitList(MyScriptParser::ListContext* ctx) override;
    antlrcpp::Any visitAtom(MyScriptParser::AtomContext* ctx) override;
};

