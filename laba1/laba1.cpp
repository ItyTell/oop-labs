#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip> 

using namespace std;



void print_menu() {
    cout << "Enter generator type: " << endl;
    cout << "\t1 - Linear Congruential Generator" << endl;
    cout << "\t2 - Quadratic Congruential Generator" << endl;
    cout << "\t3 - Fibonacci Numbers Generator" << endl;
    cout << "\t4 - Inverse Congruent SequenceGenerator" << endl;
    cout << "\t5 - Union Method Generator" << endl;
    cout << "\t6 - Sigma Method Generator" << endl;
    cout << "\t7 - Polar Coordinate Method Generator" << endl;
    cout << "\t8 - Relation Method Generator" << endl;
    cout << "\t9 - Logarithm Method Generator" << endl;
    cout << "\t10 - Arens Method Generator\n" << endl;
}


vector<float> mashtab(vector<int> c, int len, int m){
    vector<float> p;
    p.push_back(c[0]);
    p.push_back(c[1]);
    for (int i = 2; i < len; i++){
        p.push_back(c[i]);
        p[i] /= (m - 1); // [0; m] => [0; 1)
        p[i] += p[0] / p[1];
        p[i] *= p[1]; // [0; 1) => [a; b)
    }
    return p;
}


bool isCoprime(int a, int b) {
    for (int gcd = a; ; gcd = b, b = a % b, a = gcd)
        if (!b) return gcd==1;
}

vector<int> divisors(int m){
    vector<int> a;a.push_back(1);
    int k = m , c = 0;
    for( int i = 2; (m != 1 || i != k); i++){
        if (m % i == 0){ 
            m /= i;
            if (a[c] != i){a.push_back(i);i--;}
        }
    }
    return a;
}

bool first_con(int a, int c, int m){
    bool z, l, s;
    vector<int> n = divisors(m);
        l = 1;
        bool flag = n.size() == 1;
        for (int i = 1; (i < n.size()) && l && flag; i++){
           l = ((a - 1) % n[i]) == 0;
        }
        s = 1;
        if (m % 4 == 0){s = (a - 1) % 4 == 0;}
        z = (!isCoprime(m, c)) || !l || !s;
    return z;
}

bool second_con(int a, int c, int m, int d){
    bool z, l, s, p, e;
    vector<int> n = divisors(m);
        l = 1;
        bool flag = n.size() == 1;
        for (int i = 1; (i < n.size()) && l && flag; i++){
            if (n[i] % 2 !=0){
                l = (((a - 1) % n[i]) == 0) && (d % n[i] == 0);
            }
        }
        s = 1;
        p = 1;
        e = 1;
        if (m % 4 == 0){s = (a - 1) % 4 == d % 4;}
        else if (m % 2 == 0){p = (a - 1) % 2 == d % 2;}
        if (m % 3 == 0){e = ((d % 9) != (c % 3));}
        z = (!isCoprime(m, c)) || !l || !s || !p || !e;
    return z;
}


int cond(float x, float a, float b, float f){
    int p;
    x -= a; b -= a; p = 100 * x /b; p /= 10; 
    if (p == 10){p = 9;}
    if (p < 0|| p > 10){ p = 9;}
    return p;
}

void prnt100(vector<float> st, int f, int len){
    float l = 0;
    cout << " Segment  -- frequency\n ";
    for (int i = 1; i < f; i++){
        cout << " [" << 10 * (i - 1) << ";" << i * 10 << ")";
        cout << "  -- |" << st[i - 1] / len << "|\n";
        l += st[i - 1] / len;
    }
    cout << "[90;100]  -- |" << st[9] / len << "|\n";
    l += st[9] / len;

    cout << "Sum of the frequency == " << l << "\n";
}

void prnt3(vector<float> st, int f, int len){
    float l = 0;
    cout << " Segment  -- frequency\n";
    for (int i = 1; i < f; i++){
        cout << "[" << -3 + 0.6 * (i - 1) << ";" << -3 + i * 0.6 << ")";
        if (-3 + 0.6 * (i - 1) >= 0){cout <<" ";}
        if (-3 + 0.6 * i >= 0){cout <<" ";}
        cout << "  -- |" << st[i - 1] / len << "|\n";
        l += st[i - 1] / len;
    }
    cout << "[2.40;3.00]    -- |" << st[9] / len << "|\n";
    l += st[9] / len;

    cout << "Sum of the frequency == " << l << "\n";
}

