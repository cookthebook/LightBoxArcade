# LightBoxArcade

Reponsive lighting project for fightsicks (8 button) using an STMG070RB.

## Requirements

- [`amazon-freertos`](git@github.com:aws/amazon-freertos.git)
- `arm-none-eabi-gcc/gdb`
- `st-util`

## Design

### Hardware

Each button is assigned the following:

- Digital input pin for state tracking
- Digital output pin for simple on/off lighting
- A (potentially shared) PWM pin for dimming effects
- Simple one color LED

### Patterns

Lighting patterns are preprogrammed routines that control the output of every LED.

Some examples of patterns:

- Every button on
- Every button off, after 1 second fully on, after 1 more fully off
- A single button on
- LP on, LK and MP on,  MK and HP on, HK and 3P on, then finally 3K on

### Events

An event is what triggers a pattern to start or to stop early. An event can happen due to any of the following:

- Button press
- Button release
- Timer expiration
- Active pattern end

There can only ever be one active pattern, so if a new pattern starts the previously active one will be automatically stopped.

### Triggers

Triggers are what ties any type of event to a certain pattern. When an event occurs, if a trigger is defined for that event the corresponding pattern will be started.

Triggers must be defined to replace themselves upon usage. This can be either replacing itself with itself for static effects, or a different trigger for more complex behaviors.

Multiple triggers can be active at the same time, but note that if two triggers have the same event type, the one defined first will have priority.
