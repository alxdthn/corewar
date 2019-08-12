FILE=$1
./asm $1;
./vm_champs/corewarNEW -v $2 ${FILE//.s/.cor} > origin_out.txt;
./corewar -v $2 ${FILE//.s/.cor} > project_out.txt
diff -q origin_out.txt project_out.txt > test.diff