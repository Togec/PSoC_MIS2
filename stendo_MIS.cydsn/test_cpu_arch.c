#include "stdio.h"
#include "stdint.h"
#include "minunit.h"

char * test_cpu_pointers() {
    char * buffer[100];
    char * buffer_test[100];
    int index;
    
    int16_t int16_ref;
    int16_t int16_test;
    
    float float_ref;
    float float_test;
    
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        int16_ref = 0;
        //*(float *)(&buffer[index]) = int16_ref;
        memset(buffer, 0xFF, sizeof(buffer));
        memcpy(&buffer[index], &int16_ref, sizeof(int16_ref));
        memcpy(&int16_test, &buffer[index], sizeof(int16_test));
        sprintf(text, "copy int16_ref = 0 using memcpy(&buffer[index], &int16_ref, sizeof(int16_ref)), index = %d", index);
        it(text, int16_ref == int16_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        int16_ref = 0x4031;
        //*(float *)(&buffer[index]) = int16_ref;
        memset(buffer, 0x00, sizeof(buffer));
        memcpy(&buffer[index], &int16_ref, sizeof(int16_ref));
        memcpy(&int16_test, &buffer[index], sizeof(int16_test));
        sprintf(text, "copy int16_ref = 0x4031 using memcpy(&buffer[index], &int16_ref, sizeof(int16_ref)), index = %d", index);
        it(text, int16_ref == int16_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        int16_ref = 0;
        memset(buffer, 0xFF, sizeof(buffer));
        *(int16_t *)(&buffer[index]) = int16_ref;
        //memcpy(&buffer[index], &int16_ref, sizeof(int16_ref));
        memcpy(&int16_test, &buffer[index], sizeof(int16_test));
        sprintf(text, "copy int16_ref = 0 using memcpy(&buffer[index], &int16_ref, sizeof(int16_ref)), index = %d", index);
        it(text, int16_ref == int16_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        float_ref = 0.0;
        //*(float *)(&buffer[index]) = float_ref;
        memset(buffer, 0xFF, sizeof(buffer));
        memcpy(&buffer[index], &float_ref, sizeof(float_ref));
        memcpy(&float_test, &buffer[index], sizeof(float_test));
        sprintf(text, "copy float_ref = 0.0 using memcpy(&buffer[index], &float_ref, sizeof(float_ref), index = %d", index);
        it(text, float_ref == float_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        float_ref = 1.0;
        //*(float *)(&buffer[index]) = float_ref;
        memset(buffer, 0x00, sizeof(buffer));
        memcpy(&buffer[index], &float_ref, sizeof(float_ref));
        memcpy(&float_test, &buffer[index], sizeof(float_test));
        sprintf(text, "copy float_ref = 1.0 using memcpy(&buffer[index], &float_ref, sizeof(float_ref), index = %d", index);
        it(text, float_ref == float_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        float_ref = 0.0;
        memset(buffer, 0xFF, sizeof(buffer));
        *(float *)(&buffer[index]) = float_ref;
        //memcpy(&buffer[index], &float_ref, sizeof(float_ref));
        memcpy(&float_test, &buffer[index], sizeof(float_test));
        sprintf(text, "copy float_ref = 0.0 using *(float *)(&buffer[index]) = float_ref, index = %d", index);
        it(text, float_ref == float_test);
    }
    
    for (index = 0; index < sizeof(float_ref); index++)
    {
        float_ref = 1.0;
        memset(buffer, 0x00, sizeof(buffer));
        *(float *)(&buffer[index]) = float_ref;
        //memcpy(&buffer[index], &float_ref, sizeof(float_ref));
        memcpy(&float_test, &buffer[index], sizeof(float_test));
        sprintf(text, "copy float_ref = 1.0 using *(float *)(&buffer[index]) = float_ref, index = %d", index);
        it(text, float_ref == float_test);
    }
    
    return 0;
}

struct Tests TestCollection[] =
{
    {"CPU pointers", &test_cpu_pointers}
};

const int testsCount = sizeof(TestCollection)/sizeof(struct Tests);