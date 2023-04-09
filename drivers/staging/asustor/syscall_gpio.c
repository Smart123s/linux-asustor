#include <linux/syscalls.h> /* SYSCALL_DEFINEx */
#include <linux/gpio.h>

#define LABEL_MAX_SIZE 32

enum gpioctl_cmd_type
{
    // access gpio
    GPIOCTL_DIRECTION_INPUT = 0,
    GPIOCTL_DIRECTION_OUTPUT,
    GPIOCTL_GET_VALUE,
    GPIOCTL_SET_VALUE,
    // access gpio chip
    GPIOCTL_GET_BASE,
    GPIOCTL_GET_NGPIO,
    // request/free
    GPIOCTL_REQUEST,
    GPIOCTL_FREE,

    GPIOCTL_MAX_CMD,
};

struct gpioctl_args
{
    unsigned offset;
    int value;
    char label[LABEL_MAX_SIZE];
};

static inline int gpiochip_match_name(struct gpio_chip *gc, void *data)
{
    return 0;
}

static int gpio_ctrl(unsigned int cmd, unsigned long args)
{
    return 0;
}

SYSCALL_DEFINE2(gpioctl, unsigned int, cmd, unsigned long, args)
{
    return gpio_ctrl(cmd, args);
}


