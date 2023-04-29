#include "Number.hpp"

int plusic(int a, int b){return a + b;}
int minusic(int a, int b){return a - b;}
int max(int a, int b){return (a > b ? a : b);}


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



}




ostream & operator << (ostream & out, Number a){
    if (!a.getC()){cout << "-";};
    deque<int> n = a.getN();
    size_t size = n.size();
    int q = a.get_q();
    for (size_t i = 0; i <size; i++){if ( i == size - q){cout << ",";} cout << n[i];}
    return out;
}


Number::Number(bool c, int q):c(c), q(q){n = {0};}
Number::Number(deque<int> n, bool c, int q):n(n), c(c), q(q) {this->format();}
Number::Number(deque<int> n, int mod, bool c, int q):n(n), c(c), mod(mod), q(q){this->format();}
Number::Number(double k){
    int i;
    for (i = 1; i < k; i *= 10){}
    i /= 10;
    deque<int>deq;int r = 0;
    while (k - round(k) < 0.0001){
        k *= 10;
        r += 1;
        i *= 10;
    }
    int p = k;
    while (p != 0){
        deq.push_back(p / i);
        p %= i;
        i /= 10;
    }
    this->n = deq;
    this->c = true;
    this->q =  r;
}

Number::~Number(){n.clear();}

Number::Number(Number const& a):mod(a.mod),n(a.n), c(a.c), q(a.q){}




Number & Number::operator = (Number const& a){
    n = a.n;
    c = a.c;
    mod = a.mod;
    q = a.q;
    this->format();
    return *this;
}

bool operator > (const Number& a, const Number& b){
    if (b.getC() > a.getC()){return 1;}
    else if (a.getC() > b.getC()){return 0;}
    Number e = a;
    Number d = b;
    d._straight(e);
    deque<int> nd = d.getN();
    deque<int> ne = e.getN();

    size_t size = nd.size();
    for (size_t i = 0; i < size; i++){
        if (ne[i] > nd[i]){if (!(d.getC() || e.getC())){return 0;} return 1;}
        else if (ne[i] < nd[i]){if (!d.getC() && !e.getC()){return 1;} return 0;}
    }
    return 0;
}

bool operator == (const Number& a, const Number& b){
    if(a.getC() != b.getC()){return 0;}
    Number e = a;
    Number d = b;
    d._straight(e);
    deque<int> nd = d.getN();
    deque<int> ne = e.getN();
    size_t size = nd.size();
    for (size_t i = 0; i < size; i++){
        if (nd[i] != ne[i]){return 0;}
    }
    return 1;
}

bool operator < (const Number& a, const Number& b){
    return (b > a);
}

const Number Number::operator + (){
    Number a = *this;
    return a;
}

const Number Number::operator - (){
    Number b = *this;
    b.c = !c;
    return b;
}


const Number operator * (const Number b, int a){
    bool new_c = b.getC();
    if (a < 0){new_c = !b.getC();a = -a;}
    deque<int>res = b.getN();
    size_t size = res.size();
    for (size_t i = 0; i < size; i++){res[i] *= a;}
    Number num(res, b.get_mod() ,new_c, b.get_q());
    num.format();
    return num;
}

const Number operator * ( int a ,const Number b){
    return b * a;
}

const Number operator - ( const Number b, int a ){
    deque<int>x = b.getN();
    if (b.getC()){
        x[x.size() - 1 - b.get_q()] -= a;
    }
    else {x[x.size() - 1 - b.get_q()] += a;}
    Number X(x, b.get_mod(), b.getC(), b.get_q());
    return X;
}

const Number operator + ( const Number b, int a ){
    deque<int>x = b.getN();
    if (b.getC()){
        x[x.size() - 1 - b.get_q()] += a;
    }
    else {x[x.size() - 1 - b.get_q()] -= a;}
    Number X(x, b.get_mod(), b.getC(), b.get_q());
    return X;
}

void Number:: operator ++(int){
    this->n[n.size() - 1 - q] += 1;
    this->format();
}

const Number Number::operator / (int a){
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
    for (size_t i = 0; i < size - q; i++)
    {tmp = 10 * ((num.n[i] + carry) % a); carry = tmp;}
    return carry / 10;
}

