#ifndef INCLUDE_HRI_TCC_INLINE_H
#error hri_tcc_inline.h is not indended for direct use.
#endif


static Tcc* const hri_tcc_instance[TCC_INST_NUM] = TCC_INSTS;


#define HRI_TCC_NO_RETURN_VALUE

#define HRI_TCC_RANGE_CHECK_TIMER(timer, rtnval)  \
  if( timer >= HRI_TCC_NUM_INSTANCES )            \
  {                                              \
    return rtnval;                               \
  }

#define HRI_TCC_RANGE_CHECK_CHANNEL(channel, rtnval)  \
  if( channel >= HRI_TCC_NUM_CHANNELS )               \
  {                                                  \
    return rtnval;                                   \
  }

#define HRI_TCC_RANGE_CHECK_OUTPUT(output, rtnval)  \
  if( output >= HRI_TCC_NUM_OUTPUTS )               \
  {                                                \
    return rtnval;                                 \
  }


#define HRI_TCC_WAIT_FOR_SYNC(timer, sync_bit)  \
  while( hri_tcc_instance[timer]->SYNCBUSY.reg | sync_bit )


static inline void HRI_TCC_SoftwareReset( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.SWRST = 1;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_SWRST );
}

static inline void HRI_TCC_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.ENABLE |= 1;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_ENABLE );
}

static inline void HRI_TCC_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.ENABLE = 0;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_ENABLE );
}

static inline void HRI_TCC_Prescaler_Set( hri_tcc_instance_t timer, hri_tcc_prescale_t prescale )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );
  
  hri_tcc_instance[timer]->CTRLA.bit.PRESCALER = prescale;
}

static inline void HRI_TCC_RunInStandby_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.RUNSTDBY = 1;
}

static inline void HRI_TCC_RunInStandby_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLA.bit.RUNSTDBY = 0;
}

static inline void HRI_TCC_Capture_Enable( hri_tcc_instance_t timer, hri_tcc_channel_t channel )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->CTRLA.reg |= (TCC_CTRLA_CPTEN0 << channel);
}
static inline void HRI_TCC_Capture_Disable( hri_tcc_instance_t timer, hri_tcc_channel_t channel )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE);
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->CTRLA.reg &= ~(TCC_CTRLA_CPTEN0 << channel);
}

static inline void HRI_TCC_Direction_Set( hri_tcc_instance_t timer, hri_tcc_direction_t direction )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( direction )
  {
    case HRI_TCC_DIRECTION_UP:
      hri_tcc_instance[timer]->CTRLBCLR.reg = TCC_CTRLBCLR_DIR;
      break;
    case HRI_TCC_DIRECTION_DOWN:
      hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_DIR;
      break;
    default:
      break;
  }
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline hri_tcc_direction_t HRI_TCC_Direction_Get( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_DIRECTION_UP );

  return (hri_tcc_direction_t)hri_tcc_instance[timer]->CTRLBSET.bit.DIR;
}

static inline void HRI_TCC_Oneshot_Enable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_ONESHOT;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Oneshot_Disable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBCLR.reg = TCC_CTRLBCLR_ONESHOT;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Retrigger( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Stop( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_STOP;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_Update( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_UPDATE;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_Command_ReadSync( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_CTRLB );
}

static inline void HRI_TCC_OutputInvert_Enable( hri_tcc_instance_t timer, hri_tcc_output_t output )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );
  HRI_TCC_RANGE_CHECK_OUTPUT( output, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->DRVCTRL.reg |= (TCC_DRVCTRL_INVEN0 << output);
}

static inline void HRI_TCC_OutputInvert_Disable( hri_tcc_instance_t timer, hri_tcc_output_t output )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );
  HRI_TCC_RANGE_CHECK_OUTPUT( output, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->DRVCTRL.reg &= ~(TCC_DRVCTRL_INVEN0 << output);
}

