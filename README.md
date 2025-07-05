# 🚀 Post-Quantum Cryptography Optimization: CRYSTALS-Dilithium for Resource-Constrained Devices

This project demonstrates the **optimization of the post-quantum signature scheme CRYSTALS-Dilithium (Dilithium-II)** for **resource-constrained devices** such as IoT nodes and embedded systems. It includes:

✅ An **optimized implementation of Dilithium-II** leveraging memory management and vectorized operations.
✅ A **benchmarking suite** comparing the optimized Dilithium-II against the standard Dilithium-II, Dilithium-III, Dilithium-V, and Falcon-512.
✅ Python visualization tools for analyzing key generation, signing, and verification performance.

---

## 📂 Features

* ⚡ **Optimized Dilithium-II** for better performance on constrained devices.
* 📊 **Performance benchmarking** for lattice-based signature schemes (Dilithium II/III/V, Falcon).
* 📈 **Grouped bar chart visualization** for direct comparison.
* 📄 **CSV export** for easy data analysis and reporting.
* 🛡️ Uses **liboqs** for post-quantum cryptographic primitives.

---

## 🛠 Technologies Used

* **C (GCC)** – Optimized implementation and benchmarking suite.
* **liboqs** – Open Quantum Safe library for post-quantum cryptography.
* **Python 3 (Matplotlib, Pandas)** – Data visualization and analysis.

---

## 📝 Project Structure

```
.
├── dilithium_optimized.c          # Optimized Dilithium-II implementation with benchmarking
├── results.csv                    # Benchmark results (auto-generated)
├── plot_results.py                # Python script for visualization
├── pqc_comparison.png             # Grouped bar chart (auto-generated)
├── README.md                      # Project documentation
```

---

## 🚀 Getting Started

### 📥 Prerequisites

* GCC or Clang compiler with C99 support
* liboqs installed ([installation guide](https://github.com/open-quantum-safe/liboqs))
* Python 3 with `matplotlib` and `pandas`

```bash
pip install matplotlib pandas
```

### 🛠 Build and Run

1. **Compile the C code**:

   ```bash
   gcc dilithium_optimized.c -loqs -o dilithium_optimized
   ```

2. **Run benchmarks**:

   ```bash
   ./dilithium_optimized
   ```

   This generates `results.csv`.

3. **Visualize results**:

   ```bash
   python3 plot_results.py
   ```

---


## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🤝 Acknowledgements

* [Open Quantum Safe Project (liboqs)](https://openquantumsafe.org/)
* [NIST Post-Quantum Cryptography Standardization](https://csrc.nist.gov/Projects/post-quantum-cryptography)
