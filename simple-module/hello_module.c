#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int count = 5;
module_param(count, int, 0);

static char *string = "test";
module_param(string, charp, 0);

int init_module(void)
{
    printk(KERN_INFO "Hello!\n");
    int i = 0;
    for (; i < count; i++)
        printk("%s",string);
    printk("\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye!\n");
}

MODULE_AUTHOR("Emin Gadzhiev");
MODULE_DESCRIPTION("Simple module for Linux Kernel");
