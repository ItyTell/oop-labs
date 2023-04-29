#include<iostream>

using namespace std;





int plusic(int a, int b){return a + b;}
int minusic(int a, int b){return a - b;}
int mult(int a, int b){return a * b;}
char oposite(char c){if (c == '+'){return '-';} else if (c == '-'){return '+';}else return 'e';}


struct Number{


    Number(int*n, size_t size, char c = '+'){
        this->size = size;
        this->n = new int[size];
        for (int i = 0; i< size; i++){
            this-> n[i] = n[i];
        }
        this->c = c;
        this->format();
    }
    ~Number(){delete [] n;}


    Number(Number const& a):
    size(a.size), n(a.n), c(a.c)
    {
        int* n_a = a.n;
        for (size_t i = 0; i < size; i++){
            n[i] = n_a[i];
        }
    }

    Number & operator = (Number const& a){
        if (this != &a){
            delete [] n;
            int* n_a = a.n;
            size = a.size;
            n = new int[size];
            for (size_t i = 0; i < size; i++){
                n[i] = n_a[i];
            }
        }
        return *this;
    }

    void format(){

        this->_form_digit();
        this->_del0();
    }

    int* const getN(){int* n1 = new int[size]; for (int i = 0; i < size; i++){n1[i] = n[i];} return n1;}
    size_t const sizeN(){return size;}
    char const getc(){return c;}

    void setN(int* new_n){delete [] n; n = new_n;}
    void set_size(size_t size){this->size = size;}
    void changec(){c = oposite(c);}

    bool operator > (Number& a){
        int d = size - a.sizeN();
        if (!d){return d > 0;}
        int* n_a = a.getN();
        for (int i = 0; i < size; i++){
            if(n[i] > n_a[i]){return true;}
            else if (n[i] < n_a[i]){return false;}
        }
        return false;
    }


    Number operator + (Number a){
        this->_straight(a.sizeN());
        a.straight(size);
        if (c == a.getc()){Number b = this->_plus(a);this->format(); a.format();return b;}
        else{
            if (a > *this){Number p = a._minus(*this);this->format(); a.format(); return p;}
            else {Number p = this->_minus(a);this->format(); a.format();cout << endl;return p;}
        }
    }

    Number operator - (Number& a){
        Number r(a.getN(), a.sizeN(), oposite(a.getc()));
        Number k = (*this + r);
        return k;
    }

    void straight(size_t t){
        this->_straight(t - 1); 
    }

    long long tolong(){
        int i;
        double sum = 0, k = 1;
        for (i = 0; i < size; i++){
            sum += k * n[size - 1 - i];
            k *= 10;
        }
        return sum;
    }

    private:

        int* n;
        size_t size;
        char c;

        Number _operation(Number a, int (*func)(int, int)){
            int* new_n = new int[size];
            int* n_a = a.getN();
            for (int i = 0; i < size; i++){
                new_n[i] = func(n[i], n_a[i]);
            }
            Number x(new_n, size, c);
            return x;
        }

        Number _plus(Number a){
            return this->_operation(a, plusic);
        }

        Number _minus(Number a){
            return this->_operation(a, minusic);
        }

        void _add0(int k){
            size += k;
            int* p = new int[size];
            int i;
            for (int i = 0; i < k; i++){p[i] = 0;}
            for (i = k; i < size; i++){p[i] = n[i - k];}
            this->setN(p);
        }

        void _straight(size_t size_a, int k = 1){
            int d = size - size_a;
            if (d < 0){this->_add0(k - d);}
            else{      this->_add0(k );}
        }

        void _form_digit(){
            for (int i = 1; i < size; i++){
                while (n[size - i] > 9){n[size - i - 1] += 1;n[size - i] -= 10;}
                while (n[size - i] < 0){n[size - i - 1] -= 1; n[size - i] += 10;}
            }
        }

        void _del0(){
            
            int j = 0;
            while(n[j] == 0){j++;if (j == size - 1){break;}}
            if (j > 0){
                size -= j;
                int* p = new int[size];
                for (int l = 0; l < size; l++){p[l] = n[j + l];}
                this->setN(p);
            }
        }
};

ostream & operator << (ostream & out, Number a){cout << a.getc(); for (size_t i = 0; i < a.sizeN(); i++){cout << a.getN()[i];} return out;}

int main(){
    
    int a[3] = {1, 2, 3};
    int a1[4] = {1, 2, 3, 4};
    Number b(a, 3);
    Number b1(a1, 4 , '-');
    cout << b << endl;
    return 0;
}

