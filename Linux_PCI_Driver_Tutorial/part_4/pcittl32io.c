#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>

#define PCITTL32IO_INTERRUPT_STATUS_REGISTER 0x44
#define PCITTL32IO_INTERRUPT_ENABLE_REGISTER  0x46


#define PCITTL32IO_VENDOR_ID 0x178e
#define PCITTL32IO_DEVICE_ID 0x2000

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("Driver for the Quancom PCITTL32IO gpio card");

static struct pci_device_id pcittl32io_ids[] = {
	{ PCI_DEVICE(PCITTL32IO_VENDOR_ID, PCITTL32IO_DEVICE_ID) },
	{ }
};
MODULE_DEVICE_TABLE(pci, pcittl32io_ids);

struct drv_data {
	void __iomem *ptr_bar0;
};

irqreturn_t my_irq_handler(int irq, void *data) {
	struct drv_data *my_data;
	printk("pcittl32io - Now I am in the IRQ service routine!\n");
	my_data = (struct drv_data *) data;

	if(my_data != NULL)
		ioread16(my_data->ptr_bar0 + PCITTL32IO_INTERRUPT_STATUS_REGISTER);
	return IRQ_HANDLED;
}


/**
 * @brief Function is called, when a PCI device is registered
 *
 * @param dev   pointer to the PCI device
 * @param id    pointer to the corresponding id table's entry
 *
 * @return      0 on success
 *              negative error code on failure
 */
static int pcittl32io_probe(struct pci_dev *dev, const struct pci_device_id *id) {
	struct drv_data *my_data;
	int status;

	printk("pcittl32io - Now I am in the probe function.\n");

	status = pci_resource_len(dev, 0);
	printk("pcittl32io - BAR0 is %d bytes in size\n", status);
	if(status != 8192) {
		printk("pcittl32io - Wrong size of BAR0!\n");
		return -1;
	}

	printk("pcittl32io - BAR0 is mapped to 0x%llx\n", pci_resource_start(dev, 0));

	status = pcim_enable_device(dev);
	if(status < 0) {
		printk("pcittl32io - Could not enable device\n");
		return status;
	}
	
	status = pcim_iomap_regions(dev, BIT(0), KBUILD_MODNAME);
	if(status < 0) {
		printk("pcittl32io - BAR0 is already in use!\n");
		return status;
	}

	my_data = devm_kzalloc(&dev->dev, sizeof(struct drv_data), GFP_KERNEL);
	if(my_data == NULL) {
		printk("pcittl32io - Error! Out of memory\n");
		return -ENOMEM;
	}

	my_data->ptr_bar0 = pcim_iomap_table(dev)[0];
	if(my_data->ptr_bar0 == NULL) {
		printk("pcittl32io - BAR0 pointer is invalid\n");
		return -1;
	}

	printk("pcittl32io - Interrupt state Word 0x%x\n", ioread16(my_data->ptr_bar0 + PCITTL32IO_INTERRUPT_STATUS_REGISTER));
	iowrite16(0x0040, my_data->ptr_bar0 + 0x800 + 0x0);  //set time tag rollover interrupt + EOM
	iowrite16(0x0008, my_data->ptr_bar0 + 0x800 + 0x2);  //set interrupt type as LEVEL
	iowrite16(0x0001, my_data->ptr_bar0 + PCITTL32IO_INTERRUPT_ENABLE_REGISTER);  //enable BRM0 interrupt
	printk("pcittl32io - BRM Interrupt Register 0x%x\n", ioread16(my_data->ptr_bar0 + 0X800 + 0X0));
/* Let's set up the interrupt */
	if(dev->irq) {
		status = devm_request_irq(&dev->dev, dev->irq, my_irq_handler, 0, KBUILD_MODNAME, my_data);
		if(status) {
			printk("pcittl32io - Error requesting IRQ\n");
			return -1;
		}
		printk("pcittl32io - Requesting IRQ %d was successful\n", dev->irq);
		/* Setup PCI device */
		ioread16(my_data->ptr_bar0 + PCITTL32IO_INTERRUPT_STATUS_REGISTER);
		//iowrite16((1 | (1<<1)), my_data->ptr_bar0 + PCITTL32IO_OFFSET_IRQ);
	}
	return 0;
}

/**
 * @brief Function is called, when a PCI device is unregistered
 *
 * @param dev   pointer to the PCI device
 */
static void pcittl32io_remove(struct pci_dev *dev) {
	printk("pcittl32io - Now I am in the remove function.\n");
}

/* PCI driver struct */
static struct pci_driver pcittl32io_driver = {
	.name = "pcittl32io",
	.id_table = pcittl32io_ids,
	.probe = pcittl32io_probe,
	.remove = pcittl32io_remove,
};

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("pcittl32io - Registering the PCI device\n");
	
	return pci_register_driver(&pcittl32io_driver);
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	printk("pcittl32io - Unregistering the PCI device\n");
	pci_unregister_driver(&pcittl32io_driver);
}

module_init(my_init);
module_exit(my_exit);


