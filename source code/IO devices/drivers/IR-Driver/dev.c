/* 
	This unit responsible to the user device for this driver.
	It will use the function from IR_board.h to access
	and read images, then give it to the user.
*/

#include "IR_board.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/major.h>
#include <linux/types>
#include <linux/fs.h>

#define DEVICE_NAME "IR_board"

int major_num;

static int open(struct inode *inode, struct file *filp);
static ssize_t dev_read(struct file *f, char __user *i_buff, size_t size, loff_t *offset);
static ssize_t dev_write(struct file *f, const char __user *o_buff, size_t size, loff_t *offset);

struct block_device_operations dev_fops = {
 	.owner = THIS_MODULE,
 	 open = open,
 	.read = dev_read,
 	.write = dev_write,
};


static int open(struct inode *inode, struct file *filp)
{
	
}

static ssize_t dev_read(struct file *f, char __user *i_buff, size_t size, loff_t *offset)
{

}

static ssize_t dev_write(struct file *f, const char __user *o_buff, size_t size, loff_t *offset)
{

} 

static int __init dev_init()
{
	if ((major_num = register_blkdev(0, DEVICE_NAME)) < 0) {
		printk(KERN_ALERT "IR_board: failed to register a major number");
		return -1;
	}



}

static void __exit dev_exit()
{
	if (unregister_blkdev(major_num, DEVICE_NAME) != -EINVAL) {
		printk(KERN_ALERT "IR_board: failed to unregister major number");
	}


}

module_init(dev_init);
module_exit(dev_exit);
MODULE_DESCRIPTION("IR Sensors Driver");
MODULE_LICENSE("GPL");