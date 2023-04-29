#include<iostream>
#include<cmath>
#include<vector>

using namespace std;



int Jakobi(int a,int n){
    if (a == 0 || a == 1){return a;}
    int s = 0;
    int e = 0, a1 = n - 1;
    while (a1 % 2 == 0){
        a1 /= 2;
        e += 1;
    }
    if (e % 2 == 0){s = 1;}
    else if (n % 8 == 1 || n % 8 == 7){s = 1;}
    else if (n % 8 == 3 || n % 8 == 5){s = -1;}

    if (n % 4 == 3 && a1 % 4 == 3){s = -s;}
    int n1 = n % a1;
    if (a1 == 1){return s;}
    else {return s * Jakobi(n1, a1);}
}

int nod(int a, int b){
    if (a == 0){return b;}
    if (b == 0){return a;}
    if (a == b){return a;}
    if (a % 2 == 0 && b % 2 == 0){return 2 * nod(a / 2, b / 2 );}
    if (a % 2 == 0){return nod(a / 2, b);}
    if (b % 2 == 0){return nod(a, b / 2);}
    if (a > b){return nod((a - b)/2, b);}
    else{return nod((b - a)/2, a);}
}


bool prostoNumer(int n){
    for (int i = 2; i<=sqrt(n); i++) 
        if (n % i == 0) 
            return false;   
    return true; 
}


int is_prime(int i){
    bool flag = true;
    int k;

    vector<int> vec = {2};

    for (int j = 0; j < i - 1; j++){
        flag = true;
        for (k = 1 + vec[vec.size() - 1]; flag ; k++){
            flag = !prostoNumer(k);
        }
        vec.push_back(k - 1);
    }
    return vec[vec.size() - 1];
}

bool Lemon(long long n){
    if (!(n % 2)){return 0;}
    if (n <= 8){return 0;}
    float n3 = pow(n, 1.0 / 3);

    for (int a = 3; a < n3; a += 2){
        if (n % a == 0){return 0;}
    }

    int h, f, r, p, j, A, B;
    for (h = 0; h < n3; h++){
        r = 1 + (sqrt(n3) / (4 * sqrt(k)));
        for (f = 0; f < r; f++){
            p = (int(sqrt(4 * h * n)) + f) * (int(sqrt(4 * h * n)) + f) - 4 * h * n;
            for (j = 2; j * j < p; j++){

                if (j * j == p){
                    A = int(sqrt(4 * h * n)) + f;
    
                    B = int(sqrt(A * A - 4 * h * n));
    
                    if ((A * A) % n == (B * B) % n){
                    
                        if ( 1 < Jakobi(A + B, n) && Jakobi(A + B, n) < n){return 0;}
                        if ( 1 < Jakobi(A - B, n) && Jakobi(A - B, n) < n){return 0;}
                    }
                }
            }
        }
    }
    return 1;
}

bool Rabin_Milller(int n){
    int s = 0, d = n - 1;
    while (d % 2 == 0){
        d /= 2;
        s += 1;
    }
    bool flag = false;

    for (int a = 1; a < n; a++){
        if ((int)round(pow(a, d)) % n == 1){continue;}

        flag = false;
        for (int r = 0; r < s; r++){
            if ( (int)round(pow(a, d * pow(2, r))) % n == -1){

                flag == true;
                break;
            }
        }

        if (!flag){return 0;}

    }

    return 1;
}


bool Solovei_Shtrassen(int h, int k){

    if (h % 2 == 0 || h <= 2){return 0;}

    int r;
    if (k > h - 2){k = h - 2;}
    for(int i = 2; i <= k; i++){
        r = (i + 1);
        if (nod(r, h) > 1){return 0;}
        
        if ((int)round(pow(r, (h - 1) / 2)) % h != Jakobi(r, h)){return 0;}
    }
    return 1;
}

bool Forbenious(int n){
    if (n % 2 == 0){return 0;}
    int j;
    for (j = 2; j * j < n; i++){if (n % (j * j) == 0){return 0;}}

    bool flag = true;
    int f = 0;
    for (j = 0; flag; j++){f  = is_prime(j);flag = !(Jakobi(f,n) == -1); if (f > n){break;}}
    double z = 0;
    if (f == 2){z = 2 + sqrt(f);}
    else {z = 1 + sqrt(f);}
    double zn = pow(z, n);
    while (zn > 0){zn -= n;}
    while (z > 0){z -= n;}
    if (abs(zn - z) < 1){return true;}
    return false;
}


int main(){

    //int n = 11;
    //cin >> n;
    //cout << endl;
    //cout << "Enter n" << endl << " 3335" << "  This number is not is_prime." << endl;
    //cout << "Enter n" << endl << " 3331	" << "  This number is is_prime." << endl << endl;
    cout << endl << Lemon(561) << endl;
    return 0;
}