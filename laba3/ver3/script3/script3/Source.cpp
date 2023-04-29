#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<deque>
#include<cmath>

std::ifstream fin;

std::ofstream fout1;

std::ofstream fout2;

std::string path_edges = "C:/c++/last_laba/edges.txt";

std::string path_result = "C:/c++/last_laba/result.txt";

std::string path_otladka = "C:/c++/last_laba/otladka.txt";

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

    Point() :x(0), y(0), num(0) {}
    Point(float x, float y, int num) :x(x), y(y), num(num) {}

    Point& operator = (Point a) { x = a.x; y = a.y; num = a.num; return *this; }

    int x;
    int y;
    int num;
};
std::ostream& operator << (std::ostream& out, const Point& a) { std::cout << "(" << a.x << ";" << a.y << ")"; return out; }

bool operator == (Point a, Point b) { if (a.x == b.x && a.y == b.y && a.num == b.num) { return 1; } else return 0; }

struct Line {

    Line() { Point a; p1 = a; p2 = a; }

    Line(const Point& a, const Point& b) : p1(a), p2(b) {}

    Line& operator = (Line l) { p1 = l.p1; p2 = l.p2; return *this; }

    Point p1;
    Point p2;

    int in(const Point& a) { int k = (p2.x - p1.x) * (p2.y - a.y) - (p2.y - p1.y) * (p2.x - a.x); if (k == 0) { return 0; } return k > 0 ? -1 : 1; }

    double height(const Point& a)const { return abs((a.x - p1.x) * (p1.y - p2.y) / (p1.x - p2.x) + p1.y - a.y); }
};


int main() {
    fin.open(path_edges);
    if (!fin.is_open()) {
        std::cout << "file is not open.";
        return 0;
    }
    std::string s1, s2;
    std::deque<Point> points;
    int number = 0;
    while (!fin.eof()) {
        s1 = s2 = "";
        fin >> s1 >> s2;
        if (s2 != "") {
            points.push_back(Point(integer(s1), 668 - integer(s2), number));
            number++;
        }
    }
    if (number <= 2) { return 0; }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {if (a.y == b.y) { return a.x < b.x; } else { return (a.y < b.y); } });

    std::deque<Point> left, right;
    Line line(points[0], points[number - 1]);

    for (Point point : points) {
        if (line.in(point) == 1) { left.push_back(point); }
        else if (line.in(point) == -1) { right.push_front(point); }
    }
    Line v;
    double a, b;
    size_t size = left.size();
    std::deque<Point> result = {};
    std::deque<Point> steck = { points[0], left[0] };
    for (int i = 1; i < size; i++) {
        v = Line(steck[0], steck[1]);
        while (v.in(left[i]) > 0) { steck.pop_back(); steck.push_front(result[result.size() - 1]); v = Line(steck[0], steck[1]); result.pop_back(); }
        result.push_back(steck[0]); steck.pop_front();  steck.push_back(left[i]);
    }
    result.push_back(steck[0]); result.push_back(steck[1]); //result.push_back(points[number - 1]);


    size = right.size();
    steck = { points[number - 1], right[0] };
    for (int i = 1; i < size; i++) {
        v = Line(steck[0], steck[1]);
        while (v.in(right[i]) > 0) { steck.pop_back(); steck.push_front(result[result.size() - 1]); v = Line(steck[0], steck[1]); result.pop_back(); }
        result.push_back(steck[0]); steck.pop_front();  steck.push_back(right[i]);
    }
    result.push_back(steck[0]); result.push_back(steck[1]); result.push_back(points[0]);

    fout1.open(path_otladka);
    fout1 << points[0].num << std::endl;
    for (int i = 0; i < left.size(); i++) { fout1 << left[i].num << std::endl; }
    fout1 << points[number - 1].num << std::endl;
    for (int i = 0; i < right.size(); i++) { fout1 << right[i].num << std::endl; }

    fout2.open(path_result);
    for (int i = 0; i < result.size() - 1; i++) { fout2 << result[i].num << " " << result[i + 1].num << std::endl; }
    return 0;
}