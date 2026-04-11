## Hardware

Fritzing breadboard layout:

![Breadboard](breadboard.png)

### Signal flow

- Zener diode → generates noise  
- MCP6024 op-amp → amplifies the signal  
- Output → connected to Teensy 4.1 ADC  

### Notes

- The circuit uses multiple amplification stages  
- Breadboard wiring may introduce additional noise  
