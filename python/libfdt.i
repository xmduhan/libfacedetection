%module libfdt

%{
    #define SWIG_FILE_WITH_INIT
    #include "libfdt.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

%apply (int DIM1, int DIM2, int DIM3, unsigned char* IN_ARRAY3) {(int rows, int cols, int n, unsigned char* img)}
%include "libfdt.h"
