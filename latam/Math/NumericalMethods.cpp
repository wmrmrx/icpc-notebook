// Integration
const int N = 3*100; // multiplo de 3
double integrate(double a, double b, function<double(double)> f) {
    double s = 0, h = (b - a)/N;
    for (int i = 1 ; i < N; i++) s += f(a + i*h)*(i%3 ? 3 : 2);
    return (f(a) + s + f(b))*3*h/8;
}
// Find some root of a function f with derivative df.
// Complexity: The precision doubles for each iteration, in ideal conditions.
// For roots with multiplicity greater than one, the precision increases linearly.
double f(double x);
double df(double x);
double findRoot(double x0=0.0) {
    double x = x0;
    double fx = f(x);
    while (abs(fx) > EPS) {
        x -= fx / df(x);
        fx = f(x);
    }
    return x;
}
// From Handbook of geometry for competitive programmers - Victor Lecomte 
// This is an algorithm to make sums of positive numbers more precise
// Complexity is O(n) amortized and the relative error of the sum is
// 2 log_2(n) eps, down from n * eps precision of the serial sum
// eps is the machine precision.
struct stableSum {
    int cnt = 0;
    vector<double> v, pref{0};
    // add number a to the sum
    void operator+=(double a) {
        assert(a >= 0);
        int s = ++cnt;
        while (s % 2 == 0) {
            a += v.back();
            v.pop_back();
            pref.pop_back();
            s /= 2;
        }
        v.push_back(a);
        pref.push_back(pref.back() + 1);
    }
    // return the sum value
    double val() {
        return pref.back();
    }
};