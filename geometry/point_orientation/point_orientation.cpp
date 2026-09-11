#include <iostream>


struct Point {
    double x;
    double y;


    Point operator-(const Point& rhs) const {
        return Point{ .x = x - rhs.x, .y = y - rhs.y };
    }

    double cross(const Point& rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    static double orient(const Point& A, const Point& B, const Point& C) {
        return (A-B).cross(A-C);
    }

    static int sorient(const Point& A, const Point& B, const Point& C) {
        double res = (A-B).cross(A-C);
        return res > 0 ? 1 : (res < 0 ? -1 : 0);
    }

    static Point from_int_input() {
        int x, y;
        std::cin >> x >> y;
        return Point{ .x = static_cast<double>(x), .y = static_cast<double>(y) };
    }
};



int main() {

    Point A = Point::from_int_input();
    Point B = Point::from_int_input();
    Point C = Point::from_int_input();
    Point P = Point::from_int_input();


    int ab_ac = Point::sorient(A, B, C);

    int ab_ap = Point::sorient(A, B, P);

    int ac_ap = Point::sorient(A, C, P);

    if (ab_ap == ac_ap || ab_ap == 0 || ac_ap == 0) {
        std::cout << "no\n";
        return 0;
    }

    if (ab_ac == ab_ap) {
        std::cout << "yes\n";
        return 0;
    }

    std::cout << "no\n";

    return 0;
}