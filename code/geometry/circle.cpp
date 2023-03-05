// Circle
//  Basic structure of circle and operations related with it. This template works
// only with double numbers since most of the operations of a circle can't be 
// done with only integers. Therefore, this template depends on point_double.cpp.
// 
// All operations' time complexity are O(1)

const double PI = acos(-1);

struct circle {
    point o; double r;
    circle() {}
    circle(point _o, double _r) : o(_o), r(_r) {}
    bool has(point p) { 
        return (o - p).norm2() < r*r + EPS;
    }
    vector<point> operator/(circle c) { // Intersection of circles.
        vector<point> inter;                   // The points in the output are in ccw order.
        double d = (o - c.o).norm();
        if(r + c.r < d - EPS || d + min(r, c.r) < max(r, c.r) - EPS)
            return {};
        double x = (r*r - c.r*c.r + d*d) / (2*d);
        double y = sqrt(r*r - x*x);
        point v = (c.o - o) / d;
        inter.pb(o + v*x + v.rotate(cw90)*y);
        if(y > EPS) inter.pb(o + v*x + v.rotate(ccw90)*y);
        return inter;
    }
    vector<point> tang(point p){
        double d = sqrt((p - o).norm2() - r*r);
        return *this / circle(p, d);
    }
    bool in(circle c){ // non strictly inside
        double d = (o - c.o).norm();
        return d + r < c.r + EPS;
    }
};
