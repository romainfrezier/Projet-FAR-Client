gcc -o client main.c lib/src/client.c lib/src/colors.c lib/src/tools.c lib/src/stringFunc.c lib/src/fileClient.c lib/src/commandClient.c lib/src/list.c -lpthread;
./client $1;