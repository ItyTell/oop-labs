#include<iostream>
#include<deque>
#include<string>
#define _USE_MATH_DEFINES
#include<cmath>
#include<complex>

using namespace std;

int plusic(int a, int b){return a + b;}
int minusic(int a, int b){return a - b;}
int max(int a, int b){return (a > b ? a : b);}

typedef complex<double> base;
 
void fft (deque<base> & a, bool invert) {

    double pi = 3.14159265358979323846;


	int n = (int) a.size();
	if (n == 1)  return;
 
	deque<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);
 
	double ang = pi * 2 / n * (invert ? -1 : 1);
	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

void multiply (const deque<int> & a, const deque<int> & b, deque<int> & res) {
	deque<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size())) { n *= 2;}
    n *= 2;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i){
		fa[i] *= fb[i];
    }
	fft (fa, true);
 
	for (size_t i=0; i < n; ++i)
		res.push_back(int (fa[i].real() + 0.5));

    int k = 2 * max(a.size(), b.size()) - min(a.size(), b.size());
        
    for (int i = 0; i < k; i++){res.pop_back();}

}

struct Number{

    //friend struct duon;
    

    Number(bool c);

    Number();

    Number(deque<int> n, bool c);

    ~Number();

    Number(deque<int> a, bool c, int p);

    Number(deque<int> n);

    Number(Number const& a);

    Number & operator = (Number const& a);

    void format();

    deque<int> getN();

    bool getC();

    Number module();

    bool operator > (Number& a);
    bool operator < (Number& a);

    Number operator - ();

    Number operator + (Number& a);

    Number operator - (Number& a);

    void operator += (Number& a);

    void operator -= (Number& a);

    Number operator * (int a);

    Number operator / (int a);

    int operator % (int a);

    Number operator * (Number& a);

    Number karatsuba(Number& a);

    Number toom_cook(Number& a);

    Number shtrassen(Number& a);

    long long tolong();


    private:
        deque<int> n;
        bool c;

        Number _operation(Number& a, int (*func)(int, int));

        Number _plus(Number& a);

        Number _minus(Number& a);

        void _form_digit();

        void _del0();

        void _0add(int k);

        void _mult_by_10(int k = 1);

        void _straight(Number& a, int k = 1);
};

ostream & operator << (ostream & out, Number a);

Number::Number():c(true){n = {0};}

Number::Number(bool c):c(c){n = {0};}

Number::Number(deque<int> n, bool c):n(n), c(c) {this->format();}

Number::Number(deque<int> n):n(n), c(true) {this->format();}

Number::~Number(){n.clear();}

Number::Number(deque<int> a, bool c, int p){
    this->c = c;
    n = {0};
    size_t size = a.size();
    long long k = 2;
    n[0] += (long long) a[0] * k;
    for (int t = 1; t < size; t++){
        n[0] += k * a[t];
        k *= 2;
        this-> format();
    }
    this->format();
}

Number::Number(Number const& a):n(a.n), c(a.c){}

Number & Number::operator = (Number const& a){
    n = a.n;
    c = a.c;
    this->format();
    return *this;
}

void Number::format(){this->_form_digit(); this->_del0();}

deque<int> Number::getN(){return n;}

bool Number::getC(){return c;}

Number Number::module(){
    Number b = *this;
    b.c = true;
    return b;
}

bool Number::operator > (Number& a){
    this->_straight(a);
    size_t size = n.size();
    for (size_t i = 0; i < size; i++){
        if (n[i] > a.n[i]){this->format(); a.format();return 1;}
        else if (n[i] < a.n[i]){this->format(); a.format();return 0;}
    }
    this->format(); a.format();
    return 0;
}
bool Number::operator < (Number& a){
    this->_straight(a);
    size_t size = n.size();
    for (size_t i = 0; i < size; i++){
        if (n[i] < a.n[i]){this->format(); a.format();return 1;}
        else if (n[i] > a.n[i]){this->format(); a.format();return 0;}
    }
    this->format(); a.format();
    return 0;
}

Number Number::operator - (){
    Number b = *this;
    b.c = !c;
    return b;
}

Number Number::operator + (Number& a){
    if (this == &a){Number p = a * 2; return p;}
    if (c == a.c){Number b = this->_plus(a);return b;}
    else{
        if (a > *this){Number p = a._minus(*this); return p;}
        else {Number p = this->_minus(a);return p;}
    }
}

Number Number::operator - (Number& a){
    if (c != a.c){Number b = this->_plus(a);return b;}
    else{
        if (a > *this){Number p = (-a)._minus(*this); return p;}
        else {Number p = this->_minus(a);return p;}
    }
}

void Number::operator += (Number& a){Number C = *this + a; *this = C;}

void Number::operator -= (Number& a){Number C = *this - a; *this = C;}

Number Number::operator * (int a){
    size_t size = n.size();
    Number num = *this;
    for (size_t i = 0; i < size; i++)
    {num.n[i] *= a;}
    num.format();
    return num;
}

Number Number::operator / (int a){
    size_t size = n.size();
    Number num = *this;
    int carry = 0, tmp;
    for (size_t i = 0; i < size; i++)
    {tmp = 10 * ((num.n[i] + carry) % a); num.n[i] = (num.n[i] + carry) / a; carry = tmp;}
    num.format();
    return num;
}