const Number operator + (const Number& a, const Number& b){
    Number z = a;
    Number x = b;
    if (x.getC() == z.getC()){Number b = x._plus(z);return b;}
    else{
        if (z.module() > x.module()){Number p = z._minus(x); return p;}
        else {Number p = x._minus(z);return p;}
    }
}

const Number operator - (const Number& a, const Number& b){
    Number z = a;
    Number x = b;
    if (z.getC() != x.getC()){Number b = x._plus(z);return b;}
    else{
        if (z.module() > x.module()){Number p = z._minus(x); return p;}
        else {x = -x;Number p = x._minus(z);return p;}
    }
}

void Number::operator += (const Number& a){Number C = *this + a; *this = C;}

void Number::operator -= (const Number& a){Number C = *this - a; *this = C;}

const Number operator * (const Number& a, const Number& b){
    Number copy1(a), copy2(b);
    deque<int> deq1 = a.getN(), deq2 = b.getN();

    size_t size = deq1.size();
    if (!size || !deq2.size()){Number z; return z;}
    Number r = a;
    Number num = r * deq2[size - 1];
    Number num1;
    for (int i = 2; i <= size; i++){
        r.add0();
        num1 = (r * deq2[size - i]);
        num += num1;
    }
    if (a.getC() == b.getC()){num = num.module();}
    else {num = -num.module();}
    num.set_q(b.get_q() + a.get_q());
    return num;
}


const Number operator % (const Number& a, const Number& b){
    if (!b.getC()){cout << "ERROR"; Number zero; return zero;}
    Number num1(a), num2(b);
    while (!num1.getC()){num1 = num1 + num2;}
    while (num1 > num2){num1 = num1 - num2;}
    return num1;
}

void Number::format(){this->_form_digit(); this->_del0();if (n.size() == 0){n.push_back(0); c = true;}}

void Number::_straight(Number& a, int k){
    int d = n.size() - a.n.size();
    if (d < 0){a._0add(k);this->_0add(k - d);}
    else{      this->_0add(k);    a._0add(k + d);}
}

Number Number::change_mod2(){
    size_t size = n.size();
    int k = n[size - 1];
    int r = 5;
    deque<int> deq;
    for (int i = 2; i <= size; i++){
        deq.push_front(k % 2);
        k /= 2;
        k += r * n[size - i];
        r *= 5;
    }
    while (k){deq.push_front(k % 2); k /= 2;}
    Number a(deq, c);
    a.mod = 2;
    return a;
}

Number Number::change_mod10(){
    long long s = 0;
    long long k = 1;
    size_t size = n.size();
    for (int i = 1; i <= size; i++){
        s += k * n[size - i];
        k *= 2;
    }
    deque<int>deq;
    while (s){
        deq.push_front(s % 10);
        s /= 10;
    }
    Number A(deq, 10, c, q);
    return A;
}

deque<int> Number::getN() const {return n;}
bool Number::getC() const {return c;}
int Number::get_mod() const {return mod;}
int Number::get_q() const {return q;}

void Number::set_q(size_t new_q){q = new_q;}


Number Number::module(){
    Number b = *this;
    b.c = true;
    return b;
}


void Number::_form_digit(){
            size_t size = n.size();
            for (size_t i = 1; i < size; i++){
                while (n[size - i] > mod - 1){n[size - i - 1] += 1;n[size - i] -= mod;}
                while (n[size - i] < 0){n[size - i - 1] -= 1; n[size - i] += mod;}
            }
            while (n[0] > mod){n.push_front(n[0] / mod);n[1] %= mod;}
        }

void Number::_del0(){int j = 0; while((n[j] == 0) && (n.size() > 0)){n.pop_front();}}

void Number::_0add(int k){for (int i = 0; i < k; i++){n.push_front(0);}}

void Number::add0(int k){for (int i = 0; i < k; i++){n.push_back(0);}}

const Number Number::_operation(const Number& a, int (*func)(int, int)){
    Number z(*this), x(a);
    for (int f = 0; f < z.q - x.q; f++){x.add0();}
    for (int f = 0; f < x.q - z.q; f++){z.add0();}

    z._straight(x);
    deque<int> new_n;
    for (int i = 0; i < z.n.size(); i++){
        new_n.push_back(func(z.n[i], x.n[i]));
    }
    Number res(new_n, mod ,c, max(z.q, x.q));
    return res;
}

