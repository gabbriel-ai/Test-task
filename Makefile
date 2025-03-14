

all:
	gcc -Wall -Werror -Wextra -std=c++17 -pedantic main.cpp -o task.out -lstdc++

clean:
	rm task.out