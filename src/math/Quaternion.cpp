//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/math/Quaternion.h"

const Quaternion Quaternion::ZERO = Quaternion();

Quaternion::Quaternion(){
    s = 0;
    v = Vector3::ZERO;
}


Quaternion::Quaternion(float uS,Vector3& uV):s(uS),v(uV){ }


Quaternion::~Quaternion(){ }


Quaternion::Quaternion(const Quaternion & value){

    s=value.s;
    v=value.v;

};


Quaternion& Quaternion::operator=(const Quaternion& value){

    s=value.s;
    v=value.v;

    return *this;
};

//add
void Quaternion::operator+=(const Quaternion& q){

    s+=q.s;
    v+=q.v;

}

Quaternion Quaternion::operator+(const Quaternion& q)const{

    float scalar=s+q.s;
    Vector3 imaginary=v+q.v;

    return Quaternion(scalar,imaginary);
}

//substract
void Quaternion::operator-=(const Quaternion& q){

    s-=q.s;
    v-=q.v;
}

Quaternion Quaternion::operator-(const Quaternion& q)const{

    float scalar=s-q.s;
    Vector3 imaginary=v-q.v;

    return Quaternion(scalar,imaginary);
}

//multiply
void Quaternion::operator*=(const Quaternion& q){

    (*this)=multiply(q);
}

Quaternion Quaternion::operator*(const Quaternion& q)const{

    float scalar=s*q.s - v.dot(q.v);

    Vector3 imaginary=q.v*s + v*q.s + v.cross(q.v);

    return Quaternion(scalar,imaginary);

}

Quaternion Quaternion::multiply(const Quaternion& q)const{

    float scalar=s*q.s - v.dot(q.v);

    Vector3 imaginary=q.v*s + v*q.s + v.cross(q.v);

    return Quaternion(scalar,imaginary);

}

void Quaternion::operator*=(const float value){

    s*=value;
    v*=value;
}


Quaternion Quaternion::operator*(const float value)const{

    float scalar=s*value;
    Vector3 imaginary=v*value;

    return Quaternion(scalar,imaginary);

}

Quaternion Quaternion::operator*(const Vector3& uValue)const{


    float sPart=-(v.x*uValue.x+ v.y*uValue.y + v.z*uValue.z);
    float xPart=s*uValue.x + v.y*uValue.z - v.z*uValue.y;
    float yPart=s*uValue.y + v.z*uValue.x - v.x*uValue.z;
    float zPart=s*uValue.z + v.x*uValue.y - v.y*uValue.x;

    Vector3 vectorPart(xPart,yPart,zPart);
    Quaternion result(sPart,vectorPart);

    return result;

}


float Quaternion::dot(Quaternion& q){

    return s*q.s+v.x*q.v.x+v.y*q.v.y+v.z*q.v.z;

}

//norm
float Quaternion::norm(){

    float scalar=s*s;
    float imaginary=v*v;

    return sqrt(scalar+imaginary);
}

//unit-norm
void Quaternion::normalize(){

    if (norm()!=0) {

        float normValue=1/norm();

        s*=normValue;
        v*=normValue;
    }
}


//conjugate
Quaternion Quaternion::conjugate(){

    float scalar=s;
    Vector3 imaginary=v*(-1);

    return Quaternion(scalar,imaginary);
}

//inverse
Quaternion Quaternion::inverse(){

    float absoluteValue=norm();
    absoluteValue*=absoluteValue;
    absoluteValue=1/absoluteValue;

    Quaternion conjugateValue=conjugate();

    float scalar=conjugateValue.s*(absoluteValue);
    Vector3 imaginary=conjugateValue.v*(absoluteValue);

    return Quaternion(scalar,imaginary);
}

void Quaternion::inverse(Quaternion& q){

    Quaternion dummy=q.inverse();

    q=dummy;
}

//Unit-Norm Quaternion (Special Form)
void Quaternion::convertToUnitNormQuaternion(){

    float angle=DegreesToRad(s);

    v.normalize();
    s=cosf(angle*0.5);
    v=v*sinf(angle*0.5);

}

//matrixTransform
Matrix3 Quaternion::transformQuaternionToMatrix3n(){

    // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
    //	0	3	6
    //	1	4	7
    //	2	5	8


    Matrix3 m;

    m.matrixData[0]=2*(s*s + v.x*v.x)-1;
    m.matrixData[3]=2*(v.x*v.y - s*v.z);
    m.matrixData[6]=2*(v.x*v.z + s*v.y);

    m.matrixData[1]=2*(v.x*v.y + s*v.z);
    m.matrixData[4]=2*(s*s + v.y*v.y)-1;
    m.matrixData[7]=2*(v.y*v.z - s*v.x);

    m.matrixData[2]=2*(v.x*v.z - s*v.y);
    m.matrixData[5]=2*(v.y*v.z + s*v.x);
    m.matrixData[8]=2*(s*s + v.z*v.z)-1;


    return m;
}

