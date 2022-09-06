#include <asm/param.h>
#include <linux/gcd.h>
#include <linux/hash.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>

int simple_init(void) {
  printk(KERN_INFO "Pablo: Module Init\n");
  printk(KERN_INFO "Pablo: Golden Ratio: %llu\n", GOLDEN_RATIO_PRIME);
  return 0;
}

void simple_exit(void) {
  printk(KERN_INFO "Pablo: GCD of 3300 and 24 is %lu", gcd(3300, 24));
  printk(KERN_INFO "Pablo: Module Exit\n");
  printk(KERN_INFO "Pablo: jiffies is %lu\n", jiffies);
  printk(KERN_INFO "Pablo: HZ is %d", HZ);
  printk(KERN_INFO "Pablo: seconds elapsed: %lu", jiffies / HZ);
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Hugen");
MODULE_DESCRIPTION("Test module");
