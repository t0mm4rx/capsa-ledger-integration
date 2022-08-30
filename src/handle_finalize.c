#include "capsa_plugin.h"

void handle_finalize(void *parameters) {
  ethPluginFinalize_t *msg = (ethPluginFinalize_t *)parameters;
  // context_t *context = (context_t *) msg->pluginContext;

  msg->uiType = ETH_UI_TYPE_GENERIC;

  // EDIT THIS: Set the total number of screen you will need.
  msg->numScreens = 1;

  msg->result = ETH_PLUGIN_RESULT_OK;
}
