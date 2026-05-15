# AVR PWM + ADC + UART System

## Overview
This project implements:
- Timer0 Phase-Correct PWM (PD6)
- Synchronized ADC sampling triggered by Timer0
- EMA filtering of ADC values
- UART transmission at 10 Hz using polling (UDRE flag)

## Architecture
- 2 kHz control loop (PWM + ADC)
- Interrupt-driven ADC processing
- Main-loop UART scheduling

## Key Features
- No blocking in ISR
- Fixed-point EMA filter
- Hardware-synchronized sampling
- Minimal AVR register-level implementation


## Problem Statement

Design a bare-metal embedded system on ATmega328PB that:

- Generates Phase-Correct PWM on Timer0 (PD6)
- Achieves approximately 2 kHz control/sampling rate
- Performs ADC sampling synchronized with PWM using Timer0 overflow trigger
- Applies exponential moving average (EMA) filtering to ADC readings
- Converts filtered ADC value into current (0–100 A scale)
- Transmits current data over UART at ~10 Hz
- Ensures non-blocking, interrupt-safe design
