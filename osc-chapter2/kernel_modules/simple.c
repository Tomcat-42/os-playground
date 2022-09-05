#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

int simple_init(void) {
  printk(KERN_INFO "Module Init\n");
  return 0;
}

void simple_exit(void) { printk(KERN_INFO "Module Exit\n"); }

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Hugen");
MODULE_DESCRIPTION("Test module");
