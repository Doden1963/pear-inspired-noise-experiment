# PEAR-Inspired Noise Experiment

Zener-based noise experiment using Teensy 4.1 to test possible effects of intention on randomness.

---

## Overview

This project generates analog electronic noise using a zener diode, amplifies the signal using multiple op-amp stages (MCP6024), and samples it with a Teensy 4.1.

The signal is converted into bits and analyzed statistically using Python.

Inspired by PEAR (Princeton Engineering Anomalies Research), the project explores whether intention (e.g. focusing on "UP" or "DOWN") may influence statistical outcomes.

---

## Hardware

### Breadboard version

![Breadboard](breadboard.png)

### Signal flow

1. Zener diode generates analog noise
2. MCP6024 op-amp amplifies the signal through multiple stages
3. Output is connected to the Teensy 4.1 ADC

### Notes

* The circuit uses high gain amplification
* Breadboard wiring may introduce additional noise
* PCB version is recommended for more stable results

### Files

* `noise_generator.fzz` – Fritzing project (open in Fritzing)
* `schematic.png` – circuit overview
* `pcb.png` – PCB layout
* `gerbers.zip` – files for PCB manufacturing

---

## Firmware (Teensy)

* Reads analog signal from ADC
* Sends data over serial to computer

---

## Software (Python)

* Receives data stream
* Converts signal into bits
* Performs statistical analysis (z-score, p-values)
* Displays results

---

## Experimental Method

Each run consists of:

* Baseline period (no intention)
* Test period:

  * UP (intention to increase values)
  * DOWN (intention to decrease values)
  * NONE (control condition)

Results are evaluated statistically to detect deviations from randomness.

---

## Repository Structure

hardware/ → circuit design and images
firmware/ → Teensy code
software/ → Python analysis

---

## Status

Work in progress

---

## License

To be added

