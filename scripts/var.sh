./var > tmp.out
DIFF=$(diff tmp.out ../data/var.out)
if [ "$DIFF" == "" ] 
then
    printf "Test(var)\tpass\n"
else
    printf "Test(var)\tfail\n"
    echo ${DIFF}
fi

rm tmp.out
