# Ditherbox
Dithering tool for Astrophotography without guiding. This tool uses an ATtiny 84 to control an equatorial mount through its ST4 port.<br />
Dithering is commonly used in astrophotography to reduce pattern noise. However, to automate the process it is necessary to have a guiding setup, or camera control software. This means that you have to take a computer out "in the field".
In order to use dithering in a non-guided, stand-alone situation, I have developed this little tool.<br />
The box consists of a microcontroller (Atmel ATtiny 84) and 5 optocouplers. The microcontroller checks the state of an input (PA7), coming from a camera controller (Synscan camera control or an intervallometer). Between exposures, when the input is HIGH, the microcontroller sends a signal through the ST4 port to the mount (RA+, RA-, DEC+, DEC-). This signal offsets the mount and the camera sensor from one exposure to the next.<br />
The amount of offset is determined by the user through the camera controller and guiding speed settings on the Synscan controller.
The tool will send a signal to the mount as long as the input is high.
Dithering follows an outward spiraling pattern (DEC+, RA+, DEC-, DEC-, RA-, RA-, DEC+, DEC+, DEC+, etc).<br />
The device does not know how many exposures will be taken. After the last exposure, the mount will not stop by itself. Just hit the reset button to stop.<br />
The software allows for 110 exposures before the pattern repeats itself. However, if more exposures are being used, a new spiraling pattern will start where the last one ended. The last loop in the spiral has 10 steps per side. This corresponds to 10 x 15 = 150 pixels. This means that the pattern ends 75 pixels from the start position in both Dec and RA.
# Hardware
Microcontroller: Atmel ATtiny84<br />
Input (from camera controller): PA7<br />
Output (to mounts ST4 port): PA0 ... PA3<br />
Output to camera: PA5<br />
Optional output to indicator LED: PA4<br />
Reset input: RST input of the ATtiny<br />
ST4 and camera outputs are electrically isolated through the use of optocouplers.<br />
If a Synscan Handcontroller is used as camera controller, power may be taken from the RJ11 connector. This is 12 V, a voltage converter (5 V) is included in the schematics. If another camera controller is used, power must be provided by other means (e.g. 3.7 V LiPo battery). In this case, the voltage regulator may be omitted.
Connection from the tool to the mount is not critical. If wires are mixed, the pattern will not be a spiral. But try not to mix Dec with RA, or the mount will just swing back and forth.<br />
There is a reset button which resets the microcontroller.<br />
# Theory
It is recommended to dither approximately 15 pixels.
The user has to calculate how many arcseconds, which speed and which time to dither.
Example: <br />
Assume the resolution of the camera is 1" per pixel. Sidereal rate is 15 arcseconds per second (time); therefore one second dithering at sidereal rate will offset the mount and sensor 15 pixels.
If the guiding speed is set to less, e.g. 0,5 * sidereal, one second dithering will only result in 7.5 pixels offset.

Assume the resolution of the camera is 2" per pixel
15 pixels is equivalent to 30 arcseconds
Sidereal rate is 15 arcseconds per second.
If guiding speed is sidereal rate, you have to dither for 2 seconds. At half sidereal rate, dither for 4 seconds.

On your camera controller, set the time between exposures to the time you need to dither.
If you need to increase the time between exposures, decrease the guiding speed accordingly.
#Note
When I built the box, I tested it with powering from the Synscan and powering from a 3.7 V LiPo battery. Both worked, but testing cost me a 5 V regulator. The box now contains a 3.3 V regulator instead. This works great.
