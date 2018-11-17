#ifndef INCLUDE_HRI_TC_INLINE_H
#error hri_tc_inline.h is not indended for direct use.
#endif


static Tc* const hri_tc_instance[TC_INST_NUM] = TC_INSTS;


#define HRI_TC_NO_RETURN_VALUE

#define HRI_TC_RANGE_CHECK_TIMER(timer, rtnval)  \
  if( timer >= HRI_TC_NUM_INSTANCES )            \
  {                                              \
    return rtnval;                               \
  }

#define HRI_TC_RANGE_CHECK_CHANNEL(channel, rtnval)  \
  if( channel >= HRI_TC_NUM_CHANNELS )               \
  {                                                  \
    return rtnval;                                   \
  }

#define HRI_TC_RANGE_CHECK_OUTPUT(output, rtnval)  \
  if( output >= HRI_TC_NUM_OUTPUTS )               \
  {                                                \
    return rtnval;                                 \
  }


#define HRI_TC_WAIT_FOR_SYNC(timer)  \
  while( hri_tc_instance[timer]->COUNT32.STATUS.reg | TC_STATUS_SYNCBUSY )


static inline void HRI_TC_SoftwareReset( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLA.bit.SWRST = 1;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Enable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLA.bit.ENABLE = 1;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Disable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLA.bit.ENABLE = 0;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Mode_Set( hri_tc_instance_t timer, hri_tc_mode_t mode )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLA.bit.MODE = mode;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Waveform_Set( hri_tc_instance_t timer, hri_tc_waveform_t waveform )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLA.bit.WAVEGEN = waveform;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Prescaler_Set( hri_tc_instance_t timer, hri_tc_prescale_t prescale )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLA.bit.PRESCALER = prescale;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_RunInStandby_Enable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLA.bit.RUNSTDBY = 1;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_RunInStandby_Disable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLA.bit.RUNSTDBY = 0;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Direction_Set( hri_tc_instance_t timer, hri_tc_direction_t direction )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  switch( direction )
  {
    case HRI_TC_DIRECTION_UP:
      hri_tc_instance[timer]->COUNT32.CTRLBCLR.reg = TC_CTRLBCLR_DIR;
      break;
    case HRI_TC_DIRECTION_DOWN:
      hri_tc_instance[timer]->COUNT32.CTRLBSET.reg = TC_CTRLBSET_DIR;
      break;
    default:
      break;
  }
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline hri_tc_direction_t HRI_TC_Direction_Get( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_DIRECTION_UP);
  
  return (hri_tc_direction_t)hri_tc_instance[timer]->COUNT32.CTRLBSET.bit.DIR;
}

