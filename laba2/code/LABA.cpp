#include "Number.hpp"

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


Number get_number(){
    string s;
    cin >> s;
    deque<int> a;
    for (int i = 0; i < s.size(); i++){a.push_back(s[i] - '0');}
    Number x(a);
    return x;
}

int main(){
    deque<int> a = {1, 2};
    Number A(a, 1);
    deque<int> b = {1};
    Number B(b, 1);
    cout << A << "  *  " << B << "  =   " << A * B ;// " =  toom_cook  =  " << B.toom_cook(A) << endl;
    //duon L(A), K(B);
    //cout << L << endl;
    //cout << L * L << "  = shanhage  =   " << L.shanhage(L) << endl ;
    //cout << L % K;


    return 0;
}

