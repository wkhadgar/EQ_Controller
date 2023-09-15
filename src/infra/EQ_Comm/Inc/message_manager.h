/**
 * @file message_manager.h
 * @author Paulo Santos (pauloxrms@gmail.com)
 * @brief Declara as funções de comunicação entre EQMRX e EQMTX.
 * @version 0.1
 * @date 23-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef EQ_CONTROLLER_MESSAGE_MANAGER_H
#define EQ_CONTROLLER_MESSAGE_MANAGER_H

#ifdef USE_NRF24L01

#include "nrf24l01p.h"
#include "main.h"
#include <string.h>

/**
 * @brief NRF24L01 radio channel.
 */
#define MSG_MNG_EQM_RF_CHANNEL 0

/**
 * @brief Test the signal by only sending a carrier wave to the receiver.
 */
#define MSG_MNG_TEST_CARRIER 0

#if MSG_MNG_TEST_CARRIER == 1
/**
 * @brief Iterations of the channel switching.
 */
#define MSG_MNG_CARRIER_ITERATIONS 300
#endif /* TEST_CARRIER */

#endif /* USE_NRF24L01 */

/**
 * @brief Enumerates the type of this device.
 */
typedef enum transceiver_node {
    TRANSCEIVER_NODE_CONTROLLER = 0, /**< Controller node. */
    TRANSCEIVER_NODE_MOUNT,          /**< Mount node. */
} transceiver_node_t;

/**
 * @brief Enumera os tipos de mensagens.
 */
typedef enum message_type {
    MESSAGE_FULL_STOP = 0,
    MESSAGE_START_TRACKING,
    MESSAGE_MOVE_AXIS,
    MESSAGE_SETTING,
} message_type_t;

/**
 * @brief Estrutura os metadados de uma mensagem de movimentação.
 */
typedef struct move_axis_metadata {

} move_axis_metadata_t;

/**
 * @brief Estrutura os metadados de uma mensagem de configuração
 */
typedef struct setting_metadata {

} setting_metadata_t;

/**
 * @brief Une os tipos de metadados.
 */
typedef union message_metadata {
    move_axis_metadata_t move_axis;
    setting_metadata_t setting;
} message_metadata_t;

/**
 * @brief Estrutura uma mensagem.
 */
typedef struct eqm_message {
    message_type_t type;
    message_metadata_t metadata;
} eqm_message_t;

/**
 * @brief Initiates the node with the given configuration.
 *
 * @param node_mode type of the node, can be a controller or a mount.
 * @param address Address of the communication.
 * @retval 0 if successfully connected.
 * @retval -1 if unable to start the module.
 * @retval -2 if unable to connect.
 */
int msg_mng_init_node(transceiver_node_t node_mode, const uint8_t* address);

/**
 * @brief Envia uma mensagem para o EQM configurado.
 *
 * @param msg Mensagem a ser enviada.
 */
bool msg_mng_send_message(eqm_message_t msg);


#endif /* EQ_CONTROLLER_MESSAGE_MANAGER_H */