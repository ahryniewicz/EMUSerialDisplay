#include <EMUSerial.h>
#include "display.hpp"
#include "config.hpp"

/* ================= EMU related definitions =================== */
String sMAP;
String sAFR;
#if (USE_RPM_PARAMETER)
String sRPM;
#endif
#if (USE_TPS_PARAMETER)
String sTPS;
#endif
#if (USE_IAT_PARAMETER)
String sIAT;
#endif
#if (USE_IGN_ANGLE_PARAMETER)
String sIGN_ANGLE;
#endif
#if (USE_KNOCK_LEVEL_PARAMETER)
String sKNOCK_LEVEL;
#endif
#if (USE_INJ_DC_PARAMETER)
String sINJ_DC;
#endif
#if (USE_OIL_PRESS_PARAMETER)
String sOP;
#endif
#if (USE_OIL_TEMP_PARAMETER)
String sOT;
#endif
#if (USE_CLT_PARAMETER)
String sCLT;
#endif
#if (USE_LAMBDA_PARAMETER)
String sLAMBDA;
#endif
#if (USE_LAMBDA_TARGET_PARAMETER)
String sLAMBDA_TARGET;
#endif
#if (USE_AFR_TARGET_PARAMETER)
String sAFR_TARGET;
#endif

typedef enum {
  MAP,
  AFR,
#if (USE_RPM_PARAMETER)
  RPM,
#endif
#if (USE_TPS_PARAMETER)
  TPS,
#endif
#if (USE_IAT_PARAMETER)
  IAT,
#endif
#if (USE_IGN_ANGLE_PARAMETER)
  IGN_ANGLE,
#endif
#if (USE_KNOCK_LEVEL_PARAMETER)
  KNOCK_LEVEL,
#endif
#if (USE_INJ_DC_PARAMETER)
  INJ_DC,
#endif
#if (USE_OIL_PRESS_PARAMETER)
  OP,
#endif
#if (USE_OIL_TEMP_PARAMETER)
  OT,
#endif
#if (USE_CLT_PARAMETER)
  CLT,
#endif
#if (USE_LAMBDA_PARAMETER)
  LAMBDA,
#endif
#if (USE_LAMBDA_TARGET_PARAMETER)
  LAMBDA_TARGET,
#endif
#if (USE_AFR_TARGET_PARAMETER)
  AFR_TARGET,
#endif
  EMU_PARAMS_NUM
}emu_param_t;
EMUSerial emu(Serial1,Serial);
/* ================= /EMU related definitions ================== */

/* ================= Display related definitions =============== */
display_info_t emu_data[EMU_PARAMS_NUM] = {
  [MAP]={"MAP",&sMAP},
  [AFR]={"AFR",&sAFR},
#if (USE_RPM_PARAMETER)
  [RPM]={"RPM",&sRPM},
#endif
#if (USE_TPS_PARAMETER)
  [TPS]={"TPS",&sTPS},
#endif
#if (USE_IAT_PARAMETER)
  [IAT]={"IAT",&sIAT},
#endif
#if (USE_IGN_ANGLE_PARAMETER)
  [IGN_ANGLE]={"IGN_ANGLE",&sIGN_ANGLE},
#endif
#if (USE_KNOCK_LEVEL_PARAMETER)
  [KNOCK_LEVEL]={"KNOCK_LEVEL",&sKNOCK_LEVEL},
#endif
#if (USE_INJ_DC_PARAMETER)
  [INJ_DC]={"INJ_DC",&sINJ_DC},
#endif
#if (USE_OIL_PRESS_PARAMETER)
  [OP]={"OP",&sOP},
#endif
#if (USE_OIL_TEMP_PARAMETER)
  [OT]={"OT",&sOT},
#endif
#if (USE_CLT_PARAMETER)
  [CLT]={"CLT",&sCLT},
#endif
#if (USE_LAMBDA_PARAMETER)
  [LAMBDA]={"L",&sLAMBDA},
#endif
#if (USE_LAMBDA_TARGET_PARAMETER)
  [LAMBDA_TARGET]={"L_T",&sLAMBDA_TARGET},
#endif
#if (USE_AFR_TARGET_PARAMETER)
  [AFR_TARGET]={"AFR_TARGET",&sAFR_TARGET}
#endif
};
int DispalySets[NUMBER_OF_DISPLAY_SETS][3] = DISPLAY_SETS;
int ActiveDisplaySet;
/* ================= /Display related definitions ============== */

/* ================= Controller related definitions ============ */
int encoderPinA = 34;
int encoderPinB = 35;
int buttonPin = 32;

volatile int enc_val = 0;
volatile boolean button_pressed;
int last_enc_state;

#if (USE_BUZZER_FOR_ALARM)
int buzzerPin = 2;
hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR()
{
    digitalWrite(buzzerPin, !digitalRead(buzzerPin));
}
#endif

void button_handler(){
  Serial.println("Button pressed handler");
  button_pressed = true;
  detachInterrupt(buttonPin);
}

void encoder_handler(){
  int enc_state = digitalRead(encoderPinA);
  if (last_enc_state != enc_state) {
    if (digitalRead(encoderPinB) != enc_state) {
      enc_val++;
    } else {
      enc_val--;
    }
    last_enc_state = enc_state;
    detachInterrupt(encoderPinA);
  }
}
/* ================= /Controller related definitions =========== */


