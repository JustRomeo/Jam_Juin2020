#include "ErrorHandling.hpp"

ErrorHandling::ErrorHandling() {}
ErrorHandling::~ErrorHandling() {}

bool ErrorHandling::isEnvDisplay(char **env) {
    if (!env || !env[0])
        return false;
    for (size_t i = 0; env[i]; i ++)
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    return false;
}