gcc -o user user.c lib/colors.c lib/stringFunc.c lib/fileUser.c lib/commandUser.c -lpthread;
./user 127.0.0.1 $1;