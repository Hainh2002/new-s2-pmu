/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = fcu_frdyi_isr, /* FCU FRDYI (Flash ready interrupt) */
            [1] = fcu_fiferr_isr, /* FCU FIFERR (Flash access error interrupt) */
            [2] = agt_int_isr, /* AGT0 INT (AGT interrupt) */
            [3] = can_error_isr, /* CAN0 ERROR (Error interrupt) */
            [4] = can_rx_isr, /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [5] = can_tx_isr, /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [6] = can_rx_isr, /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [7] = can_tx_isr, /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [8] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [9] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [10] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [11] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_FCU_FRDYI), /* FCU FRDYI (Flash ready interrupt) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_FCU_FIFERR), /* FCU FIFERR (Flash access error interrupt) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_AGT0_INT), /* AGT0 INT (AGT interrupt) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_CAN0_ERROR), /* CAN0 ERROR (Error interrupt) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_RX), /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_TX), /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_RX), /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_TX), /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_SCI0_RXI), /* SCI0 RXI (Receive data full) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TXI), /* SCI0 TXI (Transmit data empty) */
            [10] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TEI), /* SCI0 TEI (Transmit end) */
            [11] = BSP_PRV_IELS_ENUM(EVENT_SCI0_ERI), /* SCI0 ERI (Receive error) */
        };
        #endif
