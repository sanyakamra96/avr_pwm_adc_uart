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
