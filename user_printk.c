#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "user_printk"

/* "open" is the function to open device */
// Kernel use inode to point to file
// inode : the information of device opened by user process
static int user_printk_open(struct inode *inode , struct file *filp) {
	return 0;
}

static ssize_t user_printk_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    char desp[len]; 
    if (copy_from_user(&desp, buff, len) == 0) {
        printk(KERN_INFO "%s\n", desp);
    }
    else {
        printk(KERN_ALERT "Failed to copy_from_user.");
        return -1;
    }
    return 0;
}

// file_operation data structure is the center of Linux character device, 
// when program calls kernel module, all depend on the content in file_operation, 
// defined in <linux/fs.h>
static const struct file_operations user_printk_fops = {
    // To avoid the module to be unmounted when operating, 
    // so it always initialize to "THIS_MODULE"
	.owner   	= THIS_MODULE,			
	.open    	= user_printk_open,
	.write		= user_printk_write
};

static struct miscdevice user_printk_dev = {
    // minor-device number is secondary device, 
    // and MISC_DYNAMIC_MINOR means to be allocated by system automatically
	.minor = MISC_DYNAMIC_MINOR,		
    // This name will show under /dev route
	.name  = DEVICE_NAME,				
	.fops  = &user_printk_fops
};

static int __init user_printk_init(void) {
    misc_register(&user_printk_dev);
    printk(KERN_INFO "user_printk init\n");
    return 0;
}

static void __exit user_printk_cleanup(void) {
  printk(KERN_INFO "user_printk cleanup\n");
}

module_init(user_printk_init);
module_exit(user_printk_cleanup);
