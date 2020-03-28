/**
 * @file my_drv.c
 * @author meng_yu (imyumeng@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-15
 * 
 * @copyright imyumeng@qq.com Copyright (c) 2020
 * 
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>   //file_operations structure define in tjis header file
#include <linux/init.h> //define module_ini
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/unistd.h>
#include <linux/fcntl.h>
#include <linux/device.h>
#include <linux/mman.h>

#include "my_drv.h"

// #define DRV_NAME "drv_meng"
#define DEV_NAME "dev_meng"
#define DRIVER_VERSION 0x00000001
#define DRIVER_VERSION_STR(VER) #VER
#define MAX_SIZE 1024

static int nvme_major;
static struct class *class_nvme;
char message[MAX_SIZE] = {0};
static int __init dev_init(void);
static void __exit dev_exit(void);
int my_open(struct inode *inode, struct file *file);
int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *user, size_t count, loff_t *f);
ssize_t my_write(struct file *file, const char __user *user, size_t count, loff_t *f);

MODULE_AUTHOR("YM");
MODULE_LICENSE("GPL");

module_init(dev_init);
module_exit(dev_exit);

static const struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int __init dev_init(void)
{
    int err = 0;
    LOG_DBG("dev_init");
    nvme_major = register_chrdev(0, DEV_NAME, &my_fops);
    if (nvme_major < 0)
    {
        LOG_ERR("register_chrdev fail");
        goto unreg_chrdrv_fail_out;
    }
    LOG_DBG("register_chrdev id:%d", nvme_major);
    /* Check if class_nvme creation has any issues */
    class_nvme = class_create(THIS_MODULE, DEV_NAME);
    if (IS_ERR(class_nvme))
    {
        LOG_ERR("NVMe class creation failed");
        err = PTR_ERR(class_nvme);
        goto class_create_fail_out;
    }

    // /* Register this driver */
    // err = pci_register_driver(&dnvme_driver);
    // if (err) {
    //     LOG_ERR("PCIe driver registration failed");
    // }
    return err;
class_create_fail_out:
    class_destroy(class_nvme);
unreg_chrdrv_fail_out:
    unregister_chrdev(nvme_major, DEV_NAME);
    return err;
}

static void __exit dev_exit(void)
{
    // pci_unregister_driver(&dnvme_driver);
    class_destroy(class_nvme);
    unregister_chrdev(nvme_major, DEV_NAME);
    LOG_DBG("dev_exit");
}

int my_open(struct inode *inode, struct file *file)
{
    int err = 0;
    LOG_DBG("Opening device");
    try_module_get(THIS_MODULE);
    return err;
}

int my_release(struct inode *inode, struct file *file)
{
    LOG_DBG("Device released!\n");
    module_put(THIS_MODULE);
    return 0;
}

ssize_t my_read(struct file *file, char __user *user, size_t count, loff_t *f)
{
    unsigned int buf_len = 0;
    unsigned int i = 0;

    LOG_DBG("read device!\n");

    buf_len = ARRAY_SIZE(message);

    if (buf_len < count)
        count = buf_len;

    LOG_DBG("my_drv read len:%ld", count);

    if (copy_to_user(user, message, count))
    {
        return -EFAULT;
    }

    buf_len = count;
    for (i = 0; i < buf_len; i++)
        LOG_DBG("my_drv read val[%d]=%d", i, message[i]);

    return 0;
}

ssize_t my_write(struct file *file, const char __user *user, size_t count, loff_t *f)
{
    unsigned int buf_len = 0;
    unsigned int i = 0;

    LOG_DBG("write device!\n");

    buf_len = ARRAY_SIZE(message);

    if (buf_len < count)
        count = buf_len;

    LOG_DBG("my_drv write buf len:%ld", count);

    if (copy_from_user(message, user, count))
    {
        return -EFAULT;
    }

    buf_len = count;
    for (i = 0; i < buf_len; i++)
        LOG_DBG("my_drv write val[%d]=%d", i, message[i]);

    return 0;
}