// Pragmas
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
mt19937_64 rng(123);
shuffle(permutation.begin(), permutation.end(), rng);
uniform_int_distribution<int>(a,b)(rng);
