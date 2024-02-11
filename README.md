# Lab 01: ECE 6780 Embedded System Design Spring 2024 
Lab 1 codes for class .

Authors : Kyle G. Gayliyev <br>
Date: 2-February-2024<br>
Course: ECE 6780 - Embedded System Design, ECE Department, The University of Utah<br>
GitHub IDs: ggayliye <br>
Repo: https://github.com/ggayliye/ECE6780Embedded_Sys_SPR_24 <br>
Date: 8-February-2024 (Time of when submission is/will be ready to be evaluated)<br>
Solution: Lab1<br>
Copyright: ECE 6780, Kyle G. Gayliyev - This work may not be copied for use in Academic Coursework.

<u>**Lab 01: Writing Basic I/O Code**</u><br>

## Overview of the Lab 01 
This lab explores two basic operations of the GPIO: Blinking LEDs, 
and reading the state of a pushbutton. <br>

**Note:** I will write the applications using only peripheral register
access. The single exception to this will be the HAL_Delay() function.<br>

The  Lab 01 is consisted of 2 assignements:<br>

Assignment 1: Configuring a GPIO Pin to Output and Blink an LED<br>

Assignment 2: Configuring a GPIO Pin to Input and Reading a Button<br>


### Assignment 1: Configuring a GPIO Pin to Output and Blink an LED

Assignemnt 1 requires to create the blinking demo using red and blue LEDs
on the Discovery board. 
<br>
This assignment will be completed in two steps:<br>

A): Converting the HAL Library Calls to Register Access <br>
B): Changing to the New LEDs <br>

Step-by-step instructions:<br>

A): Converting the HAL Library Calls to Register Access <br>

1. Use the RCC to enable the GPIOC peripheral clock<br>
* Remove the __HAL_RCC_GPIOC_CLK_ENABLE() HAL library macro.<br>
* Use the stm32f072xb.h header file to determine the register that 
enables the GPIOC peripheral clock.<br>
* Set the appropriate bit using bitwise operations and either a bitmask or defined bit name.<br>
2. Configure the LED pins to slow-speed, push-pull output mode without pull-up/down resistors.<br>
* Remove the GPIO_InitTypeDef struct and HAL_GPIO_Init() function call.<br>
* The green and orange LEDs are on pins PC8 and PC9.<br>
* Set the pins to general-purpose output mode in the MODER register.<br>
* Set the pins to push-pull output type in the OTYPER register.<br>
* Set the pins to low speed in the OSPEEDR register.<br>
* Set to no pull-up/down resistors in the PUPDR register.<br>
Each register map in the peripheral reference manual documents the starting state of bits in 
the register. Although clearing bits that should already be zero is not always necessary, \
it is good style to ensure that every bit is in a known state.<br>
3. Initialize one pin logic high and the other to low.<br>
* Remove the HAL_GPIO_WritePin() function call.<br>
* Use either the ODR or BSRR register.<br>
4. Toggle both pin output states within the endless loop.<br>
* Remove the HAL_GPIO_TogglePin() function call.<br>
* Use either the ODR or BSRR register.<br>
5. Leave the HAL delay function within the loop. Otherwise, the LEDs will toggle too rapidly to<br>
see. Feel free to change the duration to reasonable values.<br>

B): Changing to the New LEDs <br>
1. Use the Hardware Layout section of the Discovery board manual to find the pins connecting 
to the red and blue LEDs.<br>
* Page 13 of the Discovery board manual lists the STM32F0 pins used for LEDs.<br>
* The red LED is labeled as LD5 and the blue as LD6 on the Discovery board.<br>
* All LED pins are in the GPIOC peripheral.<br>
2. Update the pin initialization and toggle code to use the new pins.<br>

### Assignment 2: Configuring a GPIO Pin to Input and Reading a Button
Requires to change the version of the flashing LED program to button press so that the LEDs will toggle instead
of the delay.

Instructions:<br>

1. Use the Hardware Layout section of the Discovery board manual to find the pin connected to the
“USER” button.<br>
* The user button is labeled as B1 on the Discovery board.<br>
* Search through and find the material on available buttons.<br>
2. Use the RCC to enable the clock to the appropriate GPIO peripheral.<br>
3. Configure the button pin to input mode with the internal pull-down resistor enabled.<br>
* Set the pins to input mode in the MODER register.<br>
* Set the pins to low speed in the OSPEEDR register.<br>
* Enable the pull-down resistor in the PUPDR register.<br>
4. Monitor the button pin input state within the endless program loop.<br>
* Use the IDR register.<br>
5. Toggle the LED pins when a button press is detected.<br>
6. Include a software debounce routine to prevent multiple toggles on a single button press.<br>



<pre><ins>Future extensions</ins> :  There will be no future additions to this project. </pre>

# Partnership

We're partnered in the lab with students of two, but each student is expected to complete
their work individually.

<ins> Progress Notes: </ins> <br>

