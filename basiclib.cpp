#include <string>
#include "basiclib.hpp"

using namespace std;

string makeUpperCase(string In)
{
    for(string::size_type loop=0; loop<In.length(); loop++)
    {
        if (In[loop] >= 97 && In[loop] <= 122)
        {
            In[loop] -= 32;
        }
    }
    return In;
}

string makeLowerCase(string In)
{
    for(string::size_type loop=0; loop<In.length(); loop++)
    {
        if (In[loop] >= 65 && In[loop] <= 90)
        {
            In[loop] += 32;
        }
    }
    return In;
}
