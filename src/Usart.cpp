#include "Usart.hpp"

Usart usart0(usartInfos + 0);

const UsartInfo PROGMEM usartInfos[] = {
    { &UCSR0A, &UCSR0B, &UBRR0, &UDR0 }
};

ISR(USART_UDRE_vect)
{
    if (usart0.fifo == nullptr || usart0.fifo->isEmpty()) {
        // Buffer empty, so disable interrupts
        //*usart0.info->ucsrb() &= ~_BV(UDRIE0);
        UCSR0B &= ~_BV(UDRIE0);
    } else {
        // There is more data in the output buffer. Send the next byte
        //*usart0.info->udr() = usart0.fifo->remove();
        UDR0 = usart0.fifo->remove();
    }
}

