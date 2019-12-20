#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <stdint.h>

#include "button.h"

typedef enum frame_style_enum {
    FRAME_DIGITAL = 0, /* Only ON/OFF */
    FRAME_PWM, /* Various levels of dimness */
} frame_style_t;

/* Object of how to display a single frame */
typedef struct frame_struct {
    frame_style_t style; /* how to interperet vals */
    uint8_t btn_vals[BUTTON_CNT]; /* Map of values for every LED */
} frame_t;


#define FRAME_LEN_MAX (1000)
#define FRAMES_MAX    (32)
/* Object that contains all the info for a full LED pattern */
typedef struct pattern_struct {
    uint8_t frame_len; /* length of one frame in ms */
    uint8_t nframes; /* length of the frames array */
    frame_t *frames; /* array of button LED bitmaps */
} pattern_t;



/* Start going through the frame of the given pattern
 * The internal current pattern is automatically stopped if running, since
 * this town ain't big enough for the two of us
 *
 * Returns immediately */
int pattern_start(const pattern_t *ptn);

/* Stop the current pattern
 * If a default frame is set, the LED's will be set accordingly.
 * Otherwise, the LED's stay in the last known state. */
int pattern_stop();

/* Set a default frame for when a pattern isn't active */
int pattern_set_default_frame(const frame_t *frame);

const frame_t *pattern_get_default_frame();

const pattern_t *pattern_get_active_pattern();


/* Fill the pattern with a basic pulsing style */
int pattern_set_ripple(pattern_t *ptn, button_loc_t start_btn);

/* Frames are only with LEDs on */
int pattern_set_onlyon(pattern_t *ptn);

/* Frames are only with LEDs off */
int pattern_set_onlyoff(pattern_t *ptn);

#endif /* _PATTERN_H_ */
