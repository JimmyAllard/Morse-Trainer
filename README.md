# Morse Trainer

A Morse code trainer built on an **Arduino UNO R3**. The device lets a user practice sending and/or decoding Morse code using a physical button, hear the result through a buzzer, adjust the volume with a potentiometer, and read feedback on a 16x2 LCD screen.

This is a personal learning project developed with an embedded, test-driven workflow: **VS Code + Dev Container**, **PlatformIO**, **Ceedling** (Unity-based unit testing for the C logic), **Doxygen** (code documentation), and the **Wokwi** simulator for hardware-in-the-loop development without needing the physical board on hand at all times.

## Features

- Morse code input via a push button (dot / dash / letter / word timing)
- Audio feedback through a passive buzzer
- Adjustable buzzer volume via a potentiometer
- Visual feedback and training prompts on a 16x2 LCD
- Unit-tested core Morse encoding/decoding logic (Ceedling / Unity)
- Simulated in Wokwi for quick iteration without hardware
- Doxygen-generated code documentation

## Hardware

This project uses parts from an Arduino UNO R3 "super starter kit." Datasheets below are for the general component type/driver chip; if your kit uses a different manufacturer part, check its included documentation for exact electrical ratings.

| Component | Role in the project | Datasheet |
|---|---|---|
| Arduino UNO R3 (ATmega328P) | Main controller | [Arduino UNO R3 datasheet](https://docs.arduino.cc/resources/datasheets/A000066-datasheet.pdf) |
| Passive buzzer | Plays Morse tones (driven via `tone()` on a digital pin) | Generic component — no single manufacturer datasheet |
| Potentiometer (linear, e.g. B10K/WH148) | Controls buzzer volume (analog input) | Generic component — no single manufacturer datasheet |
| Push button | User input for keying Morse (dot/dash timing) | Generic tactile switch — no single manufacturer datasheet |
| LCD1602 Module (HD44780-compatible) | Displays prompts, decoded characters, and feedback | |

### Wiring

TODO

## Development Environment

This project is developed inside a **VS Code Dev Container**, so no local toolchain installation is required beyond Docker and VS Code.

- [**PlatformIO**](https://docs.platformio.org/en/latest/) — build system and Arduino framework integration
- [**Ceedling**](https://throwtheswitch.github.io/Ceedling/latest/) — C unit testing (Unity/CMock) for hardware-independent Morse logic
- [**Doxygen**](https://www.doxygen.nl/manual/docblocks.html) — source code documentation generation
- [**Wokwi**](https://docs.wokwi.com/?utm_source=wokwi) — in-editor circuit simulation (Arduino UNO + buzzer + potentiometer + button + LCD1602)

### Getting started

```bash
# Clone the repository
git clone <repo-url>
cd morse-trainer

# Open in VS Code and reopen in the dev container when prompted
code .
```

Build and upload with PlatformIO, run unit tests with Ceedling, and use the Wokwi extension to simulate the circuit directly in VS Code without physical hardware.

## Project Structure

```
.
├── .devcontainer/      # Dev container configuration
├── .vscode/            # VS Code + PlatformIO settings
├── docs/               # Doxygen output (generated, ignored by git)
├── include/            # Application headers (Arduino/C)
├── lib/               
│   └── morse-core/
│       ├── include/    # Ceedling/Core firmware headers
│       ├── src/        # Ceedling/Core firmware sources
│       └── test/       # Ceedling/Unity unit tests
├── src/                # Application sources (Arduino/C)
├── test/               # PlatformIO/Unit tests
├── wokwi.toml          # Wokwi simulator config
├── diagram.json        # Wokwi circuit diagram
├── platformio.ini      # PlatformIO project configuration
└── README.md
```