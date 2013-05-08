#ifndef MAIN_HPP
#define MAIN_HPP
/// Defines

/// Libraries
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
/// Namespaces
using namespace std;
/// Class Forward Declarations

/// Enumerations
enum HOST_OR_JOIN { HOST, JOIN };
enum EXIT_CODES { UNABLE_TO_LISTEN=1 };
/// Structs

/// Global Variables
const int PORT = 4567;
/// Global Functions
int main();
// -----
HOST_OR_JOIN HostOrJoin();
/// Project Files
#include "Tilemap.hpp"
#endif // MAIN_HPP
