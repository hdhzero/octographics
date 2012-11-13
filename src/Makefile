all:
	g++ -c Color.cpp
	g++ -c Vertex.cpp
	g++ -c Image.cpp
	ar rvs octographics.a Color.o Image.o Vertex.o 
	g++ octographics.cpp octographics.a -o octographics

clean:
	rm -rf *.o *.a *.ppm octographics
