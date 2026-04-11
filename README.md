# PEAR-Inspired Noise Experiment

Zener-based noise experiment using Teensy 4.1 to test possible effects of intention on randomness.

---

## Overview

This project generates analog electronic noise using a zener diode, amplifies the signal through multiple stages, and samples it with a Teensy 4.1 microcontroller.

The sampled signal is converted into bits and analyzed statistically using Python.

The goal is to explore whether intention (e.g. focusing on "UP" or "DOWN") may influence statistical properties of the generated noise.

---

## Inspiration

This project is inspired by the work of Princeton Engineering Anomalies Research (PEAR), which investigated whether human intention could influence random physical systems.

This implementation is an independent, open-source experimental setup.

---

## System Architecture

### Hardware

* Zener diode noise source
* Multi-stage analog amplifier (MCP6024)
* Output connected to Teensy 4.1 ADC

### Firmware (Teensy)

* Reads analog signal from ADC
* Sends data over serial
* File: `teensy_noise.ino`

### Software (Python)

* Receives data stream
* Converts signal into bits
* Performs statistical analysis (z-score, p-values)
* Visualizes results

---

## Hardware

### Breadboard version

![Breadboard](breadboard.png)

### Signal flow

1. Zener diode generates analog noise
2. MCP6024 op-amp amplifies the signal through multiple stages
3. Output is sampled by the Teensy 4.1 ADC

### Notes

* High gain amplification makes the circuit sensitive to noise
* Breadboard wiring may introduce additional interference
* A PCB version is recommended for improved stability

### Files

* `noise_generator.fzz` – Fritzing project (open in Fritzing)
* `schematic.png` – circuit overview
* `pcb.png` – PCB layout
* `gerbers.zip` – files for PCB manufacturing

---

## Experimental Method

Each run consists of:

* **Baseline period** (no intention)
* **Test period** with one of the following conditions:

  * UP (intention to increase values)
  * DOWN (intention to decrease values)
  * NONE (control condition)

The output is analyzed to detect deviations from expected randomness.

---

## Repository Structure

```
/hardware     → circuit design and images  
/firmware     → Teensy code  
/software     → Python analysis  
/data         → Example output  
/docs         → Method and results  
```

---

## How to Use

### 1. Hardware

* Open the Fritzing file in `/hardware`
* Build the circuit as shown

### 2. Firmware

* Open `teensy_noise.ino` in Arduino IDE (with Teensy support)
* Select Teensy 4.1
* Upload to the board

### 3. Software

Install dependencies:

```
pip install -r software/requirements.txt
```

Run the program:

```
python software/main.py
```

---

## Notes

* This is an experimental system and results should be interpreted with care
* Noise sources and analog amplification are sensitive to layout and environment
* Statistical fluctuations can occur naturally

---

## Status

Work in progress

---

## License

Open source

