#!/bin/bash
UsbdmFlashProgrammer -target=hcs08 -device=MC9S08DZ60 -program -erase=All -security:unsecured -execute prg.s19
