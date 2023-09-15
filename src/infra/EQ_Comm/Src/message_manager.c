/**
 * @file message_manager.c
 * @author Paulo Santos (pauloroberto.santos@edge.ufal.br)
 * @brief Define as funções de comunicação entre EQMRX e EQMTX.
 * @version 0.1
 * @date 23-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "message_manager.h"

int msg_mng_init_node(transceiver_node_t node_mode, const uint8_t* address) {
    switch (node_mode) {
        case TRANSCEIVER_NODE_CONTROLLER: {
#if USE_NRF24L01
            uint16_t retries = 0;
            nrf24_data_t connect_packet = {0};

            while (!nRF24_check(address)) {
                nRF24_init(address, MSG_MNG_EQM_RF_CHANNEL);
                HAL_Delay(100);
                if (retries > 1000) {
                    return -1;
                }
                retries++;
            }

            nRF24_PrepareData("Connect", 7, COMMAND, &connect_packet);
            nRF24_StopListening();
            retries = 0;
            while (!nRF24_Talk(connect_packet, NULL, nRF24_MODE_TX)) {
                retries++;
                HAL_Delay(100);
                if (retries > 1000) {
                    return -2;
                }
            }
#endif
        } break;
        case TRANSCEIVER_NODE_MOUNT:
            break;
    }

    return 0;
}

bool send_message(eqm_message_t msg) {
}