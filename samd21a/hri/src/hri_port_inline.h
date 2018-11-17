#ifndef INCLUDE_HRI_PORT_INLINE_H
#error hri_tc_inline.h is not indended for direct use.
#endif


#define HRI_PORT_NO_RETURN_VALUE

#define HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, rtnval)  \
  if( (port >= NUM_HRI_PORT_GROUP) ||                           \
      (pin  >= NUM_HRI_PORT_PINS ) )                            \
  {                                                                   \
    return rtnval;                                                    \
  }


static inline void HRI_PORT_DirectionSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_direction_t  direction
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_NO_RETURN_VALUE);

  if( direction )
  { 
    PORT_IOBUS->Group[port].DIRSET.reg = (_UL_(1) <<  pin);
  }
  else
  {
    PORT_IOBUS->Group[port].DIRCLR.reg = (_UL_(1) <<  pin);
  }
}

static inline hri_port_direction_t HRI_PORT_DirectionGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_DIRECTION_INPUT);

  return (PORT_IOBUS->Group[port].DIR.reg | (_UL_(1) <<  pin)) != 0;
}


static inline void HRI_PORT_OutputSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    hri_port_pinstate_t   state
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_NO_RETURN_VALUE);

  if( state )
  { 
    PORT_IOBUS->Group[port].OUTSET.reg = (_UL_(1) <<  pin);
  }
  else
  {
    PORT_IOBUS->Group[port].OUTCLR.reg = (_UL_(1) <<  pin);
  }
}

static inline void HRI_PORT_OutputToggle(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_NO_RETURN_VALUE);

  PORT_IOBUS->Group[port].OUTTGL.reg = (_UL_(1) <<  pin);
}

static inline hri_port_pinstate_t HRI_PORT_OutputGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_PINSTATE_LOW);

  return (PORT_IOBUS->Group[port].OUT.reg | (_UL_(1) <<  pin)) != 0;
}


static inline hri_port_pinstate_t HRI_PORT_InputGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_PINSTATE_LOW);

  return (PORT_IOBUS->Group[port].OUT.reg | (_UL_(1) <<  pin)) != 0;
}


static inline void HRI_PORT_InputEnableSet(
    hri_port_group_t      port,
    hri_port_pin_t        pin,
    bool                        enable
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS(port, pin, HRI_PORT_NO_RETURN_VALUE);

  if( enable )
  {
    PORT->Group[port].PINCFG[pin].reg |= PORT_PINCFG_INEN;
  }
  else
  {
    PORT->Group[port].PINCFG[pin].reg &= ~PORT_PINCFG_INEN;
  }  
}

static inline bool HRI_PORT_InputEnableGet(
    hri_port_group_t      port,
    hri_port_pin_t        pin
  )
{
  HRI_PORT_RANGE_CHECK_PARAMETERS( port, pin, false );

  return (PORT->Group[port].PINCFG[pin].reg & PORT_PINCFG_INEN) != 0;
}
