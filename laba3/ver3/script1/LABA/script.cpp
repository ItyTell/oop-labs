
#include<iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>

#include <boost/polygon/voronoi.hpp>
#include <cassert>
using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::x;
using boost::polygon::y;
using boost::polygon::low;
using boost::polygon::high;



std::ifstream fin;

std::ofstream fout;

std::string path_edges = "C:/c++/last_laba/edges.txt";

std::string path_result = "C:/c++/last_laba/result.txt";

struct Point {
    int a;
    int b;
    Point(int x, int y) : a(x), b(y) {}
};

struct Segment {
    Point p0;
    Point p1;
    Segment(int x1, int y1, int x2, int y2) : p0(x1, y1), p1(x2, y2) {}
};

namespace boost {
    namespace polygon {

        template <>
        struct geometry_concept<Point> {
            typedef point_concept type;
        };

        template <>
        struct point_traits<Point> {
            typedef int coordinate_type;

            static inline coordinate_type get(
                const Point& point, orientation_2d orient) {
                return (orient == HORIZONTAL) ? point.a : point.b;
            }
        };

        template <>
        struct geometry_concept<Segment> {
            typedef segment_concept type;
        };

        template <>
        struct segment_traits<Segment> {
            typedef int coordinate_type;
            typedef Point point_type;

            static inline point_type get(const Segment& segment, direction_1d dir) {
                return dir.to_int() ? segment.p1 : segment.p0;
            }
        };
    }  // polygon
}  // boost

// Traversing Voronoi edges using edge iterator.
int iterate_primary_edges1(const voronoi_diagram<double>& vd) {
    int result = 0;
    for (voronoi_diagram<double>::const_edge_iterator it = vd.edges().begin();
        it != vd.edges().end(); ++it) {
        if (it->is_primary())
            ++result;
    }
    return result;
}

// Traversing Voronoi edges using cell iterator.
int iterate_primary_edges2(const voronoi_diagram<double>& vd) {
    int result = 0;
    for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();
        it != vd.cells().end(); ++it) {
        const voronoi_diagram<double>::cell_type& cell = *it;
        const voronoi_diagram<double>::edge_type* edge = cell.incident_edge();
        // This is convenient way to iterate edges around Voronoi cell.
        do {
            if (edge->is_primary())
                ++result;
            edge = edge->next();
        } while (edge != cell.incident_edge());
    }
    return result;
}

// Traversing Voronoi edges using vertex iterator.
// As opposite to the above two functions this one will not iterate through
// edges without finite endpoints and will iterate only once through edges
// with single finite endpoint.
int iterate_primary_edges3(const voronoi_diagram<double>& vd) {
    int result = 0;
    for (voronoi_diagram<double>::const_vertex_iterator it =
        vd.vertices().begin(); it != vd.vertices().end(); ++it) {
        const voronoi_diagram<double>::vertex_type& vertex = *it;
        const voronoi_diagram<double>::edge_type* edge = vertex.incident_edge();
        // This is convenient way to iterate edges around Voronoi vertex.
        do {
            if (edge->is_primary())
                ++result;
            edge = edge->rot_next();
        } while (edge != vertex.incident_edge());
    }
    return result;
}

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

    std::vector<Point> points;
    while (!fin.eof()) {
        s1 = s2 = "";
        fin >> s1 >> s2;
        if (s2 != "") {
            points.push_back(Point(integer(s1), 668 - integer(s2)));
        }
    }

    voronoi_diagram<double> vd;
    construct_voronoi(points.begin(), points.end(), &vd);

    fout.open(path_result);

    if (!fout.is_open()) {
        std::cout << "file is not open.";
        return 0;
    }

    std::vector<const voronoi_diagram<double>::cell_type*> edge_cells;

    for (const voronoi_diagram<double>::edge_type& e : vd.edges()) {
        if (!e.is_infinite()) {
            edge_cells.push_back(e.cell());
            fout << e.vertex0()->x() << " " << 668 - e.vertex0()->y() << "  " << e.vertex1()->x() << " " << 668 - e.vertex1()->y() << std::endl;
        }
        else {
            // This covers the infinite edge case in question.
            const voronoi_diagram<double>::vertex_type* v0 = e.vertex0();
            // Again, only consider half the half-edges, ignore edge->vertex1()
            // to avoid overdrawing the lines
            if (v0)
            {
                // Direction of infinite edge if perpendicular to direction
                // between the points owning the two half edges. 
                // Take the rotated right vector and multiply by a large 
                // enough number to reach your bounding box
                Point p1 = points[e.cell()->source_index()];
                Point p2 = points[e.twin()->cell()->source_index()];
                int end_x = (p1.b - p2.b) * 640;
                int end_y = (p1.a - p2.a) * -640;
                fout << v0->x() << " " << 668 - v0->y() << "  " << end_x << " " << 668 - end_y << std::endl;

            }
        }
    }



    return 0;
}