# DEPDisc
The DEPDisc platform is the first implementation of dielectrophoresis where both the equipment and the consumables are truly inexpensive. It utilizes CD microfluidics to allow the integration of DEP with other microfluidic operations. 
All aspects of the DEPDisc platform are open-source, including the fabrication technique for the discs (with example designs) and the device.
While the paper presents the underlying theory and the results of the DEPDisc platform, this repository is intended to provide the necessary information to reproduce the platform.

## Table of Contents
- [Discs](#Discs)
- [Device](#Device)

## Discs
In the folder [Discs](/Discs), the design files for the discs can be found. The PCB files can be used in Eagle or Fusion360 Electronics. [Example Disc PCBs](/Discs/Example%20Disc%20PCBs) are provided as inspiration. The separate [coil PCB](/Discs/Coil%20PCB/) used as transmitter is included as well. For new designs, the [coil PCB library](/Discs/Coil%20PCB%20Library/) can be used.

## Device
The [Device CAD and PCB folder](/Device%20CAD%20and%20PCB/) contains all the necessary files to reproduce the DEPDisc device. The device is composed of a PCB, off-the-shelf components, and a set of 3D printed parts. 

### PCB
To order the PCB at [JLCPCB](jlcpcb.com), the [Manufacturing folder](/Device%20CAD%20and%20PCB/PCB/Manufacturing/) with a [ZIP file](/Device%20CAD%20and%20PCB/PCB/Manufacturing/reDEP%20Base%20rev1%20v8_2024-09-17.zip) of the Gerber files is included. For assembly by JLCPCB, the [BOM file](/Device%20CAD%20and%20PCB/PCB/Manufacturing/DEPDisc%20Base%20rev1%20v8_2024-09-17.zip) and [Pick and Place file](/Device%20CAD%20and%20PCB/PCB/Manufacturing/DEPDisc%20Base%20rev1%20v8_2024-09-17.zip) are also provided. 
The ordering process is the follwing:
1. Go to [JLCPCB](jlcpcb.com)
2. Click on **Add gerber file** and upload the ZIP file
3. Select the desired options and **Enable PCB Assembly** (choose 2 as PCBA quantity instead of 5). Select **Bottom Side Assembly**.
4. After clicking **Next**, upload the **BOM file** and **CPL (Pick and Place) file**, then continue
5. When reviewing the parts, ensure that only C13 and JP3 show 'No part selected' and that the rest of the parts are correctly assigned. Then click **Next** and then **Do not Place** upon the prompt showing that the project has unselected parts.
6. Review the part placement and click **Next**, then click **Save to Cart**
7. Review the order and click **Secure Checkout**

The [design files](/Device%20CAD%20and%20PCB/PCB/Design%20Files) of the PCB for Eagle or Fusion360 Electronics are included in case this project is used as inspiration or if modifications are desired.

### Housing
The [parts for printing](/Device/3D%20Printed%20Parts) are provided as STL files. In the slicer, we recommend enabling tree-supports.
A [STEP file](/Device%20CAD%20and%20PCB/DEPDisc%20Device%20rev1.step) of the assembly is included. 

### Assembly
To assemble the device, use the following procedure:
1. Solder the pin-headers to the PCB: ![alt text](/Figures/headers_top.JPG?raw=true)![alt text](/Figures/headers_bottom.JPG?raw=true)
2. Solder two jumper wires to the motor: ![alt text](/Figures/pcb_motor.JPG?raw=true)
3. Plug the ESP32 NodeMCU Dev board into the pin-headers: ![alt text](/Figures/pcb_esp32.JPG?raw=true)
4. Screw the touch display to the display mount: ![alt text](/Figures/display_mount.JPG?raw=true)
5. Plug in 14 female-to-female jumper wires to the display. We recommend placing tape around the ends to keep the wires together when they are removed: ![alt text](/Figures/display_cables.JPG?raw=true)
6. Plug the other side of the jumper wires into the PCB: ![alt text](/Figures/pcb_display.JPG?raw=true)
7. Slide the PCB into the left side of the inner shell of the housing and move the motor through the hole: ![alt text](/Figures/pcb_housing.JPG?raw=true)
8. Screw the motor in place with two M1.2 screws: ![alt text](/Figures/motor_screws.JPG?raw=true)


