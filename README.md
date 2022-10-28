# The Macruwu
The Macropad for all! (well, at least, if you can understand the Clusterfuck posted here)
The Firmware is based on the Arduino Pico Core by earlephilhower https://github.com/earlephilhower/arduino-pico. 
I used it with the Seeed Studio Xiao RP2040, a very overpowered Board for the Job.

## How to compile

### With the Arduino IDE 2.0
In order to compile the Code, you need to install the Arduino Pico core. There is a Tutorial on how to do this on earlephilhowers Github. You will also need the Adafruit SPIFlash Library. It can be downloaded via the Library Manager. The rest should be included in the Pico Core.
If you get Library conflicts, I´m afraid, you´re on youre own. I somehow got it to compile and hav´nt touched my setup since. No Idea why it sudenly worked, but the only thing I can recomend, is to back up your Librarys and start fresh.
Also remember to change the USB Stack to the Adafruit TinyUsb Stack via Tools->USB Stack.
If you want to use the inbuilt Flash as a drive, you also have to allocate Memory under Tools->Flash Size. The first time you allocate Memory, you will have to format it. Just doing it in Windows should be fine.
P.s. The flash drive code is more or less copied from Adafruit. sorry, I was lazy...

### With PlatformIO
Well... I have no Idea, but let me know, if you find out.

## How to use (isch...)

The Macruwu OS is devided in to several Files for maximum ```'someFuckingShit' is not defined did you mean 'goFuckYourSelf'?```

The Keymapping can be set in the ```Mapping.cpp```.

In order to write something over USB, you can use ```Keyboard1.write("something");``` But this only works for most normal characters like letters and sometimes other specialty symbols. You´ll have to try it out. Things like Brackets or things that use Funktionkeys, will have to be set up manualy. This can eather be done, by sending the commands via the Tiny USB library directly, or by adding a new funktion to the Keyboard class.

**Word of Warning:** If you do not have a US Keyboard, be prepared for some HID Code treasurehunting. I havn´t found a way to change the layout, so you eather have to find a Layout and redefine all the keys in the Library, or just try and hope you find what you need.

## The I/O Expanders
I used the PCA9555 I/O Expanders from NXP. They conviniantly dont need a lot of setup and are automatically set to INPUT_PULLUP. The detailed Adressing sceme and co can be found in the Datasheet.

## Bugs
Yes

## Further documentation
I recomend reading the documentation by earlephilhower https://github.com/earlephilhower/arduino-pico. It´s a far better than this clusterfuck, but feel free to look through the code.
