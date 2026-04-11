# PEAR-Inspired Noise Experiment

Zener-based noise experiment using a Teensy 4.1 to explore whether intention (e.g. focusing on "UP" or "DOWN") may influence statistical properties of random data.

---

## 🔍 Overview

This project generates analog electronic noise using a zener diode, amplifies the signal, and samples it with a microcontroller.

The sampled signal is converted into a bitstream and analyzed statistically in real time using Python.

The goal is to explore whether directed intention correlates with deviations from expected randomness, inspired by experiments conducted by the Princeton Engineering Anomalies Research (PEAR) lab.

⚠️ This project is exploratory and does **not claim proof** of any effect.

---

## ⚙️ How It Works

### Hardware

- Zener diode noise source  
- Analog amplification (~10,000×)  
- Teensy 4.1 microcontroller (12-bit ADC)  
- External 3.3V regulator  

### Sampling

- ~15,000 samples per second  
- 12-bit resolution (0–4095)  

### Bit Generation

- Least Significant Bit (LSB) extraction  
- Von Neumann debiasing  
  - 00 / 11 → discarded  
  - 01 → 0  
  - 10 → 1  

### Channels

- **UP** → intention to increase accumulator  
- **DOWN** → intention to decrease accumulator  
- **NONE** → control (no intention)

---

## 📊 Example Results

This section shows selected visualizations from experimental runs.  
All plots are generated directly from recorded data and can be reproduced from the files in the `/data` folder.

---

### 🔹 Combined Histograms (UP / DOWN / NONE)

![UP DOWN NONE histograms](data/plots/UP%20DOWN%20NONE%20histograms.png)

Histograms of run results for the three experimental conditions:

- **UP** – intention to increase the accumulator  
- **DOWN** – intention to decrease the accumulator  
- **NONE** – no intention (control condition)

Each histogram shows:

- Distribution of run results  
- Empirical mean  
- Empirical standard deviation (σ)  
- Theoretical σ (≈ 1000)  
- Reference lines for ±1σ, ±2σ, ±3σ  

**Observations:**

- Distributions are approximately normal  
- Means are close to zero  
- Empirical σ is close to theoretical values  

---

### 🔹 All Runs Histogram

![All runs histogram](data/plots/All%20runs%20histrogram.png)

Combined distribution across all runs:

- n = 422  
- Mean ≈ 69.1  
- Empirical σ ≈ 1035  
- Theoretical σ ≈ 1000  

The distribution is consistent with expected statistical behavior and shows no strong global bias.

---

### 🔹 Example Run (LSB + Von Neumann, z ≈ 3.20)

![Example run](data/plots/visualization-of-data.png)

Example of a live run:

**Method:**
- LSB sampling + Von Neumann debiasing  

**UP channel:**
- Accumulator: +39,208  
- Bits: 150,000,000  
- z-score: +3.20  
- p ≈ 0.00137 (two-sided)  

**DOWN channel:**
- z ≈ −0.29  

**NONE (control):**
- z ≈ −0.47  

**Combined:**
- Stouffer z ≈ 2.52  
- p ≈ 0.0117  

The UP curve approaches the +3σ boundary, illustrating a statistically notable fluctuation within a single run.

---

## 🧪 Experimental Notes

- Individual runs can reach z ≈ 2–3 by chance  
- Statistical interpretation requires many independent runs  
- Von Neumann debiasing reduces bias but lowers bit rate  
- Small mean offsets are expected in finite datasets  

---

## 📁 Project Structure

pear-inspired-noise-experiment/
│
├── data/
│ ├── logs/ # Statistical results
│ └── plots/ # Generated plots
│
├── software/ # Python + Teensy code
│
└── README.md

---

## 🔁 Reproducibility

All results can be reproduced from:

- `/data/bit_dumps/` → raw bitstreams  
- `/data/logs/` → statistical outputs  
- `/software/` → processing and analysis code  

---

## 🎯 Purpose

This project aims to:

- Build a transparent, reproducible noise experiment  
- Explore statistical behavior of physical randomness  
- Investigate (without assumption) possible correlations with intention  

---

## ⚠️ Disclaimer

This project is exploratory and should not be interpreted as evidence of causal effects without rigorous statistical validation and independent replication.

---

## 📌 Inspiration

Inspired by the work of the Princeton Engineering Anomalies Research (PEAR) program.

---

## 📬 Contributions

Suggestions, critiques, and replication attempts are welcome.
