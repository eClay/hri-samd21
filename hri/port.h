#ifndef ECLAY_HRI_PORT_H
#define ECLAY_HRI_PORT_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stdint.h>

#include "utils/utils_repeat_macro.h"


#ifdef __cplusplus
extern "C" {
#endif

// Values of hri_port_group_t must match PORT group values so that
// they can be used directly in accessing PORT registers.
// e.g. Port pins PAxx are accessed through PORT->Group[0]
typedef enum
{
  HRI_PORT_GROUP_PA = 0,
  HRI_PORT_GROUP_PB = 1,
  NUM_HRI_PORT_GROUP,
  NOT_A_HRI_PORT_GROUP = NUM_HRI_PORT_GROUP
} hri_port_group_t;

typedef uint8_t hri_port_pin_t;
#define NUM_HRI_PORT_PINS           32

typedef bool hri_port_direction_t;
#define HRI_PORT_DIRECTION_INPUT    false
#define HRI_PORT_DIRECTION_OUTPUT   true

typedef bool hri_port_pinstate_t;
#define HRI_PORT_PINSTATE_LOW       false
#define HRI_PORT_PINSTATE_HIGH      true

typedef enum
{
  HRI_PORT_PULL_OFF = 0,
  HRI_PORT_PULL_UP,
  HRI_PORT_PULL_DOWN,
  NUM_HRI_PORT_PULL,
  HRI_PORT_PULL_INVALID = NUM_HRI_PORT_PULL
} hri_port_pull_t;

typedef enum
{
  HRI_PORT_STRENGTH_NORMAL = 0,
  HRI_PORT_STRENGTH_HIGH,
  NUM_HRI_PORT_STRENGTH,
  HRI_PORT_STRENGTH_INVALID = NUM_HRI_PORT_STRENGTH
} hri_port_strength_t;

typedef enum
{
  HRI_PORT_PINMUX_A = PORT_PMUX_PMUXE_A_Val,
  HRI_PORT_PINMUX_B = PORT_PMUX_PMUXE_B_Val,
  HRI_PORT_PINMUX_C = PORT_PMUX_PMUXE_C_Val,
  HRI_PORT_PINMUX_D = PORT_PMUX_PMUXE_D_Val,
  HRI_PORT_PINMUX_E = PORT_PMUX_PMUXE_E_Val,
  HRI_PORT_PINMUX_F = PORT_PMUX_PMUXE_F_Val,
  HRI_PORT_PINMUX_G = PORT_PMUX_PMUXE_G_Val,
  HRI_PORT_PINMUX_H = PORT_PMUX_PMUXE_H_Val,
  NUM_HRI_PORT_PINMUX,
  HRI_PORT_PINMUX_DISABLED = NUM_HRI_PORT_PINMUX,
  HRI_PORT_PINMUX_INVALID
} hri_port_pinmux_t;


void HRI_PORT_Initialize( void );


static inline void HRI_PORT_DirectionSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_direction_t  direction
  );

static inline hri_port_direction_t HRI_PORT_DirectionGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );

static inline void HRI_PORT_OutputSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pinstate_t   state
  );

static inline void HRI_PORT_OutputToggle(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );

static inline hri_port_pinstate_t HRI_PORT_OutputGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );

static inline hri_port_pinstate_t HRI_PORT_InputGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );


static inline void HRI_PORT_InputEnableSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    bool                        enable
  );

static inline bool HRI_PORT_InputEnableGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );


void HRI_PORT_PullSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pull_t       pull
  );

hri_port_pull_t HRI_PORT_PullGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );


void HRI_PORT_DriveStrengthSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_strength_t   strength
  );

hri_port_strength_t HRI_PORT_DriveStrengthGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );


void HRI_PORT_PinMuxSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pinmux_t     mux
  );

hri_port_pinmux_t HRI_PORT_PinMuxGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  );


#define INCLUDE_HRI_PORT_INLINE_H
#include "src/hri_port_inline.h"
#undef INCLUDE_HRI_PORT_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_PORT_H
