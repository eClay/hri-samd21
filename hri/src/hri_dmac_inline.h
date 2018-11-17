#ifndef INCLUDE_HRI_DMAC_INLINE_H
#error hri_dmac_inline.h is not indended for direct use.
#endif


#include "hri/atomic.h"

#include <stddef.h>


#define HRI_DMAC_NO_RETURN_VALUE

#define HRI_DMAC_RANGE_CHECK_CHANNEL(channel, rtnval) \
  if( channel >= HRI_DMAC_NUM_CHANNELS )              \
  {                                                   \
    return rtnval;                                    \
  }

#define HRI_DMAC_NULL_CHECK_DESCRIPTOR(descriptor, rtnval) \
  if( descriptor == NULL )                                 \
  {                                                        \
    return rtnval;                                         \
  }


static inline void HRI_DMAC_Enable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_Disable( void )
{
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_PriorityLevel_Enable( hri_dmac_priority_level_t level )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case HRI_DMAC_PRIORITY_LEVEL_0:
      DMAC->CTRL.bit.LVLEN0 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_1:
      DMAC->CTRL.bit.LVLEN1 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_2:
      DMAC->CTRL.bit.LVLEN2 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_3:
      DMAC->CTRL.bit.LVLEN3 = 1;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_PriorityLevel_Disable( hri_dmac_priority_level_t level )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case HRI_DMAC_PRIORITY_LEVEL_0:
      DMAC->CTRL.bit.LVLEN0 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_1:
      DMAC->CTRL.bit.LVLEN1 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_2:
      DMAC->CTRL.bit.LVLEN2 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_3:
      DMAC->CTRL.bit.LVLEN3 = 0;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_PriorityLevelRoundRobin_Enable( hri_dmac_priority_level_t level )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case HRI_DMAC_PRIORITY_LEVEL_0:
      DMAC->PRICTRL0.bit.RRLVLEN0 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_1:
      DMAC->PRICTRL0.bit.RRLVLEN1 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_2:
      DMAC->PRICTRL0.bit.RRLVLEN2 = 1;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_3:
      DMAC->PRICTRL0.bit.RRLVLEN3 = 1;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_PriorityLevelRoundRobin_Disable( hri_dmac_priority_level_t level )
{
  CRITICAL_SECTION_ENTER();
  switch( level )
  {
    case HRI_DMAC_PRIORITY_LEVEL_0:
      DMAC->PRICTRL0.bit.RRLVLEN0 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_1:
      DMAC->PRICTRL0.bit.RRLVLEN1 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_2:
      DMAC->PRICTRL0.bit.RRLVLEN2 = 0;
      break;
    case HRI_DMAC_PRIORITY_LEVEL_3:
      DMAC->PRICTRL0.bit.RRLVLEN3 = 0;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Enable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 1;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Disable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Reset( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLA.bit.ENABLE = 0;
  DMAC->CHCTRLA.bit.SWRST = 1;
  while( DMAC->CHCTRLA.bit.SWRST );
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_SoftwareTrigger( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->SWTRIGCTRL.reg |= DMAC_SWTRIGCTRL_SWTRIG0 << channel;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Suspend( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_SUSPEND_Val;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Resume( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.CMD = DMAC_CHCTRLB_CMD_RESUME_Val;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_TriggerAction_Set( hri_dmac_channel_t channel, hri_dmac_trigger_action_t action )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGACT = action;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_TriggerSource_Set( hri_dmac_channel_t channel, hri_dmac_trigger_source_t source )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.TRIGSRC = source;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_ArbitrationLevel_Set( hri_dmac_channel_t channel, hri_dmac_priority_level_t level )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.LVL = level;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_EventOutput_Enable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVOE = 1;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_EventOutput_Disable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVOE = 0;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_EventInput_Enable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVIE = 1;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_EventInput_Disable( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVIE = 1;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_EventInputAction_Set( hri_dmac_channel_t channel, hri_dmac_event_input_action_t action )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );
  
  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  DMAC->CHCTRLB.bit.EVACT = action;
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Interrupt_Enable( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case HRI_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_SUSP;
      break;
    case HRI_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TCMPL;
      break;
    case HRI_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTENSET.reg = DMAC_CHINTENSET_TERR;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline void HRI_DMAC_CHANNEL_Interrupt_Disable( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case HRI_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_SUSP;
      break;
    case HRI_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TCMPL;
      break;
    case HRI_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTENCLR.reg = DMAC_CHINTENCLR_TERR;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline bool HRI_DMAC_CHANNEL_InterruptFlag_Get( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt )
{
  bool flag = false;

  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, false );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case HRI_DMAC_INTERRUPT_SUSPEND:
      flag = DMAC->CHINTFLAG.bit.SUSP;
      break;
    case HRI_DMAC_INTERRUPT_TRANSFER_DONE:
      flag = DMAC->CHINTFLAG.bit.TCMPL;
      break;
    case HRI_DMAC_INTERRUPT_ERROR:
      flag = DMAC->CHINTFLAG.bit.TERR;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();

  return flag;
}

static inline void HRI_DMAC_CHANNEL_InterruptFlag_Clear( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  CRITICAL_SECTION_ENTER();
  DMAC->CHID.reg = channel;
  switch( interrupt )
  {
    case HRI_DMAC_INTERRUPT_SUSPEND:
      DMAC->CHINTFLAG.bit.SUSP = 1;
      break;
    case HRI_DMAC_INTERRUPT_TRANSFER_DONE:
      DMAC->CHINTFLAG.bit.TCMPL = 1;
      break;
    case HRI_DMAC_INTERRUPT_ERROR:
      DMAC->CHINTFLAG.bit.TERR = 1;
      break;
    default:
      break;
  }
  CRITICAL_SECTION_LEAVE();
}

static inline bool HRI_DMAC_CHANNEL_isBusy( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, false );

  return (DMAC->BUSYCH.reg | (DMAC_BUSYCH_BUSYCH0 << channel)) != 0;
}

static inline bool HRI_DMAC_CHANNEL_isPending( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, false );

  return (DMAC->PENDCH.reg | (DMAC_PENDCH_PENDCH0 << channel)) != 0;
}

static inline void HRI_DMAC_DESCRIPTOR_SourceAddress_Set( hri_dmac_descriptor_t* descriptor, const void* address )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->SRCADDR.reg = (uint32_t)address;
}

static inline void HRI_DMAC_DESCRIPTOR_DestinationAddress_Set( hri_dmac_descriptor_t* descriptor, const void* address )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->DSTADDR.reg = (uint32_t)address;
}

static inline void HRI_DMAC_DESCRIPTOR_SourceIncrement_Enable( hri_dmac_descriptor_t* descriptor )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.SRCINC = 1;
}

static inline void HRI_DMAC_DESCRIPTOR_SourceIncrement_Disable( hri_dmac_descriptor_t* descriptor )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.SRCINC = 0;
}

static inline void HRI_DMAC_DESCRIPTOR_DestinationIncrement_Enable( hri_dmac_descriptor_t* descriptor )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.DSTINC = 1;
}

static inline void HRI_DMAC_DESCRIPTOR_DestinationIncrement_Disable( hri_dmac_descriptor_t* descriptor )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.DSTINC = 0;
}

