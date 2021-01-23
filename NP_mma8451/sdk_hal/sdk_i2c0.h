/*! @file : sdk_i2c0.h
 * @author  Jose .o
 * @version 1.0.0
 * @brief   Driver para I2C con ACCEL
 * @details
 *
 */
#ifndef SDK_I2C0_H_
#define SDK_I2C0_H_
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "fsl_common.h"

/*!
 * @addtogroup SDK_HAL
 * @{
 */
/*!
 * @addtogroup I2C
 * @{
 */
/*******************************************************************************
 * Public Definitions                                                          *
 *******************************************************************************/

/*!
 * @brief Lista de direcciones de memoria para lectura de posición ACCEL
 */
enum _i2c_addresst_list_out_data {
	kXMSB = 0x01, /* !< OUT X MSB */
	kXLSB, /* !< OUT X LSB */
	kYMSB, /* !< OUT Y MSB */
	kYLSB, /* !< OUT Y LSB */
	kZMSB, /* !< OUT Z MSB */
	kZLSB, /* !< OUT > LSB */
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
 * @brief Inicializa I2C0 a la velocidad en baudios (Bps) indicada
 *
 * @param baud_rate   		Configuration de velocidad en Baudios para I2C
 *
 * @return            		Resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t I2C0_MasterInit(uint32_t baud_rate);

/*!
 * @brief Lee un byte con el Device ID del ACCEL para indicar que esta disponible
 *
 * @param device_address	Dato en Hex de dirección en bus I2C para el dispositivo a leer
 *
 * @param register_address	Dato en Hex de dirección de memoria en el dispositivo a leer
 *
 * @param device_id			Dato en Hex almacenado en la dirección de memoria en el dispositivo
 *
 * @return            		Resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t I2C0_MasterReadStatusByte(uint8_t device_address, int8_t register_address, int8_t devide_id);

/*!
 * @brief Escribe un byte en una dirección específica del dispositivo ACCEL (Acelerometro)
 *
 * @param device_address	Dato en Hex de dirección en bus I2C para el dispositivo a escribir
 *
 * @param set_g_mode		Dato en Hex de modo de operación, establece rango y sensibilidad de
 * 							lectura del ACCEL:
 *
 * 							2g (2048mg)
 *
 * 							4g (4096mg)
 *
 * 							8g (8092mg)
 *
 * @param set_filter_mode	Dato en Hex de opcional de filtrado de salida en pasa alto (HPF) para el dato
 * 							futuro a ser leido en el ACCEL:
 *
 * 							0, Desahibilitado (Por defecto)
 *
 * 							1, Habilitado
 *
 * @Note Byte a escribir con los parametros anteriores:
 *
 * 							2g, sin HPF 0x00		2g, con HPF 0x10
 *
 * 							4g, sin HPF 0x01		4g, con HPF 0x11
 *
 * 							8g, sin HPF 0x02		8g, con HPF 0x12
 *
 * @return            		Resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t I2C_MasterWriteMode(uint8_t device_address, uint8_t set_g_mode, uint8_t set_filter_mode);

/*!
 * @brief Escribe un byte en una dirección específica del dispositivo ACCEL (Acelerometro)
 *
 * @param i2c_char			Apuntador a dato ingresado (caracter) por puerto serial en UART0
 *
 * @param i2c_char_list		Apuntador a Array que almacena los caracteres condicionales
 *
 * @param data				Doble Apuntador que almacena el dato obtenido de la direccion de memoria
 * 							para lectura de valores MSB y LSB para los Ejes X, Y, Z
 *
 * 							data[0,1] = { MS Byte, LS Byte };
 *
 * @param device_address	Direccion I2C del dispositvo (ACCEL) con el que se desea comunicar
 *
 * @param memory_address	Doble Apuntador condicional a lista _i2c_addresst_list_out_data en Linea 31
 *
 * 							memory_address[] = {
 *
 * 							Para X:		kXMSB = 0x01, !< OUT X MSB
 * 										kXLSB = 0x02  !< OUT X LSB
 *
 * 							Para Y:		kYMSB = 0x03, !< OUT Y MSB
 * 										kYLSB = 0x04  !< OUT Y LSB
 *
 * 							Para Z:		kZMSB = 0x05, !< OUT Z MSB
 * 										kZLSB = 0x06  !< OUT > LSB
 *
 * 							};
 *
 * @return            		Resultado de la ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @endcode
 */
status_t I2C0_MasterReadValue(uint8_t *i2c_char, uint8_t *i2c_char_list,
		uint8_t *data, uint8_t device_address, uint32_t *memory_address);

/** @} */ // end of I2C group
/** @} */// end of SDK_HAL group
#endif /* SDK_I2C0_H_ */
