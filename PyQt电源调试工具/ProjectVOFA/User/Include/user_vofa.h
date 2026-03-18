#include "tae32f53xx_ll.h"
#include "dbg/tae32f53xx_dbg.h"
#include "user_tmr.h"
#include "stdlib.h"
#include "math.h"

typedef enum
{
  HEADER,
  DATA_ID,
  DATA_H,
  DATA_L,
  TAIL
} TYPE_MESSAGE_BYTE;

typedef enum
{
  KP_L,
  KP_C,
  I_MAX,
  KP1_DC,
  KI1,
  MAX_PI1,
  KP2_DC,
  KI2_DC,
  MAX_PI2,
  KP3,
  KI3,
  MAX_PI3,
  UdaK,
  UdbK,
  UdcK,
  Uda1K,
  Udb1K,
  Udc1K,
  KP_Q,
  KP_Z,
  KP_N,
  SPARE,
  AutoRun,
  Startup,
  Shutdown,
  Run,
  Stop,
  Reset,
  Clear,
  V_IN,
  I_IN,
  I_REF,
  V_BUS,
  CRC_H,
  CRC_L,
  DCSD,
  LIN_F,
} TYPE_DATA_ID;

typedef struct
{
  uint16_t kp_l;
  uint16_t kp_c;
  uint16_t i_max;
  uint16_t kp1_dc;
  uint16_t ki1;
  uint16_t max_pi1;
  uint16_t kp2_dc;
  uint16_t ki2_dc;
  uint16_t max_pi2;
  uint16_t kp3;
  uint16_t ki3;
  uint16_t max_pi3;
  uint16_t udak;
  uint16_t udbk;
  uint16_t udck;
  uint16_t uda1k;
  uint16_t udb1k;
  uint16_t udc1k;
  uint16_t kp_q;
  uint16_t kp_z;
  uint16_t kp_n;
  uint16_t spare;
  uint16_t autorun;
  uint16_t startup;
  uint16_t shutdown;
  uint16_t run;
  uint16_t stop;
  uint16_t reset;
  uint16_t clear;
  uint16_t v_in;
  uint16_t i_in;
  uint16_t i_ref;
  uint16_t v_bus;
  uint16_t crc_h;
  uint16_t crc_l;
  uint16_t dcsd;
  uint16_t lin_f;
} BoartDatas;

typedef struct
{
  float channel1;
  float channel2;
  float channel3;
  float channel4;
} WaveDatas;

void User_VOFA_RecvBoardData(uint16_t *datas, uint8_t *rxBuff);
void User_VOFA_SendBoardData(BoartDatas datas);
void User_VOFA_SendWaveData(float *datas);
void User_VOFA_Example();