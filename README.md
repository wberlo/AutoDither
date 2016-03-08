# AutoDither
Dithering tool for Astrophotography without guiding
Uses an ATtiny 84 to control an equatorial mount through ST4 port
Dithering is commonly used in astrophotography to reduce pattern noise. However, to automate the process it is necessary to have a guiding setup.
In order to use dithering in a non-guided situation, I have developed this little tool.
The tool consists of a microcontroller (Atmel ATtiny 84) and 5 optocouplers. The microcontroller checks the state of an input (PA7), coming from a camera controller (Synscan camera control or an intervallometer). Between exposures, when the input is HIGH, the microcontroller sends a signal through the ST4 port to the mount (RA+, RA-, DEC+, DEC-). This signal offsets the mount and the camera sensor from one exposure to the next.
The amount of offset is determined by the user through the camera controller and guiding speed settings on the Synscan controller.
The tool will send a signal to the mount as long as the input is high.
Dithering follows an outward spiraling pattern (e.g. DEC+, RA+, DEC-, DEC-, RA-, RA-, DEC+, DEC+, DEC+, etc)
# Theory
It is recommended to dither approximately 15 pixels.
The user has to calculate how many arcseconds, which speed and which time to dither.
Example:
Assume the resolution of the camera is 1" per pixel.
Sidereal rate is 15 arcseconds per second (time)
Therefore one second dithering at sidereal rate will offset the mount and sensor 15 pixels.
If the guiding speed is set to less, e.g. 0,5 * sidereal, one second dithering will only result in 7.5 pixels offset.

Assume the resolution of the camera is 2" per pixel
15 pixels is equivalent to 30 arcseconds
Sidereal rate is 15 arcseconds per second.
If guiding speed is sidereal rate, you have to dither for 2 seconds. At half sidereal rate, dither for 4 seconds.

On your camera controller, set the time between exposures to the time you need to dither.
If you need to increase the time between exposures, decrease the guiding speed accordingly.