<ins>Feb 2nd, 2024:</ins> <br>
- Created the "ECE6780Embedded_Sys_SPR_24" GitHub repo.
- Created the "lab01" project.


<ins>2nd Week Notes:</ins> <br>
Kept working on completing the assignment.

## Testing
No Unit Test files are created as the nature of the project. Manual testing 
are performed in each step to ensure code improvements.

# Time Expenditures:
<pre>Lab01: Predicted Hours: 12h		Actual Hours:	12h		 </pre>

The actual hours recorded on top reflect the time spent for the assignment including the time spent in labs. It excludes time spent reading and understanding the lab assignment instructions at the beginning of the lab (pre-lab work).

# Comments to Evaluators:


<em>To able to fully test the main.c, other files and tools are required.<br>
For example, I created the project using the STM32CubeMX software first. Then <br>
clicked "Code Generation" button from the top menu after adjusting necessary <br>
settings. The instructions on how to adjust the settings will be given below. Then, <br>
the software automatically opens the Keil uVision5 softwhere where we code main.c.<br>
The main.c will be located under the "Application/User/Core" folder on the left menu of 
the Keil uVision5 softwhere.</em><br>

The main.c includes the 1st and 2nd part of the assignment. One of the assignments<br>
must be commented out. To test the commented out part, you'll need to uncomment that <br>
section and comment out the already uncommented section. Follow the comments<br>
out the sections in the main.c file.

## Testing Instructions:
After reading the discussion above, let's adjust the settings of
STM32CubeMX and Keil uVision5 softwares. <br><br>
STM32CubeMX:<br>

Select STM32F0 in the Series filter.<br>
* Select STM32F0x2 in the Lines filter
* Select LQFP64 in the Package filter <br>
At this point, there should only be a few choices available, select STM32F072RBTx and press the OK
button.<br>
Come to Project ->Menu->Settings.<br>
Name the new project. Select a directory where STMCube can create subfolders to store project files.<br>
Change the Toolchain/IDE dropdown menu to MDK-ARM V5.<br>
On the Project tab, move to the Code Generator tab at the top of the window.<br>
STMCube may take a while to copy the files to the directory specified in the settings. Afterward,
you may be asked if you want to open the project folder or project file itself. Click "project file".<br>
Now you should be in the "Keil uVision5" program as it's opened automatically.<br><br>

Keil uVision5:<br>

Click "Flash" -> "Configure flash tools" from the top menu.<br>
Click "Target" from the top menu. Find "Arm complier" menu and select 
"use default compiler version..".


One the setting is done, replace the main.c file in the "Application/User/Core" folder <br>
with my main.c file you downloaded.<br>
From the top menu, "Project"->"Build Target".<br>
Plug in your STM32F072 Discovery Microcontroller to your computer. <br>
Click "Flash" -> "Download" from the top menu. Test it on your STM32F072 Discovery Microcontroller.



Thank you for evaluating this project and providing feedback. <br>

Have a wonderful day!

# Consulted Peers:
N/A

# Examples of Good Software Practice (GSP)
<pre><ins>DRY</ins> :</pre>
DRY is an abbreviation of "Don't repeat yourself". It's a principle of Software Engineering that
has the goal of reducing repetition and redundancy in the coding. Using abstractions and normalization
are advised over redundancy <a href="https://en.wikipedia.org/wiki/Don%27t_repeat_yourself">[2]</a>.

<pre><ins>Separation of Concerns</ins> :</pre>
This concept is similar to the "divide and conquer" principle where you divide
a big software project into small projects to complete. A software design technique that focuses on separating 
and freeing functionalities of a program is called Modular programming. Making each of the divided small 
projects independent and addressing a separate concern, it'll make it easy to reduce, detect 
and fix the errors. <a href="https://en.wikipedia.org/wiki/Separation_of_concerns">[3]</a>

<pre><ins>Good Code Typing Practices</ins> :</pre>
Good coding practices can be listed as: Naming variables with a relevant name, commenting 
in between code lines with a brief explanation if the code is not self-explanatory, creating 
helper methods that can be used multiple times and by other sections.


<pre><ins>Testing Strategies</ins> :</pre>
Unit Testing can be summarized in 3 types of techniques:<br>

1. <ins>Black Box Testing : </ins> In this testing, input, user interface, and output parts are covered.
2. <ins>White Box Testing : </ins> In this testing, functionality, design structure, and code models are covered.
3. <ins>Gray Box Testing : </ins> In this testing, analysis of code performance, relevant test cases,
methods, and functions are covered.<a href="https://www.geeksforgeeks.org/unit-testing-software-testing/">[4]</a>


# References:
1. Canvas Page Class Materials.(For example, lecture slides, additional resources and pdf files). <br>
2. https://en.wikipedia.org/wiki/Don%27t_repeat_yourself<br>
3. https://en.wikipedia.org/wiki/Separation_of_concerns<br>
4. https://www.geeksforgeeks.org/unit-testing-software-testing/<br>






