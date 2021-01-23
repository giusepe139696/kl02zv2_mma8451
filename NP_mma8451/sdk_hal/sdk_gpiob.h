/*! @file : sdk_gpiob.h
 * @author  Jose .o
 * @version 1.0.0
 * @brief   Driver para GIPOB
 * @details
 *
 */
#ifndef SDK_GPIOB_H_
#define SDK_GPIOB_H_
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "fsl_common.h"

/*!
 * @addtogroup SDK_HAL
 * @{
 */
/*!
 * @addtogroup GPIOB
 * @{
 */

/*******************************************************************************
 * Public Definitions                                                          *
 *******************************************************************************/

/*!
 * @brief Lista de Puertos disponibles para GPIO para la MKL02Z32
 */
enum _gpio_port_list_available {
	kGPIOA = 0X00, /*!<GPIO in Port A*/
	kGPIOB /*!<GPIO in Port B*/
};

/*!
 * @brief Lista de Pines disponibles para GPIO por Puerto para la MKL02Z32.
 */
enum _gpio_pin_list_available {
	/*!< Pin GPIO in Port A*/
	kPTA0 = 0x0000, /*!< PTA0/IRQ_0/SWD_CLK ADC0_SE12/CMP0_IN2/TPM1_CH0*/
	kPTA1, /*!< PTA1/IRQ_1/LPTMR0_ALT1/RESET_b*/
	kPTA2, /*!< PTA2/SWD_DIO/CMP0_OUT*/
	kPTA3, /*!< PTA3/EXTAL0/I2C0_SCL/I2C1_SDA*/
	kPTA4, /*!< PTA4/XTAL0/I2C0_SDA/I2C1_SCL*/
	kPTA5, /*!< PTA5/TPM0_CH1/SPI0_SS_b*/
	kPTA6, /*!< PTA6/TPM0_CH0/SPI0_MISO*/
	kPTA7, /*!< PTA7/IRQ_4/ADC0_SE7/SPI0_MISO/SPI0_MOSI*/
	kPTA8, /*!< PTA8/ADC0_SE3/I2C1_SCL*/
	kPTA9, /*!< PTA9/ADC0_SE2/I2C1_SDA*/
	kPTA10, /*!< PTA10/IRQ_8*/
	kPTA11, /*!< PTA11/IRQ_9*/
	kPTA12, /*!< PTA12/IRQ_13/LPTMR0_ALT2/ADC0_SE0/CMP0_IN0/TPM1_CH0/TPM_CLKIN0*/
	kPTA13, /*!< PTA13*/
	kPTA14, /*!< Not available*/
	kPTA15, /*!< Not available*/

	/*!< Pin GPIO in Port B*/
	kPTB0 = 0x0100, /*!< PTB0/IRQ_5/ADC0_SE6/EXTRG_IN/SPI0_SCK*/
	kPTB1, /*!< PTB1/IRQ_6/ADC0_SE5/CMP0_IN3/UART0_TX/UART0_RX*/
	kPTB2, /*!< PTB2/IRQ_7/ADC0_SE4/UART0_RX/UART0_TX*/
	kPTB3, /*!< PTB3/IRQ_10/I2C0_SCL/UART0_TX*/
	kPTB4, /*!< PTB4/IRQ_11/I2C0_SDA UART0_RX*/
	kPTB5, /*!< PTB5/IRQ_12/NMI_b/ADC0_SE1/CMP0_IN1/TPM1_CH1*/
	kPTB6, /*!< PTB6/IRQ_2/LPTMR0_ALT3/TPM1_CH1/TPM_CLKIN1*/
	kPTB7, /*!< PTB7/IRQ_3/TPM1_CH0*/
	kPTB8, /*!< PTB8/ADC0_SE11*/
	kPTB9, /*!< PTB9/ADC0_SE10*/
	kPTB10, /*!< PTB10/ADC0_SE9/TPM0_CH1*/
	kPTB11, /*!< PTB11/ADC0_SE8/TPM0_CH0*/
	kPTB12, /*!< PTB12*/
	kPTB13, /*!< PTB13/ADC0_SE13/TPM1_CH1*/
	kPTB14, /*!< Not available*/
	kPTB15, /*!< Not available*/
};

/*******************************************************************************
 * External vars                                                               *
 *******************************************************************************/

/*******************************************************************************
 * Public vars                                                                 *
 *******************************************************************************/

/*******************************************************************************
 * Public Prototypes                                                           *
 *******************************************************************************/
/*!
 * @brief Establece el estado específico del RGB
 *
 * @param rgb_char 			Apuntador al dato o caracter enviado por UART0
 *
 * @param rgb_char_list 	Apuntador a cada caracter especifico del array de
 * 							caracteres condicionales en el archivo principal del
 * 							proyecto a comparar con rgb_char desde code:
 * 	@code
 *  	CharacterArray: Condicionales para Led RGB (GPIOB) y ACCEL (GPIOA e I2C)
 *  	#define CHAR_LIST	"R" "r" "G" "g" "B" "b" "M" "m" "X" "x" "Y" "y" "Z" "z"
 * 	 					   !<  RGB condicionales  >!<     ACCEL condicionales     >!
 * 	@endcode
 *
 * @param status_pin		Indicador de estado del Led RGB seleccionado
 * 							0	!< Encendido
 * 							1 	!< Apagado
 *
 * @return	execution error code
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t GPIO_PinStatus(uint8_t *rgb_char, uint8_t *rgb_char_list, 	uint8_t status_pin);

/** @} */ // end of GPIOB group
/** @} */// end of SDK_HAL group
#endif /* SDK_GPIOB_H_ */
