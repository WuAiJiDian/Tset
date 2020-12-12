/*******************************************************************************
**----------------------------------------------------------------------------**
** Copyright (c) 2018 by JEE.		All rights reserved.

** This software is copyright protected and proprietary to JEE.
** JEE grants to you only those rights as set out in the license conditions.
** All other rights remain with JEE.
**----------------------------------------------------------------------------**
**
* Administrative Information
* $Namespace_: \xx\xx$
* $Class_____: C$
* $Name______: CPLD_Drv.c$
* $Variant___: 0.0.0$
* $Revision__: 0$
* $Author____: XM$
**
**----------------------------------------------------------------------------**
** MAY BE CHANGED BY USER [Yes/No]: No
**----------------------------------------------------------------------------**
** DESCRIPTION:
			The Cpld Drive code file to achieve Communicate with CPLD.
**----------------------------------------------------------------------------**
** HISTORY:
V1.0.0:   Initial version.

*******************************************************************************/
#include "EMER_ShutOff_Drv.h"
#include "Dem.h"
#include "IfxScu_reg.h"
#include "IfxPort_reg.h"
#include "Gtm.h"
#include "Icu_17_GtmCcu6.h"
#include "Dio.h"


typedef void (*EMER_ShutOffActionType)(void);
typedef struct
{
	uint8 FaultType;
	EMER_ShutOffActionType EMER_ShutOffAction;
}st_EMER_ShutOffType;

typedef struct
{
	unsigned int F0:1;
	unsigned int F1:1;
	unsigned int F2:1;
	unsigned int F3:1;
	unsigned int F4:1;
	unsigned int reserved_27:27;
} EMER_FaultSort_Bits;

typedef union
{
	unsigned int U;                         /**< \brief Unsigned access */
	signed int I;                           /**< \brief Signed access */
	EMER_FaultSort_Bits B;                    /**< \brief Bitfield access */
} un_EMER_FaultTSortype;

un_EMER_FaultTSortype EMER_FaultSort_un;





static void EMER_ShutOff_UpperASC(void);

static void EMER_ShutOff_UnderAsc(void);

static void EMER_ShutOff_UrgencyASC(void);

static void EMER_ShutOff_FreeWheel(void);

st_EMER_ShutOffType  EMER_ShutOffCfg_st[32u]=
{
		{	0	,	EMER_ShutOff_UpperASC	}	,
		{	1	,	EMER_ShutOff_UpperASC	}	,
		{	2	,	EMER_ShutOff_UpperASC	}	,
		{	3	,	EMER_ShutOff_UpperASC	}	,
		{	4	,	EMER_ShutOff_UpperASC	}	,
		{	5	,	EMER_ShutOff_UnderAsc	}	,
		{	6	,	EMER_ShutOff_UnderAsc	}	,
		{	7	,	EMER_ShutOff_UnderAsc	}	,
		{	8	,	EMER_ShutOff_UnderAsc	}	,
		{	9	,	EMER_ShutOff_UnderAsc	}	,
		{	10	,	EMER_ShutOff_UnderAsc	}	,
		{	11	,	EMER_ShutOff_UnderAsc	}	,
		{	12	,	EMER_ShutOff_UnderAsc	}	,
		{	13	,	EMER_ShutOff_UnderAsc	}	,
		{	14	,	EMER_ShutOff_UnderAsc	}	,
		{	15	,	EMER_ShutOff_UnderAsc	}	,
		{	16	,	EMER_ShutOff_UnderAsc	}	,
		{	17	,	EMER_ShutOff_UnderAsc	}	,
		{	18	,	EMER_ShutOff_UnderAsc	}	,
		{	19	,	EMER_ShutOff_UnderAsc	}	,
		{	20	,	EMER_ShutOff_UnderAsc	}	,
		{	21	,	EMER_ShutOff_UnderAsc	}	,
		{	22	,	EMER_ShutOff_UnderAsc	}	,
		{	23	,	EMER_ShutOff_UnderAsc	}	,
		{	24	,	EMER_ShutOff_UnderAsc	}	,
		{	25	,	EMER_ShutOff_UnderAsc	}	,
		{	26	,	EMER_ShutOff_UnderAsc	}	,
		{	27	,	EMER_ShutOff_UnderAsc	}	,
		{	28	,	EMER_ShutOff_UnderAsc	}	,
		{	29	,	EMER_ShutOff_UnderAsc	}	,
		{	30	,	EMER_ShutOff_UnderAsc	}	,
		{	31	,	EMER_ShutOff_UnderAsc	}	,
};

