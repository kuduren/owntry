#include <iostream>
#include <tuple>
#ifndef SCHEME_H
#define SCHEME_H


//数值模板
#define num(A) num<A>
template<auto a>
struct num {
    static const  decltype(a) value = a;
    using type = num;
};
template<char... c>
struct Symbol {
    static constexpr char const value[sizeof...(c)+1] = {c...,'\0'};
    using type = Symbol;
};
//nil类型
struct nil {
    using type = nil;
    static constexpr char const  value[5] = "nil";
};


//分支判断
//If(A)Then(do thing1)Else(do thing2)
#define If(A)       If<A
#define Then(do1)    ,do1
#define Else(do2)    ,do2>::type
template<bool,typename Then,typename Else>
struct If ;
template<typename Then,typename Else>
struct If<true,Then,Else> {
    using type = Then;
};
template<typename Then,typename Else>
struct If<false,Then,Else> {
    using type = Else;
};

//类的类型是否相同
#define is_same_type(A,B) is_same_type<A,B>::value
template<typename T,typename U>
struct is_same_type {
    static const bool value = false;
};
template<typename T>
struct is_same_type<T,T> {
    static const bool value = true;
};

//序队
#define cons(A,B)  cons<A,B>
template<typename T,typename U>
struct cons {
    using car_type = T;
    using cdr_type = U;
    using type = cons;
};
#define car(A) car<A>
template<typename T>
using car = typename T::car_type;
#define cdr(A) cdr<A>
template<typename T>
using cdr = typename T::cdr_type;

//list模板
template<typename... Arg>
struct list ;
template<typename T,typename... Arg>
struct list<T,Arg...> {
    using car_type = T;
    using cdr_type = list<Arg...>;
    using type = cons(car_type,cdr_type);
};
template<typename T>
struct list<T> {
    using car_type = T;
    using cdr_type = nil;
    using type = cons(T,nil);
};
template<>
struct list<> {
    using car_type = nil;
    using cdr_type = nil;
    using type = nil;
};
template<typename T>
constexpr bool is_nil= is_same_type(typename T::type,nil);


#endif
