#pragma once
#pragma warning (disable : 4275)

#pragma region STL
#include <iostream>
#include <string>
#include <fstream>
#pragma endregion

#pragma region Collections
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <list>
#pragma endregion

#pragma region SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#pragma endregion

using namespace std;
using namespace sf;

#define FORCEINLINE __forceinline
#define INLINE __inline
#define Super __super
#define SLEEP(_duration) sleep(_duration)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)