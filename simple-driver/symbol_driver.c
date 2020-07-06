#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "NewDevice"

static int Major = 0;
static char *msg_Ptr;
static char msg[100];
static int Device_Open = 0;

MODULE_LICENSE("GPL");

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);

struct file_operations fops = {
    .read = device_read,
    .open = device_open,
    .release = device_release
};

int init_module(void)
{
    printk(KERN_INFO "Hello!\n");
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 1) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }
    printk(KERN_INFO "I was assigned major number %d.\n", Major);
    printk(KERN_INFO "To talk to the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
    return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "Goodbye!\n");
}

static int device_open(struct inode *inode, struct file *file)
{
    /*static int counter = 0;*/
    if (Device_Open)
        return -EBUSY;
    Device_Open++;
    /*sprintf(msg, "Device opened %d times.\n", counter++);
    msg_Ptr = msg;*/
    sprintf(msg, "HELLOWORLDHELLO\n");
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--;
    module_put(THIS_MODULE);
    return 0;
}

static ssize_t device_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
    int bytes_read = 0;
    
    if (*msg_Ptr == 0)
        return 0;

    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

MODULE_AUTHOR("Emin Gadzhiev");
MODULE_DESCRIPTION("Simple symbol driver for Linux Kernel");
