#ifndef _RISCV_INTR_CONTROLLER_H
#define _RISCV_INTR_CONTROLLER_H

void            plicinit(void);
void            plicinithart(void);
int             plic_claim(void);
void            plic_complete(int);

#endif