const Number Number::_plus(const Number& a){return this->_operation(a, plusic);}

const Number Number::_minus(const Number& a){return this->_operation(a, minusic);}




//methods

Number Number::karatsuba(const Number& a, bool first_iteration){
    size_t size = n.size();
    deque<int>c = {}, d = {};
    if (size == 0 || a.n.size() == 0){c.push_back(0); Number C(c); return C;}
    if (size == 1 || a.n.size() == 1){return (*this * a);}
    Number x(*this), y(a);
    x._straight(y, 0);
    size = n.size();
    int i, m = 0;
    for (i = 0;i < size / 2; i++){c.push_back(x.n[i]);d.push_back(y.n[i]);}
    Number A(c), C(d);c = {}; d = {};
    for (i = size / 2; i < size; i++){c.push_back(x.n[i]);d.push_back(y.n[i]);m++;}
    Number B(c), D(d);

    Number AC = A.karatsuba(C, 0);
    Number BD = B.karatsuba(D, 0);
    Number E = (A + B) * (C + D) - AC - BD;
    AC.add0(2 * m);
    E.add0(m);
    Number RESULT = (AC + E + BD);
    if (first_iteration){
        if (c == a.c){RESULT.c = true;}
        else {RESULT.c = false;}
    }
    return RESULT;

}

Number Number::toom_cook(const Number& b, bool first_iteration){
    
    size_t size = n.size();
    deque<int>deq1 = {}, deq2 = {};
    Number a(b), e(*this);

    if (size == 0 || a.n.size() == 0){deq1.push_back(0); Number C(deq1); return C;}
    if (size < 3 || a.n.size() < 3){return (b * a);}

    e._straight(a, 3 - (max(size, a.n.size()) % 3));
    size = a.n.size();
    int i, m = 0;

    for (i = 0;i < size / 3; i++){deq1.push_back(e.n[i]);deq2.push_back(a.n[i]);}
    Number A2(deq1), B2(deq2);deq1.clear(); deq2.clear();
    
    for (i = size / 3; i < 2 * size / 3; i++){deq1.push_back(e.n[i]);deq2.push_back(a.n[i]);m++;}
    Number A1(deq1), B1(deq2);deq1.clear(); deq2.clear();

    for (i = 2 * size / 3; i < size; i++){deq1.push_back(e.n[i]);deq2.push_back(a.n[i]);}
    Number A0(deq1), B0(deq2);deq1.clear(); deq2.clear();

    Number A_m2 = A2 * 4 - A1 * 2 + A0;
    Number B_m2 = B2 * 4 - B1 * 2 + A0;

    Number A_m1 = A2 - A1 + A0;
    Number B_m1 = B2 - B1 + B0;

    Number A_0 = A0;
    Number B_0 = B0;

    Number A_1 = A2 + A1  + A0;
    Number B_1 = B2 + B1  + B0;

    Number A_2 = A2 * 4 + A1 * 2 + A0;
    Number B_2 = B2 * 4 + B1 * 2 + B0;

    Number C_m2 = A_m2 * B_m2;
    Number C_m1 = A_m1 * B_m1;

    Number k5 = A_0 * B_0;

    Number C_1 = A_1 * B_1;
    Number C_2 = A_2 * B_2;

    C_m2 = C_m2 - k5;
    C_m1 = C_m1 - k5;
    C_1 = C_1 - k5;
    C_2 = C_2 - k5;

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


    k1.add0(4*m);
    k2.add0(3*m);
    k3.add0(2*m);
    k4.add0(m);

    Number RESULT = k1 + k2 + k3 + k4 + k5;
    
    if (first_iteration){
        if (c == b.c){RESULT.c = true;}
        else {RESULT.c = false;}
    }
    return RESULT;
}

