g++ -O1 src/*.cpp src/*.c  -o bin/world.exe -Wall -Wno-missing-braces -I include/. -I header/. -L lib -lSDL2 -lSDL2main -lopengl32 -lgdi32 -lwinmm -lws2_32 -luser32 -lshell32
bin\world.exe