# ConsignmentTetris

This project involved programming a robot to both determine an efficient packing of items, and to execute the required motions to move the items. Here is the system in action:

![gif of system](https://user-images.githubusercontent.com/29378769/117544134-33d57000-b020-11eb-83fd-386b17f7aa43.gif)

An autonomous system can be roughly divided into 4 subsystems, which operate in a loop: sensing (taking input), planning (deciding what to do), controlling (figuring out how to do your plan) and actuating (enacting the plan). Our simulated Robot has similar subsystems: an image processor which scans the environment and outputs position and size of objects on the conveyor, a process optimizer that figures out where the objects should be placed, and a planning and control module that handles robot movement. Of course, we also had to set up the environment the robot would be working in - conveyors, shipping boxes, items and the robot itself.

This diagram depicts the data flow of our system:
![image](https://user-images.githubusercontent.com/29378769/135134984-d66f059c-a489-4d8d-909a-e28231b01c0d.png)



## Demo video

[![demo video youtube link](https://img.youtube.com/vi/xn7uCO0on6M/0.jpg)](https://www.youtube.com/watch?v=YJBlpAK8cyE)

## Project report

See the document [here](https://docs.google.com/document/d/1DVAbLG0-JVYs8TGfxziGwzxtoarIRItUwqf9t5kM0Cs) (Note that the document is currently only available to Cambridge students).

## Required Matlab modules
 - Robotic System Toolbox
 - Simscape
 - Simscape Multibody
 - Simscape Multibody Contact Forces
     - https://github.com/mathworks/Simscape-Multibody-Contact-Forces-Library 
 - Simulink
 - Simulink 3D Animation
 - Stateflow
