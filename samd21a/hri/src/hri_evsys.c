#include "hri/evsys.h"

#include "hri/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


static hri_evsys_interrupt_callback_t _interrupt_callback[HRI_EVSYS_NUM_CHANNELS];


void HRI_EVSYS_Initialize( void )
{
  EVSYS->CTRL.bit.SWRST = 1;
  while( EVSYS->CTRL.bit.SWRST );
}


void HRI_EVSYS_User_Set(
    hri_evsys_user_t user,
    hri_evsys_user_channel_t channel
  )
{
  EVSYS->USER.reg = EVSYS_USER_CHANNEL(channel) | EVSYS_USER_USER(user);
}

void HRI_EVSYS_Generator_Set(
    hri_evsys_generator_t generator,
    hri_evsys_channel_t channel,
    hri_evsys_edge_t edge,
    hri_evsys_path_t path
  )
{
  if (channel >= HRI_EVSYS_NUM_CHANNELS)   return;

  EVSYS->CHANNEL.reg = EVSYS_CHANNEL_CHANNEL(channel) | 
                       EVSYS_CHANNEL_EVGEN(generator) |
                       EVSYS_CHANNEL_EDGSEL(edge) |
                       EVSYS_CHANNEL_PATH(path);
}

void HRI_EVSYS_SoftwareTrigger(
    hri_evsys_channel_t channel
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return;

  // Need to use 16-bit write to assert Software Trigger
  *(__IO uint16_t*)&EVSYS->CHANNEL.reg = (uint16_t)(EVSYS_CHANNEL_CHANNEL(channel) |
                                                    EVSYS_CHANNEL_SWEVT );
}

bool HRI_EVSYS_isChannelBusy(
    hri_evsys_channel_t channel
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_CHBUSY8 << (channel-8))) != 0;
  }
}

bool HRI_EVSYS_isChannelUserReady(
    hri_evsys_channel_t channel
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return false;

  if( channel < 8 )
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY0 << channel)) != 0;
  }
  else
  {
    return (EVSYS->CHSTATUS.reg | (EVSYS_CHSTATUS_USRRDY8 << (channel-8))) != 0;
  }
}


void HRI_EVSYS_InterruptCallback_Set(
    hri_evsys_channel_t channel,
    hri_evsys_interrupt_callback_t callback
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return;

  _interrupt_callback[channel] = callback;
}

void HRI_EVSYS_Interrupt_Enable(
    hri_evsys_channel_t channel,
    hri_evsys_interrupt_t interrupt
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case HRI_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD0 << channel;
      }
      else
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_EVD8 << (channel-8);
      }
      break;

    case HRI_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR0 << channel;
      }
      else
      {
        EVSYS->INTENSET.reg = EVSYS_INTENSET_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}


void HRI_EVSYS_Interrupt_Disable(
    hri_evsys_channel_t channel,
    hri_evsys_interrupt_t interrupt
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case HRI_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD0 << channel;
      }
      else
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_EVD8 << (channel-8);
      }
      break;

    case HRI_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR0 << channel;
      }
      else
      {
        EVSYS->INTENCLR.reg = EVSYS_INTENCLR_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}

bool HRI_EVSYS_InterruptFlag_Get(
    hri_evsys_channel_t channel,
    hri_evsys_interrupt_t interrupt
  )
{
  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return false;

  switch( interrupt )
  {
    case HRI_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD0 << channel)) != 0;
      }
      else
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_EVD8 << (channel-8))) != 0;
      }
    
    case HRI_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR0 << channel)) != 0;
      }
      else
      {
        return (EVSYS->INTFLAG.reg | (EVSYS_INTFLAG_OVR8 << (channel-8))) != 0;
      }

    default:
      return false;
  }
}

void HRI_EVSYS_InterruptFlag_Clear(
    hri_evsys_channel_t channel,
    hri_evsys_interrupt_t interrupt
  )
{
  uint8_t channel_shift = (uint8_t)channel;

  if( channel >= HRI_EVSYS_NUM_CHANNELS )  return;

  switch( interrupt )
  {
    case HRI_EVSYS_INTERRUPT_DETECT:
      if( channel < 8 )
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD0 << channel;
      }
      else
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_EVD8 << (channel-8);
      }
      break;

    case HRI_EVSYS_INTERRUPT_OVERRUN:
      if( channel < 8 )
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR0 << channel;
      }
      else
      {
        EVSYS->INTFLAG.reg = EVSYS_INTFLAG_OVR8 << (channel-8);
      }
      break;

    default:
      break;
  }
}
