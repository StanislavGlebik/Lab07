#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/sysfs.h>

MODULE_AUTHOR("Glebik Stas, Kolesov Alexey");

//int length = 1000;
//static char buf_msg[length + 1] = "Hello\n";

struct kobject kobj;
struct kobj_type type;

static int __init init(void) 
{
	printk( KERN_INFO "ker module is loaded\n");
	kobject_init(&kobj, &type);
	kobject_set_name(&kobj, "mySysfsModule");
	kobject_add(&kobj, NULL, "mySysfsModule");
	return 0;
}

static void __exit exit( void ) 
{
	kobject_del(&kobj);
	kobject_put(&kobj);
	printk( KERN_INFO "ker module is unloaded\n");
}

module_init(init);
module_exit(exit);
