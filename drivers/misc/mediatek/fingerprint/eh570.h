#ifndef _EH570_LINUX_DIRVER_H_
#define _EH570_LINUX_DIRVER_H_

#include <linux/module.h>
#include <linux/spi/spi.h>

#define EH570_SPI_DEBUG

#ifdef EH570_SPI_DEBUG
//#define DEBUG_PRINT(fmt, args...) pr_err(fmt, ## args)
#define DEBUG_PRINT(fmt, args...) printk(fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

#define EH570_MAJOR         101 /* assigned */
#define N_SPI_MINORS            32  /* ... up to 256 */

#define EH570_ADDRESS_0 0x00
#define EH570_WRITE_ADDRESS 0xAC
#define EH570_READ_DATA 0xAF
#define EH570_WRITE_DATA 0xAE

struct egis_ioc_transfer {
	__u8			*tx_buf;
	__u8			*rx_buf;

	__u32		len;
	__u32		speed_hz;

	__u16		delay_usecs;
	__u8		bits_per_word;
	__u8		cs_change;
	__u8		opcode;
	__u8		pad[3];

};

#define EGIS_IOC_MAGIC			'k'
#define EGIS_MSGSIZE(N) \
	((((N)*(sizeof(struct egis_ioc_transfer))) < (1 << _IOC_SIZEBITS)) \
		? ((N)*(sizeof(struct egis_ioc_transfer))) : 0)
#define EGIS_IOC_MESSAGE(N) _IOW(EGIS_IOC_MAGIC, 0, char[EGIS_MSGSIZE(N)])

struct eh570_data {
	dev_t           devt;
	spinlock_t      spi_lock;
	struct spi_device   *spi;
	struct list_head    device_entry;

	/* buffer is NULL unless this device is open (users > 0) */
	struct mutex        buf_lock;
	unsigned        users;
	u8          *buffer;
};

#endif