static inline void HRI_TCC_EventInput_Enable( hri_tcc_instance_t timer, hri_tcc_event_input_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( event )
  {
    case HRI_TCC_EVENT_INPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI1 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI2 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI3 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV0:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV0 = 0;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV0 = 1;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV1:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV1 = 0;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 1;
      break;
    case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCINV1 = 1;
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventInput_Disable( hri_tcc_instance_t timer, hri_tcc_event_input_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( event )
  {
    case HRI_TCC_EVENT_INPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI1 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI2 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEI3 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV0:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV0_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI0 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV1:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 0;
      break;
    case HRI_TCC_EVENT_INPUT_EV1_INVERTED:
      hri_tcc_instance[timer]->EVCTRL.bit.TCEI1 = 0;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventInput0_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_0_action_t action )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->EVCTRL.bit.EVACT0 = action;
}

static inline void HRI_TCC_EventInput1_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_1_action_t action )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->EVCTRL.bit.EVACT1 = action;
}

static inline void HRI_TCC_EventOutput_Enable( hri_tcc_instance_t timer, hri_tcc_event_output_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( event )
  {
    case HRI_TCC_EVENT_OUTPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO0 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO1 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO2 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO3 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_COUNT:
      hri_tcc_instance[timer]->EVCTRL.bit.CNTEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
      hri_tcc_instance[timer]->EVCTRL.bit.TRGEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
      hri_tcc_instance[timer]->EVCTRL.bit.OVFEO = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventOutput_Disable( hri_tcc_instance_t timer, hri_tcc_event_output_t event )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( event )
  {
    case HRI_TCC_EVENT_OUTPUT_MC0:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO0 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC1:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO1 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC2:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO2 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_MC3:
      hri_tcc_instance[timer]->EVCTRL.bit.MCEO3 = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_COUNT:
      hri_tcc_instance[timer]->EVCTRL.bit.CNTEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_RETRIGGER:
      hri_tcc_instance[timer]->EVCTRL.bit.TRGEO = 1;
      break;
    case HRI_TCC_EVENT_OUTPUT_OVERFLOW:
      hri_tcc_instance[timer]->EVCTRL.bit.OVFEO = 1;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_EventCountMode_Set( hri_tcc_instance_t timer, hri_tcc_event_count_mode_t mode )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->EVCTRL.bit.CNTSEL = mode;
}

static inline void HRI_TCC_Interrupt_Enable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTENSET.reg = TCC_INTENSET_OVF;
      break;
    default:
      break;
  }
}

static inline void HRI_TCC_Interrupt_Disable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTENCLR.reg = TCC_INTENCLR_OVF;
      break;
    default:
      break;
  }
}

static inline bool HRI_TCC_InterruptFlag_Get( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, false );

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC0;
    case HRI_TCC_INTERRUPT_MC1:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC1;
    case HRI_TCC_INTERRUPT_MC2:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC2;
    case HRI_TCC_INTERRUPT_MC3:
      return hri_tcc_instance[timer]->INTFLAG.bit.MC3;
    case HRI_TCC_INTERRUPT_FAULT_0:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULT0;
    case HRI_TCC_INTERRUPT_FAULT_1:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULT1;
    case HRI_TCC_INTERRUPT_FAULT_A:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULTA;
    case HRI_TCC_INTERRUPT_FAULT_B:
      return hri_tcc_instance[timer]->INTFLAG.bit.FAULTB;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      return hri_tcc_instance[timer]->INTFLAG.bit.DFS;
    case HRI_TCC_INTERRUPT_ERROR:
      return hri_tcc_instance[timer]->INTFLAG.bit.ERR;
    case HRI_TCC_INTERRUPT_COUNTER:
      return hri_tcc_instance[timer]->INTFLAG.bit.CNT;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      return hri_tcc_instance[timer]->INTFLAG.bit.TRG;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      return hri_tcc_instance[timer]->INTFLAG.bit.OVF;
    default:
      return false;
  }  
}

static inline void HRI_TCC_InterruptFlag_Clear( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  switch( interrupt )
  {
    case HRI_TCC_INTERRUPT_MC0:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC0;
      break;
    case HRI_TCC_INTERRUPT_MC1:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC1;
      break;
    case HRI_TCC_INTERRUPT_MC2:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC2;
      break;
    case HRI_TCC_INTERRUPT_MC3:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_MC3;
      break;
    case HRI_TCC_INTERRUPT_FAULT_0:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULT0;
      break;
    case HRI_TCC_INTERRUPT_FAULT_1:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULT1;
      break;
    case HRI_TCC_INTERRUPT_FAULT_A:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULTA;
      break;
    case HRI_TCC_INTERRUPT_FAULT_B:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_FAULTB;
      break;
    case HRI_TCC_INTERRUPT_FAULT_DEBUG:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_DFS;
      break;
    case HRI_TCC_INTERRUPT_ERROR:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_ERR;
      break;
    case HRI_TCC_INTERRUPT_COUNTER:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_CNT;
      break;
    case HRI_TCC_INTERRUPT_RETRIGGER:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_TRG;
      break;
    case HRI_TCC_INTERRUPT_OVERFLOW:
      hri_tcc_instance[timer]->INTFLAG.reg = TCC_INTFLAG_OVF;
      break;
    default:
      break;
  }
}

