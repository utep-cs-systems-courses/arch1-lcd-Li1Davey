## Description
This Program allows you to draw a circle with two switches or play the solfa method going to the
highest not then back to the lowest note. You can also turn off the CPU by pressing S4.

Press S1 to draw a circle that gets bigger.

Press S2 to draw a circle that gets smaller.

Press S3 to play the notes from the solfa method.

Press S4 to turn off the CPU.

## Notes
1) The msp430 will show you the options for the switches at the start.

2) If you press S1 or S2 and decide to press the other draw switch, the msp430
will shrink or grow the smae circle that was being drawn.

3) S3 will clear the screen.

4) When the notes go up for the solfa method the lights get dimmer and when it
goes down they will get brighter.

5) When the notes go up for the solfa method the green LED will only be on until it
reaches the highest note where both the red and green LED will be on, then the
red LED will be on only for when the notes go down.

6) S4 will show the options you have for the switches.

7) The msp430 is a bit slow then drawing the circle so when it gets smaller
the screen will turn blue and the cirle will be drawn.

8) Due to the circle being drawn slowly there is a glitch wich causes the
circle to be drawn after a switch input. To compensate for this the defualt
text is put on the screen twice for S4.

9) To configure the C file to the msp430 type _make loadC_ on the console. To
configure the assembly file to the msp430 type _make loadS_ on the
console. Please note that these files only change what language is used to
switch what LED is off or on. 
