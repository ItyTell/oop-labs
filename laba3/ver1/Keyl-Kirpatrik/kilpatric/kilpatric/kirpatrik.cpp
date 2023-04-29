#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

std::ifstream fin;

std::ofstream fout;

std::string path_edges = "C:/c++ code/LABA/edges.txt";

std::string path_result = "C:/c++ code/LABA/result.txt";


int integer(std::string s) {
    int l = 0, sum = 0;
    int i = 0;
    size_t size = s.size();
    for (; i < size; i++) {
        l = int(s[i]);
        sum *= 10;
        if (l >= 48 && l <= 57) {
            sum += l - 48;
        }
        else { throw std::logic_error("not a constant"); }
    }
    return sum;
}


struct Point
{
    Point(float x, float y, int num):x(x), y(y), num(num) {}

    Point& operator = (Point a) { x = a.x; y = a.y; num = a.num; return *this; }

    int x;
    int y;
    int num;
};
std::ostream & operator << (std::ostream& out, const Point& a) { std::cout << "(" << a.x << ";" << a.y << ")"; return out; }




int main() {
    fin.open(path_edges);
    if (!fin.is_open()) {
        std::cout << "file is not open.";
        return 0;
    }

    std::string s1, s2;

    std::vector<Point> points;
    int i = 0;
    while (!fin.eof()) {
        s1 = s2 = "";
        fin >> s1 >> s2;
        if (s2 != "") {
            points.push_back(Point(integer(s1), integer(s2), i));
            i++;
        }
    }
    size_t size = points.size();

    sort(points.begin(), points.end(), [](const Point &a, const Point &b) 
        {return (a.y < b.y); });

    std::vector<int> left, right;

    for (Point each : points) { std::cout << each << std::endl; }

    for (Point each : points) { std::cout << each << std::endl; }

	return 0;
}