/*! @file : sdk_i2c0.c
 * @author  jose .o
 * @version 1.0.0
 * @date    18/01/2021
 * @brief   Driver para I2C con ACCEL
 * @details
 *
 */
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "sdk_i2c0.h"
#include "fsl_i2c.h"

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

status_t I2C0_MasterInit(uint32_t baud_rate) {
	i2c_master_config_t masterConfig;
	uint32_t sourceClock = 0;

	/*!
	 *  Parametros por Defecto para masterConfig, estructura de configuracion
	 *  maestra I2C:
	 * @_paramcode
	 * 		baudRate_Bps = 100000U;
	 * 		enableStopHold = false;
	 * 		glitchFilterWidth = 0U;
	 * 		enableMaster = true;
	 * @end_paramcode
	 */

	I2C_MasterGetDefaultConfig(&masterConfig);
	if (baud_rate < 100000U) {
		masterConfig.baudRate_Bps = baud_rate;
	}

	/*!
	 * @brief Asignacion de la frecuencia de reloj para un nombre de reloj
	 * específico.
	 *
	 * @param I2C0_CLK_SRC Nombre de reloj para I2C en clock_name_t // kCLOCK_BusClk
	 * @return Valor de la frecuencia del reloj en Hertz
	 */

	sourceClock = CLOCK_GetFreq(I2C0_CLK_SRC);

	/*!
	 * @param I2C0 			Apuntador a direccion de instancia I2C0
	 * @param masterConfig 	Apuntador a la estructura de configuracion maestra I2C
	 * @param sourceClock 	Frecuencia de reloj del I2C en Hz
	 */

	I2C_MasterInit(I2C0, &masterConfig, sourceClock);
	return (kStatus_Success);
}

status_t I2C0_MasterReadStatusByte(uint8_t device_address, int8_t register_address, int8_t devide_id) {

	i2c_master_transfer_t masterXfer;
	uint8_t i2c_rx_buffer[1];

	/* Estructura para busqueda de Byte Device ID */
	masterXfer.slaveAddress = device_address;
	masterXfer.direction = kI2C_Read;
	masterXfer.subaddress = (uint32_t) register_address;
	masterXfer.subaddressSize = 1;
	masterXfer.data = i2c_rx_buffer;
	masterXfer.dataSize = 1;
	masterXfer.flags = kI2C_TransferDefaultFlag;

	/*!
	 * @param I2C0 			Apuntador a direccion de instancia I2C0
	 * @param masterXfer 	Apuntador a la estructura de configuracion
	 */
	I2C_MasterTransferBlocking(I2C0, &masterXfer);

	/* Condicional de respuesta exitosa */
	if (i2c_rx_buffer[0] == devide_id) {
		return (kStatus_Success);
	} else {
		return (kStatus_Fail);
	}
}

