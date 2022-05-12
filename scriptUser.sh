gcc -o user user.c colors.c -lpthread;
./user 127.0.0.1 $1;