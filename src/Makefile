all:
	g++ -c Color.cpp
	g++ -c Image.cpp
	g++ -c Vector2D.cpp
	ar rvs octographics.a Color.o Image.o Vector2D.o
	g++ octographics.cpp octographics.a -o octographics

clean:
	rm *.o *.a
	rm imagem.ppm
	rm octographics
