# BeeMos bee counter module (BCM) documentation
## BCM PCB soldering and debug instructions (_STILL UNDER CONSTRUCTION_)
### 1. Solder basic elements to make the microcontroller work (starting with the hardest/riskiest to solder)
* Microcontroller
* Mini USB port
* 8 Mhz cristal
* Voltage regulator
* ...
* ...
* ...
### 2. Power the board by connecting the USB cable (one LED should turn on), check immediately that the USB port or the microcontroller are not overheating by touching them with your fingers (a few seconds are usually enough to know)
### 3. Choose "Lilipad USB" as board in the Arduino IDE, then burn bootloader with USBtiny in circuit programmer and JTAG cable in contact with the ISP pins of the board until the bootloader has finished to burn
### 4. Upload a simple "blink" sketch, confirm that the sketch was indeed uploaded (i.e. confirm that the LED is indeed blinking)
### 5. Solder the demultiplexer, upload test code to the board to send a signal on each of the pins of the demultiplexer and confirm with an oscilloscope connected to GND and to each of the pins that a signal is indeed sent on each pin 
### 6. Solder an IR emitter/receptor (QRE1113), try not to spend to much time to avoid overheating of the component. Solder the two associated resistors and check that the IR LED is emitting either using an oscilloscope between  ~~pins X and Y~~ or by using the camera of your phone (you should see a purple beam, although this works more or less depending on your phone/camera, you can try to change the angle between the phone and board). In case you see no signal from the IR LED, make sure soldering is appropriate and if fiddling with soldering doesn't work, try replacing the QRE1113 sensor (some have failed  during our test perhaps due to overheating during soldering or manufacture issues)
### 7. Solder the 15 other QRE1113s and their associated resistors
### 8. Repeat the IR LED emitting test (from step 6) on all other QRE1113s until all work
### 9. Upload test sketch to the board and see how the sensors react when passing your finger or a pencil over them in both directions
### 10. Upload full code to the board and install the PCB in its enclosure
### 11. Test in the field