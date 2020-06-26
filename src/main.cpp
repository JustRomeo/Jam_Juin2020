#include <ostream>
#include <iostream>

using namespace std;
static bool isEnvDisplay(char **env) {
    if (!env || !env[0])
        return false;
    for (size_t i = 0; env[i]; i ++) {
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    }
    return false;
}

int main(int ac, char **av, char **env) {
    if (!isEnvDisplay(env))
        return 84;
    return 0;
}