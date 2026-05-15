#include <avr/io.h>
#include <avr/interrupt.h>

// ---------------- Global ----------------
volatile uint16_t ema = 0;
volatile uint16_t uart_tick = 0;

// ---------------- PWM ----------------
void PWM_Init()
{
    DDRD |= (1 << PD6);

    TCCR0A = (1 << WGM00) | (1 << COM0A1); // phase correct PWM
    TCCR0B = (1 << CS01);                  // prescaler 8

    OCR0A = 128; // 50%
}

// ---------------- ADC ----------------
void ADC_Init()
{
    ADMUX = (1 << REFS0) | (1 << ADLAR); // AVcc, ADC0

    ADCSRA = (1 << ADEN)  |
             (1 << ADATE) |
             (1 << ADIE)  |
             (1 << ADPS2) | (1 << ADPS1); // /64

    ADCSRB = (1 << ADTS2); // Timer0 overflow trigger

    ADCSRA |= (1 << ADSC);
}

// ---------------- ADC ISR ----------------
ISR(ADC_vect)
{
    uint8_t adc = ADCH;

    ema = ema + ((adc - ema) >> 4); // EMA

    uart_tick++;
}

// ---------------- UART ----------------
void UART_Init()
{
    UBRR0 = 51; // 9600 baud @ 8 MHz
    UCSR0B = (1 << TXEN0); // TX enable only
}

void UART_Send(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))  // wait until buffer empty
        ;

    UDR0 = data; // send byte
}

// ---------------- Conversion ----------------
static inline uint8_t get_current()
{
    return (uint8_t)((ema * 100) / 255);
}

// ---------------- Main ----------------
int main()
{
    PWM_Init();
    ADC_Init();
    UART_Init();

    sei();

    while (1)
    {
        if (uart_tick >= 200) // 2 kHz → 10 Hz
        {
            uart_tick = 0;

            UART_Send(get_current());
        }
    }
}
