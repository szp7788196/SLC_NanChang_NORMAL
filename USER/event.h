#ifndef __EVENT_H
#define __EVENT_H

#include "sys.h"
#include "common.h"

#define SWITCH_ON_MIN_CURRENT		70.0f
#define SWITCH_OFF_MAX_CURRENT		70.0f

void RecordEventsECx(u8 ecx,u8 len,u8 *msg);
void CheckEventsEC15(u8 light_level);
void CheckEventsEC16(u8 light_level);
void CheckEventsEC17(u8 light_level);
void CheckEventsEC18(u8 light_level);
void CheckEventsEC19(u8 light_level,u8 get_e_para_ok);
void CheckEventsEC20(u8 light_level,u8 get_e_para_ok);
void CheckEventsEC28(u8 *cal1,u8 *cal2);
void CheckEventsEC51(u8 result,u16 version);
void CheckEventsEC52(u8 light_level);





































#endif
