#ifndef HOST_INTERRUPT_H
#define HOST_INTERRUPT_H

#define ISR(vector, ...)            \
    void vector (void)

static inline void sei(void) {};

#endif //HOST_INTERRUPT_H