static inline void HRI_TC_Oneshot_Enable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLBSET.reg = TC_CTRLBSET_ONESHOT;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Oneshot_Disable( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.CTRLBCLR.reg = TC_CTRLBCLR_ONESHOT;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Command_Retrigger( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_RETRIGGER;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Command_Stop( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLBSET.reg = TC_CTRLBSET_CMD_STOP;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_OutputInvert_Enable( hri_tc_instance_t timer, hri_tc_output_t output )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_OUTPUT(output, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLC.reg |= (TC_CTRLC_INVEN0 << output);
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_OutputInvert_Disable( hri_tc_instance_t timer, hri_tc_output_t output )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_OUTPUT(output, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLC.reg &= ~(TC_CTRLC_INVEN0 << output);
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Capture_Enable( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLC.reg |= (TC_CTRLC_CPTEN0 << channel);
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Capture_Disable( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CTRLC.reg &= ~(TC_CTRLC_CPTEN0 << channel);
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_EventInput_Enable( hri_tc_instance_t timer, hri_tc_event_input_t event )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TC_EVENT_INPUT:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.TCINV = 0;
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.TCEI = 1;
      break;
    case HRI_TC_EVENT_INPUT_INVERTED:
      hri_tc_instance[timer]->COUNT32.EVCTRL.reg |= (TC_EVCTRL_TCEI | TC_EVCTRL_TCINV);
      break;
    default:
      break;
  }
}

static inline void HRI_TC_EventInput_Disable( hri_tc_instance_t timer, hri_tc_event_input_t event )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TC_EVENT_INPUT:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.TCEI = 0;
      break;
    case HRI_TC_EVENT_INPUT_INVERTED:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.TCEI = 0;
      break;
    default:
      break;
  }
}

static inline void HRI_TC_EventInputAction_Set( hri_tc_instance_t timer, hri_tc_event_input_action_t action )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.EVCTRL.bit.EVACT = action;
}

static inline void HRI_TC_EventOutput_Enable( hri_tc_instance_t timer, hri_tc_event_output_t event )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TC_EVENT_OUTPUT_MC0:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.MCEO0 = 1;
      break;
    case HRI_TC_EVENT_OUTPUT_MC1:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.MCEO1 = 1;
      break;
    case HRI_TC_EVENT_OUTPUT_OVERFLOW:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.OVFEO = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TC_EventOutput_Disable( hri_tc_instance_t timer, hri_tc_event_output_t event )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( event )
  {
    case HRI_TC_EVENT_OUTPUT_MC0:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.MCEO0 = 0;
      break;
    case HRI_TC_EVENT_OUTPUT_MC1:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.MCEO1 = 0;
      break;
    case HRI_TC_EVENT_OUTPUT_OVERFLOW:
      hri_tc_instance[timer]->COUNT32.EVCTRL.bit.OVFEO = 0;
      break;
    default:
      break;
  }
}

static inline void HRI_TC_Interrupt_Enable( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TC_INTERRUPT_MC0:
      hri_tc_instance[timer]->COUNT32.INTENSET.reg = TC_INTENSET_MC0;
      break;
    case HRI_TC_INTERRUPT_MC1:
      hri_tc_instance[timer]->COUNT32.INTENSET.reg = TC_INTENSET_MC1;
      break;
    case HRI_TC_INTERRUPT_SYNC_READY:
      hri_tc_instance[timer]->COUNT32.INTENSET.reg = TC_INTENSET_SYNCRDY;
      break;
    case HRI_TC_INTERRUPT_ERROR:
      hri_tc_instance[timer]->COUNT32.INTENSET.reg = TC_INTENSET_ERR;
      break;
    case HRI_TC_INTERRUPT_OVERFLOW:
      hri_tc_instance[timer]->COUNT32.INTENSET.reg = TC_INTENSET_OVF;
      break;
    default:
      break;
  }
}

static inline void HRI_TC_Interrupt_Disable( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TC_INTERRUPT_MC0:
      hri_tc_instance[timer]->COUNT32.INTENCLR.reg = TC_INTENCLR_MC0;
      break;
    case HRI_TC_INTERRUPT_MC1:
      hri_tc_instance[timer]->COUNT32.INTENCLR.reg = TC_INTENCLR_MC1;
      break;
    case HRI_TC_INTERRUPT_SYNC_READY:
      hri_tc_instance[timer]->COUNT32.INTENCLR.reg = TC_INTENCLR_SYNCRDY;
      break;
    case HRI_TC_INTERRUPT_ERROR:
      hri_tc_instance[timer]->COUNT32.INTENCLR.reg = TC_INTENCLR_ERR;
      break;
    case HRI_TC_INTERRUPT_OVERFLOW:
      hri_tc_instance[timer]->COUNT32.INTENCLR.reg = TC_INTENCLR_OVF;
      break;
    default:
      break;
  }
}

static inline bool HRI_TC_InterruptFlag_Get( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, false);

  switch( interrupt )
  {
    case HRI_TC_INTERRUPT_MC0:
      return hri_tc_instance[timer]->COUNT32.INTFLAG.bit.MC0;
    case HRI_TC_INTERRUPT_MC1:
      return hri_tc_instance[timer]->COUNT32.INTFLAG.bit.MC1;
    case HRI_TC_INTERRUPT_SYNC_READY:
      return hri_tc_instance[timer]->COUNT32.INTFLAG.bit.SYNCRDY;
    case HRI_TC_INTERRUPT_ERROR:
      return hri_tc_instance[timer]->COUNT32.INTFLAG.bit.ERR;
    case HRI_TC_INTERRUPT_OVERFLOW:
      return hri_tc_instance[timer]->COUNT32.INTFLAG.bit.OVF;
    default:
      break;
  }
}

