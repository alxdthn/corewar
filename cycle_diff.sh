END=$2
for ((i = $1; i < END; i++)) do
	echo $i
	./corewar -d $i toto.cor > out1;
	./vm_champs/corewarNEW -d $i toto.cor > out2;
	diff -q out1 out2
done
