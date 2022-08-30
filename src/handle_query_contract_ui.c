#include "capsa_plugin.h"

static void set_amount_ui(ethQueryContractUI_t *msg, context_t *context) {
  if (context->selectorIndex == BUY_CAPSA) {
    strlcpy(msg->title, "Amount USDC", msg->titleLength);
    amountToString(context->amount_usdc, INT256_LENGTH, 6, "USDC ", msg->msg,
                   msg->msgLength);
  } else {
    strlcpy(msg->title, "Amount CAPSA", msg->titleLength);
    amountToString(context->amount_capsa, INT256_LENGTH, 6, "CAPSA ", msg->msg,
                   msg->msgLength);
  }
}

void handle_query_contract_ui(void *parameters) {
  ethQueryContractUI_t *msg = (ethQueryContractUI_t *)parameters;
  context_t *context = (context_t *)msg->pluginContext;

  // msg->title is the upper line displayed on the device.
  // msg->msg is the lower line displayed on the device.

  // Clean the display fields.
  memset(msg->title, 0, msg->titleLength);
  memset(msg->msg, 0, msg->msgLength);

  msg->result = ETH_PLUGIN_RESULT_OK;

  // EDIT THIS: Adapt the cases for the screens you'd like to display.
  switch (msg->screenIndex) {
  case 0:
    set_amount_ui(msg, context);
    break;
  // Keep this
  default:
    PRINTF("Received an invalid screenIndex\n");
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    return;
  }
}
