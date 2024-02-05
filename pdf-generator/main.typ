#import "template.typ": *

// Change here
#show: project.with(
  title: "Codando & Coringando",
  date: datetime.today().display(),
  authors: (
    "LipArcanjo",
    "nathan_luiz",
    "wnmrmr",
  ),
)

= Theory

== Lagrange interpolating polynomial

Given points $(x_1, y_1), (x_2, y_2), ..., (x_n, y_n)$ a polynomial $P$ with minimal degree such that $P(x_i) = y_i$ is given by

$ P(x) = sum_(i=1)^(n) y_i product_(j!=i) (x-x_j) / (x_i - x_j) $

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

To get the hash in `file.cpp` between lines `<l1>` and `<l2>`, run
```sh
./hash.sh <file.cpp> <l1> <l2>
```

Hash is made by scope, delimited by the curly brackets (`"{"`, `"}"`).

The empty hash is 
`d41d8`
while
the hash of `hash.sh` is 
`9cd12`.

= Code

// Script will be used to insert code here
