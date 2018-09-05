#include "stdafx.h"
#include "utils.h"

int Utils::getLength(const char* array)
{
	int length_array = sizeof(array);
	int length_type = sizeof(array[0]);
	return length_array / length_type;
}

int Utils::min(int a, int b)
{
	return a < b ? a : b;
}