//euler to quaternion
void Quaternion::transformEulerAnglesToQuaternion(float x,float y, float z){

    x=DegreesToRad(x);
    y=DegreesToRad(y);
    z=DegreesToRad(z);

    x=x/2;
    y=y/2;
    z=z/2;

    s=cos(z)*cos(y)*cos(x)+sin(z)*sin(y)*sin(x);
    v.x=cos(z)*cos(y)*sin(x)-sin(z)*sin(y)*cos(x);
    v.y=cos(z)*sin(y)*cos(x)+sin(z)*cos(y)*sin(x);
    v.z=sin(z)*cos(y)*cos(x)-cos(z)*sin(y)*sin(x);


}

Vector3 Quaternion::transformQuaternionToEulerAngles(){

    // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
    //	0	3	6
    //	1	4	7
    //	2	5	8


    float x=0.0;
    float y=0.0;
    float z=0.0;

    float test=2*(v.x*v.z-s*v.y);

    if (test!=1 && test!=-1) {

        x=atan2(v.y*v.z + s*v.x, 0.5-(v.x*v.x+v.y*v.y));
        y=asin(-2*(v.x*v.z-s*v.y));
        z=atan2(v.x*v.y+s*v.z, 0.5-(v.y*v.y+v.z*v.z));

    }else if (test==1){
        z=atan2(v.x*v.y+s*v.z, 0.5-(v.y*v.y+v.z*v.z));
        y=-M_PI/2.0;
        x=-z+atan2(v.x*v.y-s*v.z, v.x*v.z+s*v.y);

    }else if(test==-1){

        z=atan2(v.x*v.y+s*v.z, 0.5-(v.y*v.y+v.z*v.z));
        y=M_PI/2.0;
        x=z+atan2(v.x*v.y-s*v.z, v.x*v.z+s*v.y);

    }

    x=RadToDegrees(x);
    y=RadToDegrees(y);
    z=RadToDegrees(z);

    Vector3 euler(x,y,z);

    return euler;
}

void Quaternion::transformMatrix3nToQuaternion(Matrix3 &uMatrix){

    // 3x3 matrix - column major. X vector is 0, 1, 2, etc. (openGL prefer way)
    //	0	3	6
    //	1	4	7
    //	2	5	8

    //calculate the sum of the diagonal elements


    float trace=uMatrix.matrixData[0]+uMatrix.matrixData[4]+uMatrix.matrixData[8];

    if (trace>0) {      //s=4*qw

        s=0.5*sqrt(1+trace);
        float S=0.25/s;

        v.x=S*(uMatrix.matrixData[5]-uMatrix.matrixData[7]);
        v.y=S*(uMatrix.matrixData[6]-uMatrix.matrixData[2]);
        v.z=S*(uMatrix.matrixData[1]-uMatrix.matrixData[3]);

    }else if(uMatrix.matrixData[0]>uMatrix.matrixData[4] && uMatrix.matrixData[0]>uMatrix.matrixData[8]){ //s=4*qx

        v.x=0.5*sqrt(1+uMatrix.matrixData[0]-uMatrix.matrixData[4]-uMatrix.matrixData[8]);
        float X=0.25/v.x;

        v.y=X*(uMatrix.matrixData[3]+uMatrix.matrixData[1]);
        v.z=X*(uMatrix.matrixData[6]+uMatrix.matrixData[2]);
        s=X*(uMatrix.matrixData[5]-uMatrix.matrixData[7]);

    }else if(uMatrix.matrixData[4]>uMatrix.matrixData[8]){ //s=4*qy

        v.y=0.5*sqrt(1-uMatrix.matrixData[0]+uMatrix.matrixData[4]-uMatrix.matrixData[8]);
        float Y=0.25/v.y;
        v.x=Y*(uMatrix.matrixData[3]+uMatrix.matrixData[1]);
        v.z=Y*(uMatrix.matrixData[7]+uMatrix.matrixData[5]);
        s=Y*(uMatrix.matrixData[6]-uMatrix.matrixData[2]);

    }else{ //s=4*qz

        v.z=0.5*sqrt(1-uMatrix.matrixData[0]-uMatrix.matrixData[4]+uMatrix.matrixData[8]);
        float Z=0.25/v.z;
        v.x=Z*(uMatrix.matrixData[6]+uMatrix.matrixData[2]);
        v.y=Z*(uMatrix.matrixData[7]+uMatrix.matrixData[5]);
        s=Z*(uMatrix.matrixData[1]-uMatrix.matrixData[3]);
    }


}

Vector3 Quaternion::rotateVectorAboutAngleAndAxis(float uAngle, Vector3& target, Vector3& uAxis){

    //convert our vector to a pure quaternion

    Quaternion p(0,target);

    //normalize the axis
    uAxis.normalize();

    //create the real quaternion
    Quaternion q(uAngle,uAxis);

    //convert quaternion to unit norm quaternion
    q.convertToUnitNormQuaternion();

    Quaternion qInverse=q.inverse();

    Quaternion rotatedVector=q*p*qInverse;

    return rotatedVector.v;

}


void Quaternion::show(){

    float x=v.x;
    float y=v.y;
    float z=v.z;

    std::cout<<"("<<s<<","<<x<<","<<y<<","<<z<<")"<<std::endl;
}

bool Quaternion::operator!=(const Quaternion &q) const {
    return q.s != s || q.v != v;
}
