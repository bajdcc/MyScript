# LISP解释器

```lisp
(define introduction (lambda ()
  (let ()
    (println "Hello world!")
    (println "Refer: http://piumarta.com/software/lysp/lysp-1.1/lysp.c")
    (println "Using: ANTLR 4.7")
    (println "Author: bajdcc"))))
```

## 介绍

C++实现的LISP解释器，语法分析用ANTLR完成，解释器参考的lysp代码。

## 实现

- quote
- list
- caar, cddr, ...
- lambda
- define
- eval, apply
- cons
- let
- while, if, for
- assq
- map
- print
- 四则运算
- 等式判断

## 进度

程序可以运行。分两部分ANTLR静态库和LISP解释器。

分析原作者代码中。。。

### 重点

1. GC(抄自自己的clib库)
2. Cell结构
3. Env
4. List