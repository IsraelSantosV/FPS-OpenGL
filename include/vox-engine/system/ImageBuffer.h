//
// Created by zetta on 04/04/2022.
//

#ifndef VOXENGINE_IMAGEBUFFER_H
#define VOXENGINE_IMAGEBUFFER_H

class ImageBuffer {
public:
    virtual void enable() = 0;
    virtual void bind(unsigned int unit) = 0;
};

#endif //VOXENGINE_IMAGEBUFFER_H
