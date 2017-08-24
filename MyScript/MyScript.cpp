// MyScript.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include "CLisp.h"

using namespace std;

auto lib = R"(
(print "Init... ")
(define nil ())
(define quote     (flambda (form) (car form)))
(define list      (lambda args args))
(define dolist    (lambda args (let () args)))
(define caar      (lambda (x) (car (car x))))
(define cadr      (lambda (x) (car (cdr x))))
(define cadr      (lambda (x) (car (cdr x))))
(define cdar      (lambda (x) (cdr (car x))))
(define cddr      (lambda (x) (cdr (cdr x))))
(define cadar     (lambda (x) (car (cdr (car x)))))
(define caddar    (lambda (x) (car (cdr (cdr (car x))))))
(define global-environment
  (let ((globals ((flambda (args env) env))))
    (lambda () globals)))
(define double (lambda (x) (+ x x)))
(define make-counter (lambda (n) (lambda () (setq n (+ n 1)))))
(setq *syntax-table*
  (cons (cons 'for
    (flambda (form)
      (list 'let (list (list (caar form) (cadar form)))
        (list 'while (list '<= (caar form) (caddar form))
          (cadr form)
          (list 'setq (caar form) (list '+ 1 (caar form)))))))
  *syntax-table*))
(println "Done")
)";
auto test = R"(
(define print-line (lambda (a b n)
  (for (i 1 (- n 1)) (let () (print a) (print b)))
  (println a)
))
(define test (lambda ()
  (dolist
    (print-line "-" " " 20)
    (println "Hello world!")
    (println "Refer: http://piumarta.com/software/lysp/lysp-1.1/lysp.c")
    (println "Using: ANTLR 4.7")
    (println "Author: bajdcc")
    (print-line "-" " " 20)
    )))
)";

int main()
{
    CLisp lisp;
    auto value = lisp.run(lib);
    value = lisp.run(test);
    for (;;)
    {
        cout << ">> ";
        string in;
        getline(cin, in);
        if (in.empty())
            break;
        value = lisp.run(in);
        //if (value)
        //    lisp.println(value, std::cout);
    }
    return 0;
}

