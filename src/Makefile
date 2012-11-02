all:
	g++ -c Color.cpp
	g++ -c Image.cpp
	g++ -c Vector2D.cpp
	g++ -c Vector.cpp
	ar rvs octographics.a Color.o Image.o Vector2D.o Vector.o
	g++ octographics.cpp octographics.a -o octographics

clean:
	rm *.o *.a
	rm imagem.ppm
	rm octographics
