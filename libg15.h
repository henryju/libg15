/*
    libg15, library to handle the LCD and extra keys on the
	Logitech G15 Gaming Keyboard and similar devices.

	Copyright (c) 2017 Fabrice Delliaux <netbox253@gmail.com>
		https://github.com/netfab/libg15

	libg15 was originaly forked from g15tools.
		(c) 2006-2007 The G15tools Project -
			https://sourceforge.net/projects/g15tools/
	See also AUTHORS file.

    libg15 is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    libg15 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libg15; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#ifndef _LIBG15_H_
#define _LIBG15_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define G15_LCD 1
#define G15_KEYS 2
#define G15_DEVICE_IS_SHARED 4
#define G15_DEVICE_5BYTE_RETURN 8
#define G15_DEVICE_G13 16
#define G15_DEVICE_G510 32
#define G15_DEVICE_G110 64
#define G15_DEVICE_COLOUR 128
#define G15_STORAGE 256

#define G15_KEY_READ_LENGTH 9
#define G13_KEY_READ_LENGTH 8
#define G510_STANDARD_KEYBOARD_INTERFACE	0x0

typedef struct libg15_devices_t libg15_devices_t;

struct libg15_devices_t {
  const char *name;	// name - can be anything, only used for informational purposes
  unsigned int vendorid;
  unsigned int productid;
  unsigned int caps; // capability bitfield - G15_LCD|G15_KEYS;
};

#define DEVICE(name, vendorid, productid, caps) { \
    name, \
    vendorid, \
    productid, \
    caps \
}

  /* allow for api changes */
#define LIBG15_VERSION 1201

  enum 
  {
    G15_LOG_INFO = 1,
    G15_LOG_WARN
  };
  
  enum
  {
    G15_NO_ERROR = 0,
    G15_ERROR_OPENING_USB_DEVICE,
    G15_ERROR_WRITING_PIXMAP,
    G15_ERROR_TIMEOUT,
    G15_ERROR_READING_USB_DEVICE,
    G15_ERROR_TRY_AGAIN,
    G15_ERROR_WRITING_BUFFER,
    G15_ERROR_UNSUPPORTED,
    G15_ERROR_WRITING_PROFILE,
  };
  
  enum
  {
    G15_LCD_OFFSET = 32,    /* LCD screen format buffer header length */
    G15_LCD_HEIGHT = 43,    /* LCD screen height in pixels */
    G15_LCD_WIDTH = 160     /* LCD screen width in pixels */
  };

  enum
  {
    /*
     * Buffer length for LCD screen format
     * (( (G15_LCD_HEIGHT/8) + ((G15_LCD_HEIGHT%8) ? 1 : 0 )) * G15_LCD_WIDTH) + G15_LCD_OFFSET
     * See dumpPixmapIntoLCDFormat()
     */
    G15_BUFFER_LEN = 0x03e0
  };

  enum
  {
    G15_PROFILE_LEN = 992
  };
  
  enum
  {
    G15_LED_M1=1<<0,
    G15_LED_M2=1<<1,
    G15_LED_M3=1<<2,
    G15_LED_MR=1<<3
  };
  
  enum
  {
    G15_CONTRAST_LOW=0,
    G15_CONTRAST_MEDIUM,
    G15_CONTRAST_HIGH    
  };
  
  enum
  {
    G15_BRIGHTNESS_DARK=0,
    G15_BRIGHTNESS_MEDIUM,
    G15_BRIGHTNESS_BRIGHT
  };
  
  enum
  {
    G15_KEY_G1  = 1<<0,
    G15_KEY_G2  = 1<<1,
    G15_KEY_G3  = 1<<2,
    G15_KEY_G4  = 1<<3,
    G15_KEY_G5  = 1<<4,
    G15_KEY_G6  = 1<<5,
    G15_KEY_G7  = 1<<6,
    G15_KEY_G8  = 1<<7,
    G15_KEY_G9  = 1<<8,
    G15_KEY_G10 = 1<<9,
    G15_KEY_G11 = 1<<10,
    G15_KEY_G12 = 1<<11,
    G15_KEY_G13 = 1<<12,
    G15_KEY_G14 = 1<<13,
    G15_KEY_G15 = 1<<14,
    G15_KEY_G16 = 1<<15,
    G15_KEY_G17 = 1<<16,
    G15_KEY_G18 = 1<<17,

    G15_KEY_M1  = 1<<18,
    G15_KEY_M2  = 1<<19,
    G15_KEY_M3  = 1<<20,
    G15_KEY_MR  = 1<<21,

    G15_KEY_L1  = 1<<22,
    G15_KEY_L2  = 1<<23,
    G15_KEY_L3  = 1<<24,
    G15_KEY_L4  = 1<<25,
    G15_KEY_L5  = 1<<26,

    G15_KEY_LIGHT = 1<<27,

    G15_EXTENDED_KEY = 1<<28,

	/* G13 extended keys */
    G15_KEY_G19 = 1<<0,
    G15_KEY_G20 = 1<<1,
    G15_KEY_G21 = 1<<2,
    G15_KEY_G22 = 1<<3,

    G15_KEY_JOYBL = 1<<4,
    G15_KEY_JOYBD = 1<<5,
    G15_KEY_JOYBS = 1<<6,
    G15_JOY = 1<<7,

	/* G510 multimedia keys */
    G15_KEY_PLAY = 1 << 0,
    G15_KEY_STOP= 1 << 1,
    G15_KEY_PREV = 1 << 2,
    G15_KEY_NEXT = 1 << 3,
    G15_KEY_MUTE = 1 << 4,
    G15_KEY_RAISE_VOLUME = 1 << 5,
    G15_KEY_LOWER_VOLUME = 1 << 6,
    G15_KEY_MUTE_OUTPUT = 1 << 7,
    G15_KEY_MUTE_INPUT = 1 << 8,
  };


  /* this one return G15_NO_ERROR on success, something
   * else otherwise (for instance G15_ERROR_OPENING_USB_DEVICE */
  int initLibG15();
  
  /* initialise with or without initialising libusb. use this if something else has already
     used libusb and read devices / busses or if you want a particular device*/
  int setupLibG15(unsigned int vendorId, unsigned int productId, unsigned int init_usb);
  
  /* re-initialise a previously unplugged keyboard ie ENODEV was returned at some point */
  int re_initLibG15();

  int exitLibG15();
  /* enable or disable debugging */
  void libg15Debug(int option);
  
  int writePixmapToLCD(unsigned char const *data);
  int getJoystickX();
  int getJoystickY();
  int getBacklightState();
  int setLCDContrast(unsigned int level);
  int setLEDs(unsigned int leds);
  int setLCDBrightness(unsigned int level);
  int setKBBrightness(unsigned int level);  
  int setG510LEDColor(unsigned char r, unsigned char g, unsigned char b);  

  /* Please be warned
   * the g15 sends two different usb msgs for each key press
   * but only one of these two is used here. Since we do not want to wait
   * longer than timeout we will return on any msg recieved. in the good
   * case you will get G15_NO_ERROR and ORd keys in pressed_keys
   * in the bad case you will get G15_ERROR_TRY_AGAIN -> try again
   */
  int getPressedKeys(unsigned int *pressed_keys, unsigned int timeout);
  

#ifdef __cplusplus
}
#endif
	
#endif
