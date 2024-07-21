const int N = 3*100; // multiplo de 3
double integrate(double a, double b, function<double(double)> f) {
    double s = 0, h = (b - a)/N;
    for (int i = 1 ; i < N; i++) s += f(a + i*h)*(i%3 ? 3 : 2);
    return (f(a) + s + f(b))*3*h/8;
}
