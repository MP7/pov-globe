# Introduction #

A POV sphere consists of two very basic sections - the part that spins and the part that remains static. The goal set up by the group was to design the sphere such that all elements are within the spinning party. The motor, microcontroller, and all circuit elements spin with the ring. To do this, a number of obstacles needed to be overcome.


# Design #

## Overall Design ##

http://i.imgur.com/7OEsGyZ.jpg?1

The system has several main components:
  * Arduino Uno
  * The Motor using brush power
  * The ring
  * The hall effect sensor w/ positive & negative magnets
  * LED strip
  * Capacitor for current smoothing
  * Voltage Regulator w/ Heat sink

The voltage is supplied through brush power by the motor. The voltage is used to power all of the components in the system. The brush power does not provide constant power and will often cut out for microseconds. To accommodate this, a capacitor is used to supply power to the Arduino and LED strip when the brush power is not connected.

A voltage regulator w/ heat sink is also used in order to ensure that the Arduino does not receive more than 12 V.

The Arduino is directly connected to the LED strip and hall effect sensor. It uses information from the hall effect sensor to manage when to send information to the LED strip.

An overhead beam is attached to the top of the ring with a rod to stop the ring from wobbling back and forth. Also on this arm are the magnets used by the hall effect sensor.

# Images #

## LED Strip ##

![http://i.imgur.com/pPhstvah.jpg](http://i.imgur.com/pPhstvah.jpg)

## Capacitor & Voltage Regulator ##

![http://i.imgur.com/7si6P0vh.jpg](http://i.imgur.com/7si6P0vh.jpg)

## Brush Power System ##

![http://i.imgur.com/PRw1qyI.jpg](http://i.imgur.com/PRw1qyI.jpg)


# Process of Design #

The hardware needed to accomplish 3 main objectives:
  * Spin the ring at a rate that is capable of achieving persistence of vision.
  * Be able to identify when a new cycle has begun
  * Light up a set of LEDs in such a manner as to create a persistence of vision image.

To accomplish this, first a method of powering the inner section of the sphere needed to be established. While a number of ideas were suggested, the final design had a motor inside of a PVC tube. Holes were drilled out of the tube and the motors wires were fed through the holes. Two copper rings were wrapped around the tube and the wires that were fed through the holes were soldered to the copper rings. These copper rings are to maintain contact with a set of copper brushes. These brushes would be the source of voltage and ground for the entire project. This design allowed the voltage source to maintain regular contact with the copper rings, and thus, supply consistent power to the motor, as well as the rest of the project.

Once the motor was fitted inside this tube, the next step was to build the actual ring and attach it to the motor. The ring was made out of the lid of a plastic bucket. This gave the size and stability that would satisfy the project requirements. The ring was screwed onto the motor's tube. Next the motor was glued into a piece of plastic that was then screwed down to the base. This laid the foundation for the rest of the project. At this point, the motor was able to spin the ring when put into contact with a voltage source.

This was the first issue that we encountered during this design. The current design had a significant amount of wobble when spinning. To solve this, a wooden beam was attached to the base that went over the ring. The ring was connected to the beam by a rod. The rod hung freely from the beam and its impact on the ring's spin rate was negligible. However, it stopped nearly all of the wobble.

The next stage was to add a microcontroller. The microcontroller chosen for this project was a Arduino Uno. The Uno was attached to platform that has two PCB boards. The platform was attached to the ring section. This brought up the next issue for the design. Due to the method that power is delivered to the system, there are often instants in which the copper brushes are not in contact with the copper rings. In these instants, the system is not powered. This meant that the Uno was reset midway through a rotation. To solve this, a capacitor was added in parallel with the voltage source for current smoothing. In the instants that the voltage source is not connected to the system, the capacitor discharges are provides the necessary power.

The next issue that we faced was the Uno would shut off unexpectedly after several seconds. After some debugging, it was found that the Uno was receiving about 22 V, far beyond the 6-12 V suggested input. To solve this, a voltage regulator was added in series to decrease the voltage delivered to the Uno. Because the voltage regulator would get very hot, a heat sink was put behind it.

Next, we needed a way to identify when the ring has completed a rotation. A hall effect sensor was used for this. A hall effect sensor uses magnetic fields. It identifies a change from a positive magnet to a negative magnet. Two screws were put into the beam that was attached to the overhead beam and they were each magnetized. One screw was magnetized to positive and one to negative. When the ring spins, the hall effect sensor passes by the positive magnet and then goes by the negative magnet immediately after. When the hall effect sensor has read both the positive and negative magnets, a rotation has been completed.

Now that we have a ring that is capable of spinning, a microcontroller with a consistent power supply, and sensor to read the current frequency for the ring's rotation, the only thing left was to attach the LEDs. An Adafruit LED strip was used for simplicity's sake, and it was glued to one side of the ring. Once the LEDs were wired to the Uno, the ring was able to spin and lit up in such a way that persistence of vision was possible. At this point, all hardware was working properly. Once the software was written, images were displayed on the sphere.