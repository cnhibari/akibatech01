#include <stdint.h>
#include "driver/gpio.h"

#define SIZE_LEDMATRIX_X	(128)
#define SIZE_LEDMATRIX_Y	(32)

#define SIZE_FONT_X (8)
#define SIZE_FONT_Y (16)

#define GPIO_PIN_R1 (18)
#define GPIO_PIN_G1 (21)
#define GPIO_PIN_B1 (23)
#define GPIO_PIN_R2 (26)
#define GPIO_PIN_G2 (25)
#define GPIO_PIN_B2 (17)
#define GPIO_PIN_CLK (27)
#define GPIO_PIN_addrA (14)
#define GPIO_PIN_addrB (16)
#define GPIO_PIN_addrC (4)
#define GPIO_PIN_addrD (13)

#define GPIO_PIN_LAT (32)
#define GPIO_PIN_OE (33)

#define GPIO_PIN_LAT_L ((GPIO_PIN_LAT)-32)
#define GPIO_PIN_OE_L ((GPIO_PIN_OE)-32)

#define GPIO_MASK_R1 (1<<GPIO_PIN_R1)
#define GPIO_MASK_G1 (1<<GPIO_PIN_G1)
#define GPIO_MASK_B1 (1<<GPIO_PIN_B1)
#define GPIO_MASK_R2 (1<<GPIO_PIN_R2)
#define GPIO_MASK_G2 (1<<GPIO_PIN_G2)
#define GPIO_MASK_B2 (1<<GPIO_PIN_B2)
#define GPIO_MASK_CLK (1<<GPIO_PIN_CLK)
#define GPIO_MASK_addrA (1<<GPIO_PIN_addrA)
#define GPIO_MASK_addrB (1<<GPIO_PIN_addrB)
#define GPIO_MASK_addrC (1<<GPIO_PIN_addrC)
#define GPIO_MASK_addrD (1<<GPIO_PIN_addrD)

#define GPIO_MASK_LAT_64 (1ULL<<GPIO_PIN_LAT)
#define GPIO_MASK_OE_64 (1ULL<<GPIO_PIN_OE)
#define GPIO_MASK_LAT_L (1<<GPIO_PIN_LAT_L)
#define GPIO_MASK_OE_L (1<<GPIO_PIN_OE_L)

#define GPIO_MASK_ALLOUTPUT ((GPIO_MASK_R1)|(GPIO_MASK_G1)|(GPIO_MASK_B1)|(GPIO_MASK_R2)|(GPIO_MASK_G2)|(GPIO_MASK_B2)|(GPIO_MASK_CLK)|(GPIO_MASK_addrA)|(GPIO_MASK_addrB)|(GPIO_MASK_addrC)|(GPIO_MASK_addrD)|(GPIO_MASK_LAT_64)|(GPIO_MASK_OE_64))

const uint32_t numfont[10][SIZE_FONT_Y] =
{
	{	/* 0 */
		0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x42, 0x42,
		0x42, 0x42, 0x42, 0x24, 0x24, 0x18, 0x00, 0x00 
	},
	{	/* 1 */
		0x00, 0x10, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10,
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00
	},
	{	/* 2 */
		0x00, 0x18, 0x24, 0x42, 0x42, 0x02, 0x04, 0x08,
		0x10, 0x20, 0x20, 0x40, 0x40, 0x7e, 0x00, 0x00
	},
	{	/* 3 */
		0x00, 0x38, 0x44, 0x82, 0x82, 0x02, 0x04, 0x38,
		0x04, 0x02, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00
	},
	{	/* 4 */
		0x00, 0x08, 0x18, 0x18, 0x28, 0x28, 0x48, 0x48,
		0x88, 0xfe, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00
	},
	{	/* 5 */
		0x00, 0x7c, 0x40, 0x40, 0x40, 0xb8, 0xc4, 0x82,
		0x02, 0x02, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00
	},
	{	/* 6 */
		0x00, 0x38, 0x44, 0x40, 0x80, 0x80, 0xb8, 0xc4,
		0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00
	},
	{	/* 7 */
		0x00, 0xfe, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08,
		0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00
	},
	{	/* 8 */
		0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38,
		0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00
	},
	{	/* 9 */
		0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x46,
		0x3a, 0x02, 0x02, 0x82, 0x44, 0x38, 0x00, 0x00
	}
};


uint32_t vram[(SIZE_LEDMATRIX_Y)/2][SIZE_LEDMATRIX_X];

uint32_t addrsel[(SIZE_LEDMATRIX_Y)/2];

void vram_clear(uint32_t pv[][SIZE_LEDMATRIX_X])
{
	uint32_t x, y;
	for ( y = 0 ; y < SIZE_LEDMATRIX_Y / 2 ; ++y )
	{
		for ( x = 0 ; x < SIZE_LEDMATRIX_X ; ++x )
		{
			pv[y][x] = addrsel[y];
		}
	}
}

