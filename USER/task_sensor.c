#include "task_sensor.h"
#include "delay.h"
#include "sht2x.h"
#include "bh1750.h"
#include "task_net.h"
#include "common.h"
#include "inventr.h"
#include "rtc.h"
#include "usart.h"
#include "att7053c.h"
#include "ntc.h"

float InputCurrent = 0;
float InputVoltage = 0;
float InputFreq = 0.0f;
float InputPowerP = 0.0f;
float InputPowerQ = 0.0f;
float InputPowerS = 0.0f;
float InputPf = 0.0f;
float InputEnergyP = 0.0f;
float InputEnergyQ = 0.0f;
float InputEnergyS = 0.0f;
float Temperature = 0.0f;
float Humidity = 0.0f;
float Illumination = 0.0f;

TaskHandle_t xHandleTaskSENSOR = NULL;

SensorMsg_S *p_tSensorMsg = NULL;	//����װ�ڴ��������ݵĽṹ�����
unsigned portBASE_TYPE SENSOR_Satck;
void vTaskSENSOR(void *pvParameters)
{
	time_t times_sec_sim = 0;

	p_tSensorMsg = (SensorMsg_S *)mymalloc(sizeof(SensorMsg_S));

	ATT7053C_Init();
	
	while(1)
	{
		if(GetSysTick1s() - times_sec_sim >= 5)					//ÿ��5���ȡһ�δ���������
		{
			times_sec_sim = GetSysTick1s();

			if(PowerInterface == INTFC_DIGIT)
			{
				InventrOutPutCurrent = InventrGetOutPutCurrent();	//��ȡ��Դ�������
				delay_ms(500);
				InventrOutPutVoltage = InventrGetOutPutVoltage();	//��ȡ��Դ�����ѹ
			}

			delay_ms(100);
			InputCurrent 	= Att7053cGetCurrent();
			delay_ms(100);
			InputVoltage 	= Att7053cGetVoltage();
			delay_ms(100);
			InputFreq 		= Att7053cGetVoltageFreq();
			delay_ms(100);
			InputPowerP 	= 0.0f - Att7053cGetChannel1PowerP();
			delay_ms(100);
			InputPowerQ 	= Att7053cGetChannel1PowerQ();
			delay_ms(100);
			InputPowerS 	= Att7053cGetChannel1PowerS();
			delay_ms(100);
			InputEnergyP 	= Att7053cGetEnergyP();
			delay_ms(100);
			InputEnergyQ 	= Att7053cGetEnergyQ();
			delay_ms(100);
			InputEnergyS 	= sqrt(InputEnergyP * InputEnergyP + InputEnergyQ * InputEnergyQ);

//			Temperature 	= GetNTC_Temperature();

			if(ConnectState == MO_DATA_ENABLED)					//�豸��ʱ������״̬
			{
				p_tSensorMsg->in_put_current 	= (u16)(InputCurrent + 0.5f);
				p_tSensorMsg->in_put_voltage 	= (u16)(InputVoltage + 0.5f);
				p_tSensorMsg->in_put_freq 		= (u16)(InputFreq * 100.0f + 0.5f);
				p_tSensorMsg->in_put_power_p 	= InputPowerP >= 0 ? (s16)(InputPowerP + 0.5f) : (s16)(InputPowerP - 0.5f);
				p_tSensorMsg->in_put_power_q 	= InputPowerQ >= 0 ? (s16)(InputPowerQ + 0.5f) : (s16)(InputPowerQ - 0.5f);
				p_tSensorMsg->in_put_power_s 	= (u16)(InputPowerS + 0.5f);
				p_tSensorMsg->in_put_pf			= (u16)((float)(p_tSensorMsg->in_put_power_p / (float)p_tSensorMsg->in_put_power_s) * 100.0f + 0.5f);
				p_tSensorMsg->in_put_energy_p 	= (u32)(InputEnergyP * 1000.0f + 0.5f);
				p_tSensorMsg->in_put_energy_q 	= (u32)(InputEnergyQ * 1000.0f + 0.5f);
				p_tSensorMsg->in_put_energy_s 	= (u32)(InputEnergyS * 1000.0f + 0.5f);
				p_tSensorMsg->out_put_current 	= (u16)(InventrOutPutCurrent + 0.5f);
				p_tSensorMsg->out_put_voltage 	= (u16)(InventrOutPutVoltage + 0.5f);
				p_tSensorMsg->csq 				= 113 - (NB_ModulePara.csq * 2);
				p_tSensorMsg->temperature		= Temperature;
				p_tSensorMsg->humidity			= Humidity;
				p_tSensorMsg->illumination		= Illumination;
				p_tSensorMsg->light_level		= LightLevelPercent;

				p_tSensorMsg->year 				= calendar.w_year - 2000;
				p_tSensorMsg->month 			= calendar.w_month;
				p_tSensorMsg->date 				= calendar.w_date;
				p_tSensorMsg->hour 				= calendar.hour;
				p_tSensorMsg->minute 			= calendar.min;
				p_tSensorMsg->second 			= calendar.sec;
			}
		}

		delay_ms(1000);

//		SENSOR_Satck = uxTaskGetStackHighWaterMark(NULL);
	}
}






































