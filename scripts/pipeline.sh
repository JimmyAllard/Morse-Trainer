#!/usr/bin/env bash
#
# scripts/pipeline.sh — Morse Trainer dev pipeline
#
#   1. Ceedling unit tests     (pure logic, fails fast — no hardware needed)
#   2. Doxygen documentation
#   3. PlatformIO build
#   4. Flash a real UNO if one is plugged in, otherwise run a headless
#      Wokwi simulation
#
# Usage:
#   ./scripts/pipeline.sh [pio-environment]
#     pio-environment defaults to "uno" (the real firmware).
#     Pass e.g. "lcd_test" to run this pipeline against a smoke test instead.
#
# Env vars:
#   WOKWI_CLI_TOKEN   required for the simulation step. Get one from
#                     https://wokwi.com/dashboard/ci
#   FORCE_SIMULATE=1  skip hardware detection and always simulate, even if
#                     a board is plugged in.

set -euo pipefail

PIO_ENV="${1:-uno}"
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

log()  { printf '\n\033[1;36m==> %s\033[0m\n' "$1"; }
fail() { printf '\n\033[1;31m✗ %s\033[0m\n' "$1"; exit 1; }

# --- 1. Unit tests -------------------------------------------------------------
log "Running Ceedling unit tests"
ceedling test:all || fail "Unit tests failed — fix them before building firmware"

# --- 2. Documentation ------------------------------------------------------------
log "Generating Doxygen documentation"
doxygen Doxyfile || fail "Doxygen generation failed"

# --- 3. Build firmware -------------------------------------------------------------
log "Building PlatformIO firmware (env:${PIO_ENV})"
pio run -e "$PIO_ENV" || fail "PlatformIO build failed"

# --- 4. Flash real hardware, or simulate on Wokwi ------------------------------------
DEVICE=""
if [ "${FORCE_SIMULATE:-0}" != "1" ]; then
    for candidate in /dev/ttyACM* /dev/ttyUSB*; do
        if [ -e "$candidate" ]; then
            DEVICE="$candidate"
            break
        fi
    done
fi

if [ -n "$DEVICE" ]; then
    log "Hardware detected at $DEVICE — flashing"
    pio run -e "$PIO_ENV" -t upload --upload-port "$DEVICE" \
        || fail "Upload failed (device present but flashing failed — check USB passthrough/permissions)"
else
    log "No hardware detected — No flash"
fi

log "Pipeline complete ✅"
