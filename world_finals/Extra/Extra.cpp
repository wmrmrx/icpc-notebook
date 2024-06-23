// Pragmas
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
mt19937_64 rng(123);
shuffle(permutation.begin(), permutation.end(), rng);
uniform_int_distribution<int>(a,b)(rng);
/*
.vimrc
syntax on
set nowrap ts=4 sw=4 nocp shm+=I nu rnu ls=2 hid ic scs mouse+=a bs=indent,eol,start ai wmnu wic
imap jj <Esc>
*/
