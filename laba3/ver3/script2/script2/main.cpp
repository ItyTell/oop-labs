#include "scanline_triangulation.hpp"

#include <iomanip>
#include <iostream>
#include <unordered_set>

#include<iostream>
#include<fstream>
#include<string>
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

int main() {

    fin.open(path_edges);
    if (!fin.is_open()) {
        std::cout << "file is not open.";
        return 0;
    }
    std::string s1, s2;
    std::vector<geometry::Vector2D> points;
    int number = 0;
    while (!fin.eof()) {
        s1 = s2 = "";
        fin >> s1 >> s2;
        if (s2 != "") {
            points.emplace_back(integer(s1), 668 - integer(s2));
            number++;
        }
    }
    if (number <= 2) { return 0; }


  const auto builder = geometry::DelaunayBuilder::Create(std::move(points));
  const auto& triangulation = builder->Get();
  const auto convex_hull = geometry::BuildConvexHull(triangulation.graph);

  std::vector<geometry::Vector2D> l;
  fout.open(path_result);
  for (auto each : triangulation.points) {
      l.push_back(each);
  }
  for (auto each : triangulation.graph) {
      fout << l[each.first.v1].x << " " << 668 - l[each.first.v1].y << "  " << l[each.first.v2].x << " " << 668 - l[each.first.v2].y << std::endl;
  }

  return 0;
}
