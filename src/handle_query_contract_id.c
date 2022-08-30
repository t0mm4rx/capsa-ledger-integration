#include "capsa_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
  ethQueryContractID_t *msg = (ethQueryContractID_t *)parameters;
  const context_t *context = (const context_t *)msg->pluginContext;

  // For the first screen, display the plugin name.
  strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

  // EDIT THIS: Adapt the cases by modifying the strings you pass to `strlcpy`.
  if (context->selectorIndex == BUY_CAPSA) {
    strlcpy(msg->version, "Buy CAPSA", msg->versionLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
  } else if (context->selectorIndex == SELL_CAPSA) {
    strlcpy(msg->version, "Sell CAPSA", msg->versionLength);
    msg->result = ETH_PLUGIN_RESULT_OK;
  } else {
    PRINTF("Selector index: %d not supported\n", context->selectorIndex);
    msg->result = ETH_PLUGIN_RESULT_ERROR;
  }
}