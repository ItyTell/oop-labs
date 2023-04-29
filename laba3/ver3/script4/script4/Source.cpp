#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<deque>

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
    Point():x(0), y(0), num(0){}
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

    Point last = points[0]; bool flag;
    std::deque<int> list = { points[0].num };

    for (Point point : top) {
        line = Line(last, point);
        flag = true;
        for (Point each : points) { if (line.in(each) == 1) { flag = false; break; } }
        if (flag) { list.push_back(point.num); last = point; }
    }
    list.push_back(points[number - 1].num); last = points[number - 1];
    for (Point point : bottom) {
        line = Line(last, point);
        flag = true;
        for (Point each : points) { if (line.in(each) == 1) { flag = false; break; } }
        if (flag) { list.push_back(point.num); last = point; }
    }
    list.push_back(points[0].num);


    fout.open(path_result);
    for (int i = 0; i < list.size() - 1; i++) { fout << list[i] << " " << list[i + 1] << std::endl; }
    return 0;
}