int stats(vector<float> b, int len, int f){
    vector<float> st;
    for (int i = 0; i < f + 2; i++){st.push_back(0);} // full the vector in 0
    for (int i = 2 ; i < len; i++){st[cond(b[i], b[0], b[1], float(f))]++;}
    if (b[1] == 3){cout << setprecision(2) << fixed; prnt3(st, f, len);}
    else{cout << setprecision(2) << fixed; prnt100(st, f, len);}
    return 0;
}


vector<int> o(int a, int b){
    int d, x, y, x1, x2, y1, y2, q, r;
    if (!b){d = a; x = 1; y = 0; return {d, x, y};} 
    x2 = 1; x1 = 0; y2 = 0; y1 = 1;
    while (b > 0)
    {
        q = a/b;
        r = a -  q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b; b = r; x2 = x1; x1 = x; y2 = y1; y1 = y;   
    }
    d = a; x = x2; y = y2;
    return {d, x, y};
}

int opos(int k){ 
    vector<int> a;
    a = o(k + 1997, 1997);
    return abs(a[1]);
}


vector<int> gen1(int quo, vector<int> mas_x, int a, int c, int x0, int m) {

    mas_x.push_back(0);
    mas_x.push_back(100);
    mas_x.push_back(x0);

    for (int i = 2; i < quo; i++){
        mas_x.push_back((a * mas_x[i] + c) % m); // new number
    }
    return mas_x;
}

vector<float> G1(){
    vector<int> mas_int;
    vector<float> mas_float;

    int a, c, x0, m;

    cout << "\n Enter constants for first method: a, c, x0 - first value, m - module (should be prime, for example 1723)\n";
    cout <<  "( c and m must be coprime, a-1 % p = 0 where p is every diviser of m, if m % 4 == 0 then a - 1 % 4 = 0 \n";
    bool z, l, s;
    cin >> a >> c >> x0 >> m;
    z = first_con(a, c, m);
    while (z){
        cout << "Wrong input. Try again!!!\n Enter constants: a, c, x0 - first value, m - module (should be prime)\n";
        cout <<  "( c and m must be coprime, a-1 % p = 0 where p is every diviser of m, if m % 4 == 0 then a - 1 % 4 = 0 \n";
        cin >> a >> c >> x0 >> m;
        z = first_con(a, c, m);
    }


    mas_int = gen1(10002, mas_int, a, c, x0, m); 
    mas_float = mashtab(mas_int, 10002, m);



    return mas_float;
}


vector<int> gen2(int quo, vector<int> mas_x, int a, int c, int x0, int d, int m) {

    mas_x.push_back(0);
    mas_x.push_back(100);


    mas_x.push_back(x0);
    for (int i = 2; i < quo; i++){
        mas_x.push_back((d * mas_x[i] * mas_x[i] + a * mas_x[i] + c) % m); // new number
    }
    return mas_x;
}

vector<float> G2(){
    vector<int> mas_int;
    vector<float> mas_float;

    int a = 27, c = 33, x0 = 41, d = 33, m = 1733; //module

    cout << "\n Enter constants for second method: a, c,, d x0 - first value, m - module (should be prime, for example 1733)\n";
    cout <<  "( c and m must be coprime, a-1 % p = 0 and d % p = 0 where p is every diviser of m except 2,\n";
    cout << " if m % 4 == 0 and d % 2 = 0 then a - 1 % 4 = d % 4, if m % 2 = 0 then a - 1 % 2 = d % 2.) \n";
    bool z, l, s;
    cin >> a >> c >> x0 >> d >> m;
    z = second_con(a, c, m, d);
    while (z){
        cout << "Wrong input. Try again!!!\n Enter constants: a, c, x0 - first value, m - module (should be prime)\n";
        cout <<  "( c and m must be coprime, a-1 % p = 0 and d % p = 0 where p is every diviser of m except 2,";
        cout << " if m % 4 == 0 and d % 2 = 0 then a - 1 % 4 = d % 4, if m % 2 = 0 then a - 1 % 2 = d % 2.) \n";
        cin >> a >> c >> x0 >> a >> m;
        z = second_con(a, c, m, d);
    }


    mas_int = gen2(10002, mas_int, a, c, x0, d, m); 
    mas_float = mashtab(mas_int, 10002, m);
    return mas_float;
}