static inline void HRI_TC_InterruptFlag_Clear( hri_tc_instance_t timer, hri_tc_interrupt_t interrupt )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);

  switch( interrupt )
  {
    case HRI_TC_INTERRUPT_MC0:
      hri_tc_instance[timer]->COUNT32.INTFLAG.reg = TC_INTFLAG_MC0;
      break;
    case HRI_TC_INTERRUPT_MC1:
      hri_tc_instance[timer]->COUNT32.INTFLAG.reg = TC_INTFLAG_MC1;
      break;
    case HRI_TC_INTERRUPT_SYNC_READY:
      hri_tc_instance[timer]->COUNT32.INTFLAG.reg = TC_INTFLAG_SYNCRDY;
      break;
    case HRI_TC_INTERRUPT_ERROR:
      hri_tc_instance[timer]->COUNT32.INTFLAG.reg = TC_INTFLAG_ERR;
      break;
    case HRI_TC_INTERRUPT_OVERFLOW:
      hri_tc_instance[timer]->COUNT32.INTFLAG.reg = TC_INTFLAG_OVF;
      break;
    default:
      break;
  }
}

static inline bool HRI_TC_isStopped( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, true);
  
  return hri_tc_instance[timer]->COUNT32.STATUS.bit.STOP == 1;
}

static inline bool HRI_TC_isRunning( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, false);
  
  return hri_tc_instance[timer]->COUNT32.STATUS.bit.STOP == 0;
}

static inline void HRI_TC_Count8_Set( hri_tc_instance_t timer, uint8_t count )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT8.COUNT.reg = count;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Count16_Set( hri_tc_instance_t timer, uint16_t count )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT16.COUNT.reg = count;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Count32_Set( hri_tc_instance_t timer, uint32_t count )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT32.COUNT.reg = count;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline uint8_t HRI_TC_Count8_Get( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);

  hri_tc_instance[timer]->COUNT8.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount8, COUNT.reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT8.COUNT.reg;
}

static inline uint16_t HRI_TC_Count16_Get( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);

  hri_tc_instance[timer]->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount16, COUNT.reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT16.COUNT.reg;
}

static inline uint32_t HRI_TC_Count32_Get( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);

  hri_tc_instance[timer]->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, COUNT.reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT32.COUNT.reg;
}

static inline void HRI_TC_Period8_Set( hri_tc_instance_t timer, uint8_t period )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  
  hri_tc_instance[timer]->COUNT8.PER.reg = period;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline uint8_t HRI_TC_Period8_Get( hri_tc_instance_t timer )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);

  return hri_tc_instance[timer]->COUNT8.PER.reg;
}

static inline void HRI_TC_Compare8_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint8_t compare )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT8.CC[channel].reg = compare;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Compare16_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint16_t compare )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT16.CC[channel].reg = compare;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline void HRI_TC_Compare32_Set( hri_tc_instance_t timer, hri_tc_channel_t channel, uint32_t compare )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, HRI_TC_NO_RETURN_VALUE);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, HRI_TC_NO_RETURN_VALUE);

  hri_tc_instance[timer]->COUNT32.CC[channel].reg = compare;
  HRI_TC_WAIT_FOR_SYNC(timer);
}

static inline uint8_t HRI_TC_Compare8_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT8.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount8, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT8.CC[channel].reg;
}

static inline uint16_t HRI_TC_Compare16_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount16, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT16.CC[channel].reg;
}

static inline uint32_t HRI_TC_Compare32_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT32.CC[channel].reg;
}

static inline uint8_t HRI_TC_Capture8_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT8.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount8, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT8.CC[channel].reg;
}

static inline uint16_t HRI_TC_Capture16_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount16, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT16.CC[channel].reg;
}

static inline uint32_t HRI_TC_Capture32_Get( hri_tc_instance_t timer, hri_tc_channel_t channel )
{
  HRI_TC_RANGE_CHECK_TIMER(timer, 0);
  HRI_TC_RANGE_CHECK_CHANNEL(channel, 0);

  hri_tc_instance[timer]->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_ADDR(offsetof(TcCount32, CC[channel].reg));
  HRI_TC_WAIT_FOR_SYNC(timer);

  return hri_tc_instance[timer]->COUNT32.CC[channel].reg;
}


#define HRI_TC_INTERRUPT_HANDLER_FLAG(timer,interrupt,flag,callback)  \
  if( (flags | TC_INTFLAG_##flag) && (enable | TC_INTENSET_##flag) )  \
  { \
    hri_tc_instance[timer]->COUNT32.INTFLAG.bit.flag = 1;  \
    callback( timer, interrupt ); \
    return; \
  }
