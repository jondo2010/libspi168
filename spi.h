//
//	spi.h
//	SPI support for the AVR ATMEGA168 micro-controller.
//
//	Michael Jean <michael.jean@shaw.ca>
//

#ifndef _SPI_H
#define _SPI_H

//
//	Each possible slave has a `slave descriptor' that enables the SPI
//	system to control the slave select lines. Each slave also requires
//	a different amount of delay before/after altering the slave
//	select line.
//
//	N.B. We assume that the slave pins are already configured as outputs.
//

typedef struct spi_slave_desc_t
{
	volatile 	uint8_t		*port;				// slave select port
				uint8_t 	pin;				// slave select pin
				double		select_delay;		// slave select delay (us)
				double		deselect_delay;		// slave deselect delay (us)
}
spi_slave_desc_t;

//
//	Initialize the SPI subsystem. By default, we run SPI at 4 MHz. Initializes
//	all of the SPI pin directions. Does not automatically setup the slave select
//	pin directions.
//

void
spi_init (void);

//
//	Setup a slave. There are a maximum of eight slave ids, and `slave_id'
//	is valid for the range 0-7. The slave descriptor provided is copied in
//	to the local array of descriptors. You are still required to setup the
//	slave select pin directions (DDRx). Automatically pulls the slave select
//	line high.
//

void
spi_setup_slave
(
	uint8_t 		 	slave_id,
	spi_slave_desc_t 	*slave_desc
);

//
//	Pull the slave select line low for the slave with id `slave_id',
//	and delay for the amount of microseconds defined in the slave
//	descriptor.
//

void
spi_slave_select
(
	uint8_t slave_id
);

//
//	Release the slave select line for the slave with id `slave_id',
//	and delay for the amount of microseconds defined in the slave
//	descriptor.
//

void
spi_slave_deselect
(
	uint8_t slave_id
);

//
//	Write a single byte to the slave.
//

void
spi_putch
(
	uint8_t byte
);

//
//	Write an array of `n' bytes to the slave from the array pointed
//	to by `dst'.
//

void
spi_puts
(
	uint8_t *src,
	uint8_t	n
);

//
//	Read a single byte from the slave and return it.
//

uint8_t
spi_getch (void);

//
//	Read an array of `n' bytes from the slave to the array pointed
//	to by `dst'.
//

void
spi_gets
(
	uint8_t *dst,
	uint8_t	n
);

#endif /* _SPI_H */
