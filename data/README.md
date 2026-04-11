## 📊 Example Results

This section shows selected visualizations from experimental runs.  
All plots are generated directly from recorded data and can be reproduced from the files in the `/data` folder.

---

### 🔹 Combined Histograms (UP / DOWN / NONE)

![UP DOWN NONE histograms](plots/UP%20DOWN%20NONE%20histograms.png)

Histograms of run results for the three experimental conditions:

- **UP** – intention to increase the accumulator  
- **DOWN** – intention to decrease the accumulator  
- **NONE** – no intention (control condition)

Each histogram shows:

- Distribution of run results  
- Empirical mean (middel)  
- Empirical standard deviation (σ empirisk)  
- Theoretical standard deviation (σ teoretisk ≈ 1000)  
- Reference lines for ±1σ, ±2σ, ±3σ  

Observations:

- The distributions are approximately normal  
- Means are close to zero, as expected under randomness  
- Empirical σ is close to theoretical values (~1000), indicating stable statistical behavior  

---

### 🔹 All Runs Histogram

![All runs histogram](plots/All%20runs%20histrogram.png)

Combined distribution across all runs (n = 422):

- Mean ≈ **69.1**  
- Empirical σ ≈ **1035**  
- Theoretical σ ≈ **1000**

The distribution is close to a normal distribution centered near zero, with only a small positive offset relative to σ.

This suggests no strong global bias across all runs.

---

### 🔹 Example Run (LSB + Von Neumann, z ≈ 3.20)

![Example run](data/plots/Skærmbillede%202026-04-11%20201932.png)

Example of a live run using:

- **Bit method:** LSB sampling with Von Neumann debiasing  

**UP channel:**
- Accumulator: **+39,208**  
- Bits: **150,000,000**  
- z-score: **+3.20**  
- p ≈ **0.00137 (two-sided)**  

**DOWN channel:**
- z ≈ **−0.29** (no significant deviation)

**NONE (control):**
- z ≈ **−0.47** (consistent with randomness)

**Combined (Fisher & Stouffer):**
- Stouffer z ≈ **2.52**  
- p ≈ **0.0117 (two-sided)**  

The plot shows the accumulator evolving over time relative to ±1σ, ±2σ, and ±3σ boundaries.

The UP curve approaches the +3σ region, illustrating a statistically notable deviation within this single run.

---

## 📁 Reproducibility

All plots shown above can be traced back to:

- Raw bitstreams in `/data/bit_dumps/`
- Log files in `/data/logs/`
- Processing pipeline in `/software/`

---

## ⚠️ Notes

- Individual runs can occasionally reach z-scores around 2–3 by chance  
- Interpretation requires aggregation over many independent runs  
- Von Neumann debiasing reduces bias but also reduces effective bit rate  
- Small deviations of the mean relative to σ are expected in finite samples  


