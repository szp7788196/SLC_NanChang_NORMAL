#ifndef __UART4_H
#define __UART4_H
#include "sys.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "fifo.h"
#include "ringbuf.h"

#define NET_BUF_MAX_LEN			1024

extern volatile char rsp_ok;
extern RingBuf ring_fifo;
extern RingBuf ring_fifo1;
extern uint8_t rx_fifo[NET_BUF_MAX_LEN];
extern uint8_t rx_fifo1[NET_BUF_MAX_LEN];
extern int8_t dl_buf_id;

/*
 *  @brief USART2初始化函数
 */
void USART2_Init(u32 bound);
/*
 *  @brief USART2串口发送api
 */
void USART2_Write(uint8_t *Data, uint32_t len);

#endif

