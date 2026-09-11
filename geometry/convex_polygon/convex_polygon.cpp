#include <iostream>
#include <vector>


struct Point {
    double x;
    double y;


    static Point from_int_input() {
        int x, y;
        std::cin >> x >> y;
        return Point { static_cast<double>(x), static_cast<double>(y) };
    }

    double cross(const Point& rhs) const{
        return x * rhs.y - y * rhs.x;
    }

    Point operator-(const Point& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }

    static double orient(const Point& A, const Point& B, const Point& C) {
        return (A-B).cross(A-C);
    }

    static int sorient(const Point& A, const Point& B, const Point& C) {
        double res = Point::orient(A, B ,C);
        return res > 0 ? 1 : (res < 0 ? -1 : 0);
    }
};

/* 1: outside, 0 boundary, -1 inside */
int point_polygon_position(const Point& P, const std::vector<Point>& polygon) {

    int n = polygon.size();



    int orientation = 0;
    for (size_t i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        int k = (i + 2) % n;

        int ori = Point::sorient(polygon[i], polygon[j], polygon[k]);
        if (ori != 0) {
            orientation = ori;
            break;
        }
    }
    


    bool boundary = false;

    for (size_t i = 0; i < n; i++)
    {

        int j = (i + 1) % n;
        int k = (i + 2) % n;

        int orr = Point::sorient(polygon[i], polygon[j], P);
        if (orr == 0) {
            boundary = true;
            continue;
        }
        if (orr != orientation) {
            return 1;
        }
    }
    
    return boundary ? 0 : -1;

}


int main() {

    int n;
    std::cin >> n;

    // polygon is guaranteed convex
    std::vector<Point> vertices;
    vertices.reserve(n);

    for (size_t i = 0; i < n; i++)
    {
        vertices.push_back(Point::from_int_input());
    }
    
    int q;
    std::cin >> q;


    for (size_t i = 0; i < q; i++)
    {
        int pos = point_polygon_position(Point::from_int_input(), vertices); 
        if (pos == 1) {
            std::cout << "outside\n";
        } else if (pos == 0) {
            std::cout << "boundary\n";
        } else {
            std::cout << "inside\n";
        }
    }





    return 0;
}