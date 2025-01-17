#include "Utilities.h"

u_int GetUniqueID()
{
	static u_int _id = 0;
	return ++_id;
}