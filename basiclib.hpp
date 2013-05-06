#ifndef BASIC_LIB
#define BASIC_LIB
#include <string>
#include <sstream>
#include <cstdlib>
#include <list>
#include <math.h>

const long double pi = 3.14159265358979323846264338327950288419716939937510;

template <class Type>
inline Type StringTo(std::string In)
{
    std::istringstream Stream;
    Stream.str(In);
    Type Out;
    Stream >> Out;
    return Out;
}

template <class Type>
inline std::string StringOf(Type In)
{
    std::ostringstream Stream;
    Stream << In;
    return Stream.str();
}

template <class Type>
inline Type DegToRad(Type x)
{
    return (x/180)*pi;
}

std::string MakeUpperCase(std::string In);
std::string MakeLowerCase(std::string In);
#endif
