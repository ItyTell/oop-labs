#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<deque>
#include<cmath>

std::ifstream fin;

std::ofstream fout;

std::string path_edges = "C:/c++/LABA/edges.txt";

std::string path_result = "C:/c++/LABA/result.txt";

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
    Point(float x, float y, int num) :x(x), y(y), num(num) {}

    Point(){}

    Point& operator = (Point a) { x = a.x; y = a.y; num = a.num; return *this; }

    int x = 0;
    int y = 0;
    int num = 0;
};
std::ostream& operator << (std::ostream& out, const Point& a) { std::cout << "(" << a.x << ";" << a.y << ")"; return out; }

bool operator == (Point a, Point b) { if (a.x == b.x && a.y == b.y && a.num == b.num) { return 1; } else return 0; }

Point zero;

struct Line {

    Line(Point& A, Point& B) {
        if (A.x == B.x) { vertical = 1; c = A.x; }
        else {
            this->a = float(A.y - B.y) / float(B.x - A.x);
            this->b = A.y + a * A.x;
            p1 = A; p2 = B;
        }
    }

    Line& operator = (Line l) { a = l.a; b = l.b; vertical = l.vertical; c = l.c; p1 = l.p1; p2 = l.p2; return *this; }

    int in(Point& p) {
        if (this->vertical) { if (p.x - c < 0.001) { return 0; } else { return p.x > c ? 1 : -1; } }
        if (p.y + a * p.x > b) { return 1; }
        else if (p.y + a * p.x < b) { return -1; }
        else return 0;
    }

    double height(const Point& p) const{ if (vertical) { return abs(p.x - c); } return abs(a * p.x + b - p.y); }

    float a = 0;
    float b = 0;
    float c = 0;
    bool vertical = 0;
    Point p1 = zero;
    Point p2 = zero;
};

const std::deque<Point>& operator + (const std::deque<Point> l1, const std::deque<Point> l2) {
    std::deque<Point> res = l1;
    for (Point each : l2) { res.push_back(each); }
    return res;
}

const std::deque<Point>& Alg(std::deque<Point> points, Line line) {
    if (points.size() <= 1) { return points; }
    std::deque<Point> result, left , right;
    auto max = std::max_element(points.begin(), points.end(), [line](const Point& a, const Point& b) {return line.height(a) < line.height(b); });
    Line line_left(line.p1, *max), line_right(*max, line.p2);
    result.push_back(*max);
    for (Point point : points) {
        if (line_left.in(point) == 1) { left.push_back(point); }
        else if (line_right.in(point) == 1) { right.push_front(point); }
    }
    return Alg(left, line_left) + result + Alg(right, line_right);
}

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
    if (number <= 1) { return 0; }
    sort(points.begin(), points.end(), [](const Point& a, const Point& b)
        {
            if (a.x == b.x) { return a.y < b.y; }
            else { return (a.x < b.x); } });

    std::deque<Point> top, bottom;

    Line line(points[0], points[number - 1]);

    for (Point point : points) {
        if (line.in(point) == 1) { top.push_back(point); }
        else if (line.in(point) == -1) { bottom.push_front(point); }
    }

    Point last = points[0]; bool flag = true;
    std::deque<Point> list = Alg(top, line);
    list.push_front(points[0]); list.push_back(points[number - 1]);


    fout.open(path_result);
    for (int i = 0; i < list.size() - 1; i++) { fout << list[i].num << " " << list[i + 1].num << std::endl; }
    return 0;
}