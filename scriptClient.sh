gcc -o client client.c lib/src/colors.c lib/src/tools.c lib/src/stringFunc.c lib/src/fileClient.c lib/src/commandClient.c lib/src/list.c -lpthread;
./client 127.0.0.1 $1;