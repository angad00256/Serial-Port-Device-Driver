#include"headers.h"
#include"declarations.h"

ssize_t dev_read(struct file *fileptr, char __user *ubuff, size_t size, loff_t *pos)
{
	struct Dev *ldev;
	char *kbuff;
	int ret;
	int nocsr;
	int nobtr;
	int nob;
	int i;
	unsigned char ch;
	unsigned char lsr;

	kbuff=NULL;
	ret=0;
	nocsr=0;
	nobtr=0;
	nob=0;
	i=0;

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

	nobtr = size*8;

	#ifdef DEBUG
		printk(KERN_ALERT"Number of bits to be read : %d \n",nobtr);
		printk(KERN_ALERT"Write Operation Begins!! \n");
	#endif

	while(nob != nobtr)
	{
		outb(0,MCR);

		lsr ^= lsr;
		lsr = inb(LSR);

		lsr = lsr<<7;
		lsr = lsr>>7;
		
		if( (lsr&1) == 1)
		{
			outb(2,MCR);
		
			ch = inb(RBR);
		
			#ifdef DEBUG
				printk(KERN_ALERT"Character read : %c \n",ch);
			#endif

			*(kbuff + i) = ch;

			i++;
			nob+=8;
		}
	}
	
	ret = copy_to_user(ubuff,kbuff,size);

	nocsr = size-ret;
	
	#ifdef DEBUG
		printk(KERN_ALERT"Data read : %s \n",kbuff);
		printk(KERN_ALERT"Number of characters successfully copied from kernel to user : %d \n",nocsr);
		printk(KERN_ALERT"Reading Done Successfully!! \n");
	#endif
	
	return nocsr;
OUT:
	return -1;	
}
