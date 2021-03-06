#include <libconfig.h>

#define DEFAULT_PORT 8080
#define DEFAULT_SLEEP_TIME 1

static const char *FILE_CONFIG = "/etc/ceserver/imageserver.cfg";

config_t cfg;
config_setting_t *sleep_daemon_setting;
config_setting_t *port_server_setting;
config_setting_t *active_server_setting;

int get_port_config();
int get_sleep_time();
int check_active();
void update_active(int value);
