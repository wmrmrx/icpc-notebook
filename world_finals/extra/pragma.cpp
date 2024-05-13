// Pragmas
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
mt19937_64 rng(123);
shuffle(permutation.begin(), permutation.end(), rng);
uniform_int_distribution<int>(a,b)(rng);
/*
syntax on

set nowrap
set tabstop=4
set shiftwidth=4
set nocompatible
set shortmess+=I
set number
set relativenumber
set laststatus=2
set hidden
set ignorecase
set smartcase
set incsearch
set mouse+=a
set backspace=indent,eol,start
set autoindent
set wildmenu
set wildignorecase
imap jj <Esc>

*/
