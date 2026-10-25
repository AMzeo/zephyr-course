
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static const struct gpio_dt_spec led =
    GPIO_DT_SPEC_GET(DT_ALIAS(app_led1), gpios);


static int sample_fetch_my_impl(const struct device *dev,
                                enum sensor_channel chan)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);

    LOG_INF("sensor_sample_fetch: turning LED ON");
    return gpio_pin_set_dt(&led, 1);
}

static int channel_get_my_impl(const struct device *dev,
                              enum sensor_channel chan,
                              struct sensor_value *val)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(val);

    LOG_INF("sensor_channel_get: turning LED OFF, channel %d", chan);
    return gpio_pin_set_dt(&led, 0);
}

static DEVICE_API(sensor, app_iomico_lecture) = {
    .sample_fetch = sample_fetch_my_impl,
    .channel_get = channel_get_my_impl,
};

static int init(const struct device *dev)
{
    ARG_UNUSED(dev);

    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED GPIO device is not ready");
        return -ENODEV;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED: %d", ret);
        return ret;
    }

    LOG_INF("Device Initialized");
    return 0;
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL,
                      POST_KERNEL, 80, &app_iomico_lecture);
