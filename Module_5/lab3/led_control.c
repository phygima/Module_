#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vika");
MODULE_DESCRIPTION("A simple Linux driver for controlling keyboard LEDs");
MODULE_VERSION("0.1");

static struct kobject *led_kobj;
static int led_state = 0;

// Прототипы функций
static void update_leds(void);
static void blink_leds(void);

static ssize_t led_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", led_state);
}

static ssize_t led_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%x", &led_state);
    update_leds();
    return count;
}

static struct kobj_attribute led_attribute = __ATTR(led_control, 0664, led_show, led_store);

static void update_leds(void)
{
    blink_leds(); // Мигание лампочек при изменении состояния
}

static void blink_leds(void)
{
    int i;
    for (i = 0; i < 5; i++) // Мигаем 5 раз
    {
        // Зажигаем все лампочки
        pr_info("LEDs ON\n");
        msleep(500); // Ждем 500 миллисекунд

        // Гасим все лампочки
        pr_info("LEDs OFF\n");
        msleep(500); // Ждем 500 миллисекунд
    }
}

static int __init led_control_init(void)
{
    int error;

    // Создаем директорию в /sys/kernel/
    led_kobj = kobject_create_and_add("led_control", kernel_kobj);
    if (!led_kobj)
        return -ENOMEM;

    // Создаем файл атрибута в созданной директории
    error = sysfs_create_file(led_kobj, &led_attribute.attr);
    if (error) {
        kobject_put(led_kobj);
        return error;
    }

    pr_info("LED control module loaded\n");
    return 0;
}

static void __exit led_control_exit(void)
{
    sysfs_remove_file(led_kobj, &led_attribute.attr);
    kobject_put(led_kobj);
    pr_info("LED control module unloaded\n");
}

module_init(led_control_init);
module_exit(led_control_exit);