void setup(void)
{
  Serial.begin(115200); //Debugging

  /* EMU init*/
	Serial1.begin(19200, SERIAL_8N1, 19, -1); //EMU Serial setup, 8 Data Bits 1 Stopbit, RX Pin, TX Pin

  /* Encoder&PushButton init */
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(encoderPinA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinB, HIGH); //turn pullup resistor on
  last_enc_state = digitalRead(encoderPinA);
  attachInterrupt(encoderPinA,encoder_handler, CHANGE);
  attachInterrupt(buttonPin, button_handler, RISING);
  button_pressed = false;

  /* Display init */
  displayUp.p_info = &emu_data[MAP];
  displayDown.p_info = &emu_data[AFR];
  ActiveDisplaySet = 0;
  display[0].p_info = &emu_data[DispalySets[ActiveDisplaySet][0]];
  display[1].p_info = &emu_data[DispalySets[ActiveDisplaySet][1]];
  display[2].p_info = &emu_data[DispalySets[ActiveDisplaySet][2]];
  display_init();

#if (USE_BUZZER_FOR_ALARM)
  pinMode(buzzerPin, OUTPUT);
  Timer0_Cfg = timerBegin(0, 80000, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 500, true);
#endif
}

void loop()
{
/* ======================= Read EMU data ======================= */
  emu.checkEmuSerial();

  sMAP = String(emu.emu_data.MAP);
  sAFR = String(emu.emu_data.wboAFR,1);

#if (USE_RPM_PARAMETER)
  sRPM = String(emu.emu_data.RPM);
#endif

#if (USE_TPS_PARAMETER)
   sTPS = String(emu.emu_data.TPS);
#endif

#if (USE_IAT_PARAMETER)
  sIAT = String(emu.emu_data.IAT);
#endif

#if (USE_IGN_ANGLE_PARAMETER)
   sIGN_ANGLE = String(emu.emu_data.IgnAngle,1);
#endif

#if (USE_KNOCK_LEVEL_PARAMETER)
   sKNOCK_LEVEL = String(emu.emu_data.knockLevel,1);
#endif

#if (USE_INJ_DC_PARAMETER)
   sINJ_DC = String(emu.emu_data.injDC);
#endif

#if (USE_OIL_PRESS_PARAMETER)
  sOP = String(emu.emu_data.oilPressure);
#if (USE_OIL_PRESS_WARNING)
  emu_data[OP].warning = GET_OIL_PRESS_WARNING( emu.emu_data.oilPressure);
#endif
#if (USE_OIL_PRESS_ERROR)
  emu_data[OP].error = GET_OIL_PRESS_ERROR( emu.emu_data.oilPressure);
#endif
#endif /*USE_OIL_PRESS_PARAMETER*/

#if (USE_OIL_TEMP_PARAMETER)
  sOT = String(emu.emu_data.oilTemperature);
#if (USE_OIL_TEMP_WARNING)
  emu_data[OT].warning = GET_OIL_TEMP_WARNING( emu.emu_data.oilTemperature);
#endif
#if (USE_OIL_TEMP_ERROR)
  emu_data[OT].error = GET_OIL_TEMP_ERROR( emu.emu_data.oilTemperature);
#endif
#endif /*USE_OIL_TEMP_PARAMETER*/

#if (USE_CLT_PARAMETER)
  sCLT = String(emu.emu_data.CLT);
#if (USE_CLT_WARNING)
  emu_data[CLT].warning = GET_CLT_WARNING( emu.emu_data.CLT);
#endif
#if (USE_CLT_ERROR)
  emu_data[CLT].error = GET_CLT_ERROR( emu.emu_data.CLT);
#endif
#endif /*USE_CLT_PARAMETER*/

#if (USE_LAMBDA_PARAMETER)
  sLAMBDA = String(emu.emu_data.wboLambda,2);
#endif

#if (USE_LAMBDA_TARGET_PARAMETER)
  sLAMBDA_TARGET = String(emu.emu_data.lambdaTarget,2);
#endif

#if (USE_AFR_TARGET_PARAMETER)
   sAFR_TARGET = String(emu.emu_data.afrTarget,2);
#endif
/* ====================== /Read EMU data ======================= */

#if (USE_BUZZER_FOR_ALARM)
/* ====================== Buzzer alarm ========================= */
if (emu_data[OP].error || emu_data[OT].error || emu_data[CLT].error)
  timerAlarmEnable(Timer0_Cfg);
else {
  timerAlarmDisable(Timer0_Cfg);
  digitalWrite(buzzerPin, LOW);
}
/* ====================== /Buzzer alarm ======================== */
#endif

/* ====================== Update display ======================= */
  if (button_pressed) {
    ActiveDisplaySet++;
    if (ActiveDisplaySet >= NUMBER_OF_DISPLAY_SETS) {
      ActiveDisplaySet = 0;
    }

    display[0].p_info = &emu_data[DispalySets[ActiveDisplaySet][0]];
    display[1].p_info = &emu_data[DispalySets[ActiveDisplaySet][1]];
    display[2].p_info = &emu_data[DispalySets[ActiveDisplaySet][2]];
    button_pressed = false;
  }
  update_display(enc_val, button_pressed);
/* ===================== /Update display ======================= */


  attachInterrupt(buttonPin, button_handler, RISING);
  attachInterrupt(encoderPinA, encoder_handler, CHANGE);
}