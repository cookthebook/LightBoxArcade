#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdint.h>

#define BUTTON_CNT (8)

typedef enum button_loc_enum {
    LP = 0,
    MP,
    HP,
    TP,
    LK,
    MK,
    HK,
    TK,
} button_loc_t;

typedef struct button_struct {
    uint8_t value; /* the output intensity for the LED */
    button_loc_t location; /* corresponding controller location */
} button_t;

/* set internal value and set pins accordingly */
int apply_value(button_t *btn, int value);

#endif /* _BUTTON_H_ */
