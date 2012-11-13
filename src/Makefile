all:
	g++ -c Color.cpp
	g++ -c Vertex.cpp
	g++ -c Matrix.cpp
	g++ -c Image.cpp
	ar rvs octographics.a Color.o Vertex.o Matrix.o Image.o
	g++ octographics.cpp octographics.a -o octographics

clean:
	rm -rf *.o *.a *.ppm octographics
