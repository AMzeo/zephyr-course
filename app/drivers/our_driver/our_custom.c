#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include "our_driver.h"

LOG_MODULE_REGISTER(our_custom, LOG_LEVEL_INF);

struct our_custom_data {
    int operation_count;
};

static struct our_custom_data custom_data;

static int increment_count(const struct device *dev)
{
    struct our_custom_data *data = dev->data;

    data->operation_count++;

    LOG_INF("Operation count: %d", data->operation_count);

    return data->operation_count;
}

static const struct our_custom_api custom_api = {
    .increment_count = increment_count,
};

static int custom_init(const struct device *dev)
{
    ARG_UNUSED(dev);
    LOG_INF("Custom API device initialized");
    return 0;
}

DEVICE_DT_DEFINE(DT_NODELABEL(our_custom0),
                 custom_init,
                 NULL,
                 &custom_data,
                 NULL,
                 POST_KERNEL,
                 80,
                 &custom_api);