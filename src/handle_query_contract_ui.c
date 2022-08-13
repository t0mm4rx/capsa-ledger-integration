#include "boilerplate_plugin.h"

static void set_buy_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Buy", msg->titleLength);

    amountToString(context->token_amount, sizeof(context->token_amount), 6, "USDC ", msg->msg, msg->msgLength);
}

static void set_sell_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Sell", msg->titleLength);

    amountToString(context->token_amount, sizeof(context->token_amount), 6, "CAPSA ", msg->msg, msg->msgLength);
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

    // EDIT THIS: Adapt the cases for the screens you'd like to display.
    switch (msg->screenIndex) {
        case 0:
            set_buy_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
