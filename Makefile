default:
	gcc src/main.c src/duckylib/source/*.c src/duckylib/glad/glad.c -lSDL3 -lSDL3_ttf -lpthread -lm -ldl

linux:
	gcc src/main.c src/duckylib/source/*.c src/duckylib/glad/glad.c -lSDL3 -lSDL3_ttf -lpthread -lm -ldl

win:
	gcc src/main.c src/duckylib/source/*.c src/duckylib/glad/glad.c -Isrc/duckylib/glad -lSDL3 -lSDL3_ttf -lopengl32 -lgdi32 -lm

debug:
	gcc -o debug.out src/duckylib/source/*.c src/main.c src/duckylib/glad/glad.c -lSDL3 -lSDL3_ttf -lm -g -fsanitize=address
