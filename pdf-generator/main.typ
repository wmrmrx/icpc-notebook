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
the `m5dsum` of `hash.sh` is
`9cd12`.

= Code

// Script will be used to insert code here
