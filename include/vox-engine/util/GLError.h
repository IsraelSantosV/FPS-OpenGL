//
// Created by aluno on 30/03/2022.
//

#ifndef VOXENGINE_GLERROR_H
#define VOXENGINE_GLERROR_H

#include "Logger.h"

void _check_gl_error(const char *file, int line);

///
/// Usage:
/// [... some opengl calls]
/// glCheckError();
///
#define glCheckError() _check_gl_error(__FILE__,__LINE__)

#endif //VOXENGINE_GLERROR_H
