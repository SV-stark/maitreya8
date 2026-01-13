# Maitreya 8 (Fork)

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![License](https://img.shields.io/badge/license-GPLv2-blue.svg)](COPYING)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20Mac-lightgrey.svg)]()
[![Version](https://img.shields.io/badge/version-8.0-orange.svg)]()

This is a modern fork of **Maitreya 8**, originally referenced from [martin-pe/maitreya8](https://github.com/martin-pe/maitreya8). Maitreya is a comprehensive software platform for Vedic (Jyotish) and Western astrology.

---

## 🚀 Features

- **Dual System Support**: Full capability for both Vedic and Western astrological calculations.
- **Cross-Platform**: Designed for Windows, Linux, and macOS.
- **High Precision**: Integrates with the [Swiss Ephemeris](http://www.astro.com/swisseph/) for accurate planetary positions.
- **Extensive Configuration**: Highly customizable charts, dashas, and screen layouts.
- **Modernized UI**: (In Progress) Refreshed interface with improved window chrome and toolbars.

## 🛠️ Build Status & Improvements

This fork includes critical fixes and ongoing improvements over the original stable release:

- **Build System**: Fixed build errors related to Unicode encoding in C++ source files (`Sheet.cpp`).
- **Code Modernization**: Replaced deprecated `wxWidgets` API calls (e.g., `wxBrush`, `wxPen` styles) with modern, standards-compliant enums (`wxBRUSHSTYLE_*`, `wxPENSTYLE_*`) in both the `jyotish` and `gui` modules.
- **Clean Compilation**: Warning-free compilation on modern GCC/MinGW toolchains.

## 📦 Installation & Building

### Prerequisites

- **Compiler**: MinGW (Windows) or GCC (Linux/Mac)
- **Dependencies**: `wxWidgets 3.x`
- **Build Tools**: `make` (Mingw32-make)

### Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/maitreya8.git
    cd maitreya8
    ```

2.  **Build the application:**
    Run the standard make command in the root directory.
    ```bash
    mingw32-make
    ```

3.  **Run:**
    The executable will be generated in the `src/gui` or release folder.

## 📄 License

This project is licensed under the **GNU General Public License v2.0 (or later)**.  
See the [COPYING](COPYING) file for details.

### Third-Party Components
- **Swiss Ephemeris**: GPL v2.0
- **wxWidgets**: wxWindows Library Licence
- **wxPdfDocument & wxSqlite3**: wxWindows Library Licence
- **Saravali Font**: SIL Open Font License

## 🤝 Contributing

Contributions are welcome! If you're interested in modernizing C++ GUI applications or have expertise in astrological algorithms:

1.  Fork the repository.
2.  Create your feature branch (`git checkout -b feature/AmazingFeature`).
3.  Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4.  Push to the branch (`git push origin feature/AmazingFeature`).
5.  Open a Pull Request.

## 🔗 Original Project

- **Website**: [saravali.github.io](https://saravali.github.io)
- **Original Repo**: [martin-pe/maitreya8](https://github.com/martin-pe/maitreya8)

---
*Maintained by SV Stark*
