#include<iostream>
#include<deque>
#include<string>
#define _USE_MATH_DEFINES


#include<cmath>
#include<complex>



using namespace std;


int plus_int(int a, int b){return a + b;}
int minus_int(int a, int b){return a - b;}
int maximum(int a, int b){return (a > b ? a : b);}


typedef complex<double> base;
 
void fust_mult (deque<base> & a, bool invert) {

    double pi = 3.14159265358979323846;


	int n = (int) a.size();
	if (n == 1)  return;
 
	deque<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fust_mult (a0, invert);
	fust_mult (a1, invert);
 
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

void mult (const deque<int> & a, const deque<int> & b, deque<int> & res) {
	deque<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < maximum(a.size(), b.size())) { n *= 2;}
    n *= 2;
	fa.resize (n),  fb.resize (n);
 
	fust_mult (fa, false),  fust_mult (fb, false);
	for (size_t i=0; i<n; ++i){
		fa[i] *= fb[i];
    }
	fust_mult (fa, true);
 
	for (size_t i=0; i < n; ++i)
		res.push_back(int (fa[i].real() + 0.5));

    int k = 2 * maximum(a.size(), b.size()) - min(a.size(), b.size());
        
    for (int i = 0; i < k; i++){res.pop_back();}

}

struct LL{

    friend struct duon;

    LL(bool c = true):c(c){n = {0};}

    LL(deque<int> n, bool c = true):n(n), c(c) {this->format();}

    ~LL(){n.clear();}

