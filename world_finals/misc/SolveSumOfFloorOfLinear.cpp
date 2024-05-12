//nao faco ideia como funciona
//https://github.com/yosupo06/library-checker-problems/ blob/master/math/sum_of_floor_of_linear /sol/correct.cpp
/**
 * a / b, a // b : 
 * sum_{i = 0..n-1} floor((ai + b) //
 * 
 * y = (ax + b) / m, (0 <= x <= n)
 */
ll sum_of_floor(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }
    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += sum_of_floor(y_max, a, m, (a - x_max % a) % a);
    return ans;
}
