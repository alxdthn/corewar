END=$2
for ((i = $1; i < END; i++)) do
	echo $i
	./corewar -d $i $3 > out1;
	./vm_champs/corewarNEW -d $i $3 > out2;
	diff -q out1 out2
done
