/*! @file : sdk_gpiob.c
 * @author  Jose o.
 * @version 1.0.0
 * @brief   Driver para GPIOB
 * @details
 *
 */
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "sdk_gpiob.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions                                                                 *
 *******************************************************************************/

/*******************************************************************************
 * Private Prototypes                                                          *
 *******************************************************************************/

/*******************************************************************************
 * External vars                                                               *
 *******************************************************************************/

/*******************************************************************************
 * Private vars                                                                  *
 *******************************************************************************/

/*******************************************************************************
 * Private Source Code                                                         *
 *******************************************************************************/

/*******************************************************************************
 * Public Source Code                                                          *
 *******************************************************************************/

status_t GPIO_PinStatus(uint8_t *rgb_char, uint8_t *rgb_char_list, uint8_t status_pin) {
	uint8_t i = 0;
	uint16_t gpio_pin;
	uint16_t gpio_port;

	/* @ConditionalLoop Codificacion GPIO Pin y Status */
	for (i = 0; i <= 5; i++) {

		/* @ConditionalPin  Condicional de GPIO Pin */
		if (*rgb_char == rgb_char_list[i]) {

			/* @ConditionalPinStatusR GPIO Pin PTB6 (Led Red) */
			if (i == 0 || i == 1) {
				gpio_pin = kPTB6; /*!< KL02 pin-1 in QFN pinout diagram */
				break;
			} /* @EndConditionalPinStatusR */

			/* @ConditionalPinStatusG GPIO Pin PTB6 (Led Red) */
			if (i == 2 || i == 3) {
				gpio_pin = kPTB7; /*!< KL02 pin-2 in QFN pinout diagram */
				break;
			} /* @EndConditionalPinStatusG */

			/* @ConditionalPinStatusB GPIO Pin PTB6 (Led Red) */
			if (i == 4 || i == 5) {
				gpio_pin = kPTB10; /*!< KL02 pin-13 in QFN pinout diagram */
				break;
			} /* @EndConditionalPinStatusB */

		} /* @EndConditionalPin */

	} /* @EndConditionalLoop */

	/* Tomar los 8 bits MS del gpio_pin para asignar el codigo GPIO Port */
	gpio_port = gpio_pin & 0xFF00;
	gpio_port >>= 8; /*!< GPIO(Port) <- 0x0000 (Port A) o <- 0x0001 (Port B) */

	/* Solo disponible para rango de pines de (0 a 31) por Puerto */
	if ((gpio_pin & 0x00FF) > 0x001F)
		return (kStatus_Fail);

	/* Mascara para la funcion de estado Set o Clear */
	uint32_t gpio_mask = (uint32_t) (1 << ((uint8_t) gpio_pin));

	switch (gpio_port) {

	/* @CaseA Asignacion de Puerto A y Mascara al Pin seleccionado */
	case kGPIOA:
		/* @CaseA_Exe Ejecucion segun Pin Status, Clear (0) o Set (1)*/
		switch (status_pin) {
		case 0:
			GPIO_PortClear(GPIOA, gpio_mask);
			break;
		case 1:
			GPIO_PortSet(GPIOA, gpio_mask);
			break;
		default:
			return (kStatus_Fail);
			break;
		} /* @EndCaseA_Exe */
		break; /* @EndCaseA */

		/* @CaseB Asignacion de Puerto B y Mascara al Pin seleccionado */
	case kGPIOB:
		/* @CaseB_Exe Ejecucion segun Pin Status, Clear (0) o Set (1)*/
		switch (status_pin) {
		case 0:
			GPIO_PortClear(GPIOB, gpio_mask);
			break;
		case 1:
			GPIO_PortSet(GPIOB, gpio_mask);
			break;
		default:
			return (kStatus_Fail);
			break;
		} /* @EndCaseB_Exe */
		break; /* @EndCaseB */

	default:
		return (kStatus_Fail);
		break;

	}
	return (kStatus_Success);
}
