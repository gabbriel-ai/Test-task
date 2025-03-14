

all:
	gcc -Wall -Werror -Wextra -std=c++17 main.cpp -o task.out -lstdc++

clean:
	rm task.out