static inline void HRI_DMAC_DESCRIPTOR_IncrementStepSize_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_step_selection_t selection, hri_dmac_addr_inc_step_size_t size )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  switch( selection )
  {
    case HRI_DMAC_STEP_SELECTION_DESTINATION:
    default:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_DST_Val;
      break;

    case HRI_DMAC_STEP_SELECTION_SOURCE:
      descriptor->BTCTRL.bit.STEPSEL = DMAC_BTCTRL_STEPSEL_SRC_Val;
      break;
  }

  descriptor->BTCTRL.bit.STEPSIZE = size;
}


static inline void HRI_DMAC_DESCRIPTOR_BeatSize_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_beat_size_t size )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.BEATSIZE = size;
}


static inline void HRI_DMAC_DESCRIPTOR_BlockAction_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_block_action_t action )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.BLOCKACT = action;
}


static inline void HRI_DMAC_DESCRIPTOR_EventOutput_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_event_output_selection_t output )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->BTCTRL.bit.EVOSEL = output;
}

static inline void HRI_DMAC_DESCRIPTOR_BlockSize_Set( hri_dmac_descriptor_t* descriptor, uint32_t size )
{  
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  uint32_t address;
  uint8_t  beat_size = descriptor->BTCTRL.bit.BEATSIZE;

  if( descriptor->BTCTRL.bit.DSTINC )
  {
    address = descriptor->DSTADDR.reg;
    address = address + (size * (1 << beat_size));
    descriptor->DSTADDR.reg = address;
  }

  if( descriptor->BTCTRL.bit.SRCINC )
  {
    address = descriptor->SRCADDR.reg;
    address = address + (size * (1 << beat_size));
    descriptor->SRCADDR.reg = address;
  }

	descriptor->BTCNT.reg = size;
}

static inline void HRI_DMAC_DESCRIPTOR_NextDescriptor_Set( hri_dmac_descriptor_t* descriptor, const hri_dmac_descriptor_t* next )
{
  HRI_DMAC_NULL_CHECK_DESCRIPTOR( descriptor, HRI_DMAC_NO_RETURN_VALUE );

  descriptor->DESCADDR.reg = (uint32_t)next;
}
