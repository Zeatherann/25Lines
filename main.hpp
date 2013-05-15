#ifndef MAIN_HPP
#define MAIN_HPP
/// Defines

/// Libraries
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <boost/thread.hpp>
/// Namespaces
using namespace std;
/// Class Forward Declarations

/// Enumerations
enum HOST_OR_JOIN { HOST, JOIN };
enum EXIT_CODES { UNABLE_TO_LISTEN=1, UNABLE_TO_CONNECT, FAILED_TO_LOAD_RESOURCE };
/// Structs

/// Typedefs
typedef std::pair<int, int> pairi;
typedef std::pair<float, float> pairf;
/// Global Variables
const int PORT = 4567;
/// Global Functions
int main();
// -----
HOST_OR_JOIN HostOrJoin();
/// Project Files
#include "ResourceCache.hpp"
#include "Tilemap.hpp"
#endif // MAIN_HPP
