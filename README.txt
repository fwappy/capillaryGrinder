       READ ME
----------------------
Instructions for operation:

When you turn on the machine, it will show you the "home screen". This screen will list the 
OD, ID, and angle that you wish to grind at. You will initially be editing the angle, which is done
by turning the dial right or left. Once you are satisfied with the value, you can press "Next", and that
will move you on to edit the next value, OD (Outer Diameter). This is edited in the same way, and then pressing
next again will move you to the ID. Pressing it a 4th time will return you angle.

At any time, you can press set zero. This will allow you to move the arm up and down. Listed on the screen will be 
the speed at which you are moving it. Once you touch down, set the speed to zero, then press set zero again. 
This will bring you back to the home screen where you can verify the measurements. Then pressing start will begin the
grinding process. It will display the percent completed, and once done, it will raise the arm so the capillary can be removed.

At the moment, only one capillary can be ground and then the system must be reset, but that will hopefully be fixed soon.

Pressing the stop button at any time will turn off the motors and the system must be reset for anything else to happen.

There are a few variables that will be important for you to edit.

grindStepDistance: The way this code currently operates is that it will move down
		   grindStepDistance microns and stay at that place for a specified time
		   before continuing downward. By editing this value, you can change
		   amount it moves before it waits. We used 10 microns.

delayTime: 	   The delayTime sets how long it waits at each step. We used 20 seconds,
		   which is equivalent to 20000 ms. This variable uses milliseconds.


grindSpeed: 	   This variable sets how quickly it will move the grindStepDistance. You 
		   can input this speed as microns per second. We used 500 microns per second,
		   but we did not experiment with this value.



