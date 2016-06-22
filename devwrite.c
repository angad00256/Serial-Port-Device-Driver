#include"headers.h"
#include"declarations.h"

ssize_t dev_write(struct file *fileptr, const char __user *ubuff, size_t size, loff_t *pos)
{
	struct Dev *ldev;
	char *kbuff;
	int ret;
	int nocsw;
	int nob;
	int i;
	int j;
	char ch;
	unsigned char msr;

	kbuff=NULL;
	ret=0;
	nocsw=0;
	nob=0;
	i=0;
	j=0;

	ldev = fileptr->private_data; 

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Device Not Found!! \n");
		#endif
		goto OUT;
	}

	kbuff = kmalloc(sizeof(char)*(size+1),GFP_KERNEL);

	if(!kbuff)
	{
		#ifdef DEBUG
			printk(KERN_ERR"kmalloc failed!! \n");
		#endif
		goto OUT;
	}
	
	memset(kbuff,'\0',sizeof(char)*(size+1));

	ret = copy_from_user(kbuff,ubuff,size);

	nocsw = size-ret;
	nob = nocsw * 8;
	
	#ifdef DEBUG
		printk(KERN_ALERT"Number of characters successfully copied from user to kernel : %d \n",nocsw);
		printk(KERN_ALERT"Number of bits to be transferred : %d \n",nob);
		printk(KERN_ALERT"Data To Be Written : %s \n",kbuff);
		printk(KERN_ALERT"Write Operation Begins!! \n");
	#endif

	outb(0x43,LCR);

	while(j!=nob)
	{
		msr ^= msr;
		msr = inb(MSR);

		msr = msr<<3;
		msr = msr>>7;
		
		if( (msr&0) == 0)
		{
			ch = *(kbuff + i);

			#ifdef DEBUG
				printk(KERN_ALERT"Character transferred : %c \n",ch);
			#endif
		
			outb(ch,THR);

			i++;
			j+=8;

			ssleep(1);
		}
	}	

	#ifdef DEBUG
		printk(KERN_ALERT"Writing Done Successfully!! \n");
	#endif

	return nocsw;
OUT:
	return -1;	
}
