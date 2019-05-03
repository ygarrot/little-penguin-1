#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

int sleep_for(int *delay, int retval)
{
	int x;
	int y;

	y = *delay;
	for (x = 0; x < delay; ++x)
		udelay(10);
	if (y < 10)
		pr_info("We slept a long time!");
	return (x * y);
}

int my_init(void)
{
	int delay;

	delay = 10;
	return (sleep_for(&delay, delay));
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);
