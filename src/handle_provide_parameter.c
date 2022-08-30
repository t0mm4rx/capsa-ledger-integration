#include "capsa_plugin.h"

static void handle_buy_capsa(ethPluginProvideParameter_t *msg,
                             context_t *context) {
  if (context->next_param == AMOUNT_USDC) {
    copy_parameter(context->amount_usdc, msg->parameter,
                   sizeof(context->amount_usdc));
    context->next_param = UNEXPECTED_PARAMETER;
  } else {
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    return;
  }
}

static void handle_sell_capsa(ethPluginProvideParameter_t *msg,
                              context_t *context) {
  if (context->next_param == AMOUNT_CAPSA) {
    copy_parameter(context->amount_capsa, msg->parameter,
                   sizeof(context->amount_capsa));
    context->next_param = UNEXPECTED_PARAMETER;
  } else {
    PRINTF("Param not supported: %d\n", context->next_param);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    return;
  }
}

void handle_provide_parameter(void *parameters) {
  ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *)parameters;
  context_t *context = (context_t *)msg->pluginContext;
  // We use `%.*H`: it's a utility function to print bytes. You first give
  // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`)
  // and then the address (here `msg->parameter`).
  PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
         msg->parameterOffset, PARAMETER_LENGTH, msg->parameter);

  msg->result = ETH_PLUGIN_RESULT_OK;

  // EDIT THIS: adapt the cases and the names of the functions.
  switch (context->selectorIndex) {
  case BUY_CAPSA:
    handle_buy_capsa(msg, context);
    break;
  case SELL_CAPSA:
    handle_sell_capsa(msg, context);
    break;
  default:
    PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    break;
  }
}