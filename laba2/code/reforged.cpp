#include<iostream>
#include<deque>

using namespace std;





int plusic(int a, int b){return a + b;}
int minusic(int a, int b){return a - b;}
int mult(int a, int b){return a * b;}
char oposite(char c){if (c == '+'){return '-';} else if (c == '-'){return '+';}else return 'e';}


struct Number{

    Number(deque<int> n, char c = '+'):n(n), c(c) {
        this->format();
    }
    ~Number(){n.clear();}


    Number(Number const& a):
    n(a.n), c(a.c)
    {}

    Number & operator = (Number const& a){
        if (this != &a){
            n.clear();
            deque<int> n = a.n;
            c = a.c;
        }
        return *this;
    }

    void format(){this->_form_digit();this->_del0();}

    deque<int> const getN(){return n;}
    char const getc(){return c;}

    void setN(deque<int> new_n){n = new_n;}
    void changec(){c = oposite(c);}

    bool operator > (Number& a){
        this->_straight(a, 0);
        int d = n.size() - a.n.size();
        if (!d){return d > 0;}
        deque<int> n_a = a.getN();
        for (int i = 0; i < n.size(); i++){
            if(n[i] > n_a[i]){return true;}
            else if (n[i] < n_a[i]){return false;}
        }
        return false;
    }




    Number operator + (Number a){
        this->_straight(a);
        this->print();cout << endl;
        a.print();cout << endl;
        if (c == a.c){Number b = this->_plus(a);this->format(); a.format();return b;}
        else{
            if (a > *this){Number p = a._minus(*this);this->format(); a.format(); return p;}
            else {Number p = this->_minus(a);this->format(); a.format();cout << endl;p.print();return p;}
        }
    }

    Number operator - (Number& a){
        Number r(a.n, oposite(a.c));
        Number k = (*this + r);
        k.print();
        cout << endl;
        return k;
    }

    long long tolong(){
        int i;
        double sum = 0, k = 1;
        for (i = 0; i < n.size(); i++){
            sum += k * n[n.size() - 1 - i];
            k *= 10;
        }
        return sum;
    }

    void const print(){cout << c;for (int i = 0; i < n.size(); i++){cout << n[i];}}

    private:

        deque<int> n;
        char c;

        Number _operation(Number a, int (*func)(int, int)){
            deque<int> n_a = a.n, new_n;
            for (int i = 0; i < n.size(); i++){
                new_n.push_back(func(n[i], n_a[i]));
            }
            Number x(new_n, c);
            return x;
        }

        Number _plus(Number a){
            return this->_operation(a, plusic);
        }

        Number _minus(Number a){
            return this->_operation(a, minusic);
        }

        void _add0(int k){for (int i = 0; i < k; i++){n.push_front(0);}}

        void _straight(Number a, int k = 1){
            int d = n.size() - a.n.size();
            if (d < 0){a._add0(k);this->_add0(k - d);}
            else{      this->_add0(k);    a._add0(k + d);}
        }

        void _form_digit(){
            size_t size = n.size();
            for (size_t i = 1; i < size; i++){
                while (n[size - i] > 9){n[size - i - 1] += 1;n[size - i] -= 10;}
                while (n[size - i] < 0){n[size - i - 1] -= 1; n[size - i] += 10;}
            }
        }

        void _del0(){
            int j = 0;
            while(n[j] == 0){n.pop_front();}
        }
};


int main(){
    deque<int> a = {1, 2, 3};
    deque<int> a1 = {1, 2, 3, 4};
    Number b(a);
    Number b1(a1, '-');
    Number c = (b - b1);
    c.print();
    cout << endl;
    return 0;
}

