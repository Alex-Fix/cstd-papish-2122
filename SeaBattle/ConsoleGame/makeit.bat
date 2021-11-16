gcc -c main.c game.c communication.c
gcc -o main main.o game.o communication.o
gcc -c game.c communication.c unit_tests.c
gcc -o unit_tests game.o communication.o unit_tests.o
gcc -c communication.c integration_tests.c
gcc -o integration_tests communication.o integration_tests.o
IF EXIST "*.o" DEL "*.o" /s