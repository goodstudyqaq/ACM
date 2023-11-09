# g++-12 -o my.exe my.cpp #编译被测程序
# g++-12 -o std.exe std.cpp #编译正确（暴力）程序
# g++-12 -o data.exe data.cpp #编译数据生成程序
while true; do  
    ./data.exe > data.in #出数据  
    ./my.exe < data.in > my.out #被测程序  
    ./std.exe < data.in > std.out #正确（暴力）程序  
    if diff my.out std.out; then #比较两个输出文件  
        printf "AC\n"  #结果相同显示AC  
    elif diff -B -b my.out std.out; then  
        printf "PE\n"  
    else  
        printf "WA\n" #结果不同显示WA，并退出  
        exit 0  
    fi  
done  