#include "hri/port.h"

#include "hri/sam.h"

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
 extern "C" {
#endif


void HRI_PORT_Initialize( void )
{

}


void HRI_PORT_PullSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pull_t       pull
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_NO_RETURN_VALUE );

  switch( pull )
  {
    case HRI_PORT_PULL_OFF:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PULLEN;
      break;

    case HRI_PORT_PULL_UP:
      if( !(PORT_IOBUS->Group[port].DIR.reg & (_UL_(1) << pin)) )
      {
        // Pull up is controlled by output register.
        // Set only if pin is configured as input.
        PORT_IOBUS->Group[port].OUTSET.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    case HRI_PORT_PULL_DOWN:
      if( !(PORT_IOBUS->Group[port].DIR.reg & (_UL_(1) << pin)) )
      {
        // Pull down is controlled by output register.
        // Set only if pin is configured as input.
        PORT_IOBUS->Group[port].OUTCLR.reg = (_UL_(1) << pin);
      }
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PULLEN;
      break;

    default:
      break;
  }
}

hri_port_pull_t HRI_PORT_PullGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_PULL_INVALID );

  if( !(PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PULLEN) )
  {
    return HRI_PORT_PULL_OFF;
  }
  else
  {
    if( PORT_IOBUS->Group[port].OUT.reg & (_UL_(1) << pin) )
    {
      return HRI_PORT_PULL_UP;
    }
    else
    {
      return HRI_PORT_PULL_DOWN;
    }
  }
}


void HRI_PORT_DriveStrengthSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_strength_t   strength
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_NO_RETURN_VALUE );

  switch( strength )
  {
    case HRI_PORT_STRENGTH_NORMAL:
      PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_DRVSTR;
      break;

    case HRI_PORT_STRENGTH_HIGH:
      PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_DRVSTR;
      break;

    default:
      break;
  }
}

hri_port_strength_t HRI_PORT_DriveStrengthGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_STRENGTH_INVALID );

  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_DRVSTR )
  {
    return HRI_PORT_STRENGTH_HIGH;
  }
  else
  {
    return HRI_PORT_STRENGTH_NORMAL;
  }
}


void HRI_PORT_PinMuxSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pinmux_t     mux
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_NO_RETURN_VALUE );

  bool pinmux_enable = true;
  uint8_t pinmux_bitmask;
  
  switch( mux )
  {
    case HRI_PORT_PINMUX_A:
      pinmux_bitmask = PORT_PMUX_PMUXE_A_Val;
      break;
    case HRI_PORT_PINMUX_B:
      pinmux_bitmask = PORT_PMUX_PMUXE_B_Val;
      break;
    case HRI_PORT_PINMUX_C:
      pinmux_bitmask = PORT_PMUX_PMUXE_C_Val;
      break;
    case HRI_PORT_PINMUX_D:
      pinmux_bitmask = PORT_PMUX_PMUXE_D_Val;
      break;
    case HRI_PORT_PINMUX_E:
      pinmux_bitmask = PORT_PMUX_PMUXE_E_Val;
      break;
    case HRI_PORT_PINMUX_F:
      pinmux_bitmask = PORT_PMUX_PMUXE_F_Val;
      break;
    case HRI_PORT_PINMUX_G:
      pinmux_bitmask = PORT_PMUX_PMUXE_G_Val;
      break;
    case HRI_PORT_PINMUX_H:
      pinmux_bitmask = PORT_PMUX_PMUXE_H_Val;
      break;
    default:
      pinmux_enable = false;
      break;
  }

  if( pinmux_enable )
  {
    if( (pin % 2) == 0 )
    {
      // Even pin
      PORT->Group[port].PMUX[pin/2].reg &= ~PORT_PMUX_PMUXE_Msk;
      PORT->Group[port].PMUX[pin/2].reg |= PORT_PMUX_PMUXE(pinmux_bitmask);
    }
    else
    {
      // Odd pin
      PORT->Group[port].PMUX[pin/2].reg &= ~PORT_PMUX_PMUXO_Msk;
      PORT->Group[port].PMUX[pin/2].reg |= PORT_PMUX_PMUXO(pinmux_bitmask);
    }
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_PMUXEN;
  }
  else
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_PMUXEN;
  }
}

hri_port_pinmux_t HRI_PORT_PinMuxGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, HRI_PORT_PINMUX_INVALID );
  
  if( PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_PMUXEN )
  {
    uint8_t pinmux_bitmask = PORT->Group[port].PMUX[pin/2].reg;

    if( (pin % 2) == 0 )
    {
      // Even pin
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXE_Msk) >> PORT_PMUX_PMUXE_Pos;
    }
    else
    {
      // Odd pin
      pinmux_bitmask = (pinmux_bitmask & PORT_PMUX_PMUXO_Msk) >> PORT_PMUX_PMUXO_Pos;
    }

    switch( pinmux_bitmask )
    {
      case PORT_PMUX_PMUXE_A_Val:
        return HRI_PORT_PINMUX_A;
      case PORT_PMUX_PMUXE_B_Val:
        return HRI_PORT_PINMUX_B;
      case PORT_PMUX_PMUXE_C_Val:
        return HRI_PORT_PINMUX_C;
      case PORT_PMUX_PMUXE_D_Val:
        return HRI_PORT_PINMUX_D;
      case PORT_PMUX_PMUXE_E_Val:
        return HRI_PORT_PINMUX_E;
      case PORT_PMUX_PMUXE_F_Val:
        return HRI_PORT_PINMUX_F;
      case PORT_PMUX_PMUXE_G_Val:
        return HRI_PORT_PINMUX_G;
      case PORT_PMUX_PMUXE_H_Val:
        return HRI_PORT_PINMUX_H;
      default:
        return HRI_PORT_PINMUX_DISABLED;
    }
  }
  else
  {
    return HRI_PORT_PINMUX_DISABLED;
  }
}


#ifdef __cplusplus
}
#endif
