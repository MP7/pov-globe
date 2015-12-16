# Introduction #

The software is relatively straightforward. A .bmp image is stored in a header file that is loaded onto the Arduino, and this image is used by the main loop to see where to light the LEDs and what color they should be.


# Details #

The first step for the software takes place before the files are even loaded onto the Arduino. First, a BMP image must be saved into an array in a header file. The reason that this has to be done is because of memory constraints on the Uno. An Arduino Uno does not have the memory capacity to store a BMP image in SRAM. So the image is stored as a constant which allows it to be stored in program memory, which the Uno has plenty.

The motor is not controlled by the software, when the system is connected to power, it will simply start spinning. The Arduino will know when a rotation has been completed by reading from the hall effect sensor. The hall effect sensor waits to see if it senses a high value - indicating a positive magnet. Once it does that, it looks to see if there is a low value - indicating a negative magnet. Once it has sensed both, a cycle has been completed and it is ready to paint.

Now, the Uno simply writes the pixels column by column as fast as it can. Because the motor is relatively constant, this maintains an image in a fairly static location.  The Uno checks the header file (where the BMP is stored) and looks at the current column and writes all values into an array. The array is then sent to another function which updates all values in the LED strip. This function was provided by Adafruit, the strip's manufacturer. Once a column has been written to the strip, the column index number is incremented by one and the process is repeated.

Each void loop() on the Arduino does one of two things - if it has just passed by the positive and negative magnets, it resets all values (the boolean for positive magnet and negative magnet, as well as the column index). If the positive & negative magnet booleans are both false then it will update the next column.