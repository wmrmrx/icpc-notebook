//finds the area intersection of a single polygon and a 
//circle on center c and radius r
double circlePoly(point c, double r, vector<point> poly){
    auto tri = [&](point p, point q){
        auto r2 = r * r / 2;
        auto d = q - p;
        auto a = (d*p)/d.norm2();
        auto b = (p.norm2() - r*r)/d.norm2();
        auto det = a*a-b;
        if (det <= 0) return atan2(p^q,p*q) * r2;
        auto s = max((double)0, -a-sqrt(det)), t = min((double)1, -a+sqrt(det));
        if (t < 0 || 1 <= s) return atan2(p^q,p*q) * r2;
        auto u = p + d * s;
        auto v = p + d * t;
        return atan2(p^u,p*u) * r2 + (u^v)/2 + atan2(v^q,v*q) * r2;
    };
    auto sum = 0.0;
    int n = poly.size();
    for (int i = 0;i < n;i++){
        sum += tri(poly[i] - c, poly[(i+1) % n]);
    }
    return sum;
}