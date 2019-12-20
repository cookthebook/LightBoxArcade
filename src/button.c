#include "button.h"

int
apply_value(button_t *btn, int value)
{
    if (!btn) {
        return (-1);
    }

    btn->value = value;
    return (0);
}