static inline bool HRI_TCC_isStopped( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, true );
  
  return hri_tcc_instance[timer]->STATUS.bit.STOP == 1;
}

static inline bool HRI_TCC_isRunning( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, false );
  
  return hri_tcc_instance[timer]->STATUS.bit.STOP == 0;
}

static inline void HRI_TCC_Count_Set( hri_tcc_instance_t timer, uint32_t count )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE);

  hri_tcc_instance[timer]->COUNT.reg = count;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_COUNT );
}

static inline uint32_t HRI_TCC_Count_Get( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, 0 );

  hri_tcc_instance[timer]->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
  HRI_TCC_WAIT_FOR_SYNC( timer, (TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT) );

  return hri_tcc_instance[timer]->COUNT.reg;
}

static inline void HRI_TCC_Pattern_Set( hri_tcc_instance_t timer, uint8_t enable, uint8_t value )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->PATT.reg = TCC_PATT_PGE(enable) | TCC_PATT_PGV(value);
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_PATT );
}

static inline void HRI_TCC_PatternEnable_Set( hri_tcc_instance_t timer, uint8_t enable )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  *((__IO uint8_t*)hri_tcc_instance[timer]->PATT.reg) = enable;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_PATT );
}

static inline void HRI_TCC_PatternValue_Set( hri_tcc_instance_t timer, uint8_t value )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  *((__IO uint8_t*)hri_tcc_instance[timer]->PATT.reg + 1)= value;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_PATT );
}

static inline __IO uint16_t* HRI_TCC_PatternRegister( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, NULL );

  return (__IO uint16_t*)hri_tcc_instance[timer]->PATT.reg;
}

static inline __IO uint8_t* HRI_TCC_PatternRegisterEnable( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, NULL );

  return (__IO uint8_t*)hri_tcc_instance[timer]->PATT.reg;
}

static inline __IO uint8_t* HRI_TCC_PatternRegisterValue( hri_tcc_instance_t timer )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, NULL );

  return (__IO uint8_t*)hri_tcc_instance[timer]->PATT.reg + 1;
}

static inline void HRI_TCC_Waveform_Set( hri_tcc_instance_t timer, hri_tcc_waveform_t waveform )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->WAVE.bit.WAVEGEN = waveform;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_WAVE );
}

static inline void HRI_TCC_Period_Set( hri_tcc_instance_t timer, uint32_t period )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->PER.reg = period;
  HRI_TCC_WAIT_FOR_SYNC( timer, TCC_SYNCBUSY_PER );
}

static inline void HRI_TCC_Compare_Set( hri_tcc_instance_t timer, hri_tcc_channel_t channel,  uint32_t compare )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, HRI_TCC_NO_RETURN_VALUE );
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, HRI_TCC_NO_RETURN_VALUE );

  hri_tcc_instance[timer]->CC[channel].reg = compare;
  HRI_TCC_WAIT_FOR_SYNC( timer, (TCC_SYNCBUSY_CC0 << channel) );
}

static inline uint32_t HRI_TCC_Capture_Get( hri_tcc_instance_t timer, hri_tcc_channel_t channel )
{
  HRI_TCC_RANGE_CHECK_TIMER( timer, 0 );
  HRI_TCC_RANGE_CHECK_CHANNEL( channel, 0 );

  return hri_tcc_instance[timer]->CC[channel].reg;
}


#define HRI_TCC_INTERRUPT_HANDLER_FLAG(timer,interrupt,flag,callback)  \
  if( (flags | TCC_INTFLAG_##flag) && (enable | TCC_INTENSET_##flag) )  \
  { \
    hri_tcc_instance[timer]->INTFLAG.bit.flag = 1;  \
    callback( timer, interrupt ); \
    return; \
  }
