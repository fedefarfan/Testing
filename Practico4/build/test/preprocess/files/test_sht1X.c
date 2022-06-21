#include "src/errores.h"
#include "src/sht1X.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
void test_Sht1X_Configure_Init(void ){

    uint8_t value_data=195;

    uint8_t value_sck=102;

    

   _Bool 

        result;

    result=sht1X_Init(value_data,value_sck);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0000)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_HEX8);

}

void test_ERROR_Sht1X_Configure_Init(void ){

    uint8_t value_data=100;

    uint8_t value_sck=102;

    

   _Bool 

        result;

    result=sht1X_Init(value_data,value_sck);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0001)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_HEX8);

}

void test_TEMP_Configure_Measure(void ){

    uint8_t value=3;

    

   _Bool 

        result;

    result=sht1X_Measure_Configure_Comand(value);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0000)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_HEX8);

}

void test_HUM_Configure_Measure(void ){

    uint8_t value=5;

    

   _Bool 

        result;

    result=sht1X_Measure_Configure_Comand(value);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0000)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_HEX8);

}

void test_ERROR_Configure_Measure(void ){

    uint8_t value=8;

    

   _Bool 

        result;

    result=sht1X_Measure_Configure_Comand(value);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0001)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_HEX8);

}

void test_linear_hum_ESTIMATE(void ){

    uint16_t value_h=1635;

    

   _Bool 

        result;

    result=sht1X_linear_hum(value_h);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0000)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(154), UNITY_DISPLAY_STYLE_HEX8);

}

void test_ERROR_linear_hum_ESTIMATE(void ){

    uint16_t value_h=8546;

    

   _Bool 

        result;

    result=sht1X_linear_hum(value_h);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0001)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(176), UNITY_DISPLAY_STYLE_HEX8);

}

void test_True_linear_hum_ESTIMATE(void ){

    uint16_t value_h=1832;

    float temp_a=40.2;

    

   _Bool 

        result;

    result=sht1X_true_linear_hum(value_h,temp_a);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0x0000)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(199), UNITY_DISPLAY_STYLE_HEX8);

}
