# The Macruwu
The Macropad for all! (well, at least, if you can understand the Clusterfuck posted here)
The Firmware is based on the Arduino Pico Core by earlephilhower https://github.com/earlephilhower/arduino-pico. 


## Components used

I went with the RP2040 based board from seeed studio. It has a fast chip, offers integrated USB support and is only about 6$. However, it has limited GPIO pins. So if you want to build your own, I would recommend using I/O Expanders or something similar. A nother option would be to use a raspberry Pi with a RP2040. This Board beaks out most of the RP2040 Pins and has Options for Wifi.

In order to try out different Keyswitches and keep the Macruwu modular, I decided to use hotswap sockets. They arent to expensive, if you order them for Aliexpress (about 1\$/10psc). But beware, when soldering. If youre Borad Manufacturer decides to give you the shit coating on your Pads, prepare for heavy flux use.

For the I/O Expanders I used the PCA9555 from NXP. They conviniantly dont need a lot of setup and are automatically set to INPUT_PULLUP. The detailed Adressing sceme and co can be found in the Datasheet. But, as per usual nowadays, the I/O expanders are sold out. So you might want to look for them somewhere else, or find a suitable replacement. But if you can find them, I can recommend the NXP Expanders. They need minimal to no Software Setup and I haven’t had a dead one so far.

The level shifter (TXU0104PWR) is a cheap option I got from Mouser. It has 4 Chanels it can shift and is enough for the two 5V I²C Lines ans the Neopixel line.

The Keyswitches were purchesed for Aliexpress and some smaller Keyboard parts suppliers. I like clicky switches, so I went for the Gateron greens. However, I can not recoment them. They sound quite hollow and scratchy. Could maby fixed with some lube *gigidy*, but its not realy worth the trouble. 
If you want some realy clicky Keyswitches, that will any the hell out of anybody in a 30km Radius, you could go for the Kailh Low profile Chock whites. My, extremely pissed of, fellow student can confirm. However, be aware that they can not be used with relegendable Kecaps.
## How to compile

### With the Arduino IDE 2.0
First download the Code either from the repo or via the release tab. Put it in a folder and open the ```Macruwu_OS.ino``` file.

In order to compile the Code, you need to install the Arduino Pico core. There is a Tutorial on how to do this on earlephilhowers Github. You will also need the Adafruit SPIFlash Library. It can be downloaded via the Library Manager. The rest should be included in the Pico Core.
If you get Library conflicts, I´m afraid, you´re on youre own. I somehow got it to compile and hav´nt touched my setup since. No Idea why it sudenly worked, but the only thing I can recomend, is to back up your Librarys and start fresh.

EDIT: If you get a Library conflict, you may want to look for other Bugs. Sometimes the Arduino IDE shows this message, just to inform you, that it has used a cirtain Library. However, your Code may not comile due to a nother error.

Also remember to change the USB Stack to the Adafruit TinyUsb Stack via Tools->USB Stack.
If you want to use the inbuilt Flash as a drive, you also have to allocate Memory under Tools->Flash Size. The first time you allocate Memory, you will have to format it. Just doing it in Windows should be fine.
P.s. The flash drive code is more or less copied from Adafruit. sorry, I was lazy...

### With PlatformIO
Well... I have no Idea, but let me know, if you find out.

## How to use (isch...)

The Macruwu OS is devided in to several Files for maximum ```'someFuckingShit' is not defined did you mean 'goFuckYourSelf'?```

### With macroLayout.txt

NOTE: The first time you start the Macruwu, you might have problemt, with it crashing. This may be caused by the File not beeing present in the Flash dircetory. You may have to disable the ```readFile```-funktion in the ```Keyboard::init```-funktion in ```Keyboard.cpp``` and upload the File first. Then reenable the funktion and it should run.

The Layout can be set with serveral Commands. ```Layer x: ``` sets the Layer under wich the Buttons will be accesable. ```Button x: {string}``` sets the Button and is followed by the string, that will be printed by the keyboard. Remember to leave a space between ```:``` and ```{string}```. This is due to the way that the file gets read. The Character steight after the ```:``` will be ignored.

So far most characters will be interpreted correctly, however ```<``` and ```>``` have a special Meaning. They press the left and right arrowkeys respectively. Verry usefull for Macropads that print code with a lot of Brackets. Other Funktion have not jet been implemented, but feel free to add them in the ```Keyboard.cpp``` under ```Keyboard::interpet```.

In order to read the file from the Flash in to the Data structure you want to run the ```readFile```-funktion at least once. I recomend running it once in ```setup()``` and then running it each time the file is changed. this can be done with:
```
if(Macruwu.fsChanged()){
    Macruwu.readFile();
  }
```

In order to run the commands that have been set in the Datastructure you will have to run the ```interpret(layer, button)```-funktion.

### With Hardcoded Mapping
The Keymapping can be set in the ```Mapping.cpp```.

In order to write something over USB, you can use ```Keyboard1.write("something");``` But this only works for most normal characters like letters and sometimes other specialty symbols. You´ll have to try it out. Things like Brackets or things that use Funktionkeys, will have to be set up manualy. This can eather be done, by sending the commands via the Tiny USB library directly, or by adding a new funktion to the Keyboard class. But look through the Keyboard class, as I may add more Funktions in the future.

**Word of Warning:** If you do not have a US Keyboard, be prepared for some HID Code treasurehunting. I havn´t found a way to change the layout, so you eather have to find a Layout and redefine all the keys in the Library, or just try and hope you find what you need. If you have a German Keyboardlayout set, you can referance the code for some mappings.

## Bugs
Yes

## Further documentation
I recomend reading the documentation by earlephilhower https://github.com/earlephilhower/arduino-pico. It´s a far better than this clusterfuck, but feel free to look through the code.
