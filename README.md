# DEPDisc
The DEPDisc platform is the first implementation of dielectrophoresis where both the equipment and the consumables are truly inexpensive. It utilizes CD microfluidics to allow the integration of DEP with other microfluidic operations. 
All aspects of the DEPDisc platform are open-source, including the fabrication technique for the discs (with example designs) and the device.
While the paper presents the underlying theory and the results of the DEPDisc platform, this repository is intended to provide the necessary information to reproduce the platform.

This version is from the 06th of October 2024. A more current version might be available at https://github.com/nicklas-rn/DEPDisc.

## Table of Contents
- [Discs](#Discs)
- [Device](#Device)
- [How to Run](<#How to Run>)
- [Additional Figures](<#Additional Figures>)

## Discs
In the folder [Discs](/Discs), the design files for the discs can be found. The PCB files can be used in Eagle or Fusion360 Electronics. [Example Disc PCBs](/Discs/Example%20Disc%20PCBs) are provided as inspiration. The separate [coil PCB](/Discs/Coil%20PCB/) used as transmitter is included as well. For new designs, the [coil PCB library](/Discs/Coil%20PCB%20Library/) can be used.

## Device
The [Device CAD and PCB folder](/Device/) contains all the necessary files to reproduce the DEPDisc device. The device is composed of a PCB, off-the-shelf components, and a set of 3D printed parts. 

### PCB
To order the PCB at [JLCPCB](https://jlcpcb.com), the [Manufacturing folder](/Device/PCB/Manufacturing/) with a [ZIP file](/Device/PCB/Manufacturing/DEPDisc%20Base%20rev1%20v8_2024-09-17.zip) of the Gerber files is included. For assembly by JLCPCB, the [BOM file](/Device/PCB/Manufacturing/DEPDisc%20Base%20rev1%20v8_2024-09-17.zip) and [Pick and Place file](/Device/PCB/Manufacturing/DEPDisc%20Base%20rev1%20v8_2024-09-17.zip) are also provided. 
The ordering process is the follwing:
1. Go to [JLCPCB](https://jlcpcb.com)
2. Click on **Add gerber file** and upload the ZIP file
3. Select the desired options and **Enable PCB Assembly** (choose 2 as PCBA quantity instead of 5). Select **Bottom Side Assembly**.
4. After clicking **Next**, upload the **BOM file** and **CPL (Pick and Place) file**, then continue
5. When reviewing the parts, ensure that only C13 and JP3 show 'No part selected' and that the rest of the parts are correctly assigned. Then click **Next** and then **Do not Place** upon the prompt showing that the project has unselected parts.
6. Review the part placement and click **Next**, then click **Save to Cart**
7. Review the order and click **Secure Checkout**

The [design files](/Device/PCB/Design%20Files) of the PCB for Eagle or Fusion360 Electronics are included in case this project is used as inspiration or if modifications are desired.

### Housing
The [parts for printing](/Device/3D%20Printed%20Parts) are provided as STL files. In the slicer, we recommend enabling tree-supports. 
A [STEP file](/Device/DEPDisc%20Device%20rev1.step) of the assembly is included. 

### Assembly
To assemble the device, use the following procedure:
1. Place M3 nuts in all the provided slots in the 3D printed parts.
2. Solder the pin-headers to the PCB: ![alt text](/Figures/headers_top.JPG?raw=true)![alt text](/Figures/headers_bottom.JPG?raw=true)
3. Solder two jumper wires to the motor: ![alt text](/Figures/pcb_motor.JPG?raw=true)
4. Plug the ESP32 NodeMCU Dev board into the pin-headers: ![alt text](/Figures/pcb_esp32.JPG?raw=true)
5. Screw the touch display to the display mount: ![alt text](/Figures/display_mount.JPG?raw=true)
6. Plug in 14 female-to-female jumper wires to the display. We recommend placing tape around the ends to keep the wires together when they are removed: ![alt text](/Figures/display_cables.JPG?raw=true)
7. Plug the other side of the jumper wires into the PCB: ![alt text](/Figures/pcb_display.JPG?raw=true)
8. Slide the PCB into the left side of the inner shell of the housing and move the motor through the hole: ![alt text](/Figures/pcb_housing.JPG?raw=true)
9. Screw the motor in place with two M1.2 screws: ![alt text](/Figures/motor_screws.JPG?raw=true)
10. Slide the display in to the right side of the inner shell of the housing: ![alt text](/Figures/display_housing.JPG?raw=true)
11. Screw the display in place from the bottom with four M3 screws: ![alt text](/Figures/display_screws.JPG?raw=true)
12. Connect the two inner shell sides with three M3 screws: ![alt text](/Figures/housing_screws.JPG?raw=true) ![alt text](/Figures/housing_screws2.JPG?raw=true)
13. Place the right side of the outer shell on top of the inner shell by carefully bending it slightly: ![alt text](/Figures/right_outer.JPG?raw=true)
14. Push the aluminium rod through the left side of the outer shell and the hatch: ![alt text](/Figures/rod.JPG?raw=true)
15. Push the left side of the outer shell on top of the inner shell by moving it in from the left and carefully bending it slightly: ![alt text](/Figures/left_outer1.JPG?raw=true) ![alt text](/Figures/left_outer2.JPG?raw=true)
16. Screw six M3 screws into the outer shell: ![alt text](/Figures/shell_screws.JPG?raw=true)

### Programming
To program the device, use the [Arduino file](/Device/Software/DEPDisc_base.ino) provided in the [Software folder](/Device/Software). Use to following procedure:
1. Download the Arduino IDE
2. Install the ESP32 boards under the boards manager (Second tab from the top, type 'esp32' in the search bar, and click install)
3. Click on Tools -> Board -> esp32 -> ESP32 Dev Module
4. Select the correct port under Tools -> Port
5. Click on the upload button (right arrow) to upload the code to the ESP32

## How to Run
### Experimental mode
Connect the device with a USB cable to a laptop. Use the Serial Monitor of the Arduino IDE and select a Baud Rate of 115200. 
To set a specific frequency, type: `freq [frequency in Hz]`
To set a specific speed, type: spin `[PWM value between -255 and 255]`

### Run from SD card
Write a text file with the name **run.txt** to the SD card with the same commands as above. Between the commands use a newline. Use the command `delay [delay in seconds]` to set delays. Insert the SD card into the device and select 'Run from SD card'. The device will read the file and execute the commands.

## Additional Figures
- [A video showing the attraction of yeast cells to the edges of two electrodes](/Figures/dep_edge.mov).
