#include "hri/dmac.h"

#include "hri/sam.h"
#include "utils/utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Section containing first descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static hri_dmac_descriptor_t _descriptor_section[HRI_DMAC_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;

// Section containing current descriptors for all DMAC channels
COMPILER_ALIGNED(16)
static hri_dmac_descriptor_t _write_back_section[HRI_DMAC_NUM_CHANNELS] SECTION_DMAC_DESCRIPTOR;


static hri_dmac_interrupt_callback_t _interrupt_callback[HRI_DMAC_NUM_CHANNELS];


void HRI_DMAC_Initialize( void )
{
  uint8_t i = 0;

  // Reset DMAC module
  CRITICAL_SECTION_ENTER();
  DMAC->CTRL.bit.DMAENABLE = 0;
  DMAC->CTRL.bit.CRCENABLE = 0;
  DMAC->CTRL.bit.SWRST = 1;
  while( DMAC->CTRL.bit.SWRST );
  CRITICAL_SECTION_LEAVE();

  // hri_dmac_write_PRICTRL0_reg(
  //     DMAC,
  //     DMAC_PRICTRL0_LVLPRI0(CONF_DMAC_LVLPRI0) | DMAC_PRICTRL0_LVLPRI1(CONF_DMAC_LVLPRI1)
  //         | DMAC_PRICTRL0_LVLPRI2(CONF_DMAC_LVLPRI2) | DMAC_PRICTRL0_LVLPRI3(CONF_DMAC_LVLPRI3)
  //         | (CONF_DMAC_RRLVLEN0 << DMAC_PRICTRL0_RRLVLEN0_Pos) | (CONF_DMAC_RRLVLEN1 << DMAC_PRICTRL0_RRLVLEN1_Pos)
  //         | (CONF_DMAC_RRLVLEN2 << DMAC_PRICTRL0_RRLVLEN2_Pos) | (CONF_DMAC_RRLVLEN3 << DMAC_PRICTRL0_RRLVLEN3_Pos));

  DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;
  DMAC->WRBADDR.reg  = (uint32_t)_write_back_section;

  NVIC_DisableIRQ(DMAC_IRQn);
  NVIC_ClearPendingIRQ(DMAC_IRQn);
  NVIC_EnableIRQ(DMAC_IRQn);

  DMAC->CTRL.bit.DMAENABLE = 1;
}

void HRI_DMAC_CHANNEL_InterruptCallback_Set( hri_dmac_channel_t channel, hri_dmac_interrupt_callback_t callback )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, HRI_DMAC_NO_RETURN_VALUE );

  _interrupt_callback[channel] = callback;
}

hri_dmac_descriptor_t* HRI_DMAC_CHANNEL_Descriptor_Get( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, NULL );

  return &_descriptor_section[channel];
}

hri_dmac_descriptor_t* HRI_DMAC_CHANNEL_Writeback_Get( hri_dmac_channel_t channel )
{
  HRI_DMAC_RANGE_CHECK_CHANNEL( channel, NULL );

  return &_write_back_section[channel];
}


void DMAC_Handler(void)
{
  hri_dmac_channel_t channel;
  uint8_t enable;
  uint8_t flags;

  // Enter critical section to ensure that we have complete control of 
  //   CHID register while processing the interrupt flags.
  // Logic that checks the flags will limit processing to only one case
  //   for each pass through the dmac handler.
  CRITICAL_SECTION_ENTER();
    // Get ID of lowest channel with pending interrupt
    channel = DMAC->INTPEND.bit.ID;

    // Select the channel and make copy of the flags for processing.
    DMAC->CHID.reg = channel;
    enable = DMAC->CHINTENSET.reg;
    flags = DMAC->CHINTFLAG.reg;

    // Run through the interrupt flags and clear / keep only one flag to
    //   be processed after leaving critical section.
    if( (flags | DMAC_CHINTFLAG_TERR) && (enable | DMAC_CHINTENSET_TERR) )
    {
      flags = DMAC_CHINTFLAG_TERR;    // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.TERR = 1;   // clear interrupt flag
    }
    else if( flags | DMAC_CHINTFLAG_TCMPL && (enable | DMAC_CHINTENSET_TCMPL) )
    {
      flags = DMAC_CHINTFLAG_TCMPL;   // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.TCMPL = 1;  // clear interrupt flag
    }
    else if( flags | DMAC_CHINTFLAG_SUSP && (enable | DMAC_CHINTENSET_SUSP) )
    {
      flags = DMAC_CHINTFLAG_SUSP;    // keep only one flag to be processed
      DMAC->CHINTFLAG.bit.SUSP = 1;   // clear interrupt flag
    }
  CRITICAL_SECTION_LEAVE();

  if( _interrupt_callback[channel] != NULL )
  {
    if( flags | DMAC_CHINTFLAG_TERR )
    {
      _interrupt_callback[channel]( channel, HRI_DMAC_INTERRUPT_ERROR );
    }
    else if( flags | DMAC_CHINTFLAG_TCMPL )
    {
      _interrupt_callback[channel]( channel, HRI_DMAC_INTERRUPT_TRANSFER_DONE );
    }
    else if( flags | DMAC_CHINTFLAG_SUSP )
    {
      _interrupt_callback[channel]( channel, HRI_DMAC_INTERRUPT_SUSPEND );
    }
  }
}
