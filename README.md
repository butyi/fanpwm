# fanpwm

Car heater fan power control

## Introduction

Originally my car has a three position rotate switch for fan speed, which allows only two speed levels.
On high speed the fan motor has got the full battery voltage (12...14V).
On low speed there was a serial resistor wire to decrease fan speed.
Project was developed to control heater fan speed lossless and more selectable speed levels.

## Software

Software is pure assembly code as usually, since function is very easy.

### Switch

There are two digital inputs about state of three state fan turning switch.
One about low speed selection, this corresponds to second position.
One about high speed selection, this corresponds to the last third position.
Inputs are filtered by software.
Edges are captured to detect which state was switched from which other state.

### Motor 

Calculate motor level from changes of switch.
Off switch state corresponds to motor off.
High switch state corresponds to 100% PWM.
Low (middle) switch state is more sophisticated.
When low state comes from off state, it results 40% PWM.
When low state comes from high state, it results 60% PWM.
When low state is left for a short time to off state, PWM is decreased by 10%.
When low state is left for a short time to high state, PWM is increased by 10%.
10% PWM is skipped completely because fan does not start due to friction forces.

### Battery measurement

Battery supply voltage is measured.
If voltage is lower than 11V, fan is disabled to not discharge the battery.

### CAN

CAN is initialized. 
Automatic BufOff recovery is configured, there is no other error handling. 

If suitable CAN message is received, motor power is controlled by CAN signal.
CAN signal has priotity over switch inputs.
CAN uses 11 bit long CAN ID. CAN ID structure is 
- low 3 bits defines the message content. Message identifier 0 controls the motor.
- higher 6 bits is destination node ID. Node ID of this fanpwm node is 5.
- highest two bits is message priority. This is don't care from receive point of view.
This means, 11 bits in CAN ID shall be 00000101000b = 0x028
First data byte is always node ID of source node.
Second byte is motor PWM value in percentage (0% - 100%).

#### Status LED

Status LED has normal flash period when board is ready to operate.
Flash period becomes fast when low battery voltage inhibit is active.

### Display

For development debug purpose, display handler codes are part if software code.
Display shows internal variables during working.
Code is not part of final software. 
Can be switched off-on by macro definition `IS_DISPLAY`.

### Compile

- Download assembler from [aspisys.com](http://www.aspisys.com/asm8.htm).
  It works on both Linux and Windows.
- Check out the repo
- Run my bash file `./c`.
  Or run `asm8 prg.asm` on Linux, `asm8.exe prg.asm` on Windows.
- prg.s19 is now ready to download.
  Run my bash file `./p` to program the controller by USBDM.

### Download

Since I haven't written downloader/bootloader for DZ family yet, I use USBDM.

USBDM Hardware interface is cheap. I have bought it for 10€ on Ebay.
Just search "USBDM S08".

USBDM has free software tool support for S08 microcontrollers.
You can download it from [here](https://sourceforge.net/projects/usbdm/).
When you install the package, you will have Flash Downloader tools for several
target controllers. Once is for S08 family.

It is much more comfortable and faster to call the download from command line.
Just run my bash file `./p`.

## Hardware

### Controller board

The hardware is [sci2can board](https://github.com/butyi/sci2can)

### Motor control

Fan motor is switched off-on very fast by low side N-channel FET (IRLB3034).
The FET need gate driver to minimize dissipated power.
I have constructed the following circuit as MOSFET driver.

![mosfet driver](https://github.com/butyi/heaterpwm/blob/main/mosfetdriver.jpg)

I know there are much easier, cheaper solutions to drive a MOSFET, but I had these components at home, so I used these.
I have considered
- this is a 12V car, voltage limitation on MOSFET gate is not needed
- drive gate fast to both up and down
- default state must be off state for motor

## License

This is free. You can do anything you want with it.
While I am using Linux, I got so many support from free projects,
I am happy if I can give something back to the community.

## Keywords

Car, Fan, Heater, PWM, Speedcontrol, PulseWidthModulation
Motorola, Freescale, NXP, MC68HC9S08DZ60, 68HC9S08DZ60, HC9S08DZ60, MC9S08DZ60,
9S08DZ60, HC9S08DZ48, HC9S08DZ32, HC9S08DZ, 9S08DZ, UART, RS232.

###### 2021 Janos BENCSIK

