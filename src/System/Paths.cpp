#include <dirent.h>
#include <unistd.h>

#include "Paths.hpp"

Paths::Paths() {}
Paths::~Paths() {}

#include <bits/stdc++.h>
void Paths::fillPathList(vector<string> &list, string filepath) {
    string str;
    DIR *Folder;
    struct dirent *print;

    chdir(filepath.c_str());
    Folder = opendir(".");
    if (!Folder) {
        printf("Empty Folder :/\n");
        str.clear();
    }
    print = readdir(Folder);
    for (size_t i = 0; print; i ++) {
        if (print->d_type == DT_DIR);
        else {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            list.push_back(string(print->d_name));
        }
        print = readdir(Folder);
    }
    chdir("..");
    str.clear();
    sort(list.begin(), list.end()); 
}

string Paths::getPath(void) {
    char cwd[1024];

    getcwd(cwd, sizeof(cwd));
    return string(cwd);
}