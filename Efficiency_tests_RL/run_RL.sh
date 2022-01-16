filename=./tree2hist.C"(\""$1"\")"
nbevt=$2
echo $filename
root -b -q -l $filename


make clean && make -j4 && ./clover_g4_eff -r $nbevt -i $1 -n 1 -o $1.dat -N 2

nedit $1.dat &

