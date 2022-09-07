#ifndef _OTA_H__
#define _OTA_H__
//回调相关

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
  NANO_OTA_START,
  NANO_OTA_BATTERY,
  NANO_OTA_FILEVERSION,
  NANO_OTA_VERSION,
  NANO_OTA_CANCEL,
  NANO_OTA_PROGRESS,
  NANO_OTA_ERROR,
} EN_OTA_TYPE;

typedef enum {
  ERROR_TIMEOUT,       //通信超时，流程终止
  ERROR_FILENOTFOUND,  //找不到升级文件
  ERROR_NODEVICE,      //找不到升级设备
  ERROR_DEVINFOVERIFY, //设备验证失败
  ERROR_VERSION,       //固件版本获取失败
  ERROR_BATTERY,       //电池电量获取失败
  ERROR_RANDOMNUM,     //随机数发送失败
  ERROR_BINPIDVID,     //升级文件PID/VID与设备不匹配
  ERROR_BINFILEERROR,  // OTA文件校验失败
  ERROR_SAMEVERSION,   // OTA文件与固件版本一致无需升级
  ERROR_LOWBATTERY,    //遥控器电池电量过低
  ERROR_OTA16BYTEHEAR, // 16字节头文件发送失败
  ERROR_OTAIMAGEDATE,  //升级文件发送失败
  ERROR_OTA64BYTEHEAD, // 64字节头文件发送失败
  ERROR_OTAFINISH,     //升级结束指令发送失败
  ERROR_OTARESET,      //复位命令发送失败
} EN_ERROR_TYPE;

typedef struct {
  EN_OTA_TYPE type;
  char filepath[120];
  int percentageFlag;
} ST_START;

typedef struct {
  EN_OTA_TYPE type;
  short version;
} ST_VERSION;

typedef struct {
  EN_OTA_TYPE type;
  short battery;
} ST_BATTERY;

typedef struct {
  EN_OTA_TYPE type;
  short fileversion;
  char filepath[120];
} ST_FILEVERSION;

typedef struct {
  EN_OTA_TYPE type;
  double currentNum;
  double allNum;
  int percentage;
} ST_PROGRESS;

typedef struct {
  EN_OTA_TYPE type;
  EN_ERROR_TYPE error_type;
} ST_ERROR;

typedef union {
  EN_OTA_TYPE type;
  ST_START st_start;
  ST_VERSION st_version;
  ST_BATTERY st_battery;
  ST_FILEVERSION st_fileversion;
  ST_PROGRESS st_progress;
  ST_ERROR st_error;
} UN_OTAEvtMsg;

typedef void (*NanoOtaCb)(UN_OTAEvtMsg msg);

/*1: on debug mode  0: off debug mode*/
extern void Nano_SetDebugMode(char onoff);
extern void Nano_RegisterOTAReceivedCb(NanoOtaCb func);
extern void Nano_BleWriteOTA(UN_OTAEvtMsg msg);
#ifdef __cplusplus
}
#endif

#endif

