#pragma once
#include "vec3.h"
void WriteColor(std::ostream& out, color pixColor)
{
	out << static_cast<int>(255.999 * pixColor.x()) << " "
		<< static_cast<int>(255.999 * pixColor.y()) << " "
		<< static_cast<int>(255.999 * pixColor.x()) << " ";
}
