#pragma once
#include<iostream>
#include<deque>
#include<string>
#define _USE_MATH_DEFINES
#include<cmath>
#include<complex>

using namespace std;

typedef complex<double> base;

int plusic(int a, int b);
int minusic(int a, int b);
int max(int a, int b);

struct Number{

    Number(bool c = true, int q = 0);
    Number(deque<int> n, bool c = true, int q = 0);
    Number(deque<int> n, int mod, bool c = true, int q = 0);
    Number(double k);

    ~Number();

    Number(Number const& a);



    Number & operator = (Number const& a);

    const Number operator + ();

    const Number operator - ();


    void operator += (const Number& a);

    void operator -= (const Number& a);

    void operator ++ (int);



    const Number operator / (int a);

    int operator % (int a);


    void format();

    void _straight(Number& a, int k = 1);

    deque<int> getN() const;

    bool getC() const;

    int get_mod() const;

    int get_q() const;

    void set_q(size_t new_q);

    void add0(int k = 1);

    const Number _plus(const Number& a);

    const Number _minus(const Number& a);

    Number change_mod2();
    Number change_mod10();

    Number module();

    Number karatsuba(const Number& a, bool first_iteration = 1);

    Number toom_cook(const Number& a, bool first_iteration = 1);

    Number shanhage(const Number& a);

    Number shtrassen(const Number& a);

    Number cook();

    Number delit_cook(const Number& a);



    private:
        deque<int> n;
        bool c;
        int mod = 10;
        int q; 
        void _form_digit();
        void _del0();
        void _0add(int k);
        

        const Number _operation(const Number& a, int (*func)(int, int));

};

bool operator > (const Number& a, const Number& b);
    
bool operator < (const Number& a, const Number& b);

bool operator == (const Number& a, const Number& b);

const Number operator * (const Number b, int a);

const Number operator * ( int a ,const Number b);

const Number operator - ( const Number b, int a );

const Number operator + ( const Number b, int a );

const Number operator + (const Number& a, const Number& b);

const Number operator - (const Number& a, const Number& b);

const Number operator * (const Number& a, const Number& b);

const Number operator % (const Number& a, const Number& b);


ostream & operator << (ostream & out, Number a);

void fft (deque<base> & a, bool invert);
void multiply (const deque<int> & a, const deque<int> & b, deque<int> & res);
