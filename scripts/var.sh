./var ../data/example.txt > tmp.out
DIFF=$(diff tmp.out ../data/example.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(var)\tpass\n"
else
    printf "Test(var)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
