#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/sysfs.h>
#include <linux/moduleparam.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

MODULE_AUTHOR("Glebik Stas, Kolesov Alexey");

static int param=1;
module_param(param, int, 0);

struct kobject kobj;
struct kobj_type type;

struct timer_list timer;

void function(unsigned long x) {
	static int y = 0;
	static bool state = false;
	
	if (!((++y) % 3)) {
		state = !state;
	}

	printk(KERN_INFO "SOS\n");
	if (state) {
		mod_timer(&timer, jiffies + 2*param*HZ);
	}
	else {
		mod_timer(&timer, jiffies + param*HZ);
	}
}

static int __init init(void) 
{
	printk(KERN_INFO "ker module is loaded\n");
	kobject_init(&kobj, &type);
	kobject_set_name(&kobj, "mySysfsModule");
	kobject_add(&kobj, NULL, NULL);

	init_timer(&timer);
	timer.function = function;
	timer.expires = jiffies  + param*HZ;

	add_timer(&timer);

	return 0;
}

static void __exit exit( void ) 
{
	del_timer(&timer);
	kobject_del(&kobj);
	kobject_put(&kobj);
	printk( KERN_INFO "ker module is unloaded\n");
}

module_init(init);
module_exit(exit);
