#ifndef _NANO_H_
#define _NANO_H_

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
  NANO_VOICE_START, /*语音起始包*/
  NANO_VOICE_DATA,  /*语音数据包 - PCM数据*/
  NANO_VOICE_STOP,  /*语音结束包*/
} EN_VOICE_EVT;

typedef void (*VoiceDataCb)(EN_VOICE_EVT evt, char *pBuf, int pBufLen);

int Nano_Open(void);
int Nano_Close(void);
int Nano_Connected(void);
void Nano_RegisterDataReceivedCb(VoiceDataCb func);
void Nano_WavHashWrite(const char *, char *pBuf, int pBufLen);
void Nano_WavHashClose();
#ifdef __cplusplus
}
#endif
#endif
