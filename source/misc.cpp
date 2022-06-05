#include <string>

#include <misc.h>

bool Misc::isInt(std::string x)
{
    if (x.empty()) return false;
    for (int i = 0; i < (int)x.length(); i++) if (!std::isdigit(x[i])) return false;
    return true;
}

const char* Misc::timeString(long millis)
{
    const char* ret;
    
    if (millis < 1000) ret = (
        std::to_string(millis) + "ms"
    ).c_str();
    else if (millis < 60000) ret = (
        std::to_string((int)(millis / 1000)) + "s " +
        std::to_string(millis % 1000) + "ms"
    ).c_str();

    return ret;
}