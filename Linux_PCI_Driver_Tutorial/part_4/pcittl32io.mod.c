#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x7ef2b274, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x124688d8, __VMLINUX_SYMBOL_STR(pci_unregister_driver) },
	{ 0xfcc70556, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x17049ca4, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0x8c183cbe, __VMLINUX_SYMBOL_STR(iowrite16) },
	{ 0xc5534d64, __VMLINUX_SYMBOL_STR(ioread16) },
	{ 0xbde35553, __VMLINUX_SYMBOL_STR(pcim_iomap_table) },
	{ 0xeb685b13, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xcae7fc26, __VMLINUX_SYMBOL_STR(pcim_iomap_regions) },
	{ 0x3283b304, __VMLINUX_SYMBOL_STR(pcim_enable_device) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v0000178Ed00002000sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "78E384AD059BCF0C0AB793C");
