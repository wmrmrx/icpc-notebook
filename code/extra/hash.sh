# Para usar (hash das linhas [l1, l2]):
# ./hash.sh arquivo.cpp l1 l2
# md5sum do hash.sh: 9cd1295ed4344001c20548b1d6eb55b2
#
# Hash acumulativo, linha por linha:
# for i in $(seq $2 $3); do
#   echo -n "$i "
#   sed -n $2','$i' p' $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
# done
sed -n $2','$3' p' $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
