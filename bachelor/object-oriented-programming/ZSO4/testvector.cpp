#include "SpaceVector.h"

int main(int argc, char const *argv[])
{
	SpaceVector v1;
	SpaceVector v2;

	v1.Set(0, 3.0);
	v1.Set(1, 2.0);
	v1.Set(2, 3.0);
	v2.Set(0, 5.0);
	v2.Set(2, 3.0);
	v2.Set(1, 4.0);
	(v1.Cross(v2)).SchrijfUit();

	return 0;
}
