#include<iostream>
#include<deque>
#include<string>

using namespace std;


int plusic(int a, int b){return a + b;}
int minusic(int a, int b){return a - b;}
int max(int a, int b){return (a > b ? a : b);}


struct Number{

    Number(bool c = true):c(c){n = {};}

    Number(deque<int> n, bool c = true):n(n), c(c) {this->format();}

    ~Number(){n.clear();}

    Number(Number const& a):n(a.n), c(a.c){}

    Number & operator = (Number const& a){
        n = a.n;
        c = a.c;
        this->format();
        return *this;
    }

    void format(){this->_form_digit(); this->_del0();}

    deque<int> getN(){return n;}

    bool getC(){return c;}

    Number module(){
        Number b = *this;
        b.c = true;
        return b;
    }

    bool operator > (Number& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] > a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] < a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }
    bool operator < (Number& a){
        this->_straight(a);
        size_t size = n.size();
        for (size_t i = 0; i < size; i++){
            if (n[i] < a.n[i]){this->format(); a.format();return 1;}
            else if (n[i] > a.n[i]){this->format(); a.format();return 0;}
        }
        this->format(); a.format();
        return 0;
    }

    Number& operator - (){
        Number b = *this;
        b.c = !c;
        Number& k = b;
        return k;
    }

    Number& operator + (Number& a){
        if (this == &a){Number p = a * 2;Number& z = p; return z;}
        if (c == a.c){Number p = this->_plus(a);Number& z = p;return z;}
        else{
            if (a > *this){Number p = a._minus(*this);Number& z = p; return z;}
            else {Number p = this->_minus(a);Number& z = p;return z;}
        }
    }

    Number& operator - (Number& a){
        if (c != a.c){Number p = this->_plus(a);Number& z = p;return z;}
        else{
            if (a > *this){Number p = (-a)._minus(*this);Number& z = p; return z;}
            else {Number p = this->_minus(a);Number& z = p;return z;}
        }
    }

    void operator += (Number& a){Number C = *this + a; *this = C;}

    Number& operator * (int a){
        size_t size = n.size();
        Number num = *this;
        for (size_t i = 0; i < size; i++)
        {num.n[i] *= a;}
        num.format();
        Number& number = num;
        return number;
    }

    Number operator / (int a){
        size_t size = n.size();
        Number num = *this;
        for (size_t i = 0; i < size; i++)
        {num.n[i] /= a;}
        num.format();
        return num;
    }

    Number& operator * (Number& a){
        size_t size = a.n.size();
        Number r = *this;
        Number num = r * a.n[size - 1];
        for (int i = 2; i <= size; i++){
            r._mult_by_10();
            num += (r * a.n[size - i]);
        }
        Number& z = num;
        return z;
    }


    Number& karatsuba(Number& a){
        size_t size = n.size();
        deque<int>c = {}, d = {};
        if (size == 0 || a.n.size() == 0){c.push_back(0); Number C(c); Number& z = C; return z;}
        if (size == 1 || a.n.size() == 1){Number& z = (*this * a); return z;}
        this->_straight(a, 0);
        size = n.size();
        int i, m = 0;
        for (i = 0;i < size / 2; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
        Number A(c), C(d);c = {}; d = {};
        for (i = size / 2; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
        Number B(c), D(d);
        Number AC = A.karatsuba(C);
        Number BD = B.karatsuba(D);
               
        Number E = A + B;
        Number K = C + D;
        E = E.karatsuba(K);
        E = E - AC - BD;  
        AC._mult_by_10(2 * m);
        E._mult_by_10(m);
        Number& z = AC + E + BD;
        return z;

    }

    Number toom_cook(Number& a){
        size_t size = n.size();
        deque<int>c = {}, d = {};
        if (size == 0 || a.n.size() == 0){c.push_back(0); Number C(c); return C;}
        if (size == 1 || a.n.size() == 1){return (*this * a);}
        this->_straight(a, 3 - (max(size, a.n.size()) % 3));
        size = n.size();
        int i, m = 0;

        for (i = 0;i < size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);}
        Number A2(c), B2(d);c = {}; d = {};
        for (i = size / 3; i < 2 * size / 3; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
        Number A1(c), B1(d);c = {}; d = {};
        for (i = 2 * size / 3; i < size; i++){c.push_back(n[i]);d.push_back(a.n[i]);m++;}
        Number A0(c), B0(d);

        Number A_m2 = A2 * 4 - A1 * 2 + A0;
        Number B_m2 = B2 * 4 - B1 * 2 + A0;

        Number A_m1 = A2 - A1 + A0;
        Number B_m1 = B2 - B1 + A0;

        Number A_0 = A0;
        Number B_0 = A0;

        Number A_1 = A2 + A1  + A0;
        Number B_1 = B2 + B1  + A0;

        Number A_2 = A2 * 4 + A1 * 2 + A0;
        Number B_2 = B2 * 4 + B1 * 2 + A0;

        Number C_m2 = A_m2 * B_m2;
        Number C_m1 = A_m1 * B_m1;
        Number P = A_0 * B_0;
        Number C_1 = A_1 * B_1;
        Number C_2 = A_2 * B_2;

        C_m2 += -P;
        C_m1 += -P;
        C_1 += -P;
        C_2 += -P;

        Number D1 = C_1 + C_m1;
        Number D2 = C_2 + C_m2;
        Number D3 = C_1 - C_m1;
        Number D4 = C_2 - C_m2;


        
        return a;
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

        Number _operation(Number& a, int (*func)(int, int)){
            this->_straight(a);
            deque<int> new_n;
            for (int i = 0; i < n.size(); i++){
                new_n.push_back(func(n[i], a.n[i]));
            }
            Number x(new_n, c);
            this->format(); a.format();
            return x;
        }

        Number _plus(Number& a){return this->_operation(a, plusic);}

        Number _minus(Number& a){return this->_operation(a, minusic);}

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

        void _straight(Number& a, int k = 1){
            int d = n.size() - a.n.size();
            if (d < 0){a._0add(k);this->_0add(k - d);}
            else{      this->_0add(k);    a._0add(k + d);}
        }
};

ostream & operator << (ostream & out, Number a){
    if (!a.getC()){cout << "-";};
    deque<int> n = a.getN();
    size_t size = n.size();
    for (size_t i = 0; i < size; i++){cout << n[i];} return out;
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
    deque<int> a = {1, 2, 3, 3, 3, 3, 4, 6, 2, 4};
    Number A(a, 1);
    deque<int> b = {9, 3, 4, 4, 3, 3, 3, 3};
    Number B(b, 1);
    cout << A << "  *  " << B << "  =   " << A * B << " =  karatsuba  =  " << A.karatsuba(B) << endl;
    return 0;
}
