/***********************************************************************
*
*  FILE        : boot_loader.c
*  DATE        : 2019-05-18
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_smc_entry.h"

#include "r_sci_rx_if.h"
#include "r_sci_rx_pinset.h"

#include "r_fwup_if.h"


#if !defined(MY_BSP_CFG_SERIAL_TERM_SCI)
#error "Error! Need to define MY_BSP_CFG_SERIAL_TERM_SCI in r_bsp_config.h"
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (0)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI0()
#define SCI_CH_serial_term          SCI_CH0
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (1)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI1()
#define SCI_CH_serial_term          SCI_CH1
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (2)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI2()
#define SCI_CH_serial_term          SCI_CH2
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (3)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI3()
#define SCI_CH_serial_term          SCI_CH3
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (4)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI4()
#define SCI_CH_serial_term          SCI_CH4
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (5)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI5()
#define SCI_CH_serial_term          SCI_CH5
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (6)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI6()
#define SCI_CH_serial_term          SCI_CH6
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (7)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI7()
#define SCI_CH_serial_term          SCI_CH7
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (8)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI8()
#define SCI_CH_serial_term          SCI_CH8
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (9)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI9()
#define SCI_CH_serial_term          SCI_CH9
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (10)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI10()
#define SCI_CH_serial_term          SCI_CH10
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (11)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI11()
#define SCI_CH_serial_term          SCI_CH11
#elif MY_BSP_CFG_SERIAL_TERM_SCI == (12)
#define R_SCI_PinSet_serial_term()  R_SCI_PinSet_SCI12()
#define SCI_CH_serial_term          SCI_CH12
#else
#error "Error! Invalid setting for MY_BSP_CFG_SERIAL_TERM_SCI in r_bsp_config.h"
#endif

void main(void);

/* Handle storage. */
sci_hdl_t     my_sci_handle;

void main(void)
{
    fwup_err_t  result_fwup;
    nop();
    R_SCI_PinSet_serial_term();

    if (FWUP_SUCCESS != R_FWUP_Open())
    {
        while(1)
        {
            /* Open error. infinity loop */
        }
    }

    /* Enable for update firmware. (Not used in initial firmware) */
    printf("[FWUP_main DEMO] Firmware update demonstration completed.\r\n");
    while(1)
    {
    	/* infinity loop */
    }

    while(1)
    {
		result_fwup = R_FWUP_Operation();
		if (FWUP_SUCCESS == result_fwup)
		{
		    printf("[FWUP_main] Firmware update completely.\r\n");
		    R_FWUP_SoftwareReset();
            while(1); /* infinite loop for waiting Software reset */
		}
		else if (FWUP_FAIL == result_fwup)
		{
		    if (FWUP_SUCCESS != R_FWUP_Close())
		    {
	            /* Close error. */
		        nop();
		    }
		    printf("[FWUP_main] Firmware update failed.\r\n");
			while(1)
			{
				/* infinity loop */
			}
		}
		else if (FWUP_IN_PROGRESS == result_fwup)
		{
			continue;
		}
		else
		{
			while(1)
			{
				/* infinite loop */
			}
		}
    }
}
