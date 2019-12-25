#include <stdlib.h>
#include <string.h>

#include "pattern.h"

static int _pattern_valid(const pattern_t *ptn);

static pattern_t active_pattern;
static frame_t frame_buff[FRAMES_MAX];
static int current_frame = -1;

static frame_t default_frame;

int
pattern_start(const pattern_t *ptn)
{
    if (_pattern_valid(ptn)) {
        return (-1);
    }

    if (pattern_stop()) {
        return (-1);
    }

    memcpy(&active_pattern, ptn, sizeof(pattern_t));
    active_pattern.frames = frame_buff; /* Don't point to provided frames */
    memcpy(&frame_buff, ptn->frames, sizeof(frame_t) * ptn->nframes);
    current_frame = 0;

    /* TODO: create a FreeRTOS looping task that can apply the frames */

    return (0);
}

int
pattern_stop()
{
    memset(&active_pattern, 0, sizeof(pattern_t));
    memset(frame_buff, 0, sizeof(frame_buff));
    current_frame = -1;

    return (0);
}

int
pattern_set_default_frame(const frame_t *frame)
{
    if (!frame) {
        return (-1);
    }

    memcpy(&default_frame, frame, sizeof(frame_t));
    return (0);
}

const frame_t *
pattern_get_default_frame()
{
    return &default_frame;
}

const pattern_t *
pattern_get_active_pattern()
{
    return &active_pattern;
}

int
pattern_set_pulse(pattern_t *ptn)
{
    if (!_pattern_valid(ptn)) {
        return (-1);
    }

    /* off up to on */
    for (int i = 0; i < ptn->nframes / 2; i++) {
        frame_t *cur = &ptn->frames[i];
        cur->style = FRAME_PWM;

        int val = (i * 2 * UINT8_MAX) / ptn->nframes;
        for (int p = 0; p < BUTTON_CNT; p++) {
            cur->btn_vals[p] = (uint8_t)val;
        }
    }

    /* on down to off */
    for (int i = ptn->nframes / 2; i < ptn->nframes; i++) {
        frame_t *cur = &ptn->frames[i];
        cur->style = FRAME_PWM;

        int val = UINT8_MAX -
            ((i - ptn->nframes / 2) * 2 * UINT8_MAX) / ptn->nframes;
        for (int p = 0; p < BUTTON_CNT; p++) {
            cur->btn_vals[p] = (uint8_t)val;
        }
    }

    return (0);
}

int
pattern_set_onlyon(pattern_t *ptn)
{
    if (!_pattern_valid(ptn)) {
        return (-1);
    }

    for (int i = 0; i < ptn->nframes; i++) {
        frame_t *cur = &ptn->frames[i];
        cur->style = FRAME_DIGITAL;
        memset(cur->btn_vals, UINT8_MAX, sizeof(cur->btn_vals));
    }

    return (0);
}

int
pattern_set_onlyoff(pattern_t *ptn)
{
    if (!_pattern_valid(ptn)) {
        return (-1);
    }

    for (int i = 0; i < ptn->nframes; i++) {
        frame_t *cur = &ptn->frames[i];
        cur->style = FRAME_DIGITAL;
        memset(cur->btn_vals, 0, sizeof(cur->btn_vals));
    }

    return (0);
}

static int
_pattern_valid(const pattern_t *ptn)
{
    if (!ptn || !ptn->frames || ptn->nframes == 0 || ptn->nframes > FRAMES_MAX
        || ptn->frame_len == 0 || ptn->frame_len > FRAME_LEN_MAX) {
        return (-1);
    }

    return (0);
}