static void EMER_ShutOff_UpperASC(void)
{
	P02_OUT.B.P1=0x1;
	P02_OUT.B.P2=0x0;
	P02_OUT.B.P3=0x1;
	P02_OUT.B.P4=0x0;
	P02_OUT.B.P5=0x1;
	P02_OUT.B.P6=0x0;
}
static void EMER_ShutOff_UnderAsc(void)
{
	P02_OUT.B.P1=0x0;
	P02_OUT.B.P2=0x1;
	P02_OUT.B.P3=0x0;
	P02_OUT.B.P4=0x1;
	P02_OUT.B.P5=0x0;
	P02_OUT.B.P6=0x1;
}
static void EMER_ShutOff_UrgencyASC(void)
{

}
static void EMER_ShutOff_FreeWheel(void)
{

}

/*******************************************************************************
** Function Name : EmergencyStop_Init
** Parameter[in] : void
** Parameter[out]: void
** Return Value  : void
** Note          :
** Description   :
*******************************************************************************/
static void EmergencyStop_PortInit()
{
	Mcal_ResetCpuENDINIT(-1);
	Mcal_ResetCpuENDINIT(0);
	P02_ESR.B.EN1=0x1;
	P02_ESR.B.EN2=0x1;
	P02_ESR.B.EN3=0x1;
	P02_ESR.B.EN4=0x1;
	P02_ESR.B.EN5=0x1;
	P02_ESR.B.EN6=0x1;
	Mcal_SetCpuENDINIT(0);
	Mcal_SetCpuENDINIT(-1);
}
/*******************************************************************************
** Function Name : EmergencyStop_Init
** Parameter[in] : void
** Parameter[out]: void
** Return Value  : void
** Note          :
** Description   :
*******************************************************************************/
void EmergencyStop_Init()
{
	EmergencyStop_PortInit();

	Mcal_ResetCpuENDINIT(-1);
	Mcal_ResetCpuENDINIT(0);
	SCU_EMSR.B.POL=0x1;
	SCU_EMSR.B.MODE=0x0;
	SCU_EMSR.B.PSEL=0x1;
	SCU_EMSR.B.ENON=0x1;
	Mcal_SetCpuENDINIT(0);
	Mcal_SetCpuENDINIT(-1);
}


/*******************************************************************************
** Function Name : EmergencyStopChannelImmediately
** Parameter[in] : void
** Parameter[out]: void
** Return Value  : void
** Note          : static
** Description   :
*******************************************************************************/
void EmergencyStop_ChannelImmediately(void)/*ISR*/
{
	uint8 EMER_FaultSort_u8;
	/*1、 freeWheel*/

	EMER_FaultSort_un.B.F0 = Dio_ReadChannel(1);	/*DI_UDCOV_P22_11*/
	EMER_FaultSort_un.B.F1 = Dio_ReadChannel(1);	/*DI_IPHAOC_P22_10*/
	EMER_FaultSort_un.B.F2 = Dio_ReadChannel(1);	/*DI_RDYHS_P33_0*/
	EMER_FaultSort_un.B.F3 = Dio_ReadChannel(1);	/*DI_NFLTH_P13_2*/
	EMER_FaultSort_un.B.F4 = Dio_ReadChannel(1);	/*DI_NFLTL_P13_3*/

	EMER_FaultSort_u8 = EMER_FaultSort_un.U;

	EMER_ShutOffCfg_st[EMER_FaultSort_u8].EMER_ShutOffAction();

	P02_IOCR0.B.PC1=0x10;
	P02_IOCR0.B.PC2=0x10;
	P02_IOCR0.B.PC3=0x10;
	P02_IOCR4.B.PC4=0x10;
	P02_IOCR4.B.PC5=0x10;
	P02_IOCR4.B.PC6=0x10;

	Mcal_ResetCpuENDINIT(-1);
	Mcal_ResetCpuENDINIT(0);
	SCU_EMSR.B.EMSFM=0x2;
	Mcal_SetCpuENDINIT(0);
	Mcal_SetCpuENDINIT(-1);

	Gtm_ModifyOutputCtrl (0, 0, 9, 0);
	Gtm_ModifyOutputCtrl (0, 0, 10, 0);
	Gtm_ModifyOutputCtrl (0, 0, 11, 0);
	Gtm_ModifyOutputCtrl (0, 0, 12, 0);
	Gtm_ModifyOutputCtrl (0, 0, 13, 0);
	Gtm_ModifyOutputCtrl (0, 0, 14, 0);
	/*ASC*/
}




uint32 EMER_Stop_NotificationCnt_u32;
void EMER_Stop_Notification()
{
	EmergencyStop_ChannelImmediately();
	Icu_17_GtmCcu6_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_EMER_Stop);/*允许进入一次*/
	EMER_Stop_NotificationCnt_u32++;
}




