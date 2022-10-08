#ifndef __YMODEM_H
#define __YMODEM_H
#include "sys.h"

#define SOH                     (0x01)  /* start of 128-byte data packet */
#define STX                     (0x02)  /* start of 1024-byte data packet */
#define EOT                     (0x04)  /* end of transmission */
#define ACK                     (0x06)  /* acknowledge */
#define NAK                     (0x15)  /* negative acknowledge */
#define CA                      (0x18)  /* two of these in succession aborts transfer */
#define CRC16                   (0x43)  /* 'C' == 0x43, request 16-bit CRC */


#define PACKET_SIZE_1024 1024
#define PACKET_SIZE_128 128

typedef enum {
	UPDATE_SUCCESS = 0,
	WAIT_ENTER_SYSTEM,
	BUSY,
	START_PROGRAM,
	UPDATE_PROGRAM,
	SET_PARAMETER
} ProcessStatus;

typedef void (*YModem_Callback)(ProcessStatus);
typedef  void (*JumpCallback)(void);

typedef struct {
	ProcessStatus process;
	uint8_t status;
	uint8_t id;
	uint32_t addr;
	uint32_t filesize;
	char filename[32];
	YModem_Callback cb;
} YModem;

typedef struct {
	uint8_t data[1200];
	uint16_t len;
} Buffer;

void set_ymodem_status(ProcessStatus process);
ProcessStatus get_ymodem_status(void);
void ymodem_recv(Buffer *p);
void ymodem_task(void);
void load_buf(u8 *data,u32 len);
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize);

#endif
