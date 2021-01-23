/*! @file : sdk_uart0.c
 * @author  Jose .o
 * @version 1.0.0
 * @brief   Driver para UART0
 * @details
 *
*/
/*******************************************************************************
 * Includes                                                                    *
 *******************************************************************************/
#include "sdk_uart0.h"
#include "fsl_lpsci.h"

/*******************************************************************************
 * Definitions                                                                 *
 *******************************************************************************/

/*@brief Define: Nombre Interno de Función para Gestión de Interrupciones por
 * Dato en UART0
 * */
#define UART0_IRQ_FUNCTION	UART0_IRQHandler
#define UART0_IRQ_INDEX		UART0_IRQn

/*******************************************************************************
 * Private Prototypes                                                          *
 *******************************************************************************/


/*******************************************************************************
 * External vars                                                               *
 *******************************************************************************/


/*******************************************************************************
 * Private vars                                                                  *
 *******************************************************************************/

uint8_t UART0_Circular_Buffer[LENGTH_CIRCULAR_BUFFER_B];
volatile uint16_t Tx_Index; /*Index para Dato a Enviar*/
volatile uint16_t Rx_Index; /*Index de la memoria para nuevo Dato Recibido*/

/*******************************************************************************
 * Private Source Code                                                         *
 *******************************************************************************/

/*@brief Función de Gestión IRQ para UART0
 * */
void UART0_IRQ_FUNCTION(void)
{
    uint8_t data;
    if ((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(UART0))
    {
        data = LPSCI_ReadByte(UART0);

        if (((Rx_Index + 1) % LENGTH_CIRCULAR_BUFFER_B) != Tx_Index)
        {
        	UART0_Circular_Buffer[Rx_Index] = data;
            Rx_Index++;
            Rx_Index %= LENGTH_CIRCULAR_BUFFER_B;
        }
    }
}

/*******************************************************************************
 * Public Source Code                                                          *
 *******************************************************************************/

/*@brief Inicializar el UART0 en Baud Rate indicado
 * */
status_t UART0_SetUp(uint32_t baud_rate) {
	lpsci_config_t config;
	status_t status_uart;

	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = baud_rate;
	config.enableTx = true;
	config.enableRx = true;

	status_uart = LPSCI_Init(UART0, &config, CLOCK_GetFreq(kCLOCK_McgFllClk));

	if (status_uart != kStatus_Success)
		return (status_uart);

	LPSCI_EnableInterrupts(UART0, kLPSCI_RxDataRegFullInterruptEnable);
	status_uart = EnableIRQ(UART0_IRQ_INDEX);

	return(status_uart);
}

/*@brief Calculo del número de Datos Nuevos que existen en el Buffer Circular
 * @return Número de bytes pendientes por ser procesados
 * */
uint8_t UART0_NewDataOnBuffer(void) {
	uint8_t Num_New_Data_On_Buffer;
	Num_New_Data_On_Buffer = (uint8_t) (Rx_Index - Tx_Index);
	return (Num_New_Data_On_Buffer);
}

/*@brief new_byte apuntador de memoria a donde almacenar byte
 * @return Status de la Ejecución
 * */
status_t UART0_ReadByteCircularBuffer(uint8_t *new_byte) {
	if (Rx_Index != Tx_Index) {
		*new_byte = UART0_Circular_Buffer[Tx_Index];
		Tx_Index++;
		Tx_Index %= LENGTH_CIRCULAR_BUFFER_B;
		return (kStatus_Success);
	} else {
		return (kStatus_Fail);
	}
}
