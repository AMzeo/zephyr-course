#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include <zephyr/device.h>

struct our_custom_api {
    int (*increment_count)(const struct device *dev);
};

static inline int our_custom_increment_count(const struct device *dev)
{
    const struct our_custom_api *api =
        (const struct our_custom_api *)dev->api;

    return api->increment_count(dev);
}

#endif