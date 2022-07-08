#include <libMath.h>
#include <iostream>


int main(int argc, char* argv[]) 
{
	Vector2 a = Vector2(10.f, 5.f);
	Vector2 b = Vector2(3.f, -3.f);

	Vector2 c = a + b;

	std::cout << "Vector2 a: " << a.x << "x " << a.y << "y " << std::endl;
	std::cout << "Vector2 b: " << b.x << "x " << b.y << "y " << std::endl;
	std::cout << "Vector2 c = a + b" << std::endl;
	std::cout << "Vector2 c: " << c.x << "x " << c.y << "y " << std::endl;
	Matrix4 mat = Matrix4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
	Matrix4 mat2 = Matrix4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
	Matrix4 mat3 = mat * mat2;

	return 0;
}