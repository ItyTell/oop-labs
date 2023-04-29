#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<deque>
#include<cmath>

std::ifstream fin;

std::ofstream fout;

std::string path_edges = "C:/c++/last_laba/edges.txt";

std::string path_result = "C:/c++/last_laba/result.txt";

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

std::deque<Point> Alg(std::deque<Point> points, Line& line) {
    if (points.size() <= 1) { return points; }
    std::deque<Point> left, right;
    auto max = std::max_element(points.begin(), points.end(), [line](const Point& a, const Point& b) {return (line.height(a) < line.height(b)); });
    Line line_left(line.p1, *max), line_right(*max, line.p2);
    for (Point point : points) {
        if (line_left.in(point) == 1) { left.push_back(point); }
        else if (line_right.in(point) == 1) { right.push_front(point); }
    }
    std::deque<Point> result = Alg(left, line_left), res2 = Alg(right, line_right);
    result.push_back(*max);
    for (Point each : res2) { result.push_back(each); }
    return result;
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
    if (number <= 2) { return 0; }

    sort(points.begin(), points.end(), [](const Point& a, const Point& b){if (a.x == b.x) { return a.y < b.y; }else { return (a.x < b.x); } });

    std::deque<Point> top, bottom;
    Line line(points[0], points[number - 1]);

    for (Point point : points) {
        if (line.in(point) == 1) { top.push_back(point); }
        else if (line.in(point) == -1) { bottom.push_front(point); }
    }


    Point last = points[0]; bool flag = true;
    std::deque<Point> list = Alg(top, line);
    list.push_front(points[0]); list.push_back(points[number - 1]);
    line = Line(points[number - 1], points[0]);
    std::deque<Point> list2 = Alg(bottom, line);
    for (Point each : list2) { list.push_back(each); }
    list.push_back(points[0]);

    fout.open(path_result);
    for (int i = 0; i < list.size() - 1; i++) { fout << list[i].num << " " << list[i + 1].num << std::endl; }
    return 0;
}