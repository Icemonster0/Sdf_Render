CPP = g++
FLAGS = -O3 -fopenmp
HEADERS = src/includes.h src/light.h src/object.h src/settings.h src/vec3.h

Sdf_Render: main.o render.o $(HEADERS)
	$(CPP) $(FLAGS) -o Sdf_Render main.o render.o

main.o: src/main.cpp $(HEADERS)
	$(CPP) $(FLAGS) -c src/main.cpp

render.o: src/render.cpp $(HEADERS)
	$(CPP) $(FLAGS) -c src/render.cpp

clean:
	rm main.o render.o Sdf_Render3