int Number::operator % (int a){
    size_t size = n.size();
    Number num = *this;
    int carry = 0, tmp;
    for (size_t i = 0; i < size; i++)
    {tmp = 10 * ((num.n[i] + carry) % a); carry = tmp;}
    return carry / 10;
}

Number Number::operator * (Number& a){
    size_t size = a.n.size();
    if (!size || !n.size()){Number z; return z;}
    Number r = *this;
    Number num = r * a.n[size - 1];
    Number num1;
    for (int i = 2; i <= size; i++){
        r._mult_by_10();
        num1 = (r * a.n[size - i]);
        num += num1;
    }
    return num;
}


Number Number::karatsuba(Number& a){
    size_t size = n.size();
    deque<int>c = {}, d = {};
    if (size == 0 || a.n.size() == 0){Number C(); return C;}
    if (size == 1 || a.n.size() == 1){return (*this * a);}
    this->_straight(a, 0);
    size = n.size();
    int i, m = 0;
    for (i = 0;i < size / 2; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
    Number A(c), C(d);c = {}; d = {};
    for (i = size / 2; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
    Number B(c), D(d);
    Number AC = A.karatsuba(C);
    Number BD = B.karatsuba(D);
           
    Number E = (A + B);
    Number K = (C + D);
    E = E.karatsuba(K);
    E = (E - AC) - BD;  
    AC._mult_by_10(2 * m);
    E._mult_by_10(m);
    return ((AC + E) + BD);

}

Number Number::toom_cook(Number& a){
    
    size_t size = n.size();
    deque<int>c = {}, d = {};

    if (size == 0 || a.n.size() == 0){c.push_back(0); Number C(c); return C;}
    if (size < 3 || a.n.size() < 3){return (*this * a);}

    this->_straight(a, 3 - (max(size, a.n.size()) % 3));
    size = n.size();
    int i, m = 0;

    for (i = 0;i < size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
    Number A2(c), B2(d);c.clear(); d.clear();
        
    for (i = size / 3; i < 2 * size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
    Number A1(c), B1(d);c.clear(); d.clear();

    for (i = 2 * size / 3; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
    Number A0(c), B0(d);c.clear(); d.clear();

    Number A_m2 = A2 * 4; Number A12 = A1 * 2; A_m2 = A_m2 - A12; A_m2= A_m2 + A0;//Number A_m2 = A2 * 4 - A1 * 2 + A0;
    Number B_m2 = B2 * 4; Number B12 = B1 * 2; B_m2 = B_m2 - B12; B_m2= B_m2 + B0;//Number B_m2 = B2 * 4 - B1 * 2 + A0;

    Number A_m1 = A2 - A1 + A0;
    Number B_m1 = B2 - B1 + B0;

    Number A_0 = A0;
    Number B_0 = B0;

    Number A_1 = A2 + A1  + A0;
    Number B_1 = B2 + B1  + B0;

    Number A_2 = A2 * 4; Number A22 = A1 * 2; A_2 = A_2 + A22; A_2= A_2 + A0;//Number A_2 = A2 * 4 + A1 * 2 + A0;
    Number B_2 = B2 * 4; Number B22 = B1 * 2; B_2 = B_2 + B22; B_2= B_2 + B0;//Number B_2 = B2 * 4 + B1 * 2 + B0;

    Number C_m2 = A_m2*B_m2;
    Number C_m1 = A_m1*B_m1;

    Number k5 = A_0*B_0;

    Number C_1 = A_1*B_1;
    Number C_2 = A_2*B_2;

    C_m2 -= k5;
    C_m1 -= k5;
    C_1 -= k5;
    C_2 -= k5;

    Number D1 = C_1 + C_m1; // 2a + 2c
        
    Number D2 = C_2 + C_m2; // 32a + 8c
        
    Number D3 = C_1 - C_m1; // 2b + 2d

    Number D4 = C_2 - C_m2; // 16b + 4d

    D1 = D1 / 2; // a + c

    D2 = D2 / 8; // 4a + c

    D3 = D3 / 2; // b + d

    D4 = D4 / 4; // 4b + d

    Number k1 = D2 - D1; // 3a
    k1 = k1 / 3; // a

    Number k3 = D1 - k1; //c

    Number k2 = D4 - D3; // 3b
    k2 = k2 / 3; // b

    Number k4 = D3 - k2; // d


    k1._mult_by_10(4*m);
    k2._mult_by_10(3*m);
    k3._mult_by_10(2*m);
    k4._mult_by_10(m);

    Number k = k1 + k2;
    k += k3; k += k4; k+= k5;
        
    return k;
}

Number Number::shtrassen(Number& a){

    size_t size = n.size();

    if (size == 0 || a.n.size() == 0){Number C(); return C;}

        
    deque<int> new_n = {};

    multiply(n, a.n, new_n);

    size = new_n.size();

    Number b(new_n);

    return b;
}

long long Number::tolong(){
    int i;
    double sum = 0, k = 1;
    size_t size = n.size();
    for (i = 0; i < size; i++){
        sum += k * n[size - 1 - i];
        k *= 10;
    }
    if (!c){sum *= -1;}
    return sum;
}

int main(){
    return 0;
}