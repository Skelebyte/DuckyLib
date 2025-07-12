default:
	gcc src/main.c src/duckylib/glad/glad.c -lSDL3 -lm

linux:
	gcc src/main.c src/duckylib/glad/glad.c -lSDL3 -lm

win:
	gcc src/main.c src/duckylib/glad/glad.c -Isrc/duckylib/glad -lSDL3 -lopengl32 -lgdi32 -lm

debug:
	gcc -o debug.out src/main.c src/duckylib/glad/glad.c -lSDL3 -lm -g -fsanitize=address
