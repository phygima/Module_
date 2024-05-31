#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEVICE_NAME "chardev_example"
#define CLASS_NAME "chardev_class"
#define BUFFER_SIZE 1024

static int major_number;
static char message[BUFFER_SIZE] = {0};
static short message_size;
static struct class *chardev_class = NULL;
static struct device *chardev_device = NULL;
static struct cdev chardev_cdev;

static int dev_open(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "chardev: Device opened\n");
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "chardev: Device closed\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int error_count = 0;

    if (*offset >= message_size) {
        return 0;
    }

    if (len > message_size - *offset) {
        len = message_size - *offset;
    }

    error_count = copy_to_user(buffer, message + *offset, len);

    if (error_count == 0) {
        *offset += len;
        printk(KERN_INFO "chardev: Sent %zu characters to the user\n", len);
        return len;
    } else {
        printk(KERN_INFO "chardev: Failed to send %d characters to the user\n", error_count);
        return -EFAULT;
    }
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    if (len > BUFFER_SIZE - 1) {
        len = BUFFER_SIZE - 1;
    }

    if (copy_from_user(message, buffer, len) != 0) {
        printk(KERN_INFO "chardev: Failed to receive %zu characters from the user\n", len);
        return -EFAULT;
    }

    message[len] = '\0';
    message_size = len;
    printk(KERN_INFO "chardev: Received %zu characters from the user\n", len);
    return len;
}

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int __init chardev_init(void) {
    printk(KERN_INFO "chardev: Initializing the chardev\n");

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "chardev failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "chardev: Registered correctly with major number %d\n", major_number);

    chardev_class = class_create(CLASS_NAME);
    if (IS_ERR(chardev_class)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(chardev_class);
    }
    printk(KERN_INFO "chardev: Device class registered correctly\n");

    chardev_device = device_create(chardev_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(chardev_device)) {
        class_destroy(chardev_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(chardev_device);
    }
    printk(KERN_INFO "chardev: Device created correctly\n");

    cdev_init(&chardev_cdev, &fops);
    if (cdev_add(&chardev_cdev, MKDEV(major_number, 0), 1) == -1) {
        device_destroy(chardev_class, MKDEV(major_number, 0));
        class_destroy(chardev_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to add cdev\n");
        return -1;
    }

    return 0;
}

static void __exit chardev_exit(void) {
    cdev_del(&chardev_cdev);
    device_destroy(chardev_class, MKDEV(major_number, 0));
    class_unregister(chardev_class);
    class_destroy(chardev_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "chardev: Goodbye from the chardev\n");
}

module_init(chardev_init);
module_exit(chardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vika");
MODULE_DESCRIPTION("A simple Linux char driver for communication with user space");
MODULE_VERSION("1.0");
