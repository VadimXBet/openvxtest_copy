#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_

struct _momentsStruct
{
    double 	m00;
    double 	m10;
    double 	m01;
    double 	m20;
    double 	m11;
    double 	m02;
    double 	m30;
    double 	m21;
    double 	m12;
    double 	m03;

    double 	mu20;
    double 	mu11;
    double 	mu02;
    double 	mu30;
    double 	mu21;
    double 	mu12;
    double 	mu03;

    double 	nu20;
    double 	nu11;
    double 	nu02;
    double 	nu30;
    double 	nu21;
    double 	nu12;
    double 	nu03;
};

typedef struct _momentsStruct* momentsStruct;

#endif