status_t I2C_MasterWriteMode(uint8_t device_address, uint8_t set_g_mode, uint8_t set_filter_mode){

	i2c_master_transfer_t masterXfer;

	uint32_t ctrl_reg1 = 0x2A; /* !< Address: Status Registro */
	uint32_t xyz_data_cfg = 0x0E; /* !< Address: Modo de Lectura */
	const uint8_t size = 1;
	uint8_t i2c_tx_buffer[1];

	/*!
	 * @code 	Estructura para escribir Byte de modo espera para
	 * 			configurar el modo de lectura del ACCEL
	 */

	masterXfer.flags = kI2C_TransferDefaultFlag;
	masterXfer.slaveAddress = device_address;
	masterXfer.direction = kI2C_Write;

	i2c_tx_buffer[0] = 0x04; /* !< Mode Stanby en bajo ruido */

	masterXfer.subaddress = ctrl_reg1;
	masterXfer.subaddressSize = size;
	masterXfer.data = i2c_tx_buffer;
	masterXfer.dataSize = 1;

	I2C_MasterTransferBlocking(I2C0, &masterXfer);
	/*!
	 * @endcode Set Stanby Mode
	 */

	/*!
	 * @code 	Estructura para escribir Byte de Modo de Lectura
	 * 			configurar el modo de lectura del ACCEL
	 */
	masterXfer.flags = kI2C_TransferDefaultFlag;
	masterXfer.slaveAddress = device_address;
	masterXfer.direction = kI2C_Write;

	switch (set_g_mode) {
	case 2:
		switch (set_filter_mode) {
		case 0:
			i2c_tx_buffer[0] = 0x00; /* !< 2g sin HPF */
			masterXfer.subaddress = xyz_data_cfg;
			masterXfer.subaddressSize = size;
			masterXfer.data = i2c_tx_buffer;
			I2C_MasterTransferBlocking(I2C0, &masterXfer);
			break;
		case 1:
			i2c_tx_buffer[0] = 0x10; /* !< 2g con HPF */
			masterXfer.subaddress = xyz_data_cfg;
			masterXfer.subaddressSize = size;
			masterXfer.data = i2c_tx_buffer;
			I2C_MasterTransferBlocking(I2C0, &masterXfer);
			break;
		default:
			return (kStatus_Fail);
			break;
		}
		break;
		case 4:
			switch (set_filter_mode) {
			case 0:
				i2c_tx_buffer[0] = 0x01; /* !< 4g sin HPF */
				masterXfer.subaddress = xyz_data_cfg;
				masterXfer.subaddressSize = size;
				masterXfer.data = i2c_tx_buffer;
				I2C_MasterTransferBlocking(I2C0, &masterXfer);
				break;
			case 1:
				i2c_tx_buffer[0] = 0x11; /* !< 4g con HPF */
				masterXfer.subaddress = xyz_data_cfg;
				masterXfer.subaddressSize = size;
				masterXfer.data = i2c_tx_buffer;
				I2C_MasterTransferBlocking(I2C0, &masterXfer);
				break;
			default:
				return (kStatus_Fail);
				break;
			}
			break;
			case 8:
				switch (set_filter_mode) {
				case 0:
					i2c_tx_buffer[0] = 0x02; /* !< 8g sin HPF */
					masterXfer.subaddress = xyz_data_cfg;
					masterXfer.subaddressSize = size;
					masterXfer.data = i2c_tx_buffer;
					I2C_MasterTransferBlocking(I2C0, &masterXfer);
					break;
				case 1:
					i2c_tx_buffer[0] = 0x12; /* !< 8g con HPF */
					masterXfer.subaddress = xyz_data_cfg;
					masterXfer.subaddressSize = size;
					masterXfer.data = i2c_tx_buffer;
					I2C_MasterTransferBlocking(I2C0, &masterXfer);
					break;
				default:
					return (kStatus_Fail);
					break;
				}
				break;
				default:
					return (kStatus_Fail);
					break;
	}
	/*!
	 * @endcode Set Modo de Lectura
	 */

	/*!
	 * @code 	Estructura para escribir Byte de Modo Activo para
	 * 			guardar los cambios asignados al modo de lectura
	 * 			del ACCEL
	 */
	i2c_tx_buffer[0] = 0x05;

	masterXfer.subaddress = ctrl_reg1;
	masterXfer.subaddressSize = size;
	masterXfer.data = i2c_tx_buffer;

	I2C_MasterTransferBlocking(I2C0, &masterXfer);
	/*!
	 * @endcode Set Active Mode
	 */

	return (kStatus_Success);
}

status_t I2C0_MasterReadValue(uint8_t *i2c_char, uint8_t *i2c_char_list,
		uint8_t *data, uint8_t device_address, uint32_t *memory_address){

	i2c_master_transfer_t masterXfer;
	uint8_t i;
	uint8_t size;
	uint8_t i2c_rx_buffer[1];

	/*  Ciclo condicinal de asignación de memory address*/
	for (i = 8; i <= 13; i++) {
		if (*i2c_char == i2c_char_list[i]) {
			if (i == 8 || i == 9) {
				memory_address[0] = kXMSB;
				memory_address[1] = kXLSB;
				break;
			}

			if (i == 10 || i == 11) {
				memory_address[0] = kYMSB;
				memory_address[1] = kYLSB;
				break;
			}

			if (i == 12 || i == 13) {
				memory_address[0] = kZMSB;
				memory_address[1] = kZLSB;
				break;
			}

		}
	}

	/*!
	 * @code 	Estructura para Leer los Bytes segun el Read Mode
	 * 			Configurado
	 */
	masterXfer.flags = kI2C_TransferDefaultFlag;
	masterXfer.slaveAddress = device_address;
	masterXfer.direction = kI2C_Read;
	masterXfer.data = i2c_rx_buffer;
	masterXfer.dataSize = 1;

	/* Ciclo condicional de lectura de Bytes */
	for (i = 0; i <= 1; i++) {
		size = 1;
		masterXfer.subaddressSize = size;
		masterXfer.subaddress = memory_address[i];
		I2C_MasterTransferBlocking(I2C0, &masterXfer);

		/* Almacenamiento de Lecturas*/
		data[i] = i2c_rx_buffer[0];
		/*
		 * @param data [0,1] = { MS Byte, LS Byte };
		 */

	}
	/*!
	 * @endcode Read Success
	 */

	return (kStatus_Success);
}

