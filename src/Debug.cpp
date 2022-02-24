//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_DEBUG_CPP
#define FP_OPENGL_DEBUG_CPP
#include <iostream>
using namespace std;

static bool DRAW_DEBUG = true;

class Debug {
public:
    static void log(string text, bool endLine = true){
        if(!DRAW_DEBUG) return;
        cout << text;
        if(endLine){
            cout << endl;
        }
    }
};

#endif //FP_OPENGL_DEBUG_CPP
