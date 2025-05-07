# 编译部分（可选加上）
# g++-12 -o my.exe my.cpp
# g++-12 -o std.exe std.cpp
# g++-12 -o data.exe data.cpp

while true; do  
    ./data.exe > data.in || { echo "data.exe 运行失败"; exit 1; }

    ./my.exe < data.in > my.out
    if [ $? -ne 0 ]; then
        echo "my.exe 运行异常退出"
        exit 1
    fi

    ./std.exe < data.in > std.out
    if [ $? -ne 0 ]; then
        echo "std.exe 运行异常退出"
        exit 1
    fi

    if diff my.out std.out > /dev/null; then  
        echo "AC"
    elif diff -B -b my.out std.out > /dev/null; then  
        echo "PE"
    else  
        echo "WA"
        exit 1
    fi  
done
