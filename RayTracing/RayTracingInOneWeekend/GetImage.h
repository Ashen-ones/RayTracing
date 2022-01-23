#pragma once
class GetImage
{
	enum ImageType
	{	
		ppm
	};
public :
	int imageW{-1};
	int imageH{-1};
	ImageType imageType = ImageType::ppm;
	
public:
		
	GetImage(int width, int height, ImageType iType) : imageW{ width }, imageH{ height }, imageType{ iType }{}
	void Init();
	void end();
	void Input2Txt();
	void SetHead();
	void CallCommand();
	void SetImageData();

private:
protected:
};


