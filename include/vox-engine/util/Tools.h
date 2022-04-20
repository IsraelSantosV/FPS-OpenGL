//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_TOOLS_H
#define VOXENGINE_TOOLS_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <vector>
#include <FreeImage.h>
#include "vox-engine/util/Logger.h"

class Tools {
public:
    static void split(const std::string &line, const std::string &delimiter, std::vector <std::string> &output);
    static void* loadTexture(const char* path);

    template<class T>
    static inline int strcpy_s(T* d, unsigned long dmax, const T* s){
        if(dmax <=1 || !d){
            if(!d || !dmax)
                return 22;

            *d = T(0);
            return 0;
        }

        for(T* de = d+dmax-1; (d !=de || (*d = T(0))) && (*d=*s); ++d, ++s);
        return 0;
    }

    template<class T>
    static bool contains(std::vector<T> list, T target){
        for(auto& i : list){
            if(i == target) return true;
        }

        return false;
    }
};

#endif //VOXENGINE_TOOLS_H
