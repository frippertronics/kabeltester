#ifndef INTERRUPT_H
#define INTERRUPT_H

#define ISR(vector, ...)            \
    void vector (void)

static inline void sei(void) {};

#endif //INTERRUPT_H
