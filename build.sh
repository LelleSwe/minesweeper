#gcc -c -o board.o board.c -O0 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
#gcc -c -o mgui.o mgui.c -O0 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
#gcc -c -o main.o main.c -O0 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

gcc -o main.elf main.c mgui.c board.c -O3 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11