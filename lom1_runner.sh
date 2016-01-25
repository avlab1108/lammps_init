
#!/bin/bash

#SBATCH -n 10 
#SBATCH --time=12:00:00


for i in {1..10..1}
do
dname="run"$i
echo $dname
mkdir $dname
cp vrml_header.txt run256 run256.sh $dname #файло которое нужно в каждую реализацию
cd $dname
echo $RANDOM > rndseed.txt # надо как-то подогнать сид
srun --exclusive -n 1 ./run256.sh & 
cd ..
done
wait
#запускать sbatch -p (нужный партишн) ./этот_скрипт.sh
