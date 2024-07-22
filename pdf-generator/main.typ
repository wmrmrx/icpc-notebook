#import "template.typ": *

#import sym
// Change here
#show: project.with(
  title: "Universidade de São Paulo - Codando & Coringando",
  date: datetime.today().display(),
  authors: (
    "LipArcanjo",
    "nathan_luiz",
    "wnmrmr",
  ),
  logo: "phik.jpg"
)

= Template hashing

```bash
sed -n $2','$3' p' $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
```
The cli command `md5sum` is used to validate if the template was written correctly.

Write the one liner above without line breaks and save it as `hash.sh`, and run
```bash
chmod +x hash.sh
``` 
to make it executable.
vai luan

To get the hash in `file.cpp` between lines `<l1>` and `<l2>`, run
```sh
./hash.sh <file.cpp> <l1> <l2>
```

Hash is made by scope, delimited by the curly brackets (`"{"`, `"}"`).

The empty hash is 
`d41d8`
while
the `m5dsum` of `hash.sh` is
`9cd12`.

== Burnside Lemma

Let $G$ be a finite group that acts on set $X$. Let $X^g := { x in X | g.x = x }$. The number of orbits $|X slash G|$ is

$|X slash G| = 1/(|G|) sum_(g in G) |X^g| $

== Lucas' Theorem

For prime p,
$binom(n, m) = product_(i=0)^n binom(n_i, m_i) space (mod p)$

== Catalan

$C_n = 1 / (n+1) mat(2n;n) = (2n)!/(n!*(n+1)!)$
|
$C_n^k = (k+1)/(n+k+1) mat(2n +k;n)$

== Stirling numbers of the first kind

These are the number of permutation of size n with exactly k cycles

$vec(n,k,delim: "[") = (n-1)vec(n-1,k,delim: "[") + vec(n-1,k-1,delim: "[")$

$vec(0,0,delim: "[") = 1, vec(n,0,delim: "[") = vec(0,n,delim: "[") = 1$

== Stirling numbers of the second kind

These are the number of ways to partition n into exactly k non-empty
sets.

$vec(n,k,delim: "[") = (k)vec(n-1,k,delim: "[") + vec(n-1,k-1,delim: "[")$

$vec(n,k,delim: "[") = 1/k! sum_(j=0)^k (-1)^(k-j) mat(k;j)j^n$

$vec(0,0,delim: "[") = 1, vec(n,0,delim: "[") = vec(0,n,delim: "[") = 1$

== Planar Graph

If G has k connected components, then $n-m+f=k+1$.

$m <= 3n - 6$. If G has no triangles, $m ≤ 2n − 4$.

The minimum degree is less of equal 5. And can be 6 colored in O(n+m)/

=== Spherical coordinates

$x = r sin sym(theta) cos sym(phi)$  | $r = sqrt(x^2 + y^2 + z^2)$

$y = r sin sym(theta) sin sym(phi)$ | $sym(theta) = $acos$ (z/r)$

$z = r cos sym(theta)$ | $sym(phi) =$ atan2 $(y,x)$

== series and sums

$1/(1-x) = sum_(k=0) x^k$ | 
$e^x = sum_(k=0) x^k/k!$ | 
$ln(1+x) = sum_(k=1) (-1)^(k+1) x^k/k$

$sqrt(1+x) = 1 + sum_(k=1) (-1)^(k+1)x^k/2^(2k-1)$ | 
$1/(sqrt(1-x)) = sum_(k=0) x^k/4^k mat(2k;k)$

$sin x = sum_(k=0) (-1)^(k) (x)^(2k+1)/(2k+1)!$ |
$cos x = sum_(k=0) (-1)^k x^(2k)/(2k)!$

$1+2+... = (n(n+1))/2$ | $1^2+2^2+.. = (n(2n+1)(n+1))/6$

$1^3+2^3+.. = (n^2(n+1)^2)/4$ | $1^4+2^4+... = (n(n+1)(2n+1)(3n^2+3n+1))/30$

= Code

// Script will be used to insert code here