Number Number::shanhage(const Number& a){

    Number duon1(*this), duon2(a);
    duon1 = duon1.change_mod2(); duon2 = duon2.change_mod2();
    duon1._straight(duon2);
    size_t size = duon1.n.size();
    int pk = 1;
    int qk = 26;
    while (pk < size){
        qk = 3 * qk - 1;
        pk = 18 * qk + 8;
    }
    duon1._0add(pk - size);
    duon2._0add(pk - size);

    deque<int> deq = {1}; Number r(deq); r = r.change_mod2();
    r.add0(6 * qk - 1);

    Number m1 = r - 1, m2 = r * 4 - 1, m3 = 8 * r - 1, m4 = 16 * r - 1, m5 = 64 * r - 1, m6 = 256 * r - 1;
    Number  u1 = duon1 % m1, u2 = duon1 % m2, u3 = duon1 % m3, u4 = duon1 % m4, u5 = duon1 % m5, u6 = duon1 % m6;
    Number  v1 = duon2 % m1, v2 = duon2 % m2, v3 = duon2 % m3, v4 = duon2 % m4, v5 = duon2 % m5, v6 = duon2 % m6;
    Number  vu1 = v1 * u1, vu2 = v2 * u2, vu3 = v3 * u3, vu4 = v4 * u4, vu5 = v5 * u5, vu6 = v6 * u6;
    Number  w1 = vu1 % m1, w2 = vu2 % m2, w3 = vu3 % m3, w4 = vu4 % m4, w5 = vu5 % m5, w6 = vu6 % m6;
    Number  w_1 = w1 % m1, w_2 = (w2 - w_1);
    deque<int> mv = {1};
    Number m(mv);
    pk = 2 * pk;
    for (int i = 0; i < pk; i++){m.add0();}
    bool x = false;
    deque<int> w = {1,5,2,3,6,1,9,9,2};
    Number W(w, 10, true, 0);
    W = W.change_mod2();
    for(; W < m; W++){
        W.format();
        x = (W % m1 == w1) && (W % m2 == w2) && (W % m3 == w3) && (W % m4 == w4) && (W % m5 == w5) && (W % m6 == w6);
        if (x){W = W.change_mod10(); return W;}
    }
    cout << "EROR";
    return a;
}

Number Number::shtrassen(const Number& b){
    Number a(b), r(*this);

    size_t size = r.n.size();

    if (size == 0 || a.n.size() == 0){Number C(); return C;}

        
    deque<int> new_n = {};

    multiply(r.n, a.n, new_n);

    size = new_n.size();

    Number RESULT(new_n);

    if (r.c == a.c){RESULT.c = true;}
    else {RESULT.c = false;}
    return RESULT;
}

Number Number::cook(){
    Number b = *this;
    int Q = b.q;
    b.q = b.n.size();
    Q = b.q - Q;
    double z = int(32 * (4 * n[0] + 2 * n[1] + n[2]));
    z /= 4;
    Number Z = z;
    Z = Z.change_mod2();
    int k = 0, num = 5;
    Number Z2, VkZ2;
    while (pow(2, k + 1) < num){
        Z2 = Z * Z;
        VkZ2 = b * Z2;
        Z = 2 * Z - VkZ2;
        while (Z.q > pow(2, k + 1) + 1){Z.n[Z.n.size() - 1] += 1;Z.format();}
        k += 1;
    }
    return Z;
}

Number Number::delit_cook(const Number& a){
    Number b = a;
    b = b.change_mod2();
    b = b.cook();
    b = b.change_mod10();
    Number A = *this;
    return A * b;
}


Number get_number(){
    string s;
    cin >> s;
    deque<int> a;
    for (int i = 0; i < s.size(); i++){a.push_back(s[i] - '0');}
    Number x(a);
    return x;
}

int main(){
    deque<int>v1 = {1,2,3,4, 4};
    deque<int>v2 = {1,2,3,4, 3};
    Number A(v1) , B(v2);
    //deque<int> r ={1,0};
    //deque<int> vector1 = {2,4};
    //deque<int> vector2 = {4,4};
    //Number A1(vector1),A2(vector2);

    //Number Drob(v1, 10, true);
    //cout << Drob << endl;
    cout << A << " " << B << endl;

    //cout << A << "  " << B << "   A * B  = " << A * B << endl << endl
    //     << "    Karatsuba  ==   " <<  A.karatsuba(B) << endl << endl
    //     << "   toom-cook   == " << A.toom_cook(B) << endl << endl
    //     << "   shanhage    == " << A.shanhage(B) << endl << endl
    //     << "    shtrassen  == " << A.shtrassen(B) << endl << endl;
    return 0;
}