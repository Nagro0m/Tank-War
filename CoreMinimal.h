#pragma once
#pragma warning (disable : 4275)
#pragma warning (disable : 4244)
#pragma warning (disable : 4267)
#pragma warning (disable : 5056)

#pragma region STL
#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <typeindex>
#include <random>
#include <math.h>
#include <chrono>
#pragma endregion

#pragma region Collections
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <list>
#pragma endregion

#include "Color.h"

#pragma region SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#pragma endregion

#pragma region Define
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define Super __super
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) 
#define FORCEINLINE __forceinline
#define INLINE __inline
#define SLEEP(_duration) sleep(_duration)
#define NO_DISCARD _NODISCARD
#pragma endregion

using namespace std;
using namespace sf;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long long u_llong;