void vram_set(uint32_t x, uint32_t y, uint32_t color, uint32_t pv[][SIZE_LEDMATRIX_X])
{
	uint32_t data;
	uint32_t y2;

	if ( y < SIZE_LEDMATRIX_Y / 2 )
	{
		y2 = y;
		data = 0;
		if ( color & 1 )
		{
			data |= GPIO_MASK_B1;
		}
		if ( color & 2 )
		{
			data |= GPIO_MASK_R1;
		}
		if ( color & 4 )
		{
			data |= GPIO_MASK_G1;
		}
		pv[y2][x] |= data;
	}
	else
	{
		y2 = y - SIZE_LEDMATRIX_Y / 2;
		data = 0;
		if ( color & 1 )
		{
			data |= GPIO_MASK_B2;
		}
		if ( color & 2 )
		{
			data |= GPIO_MASK_R2;
		}
		if ( color & 4 )
		{
			data |= GPIO_MASK_G2;
		}
		pv[y2][x] |= data;
	}
}

void vram_num(uint32_t x, uint32_t y, uint32_t color, uint32_t num, uint32_t pv[][SIZE_LEDMATRIX_X])
{
	uint32_t x2, y2;

	uint32_t f;
	if (( num < 10 ) && ( y + SIZE_FONT_Y <= SIZE_LEDMATRIX_Y ) && ( x + SIZE_FONT_X <= SIZE_LEDMATRIX_X ))
	{
		for ( y2 = 0 ; y2 < SIZE_FONT_Y ; y2++ )
		{
			f = numfont[num][y2];
			for ( x2 = 0 ; x2 < SIZE_FONT_X ; x2++ )
			{
				if ( f & ( 1 << (SIZE_FONT_X - 1 - x2 )))
				{
					vram_set(x + x2, y + y2, color, pv);
				}
			}
		}
	}
}

void makeaddrsel(void)
{
	uint32_t y, data;

	for ( y = 0 ; y < (SIZE_LEDMATRIX_Y)/2 ; ++y )
	{
		data = 0;
		if ( y & 1 )
		{
			data |= GPIO_MASK_addrA;
		}
		if ( y & 2 )
		{
			data |= GPIO_MASK_addrB;
		}
		if ( y & 4 )
		{
			data |= GPIO_MASK_addrC;
		}
		if ( y & 8 )
		{
			data |= GPIO_MASK_addrD;
		}
		addrsel[y] = data;
	}
}

void led_update(uint32_t y, uint32_t pv[][SIZE_LEDMATRIX_X])
{
	uint32_t x;

	GPIO.out1_w1ts.data = GPIO_MASK_OE_L;
	GPIO.out1_w1tc.data = GPIO_MASK_LAT_L;

	for ( x = 0 ; x < SIZE_LEDMATRIX_X ; ++x )
	{
		GPIO.out = pv[y][x];
		GPIO.out_w1ts = GPIO_MASK_CLK;
	}

	GPIO.out1_w1ts.data = GPIO_MASK_LAT_L;
	GPIO.out1_w1tc.data = GPIO_MASK_OE_L;

}

void app_main()
{
    gpio_config_t io_conf;
	uint32_t y;

    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_MASK_ALLOUTPUT;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
	GPIO.out1_w1ts.data = GPIO_MASK_OE_L;

	makeaddrsel();
	vram_clear(vram);
	vram_num(0, 0, 1, 1, vram);
	vram_num(8, 0, 2, 2, vram);
	vram_num(16, 0, 3, 3, vram);
	vram_num(24, 0, 4, 4, vram);
	vram_num(32, 0, 5, 5, vram);
	vram_num(40, 0, 6, 6, vram);
	vram_num(48, 0, 7, 7, vram);
	vram_num(56, 0, 1, 8, vram);
	vram_num(64+0, 0, 2, 9, vram);
	vram_num(64+8, 0, 3, 0, vram);
	vram_num(64+16, 0, 4, 1, vram);
	vram_num(64+24, 0, 5, 2, vram);
	vram_num(64+32, 0, 6, 3, vram);
	vram_num(64+40, 0, 7, 4, vram);
	vram_num(64+48, 0, 1, 5, vram);
	vram_num(64+56, 0, 2, 6, vram);
	vram_num(0, 16, 3, 7, vram);
	vram_num(8, 16, 4, 8, vram);
	vram_num(16, 16, 5, 9, vram);
	vram_num(24, 16, 6, 0, vram);
	vram_num(32, 16, 7, 1, vram);
	vram_num(40, 16, 1, 2, vram);
	vram_num(48, 16, 2, 3, vram);
	vram_num(56, 16, 3, 4, vram);
	vram_num(64+0, 16, 4, 5, vram);
	vram_num(64+8, 16, 5, 6, vram);
	vram_num(64+16, 16, 6, 7, vram);
	vram_num(64+24, 16, 7, 8, vram);
	vram_num(64+32, 16, 1, 9, vram);
	vram_num(64+40, 16, 2, 0, vram);
	vram_num(64+48, 16, 3, 1, vram);
	vram_num(64+56, 16, 4, 2, vram);


	y = 0;
    while(1)
	{
		led_update(y, vram);
		++y;
		if ( y >= SIZE_LEDMATRIX_Y / 2 )
		{
			y = 0;
		}
    }
}
