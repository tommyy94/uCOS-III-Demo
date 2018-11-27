#ifndef ATOMIC_OPERATIONS_H_
#define ATOMIC_OPERATIONS_H_


static uint32_t CriticalSecCntr;


__STATIC_FORCEINLINE void EntrCritSection(void)
{
    if(CriticalSecCntr == 0)
    {
        __disable_irq();
    }

    // avoid lost of one count in case of simultaneously calling from both places
    ++CriticalSecCntr;
}


__STATIC_FORCEINLINE void ExtCritSection(void)
{
    if(--CriticalSecCntr == 0)
    {
        __enable_irq();
    }
}


// Atomic exchange of data between a memory cell and a register
// return value of the memory cell
__STATIC_FORCEINLINE uint32_t AtomicExchange (uint32_t State, uint32_t *Flag)
{
    uint32_t Hold;
    
    EntrCritSection();
    Hold = *Flag;
    *Flag = State;
    ExtCritSection();
    return(Hold);
}


#endif                                                          /* End of SERIAL_H_                                     */
