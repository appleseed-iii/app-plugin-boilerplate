#include "boilerplate_plugin.h"

// EDIT THIS: You need to adapt / remove the static functions (set_send_ui, set_receive_ui ...) to
// match what you wish to display.

// Copies the whole parameter (32 bytes long) from `src` to `dst`.
// Useful for numbers, data...
static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // Take the minimum between dst_len and parameter_length to make sure we don't overwrite memory.
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

void amountToPercent(const uint8_t *amount,
                    uint8_t amount_size,
                    char *out_buffer,
                    uint8_t out_buffer_size) {
    char tmp_buffer[100] = {0};

    amountToString(amount, amount_size, 2, "", tmp_buffer, 100);
    uint8_t amount_len = strnlen(tmp_buffer, sizeof(tmp_buffer));
    memcpy(out_buffer, tmp_buffer, amount_len);
    memcpy(out_buffer + amount_len, " %", 2);
    out_buffer[out_buffer_size - 1] = '\0';
}

// set the ui for the amount screen
static void set_amount_ui(ethQueryContractUI_t *msg, context_t *context, bool isDeposit) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    if (isDeposit) {
        amountToString(context->amount_to_deposit,
                    sizeof(context->amount_to_deposit),
                    context->decimals,
                    context->ticker,
                    msg->msg,
                    msg->msgLength);
    } else {
        amountToString(context->amount_to_withdraw,
                       sizeof(context->amount_to_withdraw),
                       context->decimals,
                       context->ticker,
                       msg->msg,
                       msg->msgLength);
    }
}

// Set UI for the "Send" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_send_ui(ethQueryContractUI_t *msg) {
    strlcpy(msg->title, "Send", msg->titleLength);

    uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    // Converts the uint256 number located in `eth_amount` to its string representation and
    // copies this to `msg->msg`.
    amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH ", msg->msg, msg->msgLength);
}

// Set UI for "Receive" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_receive_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Receive Min.", msg->titleLength);

    amountToString(context->amount_to_deposit,
                   sizeof(context->amount_to_deposit),
                   context->decimals,
                   context->ticker,
                   msg->msg,
                   msg->msgLength);
}

// Set UI for "Beneficiary" screen.
// EDIT THIS: Adapt / remove this function to your needs.
static void set_beneficiary_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Recipient", msg->titleLength);

    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;

    // Get the string representation of the address stored in `context->beneficiary`. Put it in
    // `msg->msg`.
    getEthAddressStringFromBinary(
        context->beneficiary,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,
        chainid);
}

static void set_slippage_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Slippage", msg->titleLength);

    amountToPercent(context->slippage,
                   sizeof(context->slippage),
                   msg->msg,
                   msg->msgLength);
}

static void set_recipient_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Recipient", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->recipient, msg->msg + 2, msg->pluginSharedRW->sha3, chainid);
}

static void set_contract_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Contract", msg->titleLength);
    msg->msg[0] = '0';
    msg->msg[1] = 'x';
    uint64_t chainid = 0;
    getEthAddressStringFromBinary(context->contract_address, msg->msg + 2, msg->pluginSharedRW->sha3, chainid);
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // Copy the contract address prior to any process
    ethPluginSharedRO_t *pluginSharedRO = (ethPluginSharedRO_t *) msg->pluginSharedRO;
    copy_parameter(context->contract_address, sizeof(context->contract_address), pluginSharedRO->txContent->destination);

    // EDIT THIS: Adapt the cases for the screens you'd like to display.
    // switch (msg->screenIndex) {
    //     case 0:
    //         set_send_ui(msg);
    //         break;
    //     case 1:
    //         set_receive_ui(msg, context);
    //         break;
    //     case 2:
    //         set_beneficiary_ui(msg, context);
    //         break;
    //     // Keep this
    //     default:
    //         PRINTF("Received an invalid screenIndex\n");
    //         msg->result = ETH_PLUGIN_RESULT_ERROR;
    //         return;
    // }
    switch (msg->screenIndex) {
        case 0:
            switch (context->selectorIndex) {
                case STAKE_OHM:
                    set_amount_ui(msg, context, true);
                    break;
                case UNSTAKE_SOHM:
                    set_amount_ui(msg, context, false);
                    break;
                case BOND_PURCHASE:
                    set_amount_ui(msg, context, true);
                    break;
                case BOND_REDEEM:
                    set_amount_ui(msg, context, false);
                    break;
            }
            break;
        case 1:
            set_contract_ui(msg, context);
            break;
        case 2:
            set_recipient_ui(msg, context);
            break;
        case 3:
            set_slippage_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
