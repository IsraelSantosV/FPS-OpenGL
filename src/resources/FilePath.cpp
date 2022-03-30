//
// Created by aluno on 30/03/2022.
//

#include "../../include/vox-engine/resources/FilePath.h"

#include <algorithm>
#include <string>

FilePath::FilePath(const std::string& filePath){
    _absolutePath = filePath;

    std::replace(_absolutePath.begin(), _absolutePath.end(), '\\', '/');

    std::size_t lastDot = _absolutePath.find_last_of('.');
    std::size_t lastDash = _absolutePath.find_last_of('/');
    std::size_t lastDash1 = lastDash + 1;

    if (lastDot == std::string::npos || lastDot < lastDash) {
        // No extension
        _extension = "";
        _name = _absolutePath.substr(lastDash1, _absolutePath.length() - lastDash1);
        _path = _absolutePath.substr(0, lastDash1);
    }
    else{
        _extension = _absolutePath.substr(lastDot);
        _name = _absolutePath.substr(lastDash1, lastDot - lastDash1);
        _path = _absolutePath.substr(0, lastDash1);
    }
}

std::string FilePath::getAbsolutePath(){
    return _absolutePath;
}

std::string FilePath::getExtension(){
    return _extension;
}

std::string FilePath::getName(){
    return _name;
}

std::string FilePath::getPath(){
    return _path;
}
