#pragma once
#include "RTWeekend.h"
void WriteColor(std::ostream& out, Color pixColor)
{
	out << static_cast<int>(255.999 * pixColor.x()) << " "
		<< static_cast<int>(255.999 * pixColor.y()) << " "
		<< static_cast<int>(255.999 * pixColor.x()) << " ";
}
