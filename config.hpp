#ifndef CONFIG_H
#define CONFIG_H

#define USE_BUZZER_FOR_ALARM            0

#define USE_IAT_PARAMETER               1
#define USE_EGT_PARAMETER               1
#define USE_BATT_PARAMETER              1
#define USE_LAMBDA_PARAMETER            1
#define USE_LAMBDA_TARGET_PARAMETER     1
#define USE_CEL_PARAMETER               1
#define USE_AFR_TARGET_PARAMETER        0
#define USE_KNOCK_LEVEL_PARAMETER       0
#define USE_RPM_PARAMETER               0
#define USE_TPS_PARAMETER               0
#define USE_IGN_ANGLE_PARAMETER         0
#define USE_INJ_DC_PARAMETER            0

#define USE_CLT_PARAMETER               1
#define USE_CLT_WARNING                 1
#define USE_CLT_ERROR                   1
#define CLT_WARNING_VALUE               100
#define CLT_WARNING_CONDITION(val)      (val >= CLT_WARNING_VALUE)
#define CLT_ERROR_VALUE                 105
#define CLT_ERROR_CONDITION(val)        (val >= CLT_ERROR_VALUE)

#define USE_OIL_TEMP_PARAMETER          1
#define USE_OIL_TEMP_WARNING            1
#define USE_OIL_TEMP_ERROR              1
#define OIL_TEMP_WARNING_VALUE          110
#define OIL_TEMP_WARNING_CONDITION(val) (val >= OIL_TEMP_WARNING_VALUE)
#define OIL_TEMP_ERROR_VALUE            116
#define OIL_TEMP_ERROR_CONDITION(val)   (val >= OIL_TEMP_ERROR_VALUE)

#define USE_OIL_PRESS_PARAMETER         1
#define USE_OIL_PRESS_WARNING           1
#define USE_OIL_PRESS_ERROR             1
#define OIL_PRESS_WARNING_VALUE         2.0
#define OIL_PRESS_WARNING_CONDITION(val) (val <= OIL_PRESS_WARNING_VALUE)
#define OIL_PRESS_ERROR_VALUE           1.9
#define OIL_PRESS_ERROR_CONDITION(val)  (val < OIL_PRESS_ERROR_VALUE)

#define NUMBER_OF_DISPLAY_SETS          2
#define DISPLAY_SET_1_PARAMS            {CLT, OT, OP}
#define DISPLAY_SET_2_PARAMS            {IAT, LAMBDA, LAMBDA_TARGET}
#define DISPLAY_SETS                    {DISPLAY_SET_1_PARAMS, DISPLAY_SET_2_PARAMS}


#define GET_CLT_WARNING(val)            (CLT_WARNING_CONDITION(val)?true:false)
#define GET_CLT_ERROR(val)              (CLT_ERROR_CONDITION(val)?true:false)

#define GET_OIL_TEMP_WARNING(val)       (OIL_TEMP_WARNING_CONDITION(val)?true:false)
#define GET_OIL_TEMP_ERROR(val)         (OIL_TEMP_ERROR_CONDITION(val)?true:false)

#define GET_OIL_PRESS_WARNING(val)      (OIL_PRESS_WARNING_CONDITION(val)?true:false)
#define GET_OIL_PRESS_ERROR(val)        (OIL_PRESS_ERROR_CONDITION(val)?true:false)

#endif
