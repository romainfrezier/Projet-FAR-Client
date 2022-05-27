cmake_minimum_required(VERSION 3.21)
project(Client C)

set(CMAKE_C_STANDARD 99)

add_executable(Client main.c lib/src/client.c lib/src/colors.c lib/src/tools.c lib/src/stringFunc.c lib/src/fileClient.c lib/src/commandClient.c lib/src/list.c)