    LL(deque<int> a, bool c, int p){
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

    LL(LL const& a):n(a.n), c(a.c){}

    LL & operator = (LL const& a){
        n = a.n;
        c = a.c;
        this->format();
        return *this;
    }

    void format(){this->_form_digit(); this->_del0();}

    deque<int> getN(){return n;}

    bool getC(){return c;}

    LL module(){
        LL b = *this;
        b.c = true;
        return b;
    }

    bool operator > (LL& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] > a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] < a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }
    
    bool operator < (LL& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] < a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] > a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }

    LL operator - (){
        LL b = *this;
        b.c = !c;
        return b;
    }

    LL operator + (LL& a){
        if (this == &a){LL p = a * 2; return p;}
        if (c == a.c){LL b = this->_plus(a);return b;}
        else{
            if (a > *this){LL p = a._minus(*this); return p;}
            else {LL p = this->_minus(a);return p;}
        }
    }

    LL operator - (LL& a){
        if (c != a.c){LL b = this->_plus(a);return b;}
        else{
            if (a > *this){LL p = (-a)._minus(*this); return p;}
            else {LL p = this->_minus(a);return p;}
        }
    }

    void operator += (LL& a){LL C = *this + a; *this = C;}

    void operator -= (LL& a){LL C = *this - a; *this = C;}

    LL operator * (int a){
        size_t size = n.size();
        LL num = *this;
        for (size_t i = 0; i < size; i++)
        {num.n[i] *= a;}
        num.format();
        return num;
    }

    LL operator / (int a){
        size_t size = n.size();
        LL num = *this;
        int carry = 0, tmp;
        for (size_t i = 0; i < size; i++)
        {tmp = 10 * ((num.n[i] + carry) % a); num.n[i] = (num.n[i] + carry) / a; carry = tmp;}
        num.format();
        return num;
    }

    int operator % (int a){
        size_t size = n.size();
        LL num = *this;
        int carry = 0, tmp;
        for (size_t i = 0; i < size; i++)
        {tmp = 10 * ((num.n[i] + carry) % a); carry = tmp;}
        return carry / 10;
    }

    LL operator * (LL& a){
        size_t size = a.n.size();
        if (!size || !n.size()){LL z; return z;}
        LL r = *this;
        LL num = r * a.n[size - 1];
        LL num1;
        for (int i = 2; i <= size; i++){
            r._mult_by_10();
            num1 = (r * a.n[size - i]);
            num += num1;
        }
        return num;
    }


    LL karatsuba(LL& a){
        size_t size = n.size();
        deque<int>c = {}, d = {};
        if (size == 0 || a.n.size() == 0){c.push_back(0); LL C(c); return C;}
        if (size == 1 || a.n.size() == 1){return (*this * a);}
        this->_straight(a, 0);
        size = n.size();
        int i, m = 0;
        for (i = 0;i < size / 2; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
        LL A(c), C(d);c = {}; d = {};
        for (i = size / 2; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
        LL B(c), D(d);
        LL AC = A.karatsuba(C);
        LL BD = B.karatsuba(D);
               
        LL E = (A + B);
        LL K = (C + D);
        E = E.karatsuba(K);
        E = (E - AC) - BD;  
        AC._mult_by_10(2 * m);
        E._mult_by_10(m);
        return ((AC + E) + BD);

    }

    LL toom_cook(LL& a){
        
        size_t size = n.size();
        deque<int>c = {}, d = {};

        if (size == 0 || a.n.size() == 0){c.push_back(0); LL C(c); return C;}
        if (size < 3 || a.n.size() < 3){return (*this * a);}

        this->_straight(a, 3 - (maximum(size, a.n.size()) % 3));
        size = n.size();
        int i, m = 0;

        for (i = 0;i < size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
        LL A2(c), B2(d);c.clear(); d.clear();
        
        for (i = size / 3; i < 2 * size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
        LL A1(c), B1(d);c.clear(); d.clear();

        for (i = 2 * size / 3; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
        LL A0(c), B0(d);c.clear(); d.clear();

        LL A_m2 = A2 * 4; LL A12 = A1 * 2; A_m2 = A_m2 - A12; A_m2= A_m2 + A0;//LL A_m2 = A2 * 4 - A1 * 2 + A0;
        LL B_m2 = B2 * 4; LL B12 = B1 * 2; B_m2 = B_m2 - B12; B_m2= B_m2 + B0;//LL B_m2 = B2 * 4 - B1 * 2 + A0;

        LL A_m1 = A2 - A1 + A0;
        LL B_m1 = B2 - B1 + B0;

        LL A_0 = A0;
        LL B_0 = B0;

        LL A_1 = A2 + A1  + A0;
        LL B_1 = B2 + B1  + B0;

        LL A_2 = A2 * 4; LL A22 = A1 * 2; A_2 = A_2 + A22; A_2= A_2 + A0;//LL A_2 = A2 * 4 + A1 * 2 + A0;
        LL B_2 = B2 * 4; LL B22 = B1 * 2; B_2 = B_2 + B22; B_2= B_2 + B0;//LL B_2 = B2 * 4 + B1 * 2 + B0;

        LL C_m2 = A_m2*B_m2;
        LL C_m1 = A_m1*B_m1;

        LL k5 = A_0*B_0;

        LL C_1 = A_1*B_1;
        LL C_2 = A_2*B_2;

        C_m2 -= k5;
        C_m1 -= k5;
        C_1 -= k5;
        C_2 -= k5;

        LL D1 = C_1 + C_m1; // 2a + 2c
        
        LL D2 = C_2 + C_m2; // 32a + 8c
        
        LL D3 = C_1 - C_m1; // 2b + 2d

        LL D4 = C_2 - C_m2; // 16b + 4d

        D1 = D1 / 2; // a + c

        D2 = D2 / 8; // 4a + c

        D3 = D3 / 2; // b + d

        D4 = D4 / 4; // 4b + d

        LL k1 = D2 - D1; // 3a
        k1 = k1 / 3; // a

        LL k3 = D1 - k1; //c

        LL k2 = D4 - D3; // 3b
        k2 = k2 / 3; // b

        LL k4 = D3 - k2; // d


        k1._mult_by_10(4*m);
        k2._mult_by_10(3*m);
        k3._mult_by_10(2*m);
        k4._mult_by_10(m);

        LL k = k1 + k2;
        k += k3; k += k4; k+= k5;
        
        return k;
    }

    LL shtrassen(LL& a){

        size_t size = n.size();

        if (size == 0 || a.n.size() == 0){LL C(); return C;}

        
        deque<int> new_n = {};

        mult(n, a.n, new_n);

        size = new_n.size();

        LL b(new_n);

        return b;
    }

    long long tolong(){
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

    private:
        deque<int> n;
        bool c;

        LL _operation(LL& a, int (*func)(int, int)){
            this->_straight(a);
            deque<int> new_n;
            for (int i = 0; i < n.size(); i++){
                new_n.push_back(func(n[i], a.n[i]));
            }
            LL x(new_n, c);
            this->format(); a.format();
            return x;
        }

        LL _plus(LL& a){return this->_operation(a, plus_int);}

        LL _minus(LL& a){return this->_operation(a, minus_int);}

        void _form_digit(){
            size_t size = n.size();
            for (size_t i = 1; i < size; i++){
                while (n[size - i] > 9){n[size - i - 1] += 1;n[size - i] -= 10;}
                while (n[size - i] < 0){n[size - i - 1] -= 1; n[size - i] += 10;}
            }
            while (n[0] > 9){n.push_front(n[0] / 10);n[1] %= 10;}
        }

        void _del0(){int j = 0; while((n[j] == 0) && (n.size() > 0)){n.pop_front();}}

        void _0add(int k){for (int i = 0; i < k; i++){n.push_front(0);}}

        void _mult_by_10(int k = 1){for (int i = 0; i < k; i++){n.push_back(0);}}

        void _straight(LL& a, int k = 1){
            int d = n.size() - a.n.size();
            if (d < 0){a._0add(k);this->_0add(k - d);}
            else{      this->_0add(k);    a._0add(k + d);}
        }
};

ostream & operator << (ostream & out, LL a){
    if (!a.getC()){cout << "-";};
    deque<int> n = a.getN();
    size_t size = n.size();
    for (size_t i = 0; i < size; i++){cout << n[i];} return out;
}


struct duon{

    friend struct LL;

    duon(double z, int quon){
        n = {0};
        if (z >= 1){n[0]++; z-=1;}
        for (int i = 0; i < quon; i++){
            z *= 2;
            if (z >= 1){n.push_back(1); j++; z -= 1;}
            else {n.push_back(0);}
        }
    }



    duon(bool c = true):c(c){n = {0};}
    
    duon(LL a){
        n = this->format(a);
        c = a.getC();
    }

    duon(deque<int> n, bool c = true):n(n), c(c) {this->format();}

    ~duon(){n.clear();}

    duon(duon const& a):n(a.n), c(a.c){}

    duon & operator = (duon const& a){
        n = a.n;
        c = a.c;
        this->format();
        return *this;
    }


    deque<int> getN(){return n;}

    deque<int> format(LL a){
        deque<int> p = {};
        int r = 0;
        while (a.getN().size() != 0){
            r = a % 2;
            p.push_front(r);
            a = a / 2;
        }
        return p;
    }

    void format(){this->_form_digit(); this->_del0();}

    duon operator - (){
        duon b = *this;
        b.c = !c;
        return b;
    }

    void operator ++ (){
        n[n.size() - 1]+= 1;
        this->format();
    }

    duon operator * (int a){
        size_t size = n.size();
        duon num = *this;
        for (size_t i = 0; i < size; i++)
        {num.n[i] *= a;}
        num.format();
        return num;
    }

    duon operator / (int a){
        size_t size = n.size();
        duon num = *this;
        int carry = 0, tmp;
        for (size_t i = 0; i < size; i++)
        {tmp = 2 * ((num.n[i] + carry) % a); num.n[i] = (num.n[i] + carry) / a; carry = tmp;}
        num.format();
        return num;
    }

    int operator % (int a){
        size_t size = n.size();
        duon num = *this;
        int carry = 0, tmp;
        for (size_t i = 0; i < size; i++)
        {tmp = 2 * ((num.n[i] + carry) % a); carry = tmp;}
        return carry / 2;
    }

    duon operator % (duon a){
        if(a > *this){return *this;}
        duon p;
        int i = 0;
        for (; i < a.n.size(); i++){
            p.n.push_back(n[i]);
        }
        while (p > a){p = p - a;}
        int k = n.size() - a.n.size();
        int x = 0;
        while (k > 0){
            p.format();
            i++;
            p.n.push_back(n[i]);
            while (p > a && x < 100){p._print(); cout << "  "; a._print(); cout << endl;  p = p - a; x++;}
            k--;
        }
        return p;
    }

    bool operator > (duon& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] > a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] < a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }
    bool operator < (duon& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] < a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] > a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }

    duon operator + (duon& a){
        if (this == &a){duon p = a * 2; return p;}
        if (c == a.c){duon b = this->_plus(a);return b;}
        else{
            if (a > *this){duon p = a._minus(*this); return p;}
            else {duon p = this->_minus(a);return p;}
        }
    }

    duon operator - (duon& a){
        if (c != a.c){duon b = this->_plus(a);return b;}
        else{
            if (a > *this){duon p = (-a)._minus(*this); return p;}
            else {duon p = this->_minus(a);return p;}
        }
    }

    duon operator * (duon& a){
        size_t size = a.n.size();
        if (!size || !n.size()){LL z; return z;}
        duon r = *this;
        duon num = r * a.n[size - 1];
        duon num1;
        for (int i = 2; i <= size; i++){
            r._mult_by_2();
            num1 = (r * a.n[size - i]);
            num = num + num1;
        }
        num.j = j + a.j;
        return num;
    }

    duon shanhage(duon& a){
        deque<int> zero = {0}; duon w(zero); 
        if (n.size() == 0 || a.n.size() == 0){return w;}
        this->_straight(a);
        size_t size = n.size();
        int pk = 1;
        int qk = 26;
        while (pk < size){
            qk = 3 * qk - 1;
            pk = 18 * qk + 8;
        }
        this->_0add(pk - size);
        a._0add(pk - size);
        long long r = pow(2, 6 * qk - 1) ;
        long long m1 = r - 1, m2 = r * 4 - 1, m3 = 8 * r - 1, m4 = 16 * r - 1, m5 = 64 * r - 1, m6 = 256 * r - 1;
        cout << " m1 " << m1 << " m2 " << m2 << " m3 " << m3 << " m4 " << m4 << " m5 " << m5 << " m6 " << m6 << endl;
        long long  u1 = *this % m1, u2 = *this % m2, u3 = *this % m3, u4 = *this % m4, u5 = *this % m5, u6 = *this % m6;
        long long  v1 = a % m1,     v2 = a % m2,     v3 = a % m3,     v4 = a % m4,     v5 = a % m5,     v6 = a % m6;
        long long  vu1 = v1 * u1, vu2 = v2 * u2, vu3 = v3 * u3, vu4 = v4 * u4, vu5 = v5 * u5, vu6 = v6 * u6;
        long long  w1 = vu1 % m1, w2 = vu2 % m2, w3 = vu3 % m3, w4 = vu4 % m4, w5 = vu5 % m5, w6 = vu6 % m6;
        deque<int> mv = {1};
        duon m(mv);
        pk = 2 * pk;
        for (int i = 0; i < pk; i++){m._mult_by_2();}
        bool x = false;
        ++w;
        cout << endl;
        for(; w < m; ++w){
            x = (w % m1 == w1) && (w % m2 == w2) && (w % m3 == w3) && (w % m4 == w4) && (w % m5 == w5) && (w % m6 == w6);
            if (x){return w;}
        }
        cout << "EROR";
        return w;

    }

    duon cook(){
        int k = n.size() - j;
        duon a = *this;
        a.j = n.size();
        for (int i = 0; i < 3 - k; i++){this->_mult_by_2();}
        double z = round(32 / (4 * n[0] + 2 * n[1] + n[2])) / 4;
        duon Z(z);




        return *this;
    }

    private:
        deque<int> n;
        bool c;
        int j = 0;


        duon _operation(duon& a, int (*func)(int, int)){
            this->_straight(a);
            deque<int> new_n;
            for (int i = 0; i < n.size(); i++){
                new_n.push_back(func(n[i], a.n[i]));
            }
            duon x(new_n, c);
            this->format(); a.format();
            return x;
        }

        duon _plus(duon& a){return this->_operation(a, plus_int);}

        duon _minus(duon& a){return this->_operation(a, minus_int);}


        void _form_digit(){
            size_t size = n.size();
            for (size_t i = 1; i < size; i++){
                while (n[size - i] > 1){n[size - i - 1] += 1;n[size - i] -= 2;}
                while (n[size - i] < 0){n[size - i - 1] -= 1; n[size - i] += 2;}
            }
            while (n[0] > 2){n.push_front(n[0] / 2);n[1] %= 2;}
        }

        void _del0(){int j = 0; while((n[j] == 0) && (n.size() > 0)){n.pop_front();}}

        void _0add(int k){for (int i = 0; i < k; i++){n.push_front(0);}}

        void _mult_by_2(int k = 1){for (int i = 0; i < k; i++){n.push_back(0);}}

        void _straight(duon& a, int k = 1){
            int d = n.size() - a.n.size();
            if (d < 0){a._0add(k);this->_0add(k - d);}
            else{      this->_0add(k);    a._0add(k + d);}
        }
        
        void _print(){
            size_t size = n.size();
            for (size_t i = 0; i < size; i++){cout << n[i];}
        }



};




ostream & operator << (ostream & out, duon a){
    deque<int> n = a.getN();
    size_t size = n.size();
    for (size_t i = 0; i < size; i++){cout << n[i];} return out;
}

LL get_number(){
    string s;
    cin >> s;
    deque<int> a;
    for (int i = 0; i < s.size(); i++){a.push_back(s[i] - '0');}
    LL x(a);
    return x;
}

int main(){
    deque<int> a = {1, 2};
    LL A(a, 1);
    deque<int> b = {1};
    LL B(b, 1);
    //cout << A << "  *  " << B << "  =   " << A * B << " =  toom_cook  =  " << B.toom_cook(A) << endl;
    duon L(A), K(B);
    cout << L << endl;
    //cout << L * L << "  = shanhage  =   " << L.shanhage(L) << endl ;
    cout << A.karatsuba(B);


    return 0;
}
