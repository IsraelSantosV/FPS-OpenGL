//
// Created by aluno on 30/03/2022.
//

#ifndef VOXENGINE_FILEPATH_H
#define VOXENGINE_FILEPATH_H

#include <string>

class FilePath {
public:
    FilePath() = default;
    explicit FilePath(const std::string &filePath);
    std::string getAbsolutePath();
    std::string getExtension();
    std::string getName();
    std::string getPath();
private:
    std::string _absolutePath;
    std::string _path;
    std::string _name;
    std::string _extension;
};


#endif //VOXENGINE_FILEPATH_H
