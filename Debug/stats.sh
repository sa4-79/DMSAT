echo '************************************************************'
echo 'Random total solved'
cat outputRand |grep -v '/SATISFIABLE/\|SATISFIABLE.' |grep 'SATI' | wc -l
echo 'Random Total timeout'
cat outputRand | grep 'TimeOut' | wc -l
echo 'Random total submitted'
cat outputRand | grep -a --text 'Time taken' | wc -l
echo 'Random Total SATISFIABLE'
cat outputRand |grep -v '/SATISFIABLE/\|UNSATI\|SATISFIABLE.' |grep 'SATI' | wc -l
echo 'Random Total UNSATISFIABLE'
cat outputRand |grep 'UNSATI' | wc -l
echo '************************************************************'
echo 'Application  total solved'
cat output |grep -a --text 'SATI' | wc -l
echo 'Application Total timeout'
cat output | grep  -a --text 'TimeOut' | wc -l
echo 'Application total submitted'
cat output | grep -a --text '/home/sasgha' | wc -l
echo 'Application Total SATISFIABLE'
cat output |grep  -a --text -v 'UNSATI' |grep -a --text 'SATI' | wc -l
echo 'Application Total UNSATISFIABLE'
cat output |grep  -a --text 'UNSATI' | wc -l
echo '************************************************************'
