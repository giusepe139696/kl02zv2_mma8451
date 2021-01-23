/*! @file : sdk_uart0.h
 * @author  Alvaro Luis Garcia Romero (Quote)
 * @version 1.0.0
 * @date    17/01/2021
 * @brief   Driver para UART0
 * @details
 *
 */
#ifndef SDK_UART0_H_
#define SDK_UART0_H_
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "fsl_common.h"

/*!
 * @addtogroup SDK_HAL
 * @{
 */
/*!
 * @addtogroup UART0
 * @{
 */
/*******************************************************************************
 * Public Definitions                                                          *
 *******************************************************************************/

/*@brief Longitud del Buffer Circular en bytes para recepción de datos por UART0*/
#define LENGTH_CIRCULAR_BUFFER_B 64 /*B = bytes*********************************/

/*******************************************************************************
 * External vars                                                               *
 *******************************************************************************/

/*******************************************************************************
 * Public vars                                                                 *
 *******************************************************************************/

/*******************************************************************************
 * Public Prototypes                                                           *
 *******************************************************************************/

/*@brief Inicializar el UART0 en Baud Rate indicado
 * */
status_t UART0_SetUp(uint32_t baud_rate); /*SetUp ~= Inicializar*/

/*@brief Calculo del número de Datos Nuevos que existen en el Buffer Circular
 * @return Número de bytes pendientes por ser procesados
 * */
uint8_t UART0_NewDataOnBuffer(void);

/*@brief new_byte apuntador de memoria a donde almacenar byte
 * @return Status de la Ejecución
 * @code
 * 		kStatus_Success
 * 		kStatus_Fail
 * @encode
 * */
status_t UART0_ReadByteCircularBuffer(uint8_t *new_byte);

/** @} */ // end of UART0 group

/** @} */ // end of SDK_HAL group

#endif /* SDK_UART0_H_ */
