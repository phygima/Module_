#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "mymodule"
#define BUFFER_SIZE 128

static char proc_data[BUFFER_SIZE];
static int proc_data_len;

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    ssize_t ret = 0;

    if (*ppos > 0 || count < proc_data_len) {
        return 0;
    }

    if (copy_to_user(buf, proc_data, proc_data_len)) {
        return -EFAULT;
    }

    *ppos = proc_data_len;
    ret = proc_data_len;

    return ret;
}

static ssize_t proc_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    if (count > BUFFER_SIZE) {
        proc_data_len = BUFFER_SIZE;
    } else {
        proc_data_len = count;
    }

    if (copy_from_user(proc_data, buf, proc_data_len)) {
        return -EFAULT;
    }

    return proc_data_len;
}

static const struct proc_ops proc_file_ops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

static int __init mymodule_init(void) {
    proc_create(PROC_NAME, 0666, NULL, &proc_file_ops);
    printk(KERN_INFO "mymodule: Module loaded.\n");
    return 0;
}

static void __exit mymodule_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "mymodule: Module unloaded.\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);

MODULE_LICENSE("KUJIMA");
MODULE_AUTHOR("Victoria");
MODULE_DESCRIPTION("Hello!!.");
MODULE_VERSION("0.1");