vector<int> gen3(int quo, vector<int> mas_x, int x0, int x1, int m){
    mas_x.push_back(0);
    mas_x.push_back(100);

    
    mas_x.push_back(x0);
    mas_x.push_back(x1);

    for (int i = 2; i < quo - 1; i++){
        mas_x.push_back((mas_x[i] + mas_x[i + 1] ) % m); // new number
    }
    return mas_x;
}

vector<float> G3(){
    vector<int> mas_int;
    vector<float> mas_float;

    int x0, x1, m;
    cout << "\n Enter constants for second method: x1 and x2 - first two values and a module\n";
    cin >> x0 >> x1 >> m;
    mas_int = gen3(10000, mas_int, x0, x1, m); 
    mas_float = mashtab(mas_int, 10002, m);
    return mas_float;
}


vector<int> gen4(int quo, vector<int> mas_x, int a, int c, int x0, int p){
    mas_x.push_back(0);
    mas_x.push_back(100);
    mas_x.push_back(x0);
    for (int i = 3; i < quo; i++){
        mas_x.push_back((a * opos(mas_x[i -1]) + c) % p);
    }
    return mas_x;
}

vector<float> G4(){
    vector<int> mas_int;
    vector<float> mas_float;
    int x0, a, c, p;
    cout << "\n Enter constants: a, c, x0 - first value, m - module (should be prime, for example 1997)\n";
    cin >> a >> c >> x0 >> p;
    mas_int = gen4(10000, mas_int, a, c, x0, p);
    mas_float = mashtab(mas_int, 10000, p);
    return mas_float;
}


vector<int> gen5(int quo, vector<int> x, vector<int> y){
    vector<int> mas;
    int m = 10;
    mas.push_back(0);
    mas.push_back(100);
    for (int i = 2; i < quo; i++){
        mas.push_back((abs(x[i] - y[i]) % m));
    }
    return mas;
}

vector<float> G5(){
    vector<int> mas_int1, mas_int2, mas_int;
    vector<float> mas_float;
    mas_int1 = gen2(10000, mas_int, 27, 33, 41, 33, 1733);
    mas_int2 = gen1(10000, mas_int, 19, 25, 1, 1723);  
    mas_int = gen5(10000, mas_int1, mas_int2); 
    mas_float = mashtab(mas_int, 10000, 10);
    return mas_float;
}


vector<float> gen6(int quo, vector<int> mas_sum){
    vector<float> mas;
    float sum;

    mas.push_back(-3);
    mas.push_back(3);

    for (int i = 0; i < quo; i++){
        
        sum = 0;
        for (int k = 12 * i; k < 12 * (i + 1); k++){sum += mas_sum[k + 2];}
        sum /= 1722;
        mas.push_back(sum - 6);
    }
    return mas;
}

vector<float> G6(){
    vector<int> mas_int1;
    vector<float> mas_float, mas;
    mas_int1 = gen1(60000, mas_int1, 19, 25, 1, 1723);
    mas = gen6(10000, mas_int1);
    return mas;
}


vector<float> gen7(int quo, vector<float> x, vector<float> y){
    vector<float> mas;
    int a = 0, i;
    float x1, x2, s = 0;
    mas.push_back(-3);
    mas.push_back(3);
    for (i = 0; i < quo; i++){
        while (s >= 1 || s == 0){
            x1 = 2 * x[a] - 1;
            x2 = 2 * y[a] - 1;
            s = x1 * x1 + x2 * x2;
            a += 1;
        }
        x1 = x1 * sqrt(((-2) * log(s))/s);
        x2 = x2 * sqrt(((-2) * log(s))/s);
        mas.push_back(x1);
        mas.push_back(x2);
        s = 0;
    }
    return mas;
}

vector<float> G7(){
    vector<int> mas_int1 , mas_int2;
    vector<float> mas_float, mas_1, mas_2;
    mas_int1 = gen1(30000, mas_int1, 19, 25, 1, 1723); mas_int1[1] = 1;
    mas_int2 = gen2(30000, mas_int1, 27, 33, 41, 33, 1733); mas_int2[1] = 1;
    mas_1 = mashtab(mas_int1, 30000, 1723);
    mas_2 = mashtab(mas_int2, 30000, 1733);
    mas_float = gen7(5000, mas_1, mas_2);
    return mas_float;

}


