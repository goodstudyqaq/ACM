echo "contest : $1 number: $2"
mkdir $1 && cd ./$1
touch data.in
i=0
for x in {A..Z} 
do
	touch $x.cpp
	let i++
	if [ $i -ge $2 ]; then
	break
	fi
done