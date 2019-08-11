./corewar -d $1 toto.cor > out1;
./vm_champs/corewar -d $1 toto.cor > out2;
diff -q out1 out2
diff out1 out2 > $1.diff