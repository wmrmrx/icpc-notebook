# Para usar (hash das linhas [l1, l2]):
# ./hash.sh arquivo.cpp l1 l2
# md5sum do hash.sh: 9cd1295ed4344001c20548b1d6eb55b2
sed -n $2','$3' p' $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