vector<float> gen8(int quo, vector<float> x, vector<float> y){
    vector<float> mas;
    int a = 0, i;
    float x1, x2, u;
    bool flag;
    mas.push_back(-3);
    mas.push_back(3);
    for (i = 0; i < quo; i++){
        flag = 1;
        while(flag){
            x1 = x[a + 200];
            x2 = y[a + 1000];
            if (!x2){a++; continue;}
            u = ((x1 - 0.5) / x2) * sqrt(8 / M_E);
            if (u * u <= 5 - (4 * exp(0.25) * x2)){flag = 0;}
            else{
                flag = (u * u > - 4 * log(u) * x2) || ( u * u >= 1.4 + 4 * exp(-1.35) / x2);
            }
            a++;
        }
        mas.push_back(u);
    }
    return mas;
}

vector<float> G8(){
    vector<int> mas_int1 , mas_int2;
    vector<float> mas_float, mas_1, mas_2;
    mas_int1 = gen4(30000, mas_int1, 2, 4, 6, 1997); mas_int1[1] = 1;
    mas_int2 = gen1(30000, mas_int2, 19, 25, 1, 1723); mas_int2[1] = 1;
    mas_1 = mashtab(mas_int1, 30000, 1997);
    mas_2 = mashtab(mas_int2, 30000, 1723);
    mas_float = gen8(10002, mas_1, mas_2);
    return mas_float;

}


vector<float> gen9(int quo, vector<float> x){
    float m;
    cout << "\n Enter constants: m\n";
    cin >> m;
    vector<float> mas;
    mas.push_back(0);
    mas.push_back(100);
    for (int i = 0; i < 2 * quo; i++){
        if (!x[i]){i++;continue;}
        mas.push_back(- m * log(x[i]));
    }
    return mas;
}

vector<float> G9(){
    vector<int> mas_int;
    vector<float> mas_float1 , mas_float;
    mas_int = gen2(20000, mas_int, 27, 33, 41, 33, 1733);
    mas_int[1] = 1;
    mas_float1 = mashtab(mas_int, 20000, 1723);
    mas_float = gen9(10000, mas_float1); 
    return mas_float;
}


vector<float> gen10(int quo, vector<float> x, vector<float> c){
    vector<float> mas;
    bool flag;
    float p, y;
    int a = 1, k;
    cout << "\n Enter constant: a\n";
    cin >> k;
    mas.push_back(0);
    mas.push_back(100);
    for (int i = 0; i < quo; i++){
        flag = 1;
        while(flag){
            y = tan(M_PI * x[a]);
            p = sqrt(2 * k - 1) * y + k - 1;
            flag = (p <= 0) || (c[a + 1000] > (1 + y * y) * exp((k - 1) * log(p / (k - 1)) - y * sqrt(2 * k -1)));
            a++;
        }
        mas.push_back(p);
    }
    return mas;
}

vector<float> G10(){
    vector<int> mas_int1, mas_int2;
    vector<float> mas_float1 , mas_float, mas_float2;
    mas_int1 = gen4(20000, mas_int1, 2, 4, 6, 1997);
    mas_int2 = gen3(20000, mas_int2, 1, 2, 2137);
    mas_int1[1] = 1; mas_int2[1] = 1;
    mas_float1 = mashtab(mas_int1, 20000, 1997);
    mas_float2 = mashtab(mas_int2, 20000, 2137);
    mas_float = gen10(10000, mas_float1, mas_float2); 
    return mas_float;
}


vector<float> start_alg() {
    int type;
    cin >> type;

    while (type > 10 || type < 0){
        cout << "Wrong input!!!\nOnly 1-10 requires";
        cin >> type;
    }

    switch (type) {
        case 1:
            return G1();
        case 2:
            return G2();
        case 3:
            return G3();
        case 4:
            return G4();
        case 5:
            return G5();
        case 6:
            return G6();
        case 7:
            return G7();
        case 8:
            return G8();
        case 9:
            return G9();
        case 10:
            return G10();
    }
    return {};
}


int main() {

    print_menu();

    vector<float> mas;

    mas = start_alg();

    stats(mas, 10002, 10);
    
    return 0;
}


