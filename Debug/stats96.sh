echo '************************************************************'
echo 'Random total solved'
cat /home/sasghar/minisat/Debug/OutPuts/Rand8 |grep -v '/SATISFIABLE/\|SATISFIABLE.' |grep 'SATI' | wc -l
echo 'Random Total timeout'
cat  /home/sasghar/minisat/Debug/OutPuts/Rand8 | grep 'TimeOut' | wc -l
echo 'Random total submitted'
cat /home/sasghar/minisat/Debug/OutPuts/Rand8 | grep -a --text 'Time taken' | wc -l
echo 'Random Total SATISFIABLE'
cat /home/sasghar/minisat/Debug/OutPuts/Rand8 |grep -v '/SATISFIABLE/\|UNSATI\|SATISFIABLE.' |grep 'SATI' | wc -l
echo 'Random Total UNSATISFIABLE'
cat /home/sasghar/minisat/Debug/OutPuts/Rand8 |grep 'UNSATI' | wc -l
echo '************************************************************'
echo 'Application  total solved'
cat /home/sasghar/minisat/Debug/OutPuts/APP96 |grep -a --text 'SATI' | wc -l
echo 'Application Total timeout'
cat /home/sasghar/minisat/Debug/OutPuts/APP96 | grep  -a --text 'TimeOut' | wc -l
echo 'Application total submitted'
cat /home/sasghar/minisat/Debug/OutPuts/APP96 | grep -a --text '/home/sasgha' | wc -l
echo 'Application Total SATISFIABLE'
cat /home/sasghar/minisat/Debug/OutPuts/APP96 |grep  -a --text -v 'UNSATI' |grep -a --text 'SATI' | wc -l
echo 'Application Total UNSATISFIABLE'
cat /home/sasghar/minisat/Debug/OutPuts/APP96 |grep  -a --text 'UNSATI' | wc -l
echo '************************************************************'
