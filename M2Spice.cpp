#include "Controller/AnalisisAlgorithms/MNAanalisis.h"
extern "C" {
    __attribute__((visibility("default"))) int Add(int a, int b) {
        return a + b;
    }

    __attribute__((visibility("default"))) void DoMath(double* data, int size) {
        for (int i = 0; i < size; ++i) {
            data[i] *= 2.0;
        }
    }
    __attribute__((visibility("default"))) int RE(){
            
            return 7;
    }

    
}
