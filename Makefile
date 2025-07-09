default:
	gcc src/main.c src/duckylib/glad/glad.c -lSDL3 -lm

debug:
	gcc -o debug.out src/main.c src/duckylib/glad/glad.c -lSDL3 -lm -g -fsanitize=address