#include "GetImage.h"
#include <iostream>

void GetImage::Init()
{

}
void GetImage::End()
{

}
void GetImage::Input2Txt()
{

}

void GetImage::SetImageData()
{
	
}

void GetImage::SetHead()
{
	if (imageType == ImageType::ppm)
	{
		std::cout << "P3\n" << imageW << " " << imageH << "\n255\n";
	}
}
void GetImage::CallCommand()
{
	
}
