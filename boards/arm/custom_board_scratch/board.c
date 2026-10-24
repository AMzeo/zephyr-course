#include <zephyr/kernel.h>
#include <zephyr/init.h>

static int custom_board_init(void)
{
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(custom_board_init, PRE_KERNEL_1, 0);