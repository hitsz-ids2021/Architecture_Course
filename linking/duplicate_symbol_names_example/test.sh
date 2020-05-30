# $1: the number x in source file foox.c and barx.c
if [ x$1 = x ];then
    echo "Please input file number you want to test"
else if [ x$2 = x ];then
    echo "Please input the times you want to test"
    else
        for((i=0;i<$2;i++));do
            out="foobar$1_${i}"
            gcc -o tmp/$out "foo$1.c" "bar$1.c" show_bytes_b.c
            tmp/$out
        done
    fi
fi
