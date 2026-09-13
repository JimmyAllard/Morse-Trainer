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

Pin assignments are defined once in `include/pins.h` and mirrored in `diagram.json` for the Wokwi simulation.

| Signal | Arduino UNO pin |
|---|---|
| LCD RS | D12 |
| LCD E (enable) | D11 |
| LCD D4 | D5 |
| LCD D5 | D4 |
| LCD D6 | D3 |
| LCD D7 | D2 |
| Buzzer signal | D9 (PWM) |
| Button | D8 (`INPUT_PULLUP`, active LOW) |

- **LCD1602** is wired in **4-bit direct mode** (no I2C backpack): `RW` → GND, `VSS` → GND, `VDD`/`A` (backlight) → 5V, `K` → GND, `V0` (contrast) → GND for maximum contrast. If your module needs adjustable contrast, wire `V0` through a separate trim potentiometer instead.
- **Buzzer volume potentiometer** is wired as a hardware rheostat in series with the buzzer — one leg to the buzzer's negative terminal, the wiper to GND — rather than read by software. Turning it changes the buzzer's loudness directly; no analog pin or code is involved.
- **Button** connects one leg to D8 and the other to GND. No external pull-up resistor is needed since the firmware uses the ATmega328P's internal pull-up (`INPUT_PULLUP`).

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

The first container build installs PlatformIO, Ceedling, and Doxygen, so it can take a few minutes. Once it's done, confirm the toolchain is ready:

```bash
pio --version
ceedling version
doxygen --version
```

From there, this is the day-to-day workflow:

1. **Run the unit tests** — pure Morse logic in `lib/morse-core`, no hardware needed:
```bash
   ceedling test:all
```
2. **Build the firmware**:
```bash
   pio run -e uno
```
3. **Simulate on Wokwi** — no physical board required:
   - Command Palette → `Wokwi: Start Simulator` (requires a free license, activated once via `Wokwi: Request a New License`), or
   - `wokwi-cli .` for a headless run (requires a `WOKWI_CLI_TOKEN` from [wokwi.com/dashboard/ci](https://wokwi.com/dashboard/ci))
4. **Flash to a real UNO**, if one is connected:
```bash
   pio run -e uno -t upload
```
   On Windows with Docker Desktop, USB devices aren't passed through to the container automatically — see [usbipd-win](https://github.com/dorssel/usbipd-win) to share the board into WSL2 first.
5. **Generate documentation**:
```bash
   doxygen Doxyfile
```
   Output lands in `docs/html/index.html`.

To run all of the above in one go — test, document, build, then flash a connected board or fall back to a headless Wokwi simulation automatically — use:

```bash
./scripts/pipeline.sh
```

There are also isolated environments under `src/smoke_tests/` for bringing up one peripheral at a time before wiring everything together, e.g.:

```bash
pio run -e lcd_test -t upload      # or buzzer_test / button_test
```

Build and upload with PlatformIO, run unit tests with Ceedling, and use the Wokwi extension to simulate the circuit directly in VS Code without physical hardware.

## Project Structure

```
.
├── .devcontainer/          # Dev container configuration (Containerfile, devcontainer.json)
├── .vscode/                # VS Code + PlatformIO settings
├── docs/                   # Doxygen output (generated, ignored by git)
├── include/                # Shared application headers (e.g. pins.h)
├── lib/
│   └── morse-core/
│       ├── include/        # Pure C headers for the Morse logic
│       ├── src/            # Pure C implementation (hardware-independent)
│       └── test/
│           └── support/    # Ceedling test support files
├── scripts/
│   └── pipeline.sh         # test -> docs -> build -> flash/simulate, all in one
├── src/
│   ├── smoke_tests/        # Isolated per-peripheral test sketches (LCD/buzzer/button)
│   └── main.cpp            # Main application firmware
├── test/                   # PlatformIO's own test runner (`pio test`) — separate from Ceedling
├── .gitignore
├── diagram.json            # Wokwi circuit diagram
├── Doxyfile                # Doxygen configuration
├── platformio.ini          # PlatformIO project configuration
├── project.yml             # Ceedling project configuration
├── README.md
└── wokwi.toml              # Wokwi simulator config
```