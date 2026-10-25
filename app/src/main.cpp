#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#define SLEEP_TIME_MS CONFIG_APP_HEARTBEAT_PERIOD_MS

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led2)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
    void test() 
    {
        const struct device *driver =
        DEVICE_DT_GET(DT_NODELABEL(our_driver0));

    if (!device_is_ready(driver)) {
        LOG_ERR("Driver is not ready");
        return;
    }

    struct sensor_value val{};

    int ret = sensor_sample_fetch(driver);
    LOG_INF("Fetch ret: %d", ret);

    k_msleep(2000);

    ret = sensor_channel_get(
        driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
    LOG_INF("Channel ret: %d", ret);
    }
}

int main(void)
{
    test();

    printk("Application main started\n");
    printk("LED device ready: %d\n", gpio_is_ready_dt(&led));

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    printk("LED configure result: %d\n", ret);

    if (ret < 0) {
        return 0;
    }

    while (1) {
        ret = gpio_pin_toggle_dt(&led);
        //printk("LED toggle result: %d\n", ret);
        k_msleep(SLEEP_TIME_MS);
        //test();
    }

    return 0;
}