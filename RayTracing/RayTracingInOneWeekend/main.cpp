#include<iostream>
#include "vec3.h"
using namespace std;
void WriteColor(std::ostream& out, color pixColor)
{
	out << static_cast<int>(255.999 * pixColor.x()) << " "
		<< static_cast<int>(255.999 * pixColor.y()) << " "
		<< static_cast<int>(255.999 * pixColor.x()) << " ";

}

int main()
{
	const int imageWidth = 256;
	const int imageHeight = 256;
	//¹Ì¶¨¸ñÊ½
	std::cout<< "P3\n" << imageWidth<<" "<< imageHeight << "\n255\n";
	for (int i = imageHeight - 1;i>=0; i--)
	{
		for (int j = 0;j < imageWidth;j++)
		{
			color pixelCoor = color(double(i) / (imageWidth - 1),double(j) / (imageHeight - 1), 0.25);
			WriteColor(std::cout, pixelCoor);
		}
	}
}