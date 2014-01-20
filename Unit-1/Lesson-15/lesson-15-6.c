/* 如下是摘自Linux内核代码( linux/drivers/char/raw.c  )中的定义 */

static const struct file_operations raw_fops = {
	.read		= do_sync_read,
	.aio_read	= generic_file_aio_read,
	.write		= do_sync_write,
	.aio_write	= blkdev_aio_write,
	.fsync		= blkdev_fsync,
	.open		= raw_open,
	.release	= raw_release,
	.unlocked_ioctl = raw_ioctl,
	.llseek		= default_llseek,
	.owner		= THIS_MODULE,
};

static const struct file_operations raw_ctl_fops = {
	.unlocked_ioctl = raw_ctl_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= raw_ctl_compat_ioctl,
#endif
	.open		= raw_open,
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
};