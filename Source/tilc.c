#include "tilt.h"
#include "project.h"
#include "spi.h"

//#include <stdint.h>
//#include <stdlib.h>

enum adis16209_reg_e /*!< Register map. */
{
    adis16209_reg_endurance  = 0x0000, /*!< Diagnostics, flash write counter (16-bit binary) */
    adis16209_reg_supply_out = 0x0002, /*!< Output, power supply */
    adis16209_reg_xaccl_out  = 0x0004, /*!< Output, x-axis acceleration */
    adis16209_reg_yaccl_out  = 0x0006, /*!< Output, y-axis acceleration */
    adis16209_reg_aux_adc    = 0x0008, /*!< Output, auxiliary ADC */
    adis16209_reg_temp_out   = 0x000A, /*!< Output, temperature */
    adis16209_reg_xincl_out  = 0x000C, /*!< Output, ±90° x-axis inclination */
    adis16209_reg_yincl_out  = 0x000E, /*!< Output, ±90° y-axis inclination */
    adis16209_reg_rot_out    = 0x0010, /*!< Output, ±180° vertical rotational position */
    adis16209_reg_xaccl_null = 0x0012, /*!< Calibration, x-axis acceleration offset null */
    adis16209_reg_yaccl_null = 0x0014, /*!< Calibration, y-axis acceleration offset null */
    adis16209_reg_xincl_null = 0x0016, /*!< Calibration, x-axis inclination offset null */
    adis16209_reg_yincl_null = 0x0018, /*!< Calibration, y-axis inclination offset null */
    adis16209_reg_rot_null   = 0x001A, /*!< Calibration, vertical rotation offset null */
    adis16209_reg_alm_mag1   = 0x0020, /*!< Alarm 1, amplitude threshold */
    adis16209_reg_alm_mag2   = 0x0022, /*!< Alarm 2, amplitude threshold */
    adis16209_reg_alm_smpl1  = 0x0024, /*!< Alarm 1, sample period */
    adis16209_reg_alm_smpl2  = 0x0026, /*!< Alarm 2, sample period */
    adis16209_reg_alm_ctrl   = 0x0028, /*!< Alarm, source control register */
    adis16209_reg_aux_dac    = 0x0030, /*!< Auxiliary DAC data */
    adis16209_reg_gpio_ctrl  = 0x0032, /*!< Operation, digital I/O configuration and data */
    adis16209_reg_msc_ctrl   = 0x0034, /*!< Operation, data-ready and self-test control */
    adis16209_reg_smpl_prd   = 0x0036, /*!< Operation, sample rate configuration */
    adis16209_reg_avg_cnt    = 0x0038, /*!< Operation, filter configuration */
    adis16209_reg_slp_cnt    = 0x003A, /*!< Operation, sleep mode control */
    adis16209_reg_status     = 0x003C, /*!< Diagnostics, system status register */
    adis16209_reg_command    = 0x003E  /*!< Operation, system command register */
};

static void adis16209_chip_select_clear(void)
{
	LATCbits.LATC1 = 0;
}

static void adis16209_chip_select_set(void)
{
	LATCbits.LATC1 = 1;
}

static void adis16209_write_spi(unsigned char data)
{
	if (PIE1bits.SSPIE == 1)
	{
		PIE1bits.SSPIE = 0;
		WriteSPI(data);
		PIE1bits.SSPIE = 1;
	}
	else
	{
		WriteSPI(data);
	}
}

static unsigned char adis16209_read_spi(void)
{
	unsigned char ret;
	
	if (PIE1bits.SSPIE == 1)
	{
		PIE1bits.SSPIE = 0;
		ret = ReadSPI();
		PIE1bits.SSPIE = 1;
	}
	else
	{
		ret = ReadSPI();
	}
	return ret;
}
unsigned short adis16209_get_status(void)
{
    unsigned char statusHigh;
    unsigned char statusLow;

    adis16209_chip_select_clear();

    //adis16209_spi_transfer(adis16209_reg_status, &statusHigh);
    adis16209_write_spi((unsigned char)adis16209_reg_status);
    statusHigh = adis16209_read_spi();
	//adis16209_spi_transfer(adis16209_reg_status+1, &statusLow);
	adis16209_write_spi((unsigned char)adis16209_reg_status + 1);
	statusLow = adis16209_read_spi();
	
    adis16209_chip_select_set();

    return (unsigned short)(statusHigh << 8) | statusLow;
}

unsigned char adis16209_get_sample_rate(void)
{
	unsigned char rate;
	
	adis16209_chip_select_clear();

	adis16209_write_spi((unsigned char)adis16209_reg_smpl_prd + 1);
	rate = adis16209_read_spi();
	
    adis16209_chip_select_set();

    return rate;
}

/*
void adis16209_get_accl(int16_t* x, int16_t* y)
{
    static unsigned char regHigh;
    static unsigned char regLow;

    adis16209_chip_select_clear();
    adis16209_spi_transfer(adis16209_reg_xaccl_out, NULL);
    adis16209_spi_transfer(0xFF, NULL);
    adis16209_chip_select_set();

    OSTimeDlyHMSM(0,0,0,1);

    adis16209_chip_select_clear();
    adis16209_spi_transfer(adis16209_reg_xincl_out, &regHigh);
    adis16209_spi_transfer(0xFF, &regLow);
    adis16209_chip_select_set();
    regHigh &= 0x3F;
    if((regHigh & 0x20) != 0)
    {
        regHigh |= 0xC0;
    }
    *x = (int16_t)(regHigh<<8) | regLow;

    OSTimeDlyHMSM(0,0,0,1);

    adis16209_chip_select_clear();
    adis16209_spi_transfer(adis16209_reg_xincl_out, &regHigh);
    adis16209_spi_transfer(0xFF, &regLow);
    adis16209_chip_select_set();
    regHigh &= 0x3F;
    if((regHigh & 0x20) != 0)
    {
        regHigh |= 0xC0;
    }
    *y = (int16_t)(regHigh<<8) | regLow;
}
*/
