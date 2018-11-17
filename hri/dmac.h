#ifndef ECLAY_HRI_DMAC_H
#define ECLAY_HRI_DMAC_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


#define HRI_DMAC_NUM_CHANNELS    DMAC_CH_NUM
typedef uint8_t  hri_dmac_channel_t;

typedef DmacDescriptor  hri_dmac_descriptor_t;


typedef enum
{
  HRI_DMAC_COMMAND_NO_ACTION = DMAC_CHCTRLB_CMD_NOACT_Val,
  HRI_DMAC_COMMAND_SUSPEND   = DMAC_CHCTRLB_CMD_SUSPEND_Val,
  HRI_DMAC_COMMAND_RESUME    = DMAC_CHCTRLB_CMD_RESUME_Val
} hri_dmac_command_t;

typedef enum
{
  HRI_DMAC_TRIGGER_ACTION_BLOCK       = DMAC_CHCTRLB_TRIGACT_BLOCK_Val,
  HRI_DMAC_TRIGGER_ACTION_BEAT        = DMAC_CHCTRLB_TRIGACT_BEAT_Val,
  HRI_DMAC_TRIGGER_ACTION_TRANSACTION = DMAC_CHCTRLB_TRIGACT_TRANSACTION_Val
} hri_dmac_trigger_action_t;

typedef enum
{
  HRI_DMAC_TRIGGER_SOURCE_DISABLE     = 0x00,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM0_RX  = 0x01,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM0_TX  = 0x02,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM1_RX  = 0x03,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM1_TX  = 0x04,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM2_RX  = 0x05,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM2_TX  = 0x06,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM3_RX  = 0x07,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM3_TX  = 0x08,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM4_RX  = 0x09,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM4_TX  = 0x0A,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM5_RX  = 0x0B,
  HRI_DMAC_TRIGGER_SOURCE_SERCOM5_TX  = 0x0C,
  HRI_DMAC_TRIGGER_SOURCE_TCC0_OVF    = 0x0D,
  HRI_DMAC_TRIGGER_SOURCE_TCC0_MC0    = 0x0E,
  HRI_DMAC_TRIGGER_SOURCE_TCC0_MC1    = 0x0F,
  HRI_DMAC_TRIGGER_SOURCE_TCC0_MC2    = 0x10,
  HRI_DMAC_TRIGGER_SOURCE_TCC0_MC3    = 0x11,
  HRI_DMAC_TRIGGER_SOURCE_TCC1_OVF    = 0x12,
  HRI_DMAC_TRIGGER_SOURCE_TCC1_MC0    = 0x13,
  HRI_DMAC_TRIGGER_SOURCE_TCC1_MC1    = 0x14,
  HRI_DMAC_TRIGGER_SOURCE_TCC2_OVF    = 0x15,
  HRI_DMAC_TRIGGER_SOURCE_TCC2_MC0    = 0x16,
  HRI_DMAC_TRIGGER_SOURCE_TCC2_MC1    = 0x17,
  HRI_DMAC_TRIGGER_SOURCE_TC3_OVF     = 0x18,
  HRI_DMAC_TRIGGER_SOURCE_TC3_MC0     = 0x19,
  HRI_DMAC_TRIGGER_SOURCE_TC3_MC1     = 0x1A,
  HRI_DMAC_TRIGGER_SOURCE_TC4_OVF     = 0x1B,
  HRI_DMAC_TRIGGER_SOURCE_TC4_MC0     = 0x1C,
  HRI_DMAC_TRIGGER_SOURCE_TC4_MC1     = 0x1D,
  HRI_DMAC_TRIGGER_SOURCE_TC5_OVF     = 0x1E,
  HRI_DMAC_TRIGGER_SOURCE_TC5_MC0     = 0x1F,
  HRI_DMAC_TRIGGER_SOURCE_TC5_MC1     = 0x20,
  HRI_DMAC_TRIGGER_SOURCE_TC6_OVF     = 0x21,
  HRI_DMAC_TRIGGER_SOURCE_TC6_MC0     = 0x22,
  HRI_DMAC_TRIGGER_SOURCE_TC6_MC1     = 0x23,
  HRI_DMAC_TRIGGER_SOURCE_TC7_OVF     = 0x24,
  HRI_DMAC_TRIGGER_SOURCE_TC7_MC0     = 0x25,
  HRI_DMAC_TRIGGER_SOURCE_TC7_MC1     = 0x26,
  HRI_DMAC_TRIGGER_SOURCE_ADC_RESRDY  = 0x27,
  HRI_DMAC_TRIGGER_SOURCE_DAC_EMPTY   = 0x28,
  HRI_DMAC_TRIGGER_SOURCE_I2S_RX0     = 0x29,
  HRI_DMAC_TRIGGER_SOURCE_I2S_RX1     = 0x2A,
  HRI_DMAC_TRIGGER_SOURCE_I2S_TX0     = 0x2B,
  HRI_DMAC_TRIGGER_SOURCE_I2S_TX1     = 0x2C,
} hri_dmac_trigger_source_t;

typedef enum
{
  HRI_DMAC_PRIORITY_LEVEL_0 = DMAC_CHCTRLB_LVL_LVL0_Val,
  HRI_DMAC_PRIORITY_LEVEL_1 = DMAC_CHCTRLB_LVL_LVL1_Val,
  HRI_DMAC_PRIORITY_LEVEL_2 = DMAC_CHCTRLB_LVL_LVL2_Val,
  HRI_DMAC_PRIORITY_LEVEL_3 = DMAC_CHCTRLB_LVL_LVL3_Val,
} hri_dmac_priority_level_t;

typedef enum
{
  HRI_DMAC_EVENT_INPUT_ACTION_NOACT   = DMAC_CHCTRLB_EVACT_NOACT_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_TRIG    = DMAC_CHCTRLB_EVACT_TRIG_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_CTRIG   = DMAC_CHCTRLB_EVACT_CTRIG_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_CBLOCK  = DMAC_CHCTRLB_EVACT_CBLOCK_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_SUSPEND = DMAC_CHCTRLB_EVACT_SUSPEND_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_RESUME  = DMAC_CHCTRLB_EVACT_RESUME_Val,
  HRI_DMAC_EVENT_INPUT_ACTION_SSKIP   = DMAC_CHCTRLB_EVACT_SSKIP_Val,
} hri_dmac_event_input_action_t;

typedef enum
{
  HRI_DMAC_BEAT_SIZE_1BYTE = DMAC_BTCTRL_BEATSIZE_BYTE_Val,
  HRI_DMAC_BEAT_SIZE_2BYTE = DMAC_BTCTRL_BEATSIZE_HWORD_Val,
  HRI_DMAC_BEAT_SIZE_4BYTE = DMAC_BTCTRL_BEATSIZE_WORD_Val
} hri_dmac_beat_size_t;

typedef enum
{
	HRI_DMAC_STEP_SELECTION_DESTINATION = DMAC_BTCTRL_STEPSEL_DST_Val,
	HRI_DMAC_STEP_SELECTION_SOURCE      = DMAC_BTCTRL_STEPSEL_SRC_Val,
} hri_dmac_step_selection_t;

typedef enum
{
	HRI_DMAC_ADDR_INC_STEP_SIZE_X1   = DMAC_BTCTRL_STEPSIZE_X1_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X2   = DMAC_BTCTRL_STEPSIZE_X2_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X4   = DMAC_BTCTRL_STEPSIZE_X4_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X8   = DMAC_BTCTRL_STEPSIZE_X8_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X16  = DMAC_BTCTRL_STEPSIZE_X16_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X32  = DMAC_BTCTRL_STEPSIZE_X32_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X64  = DMAC_BTCTRL_STEPSIZE_X64_Val,
	HRI_DMAC_ADDR_INC_STEP_SIZE_X128 = DMAC_BTCTRL_STEPSIZE_X128_Val,
} hri_dmac_addr_inc_step_size_t;

typedef enum
{
  HRI_DMAC_BLOCK_ACTION_NONE      = DMAC_BTCTRL_BLOCKACT_NOACT_Val,
  HRI_DMAC_BLOCK_ACTION_INTERRUPT = DMAC_BTCTRL_BLOCKACT_INT_Val,
  HRI_DMAC_BLOCK_ACTION_SUSPEND   = DMAC_BTCTRL_BLOCKACT_SUSPEND_Val,
  HRI_DMAC_BLOCK_ACTION_BOTH      = DMAC_BTCTRL_BLOCKACT_BOTH_Val
} hri_dmac_block_action_t;

typedef enum
{
  HRI_DMAC_EVENT_OUTPUT_DISABLE = DMAC_BTCTRL_EVOSEL_DISABLE_Val,
  HRI_DMAC_EVENT_OUTPUT_BLOCK   = DMAC_BTCTRL_EVOSEL_BLOCK_Val,
  HRI_DMAC_EVENT_OUTPUT_BEAT    = DMAC_BTCTRL_EVOSEL_BEAT_Val
} hri_dmac_event_output_selection_t;

typedef enum
{
  HRI_DMAC_INTERRUPT_SUSPEND,
  HRI_DMAC_INTERRUPT_TRANSFER_DONE,
  HRI_DMAC_INTERRUPT_ERROR,
} hri_dmac_interrupt_t;

typedef void (*hri_dmac_interrupt_callback_t)( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt );


void HRI_DMAC_Initialize( void );

static inline void HRI_DMAC_Enable( void );
static inline void HRI_DMAC_Disable( void );

static inline void HRI_DMAC_PriorityLevel_Enable( hri_dmac_priority_level_t level );
static inline void HRI_DMAC_PriorityLevel_Disable( hri_dmac_priority_level_t level );

static inline void HRI_DMAC_PriorityLevelRoundRobin_Enable( hri_dmac_priority_level_t level );
static inline void HRI_DMAC_PriorityLevelRoundRobin_Disable( hri_dmac_priority_level_t level );

static inline void HRI_DMAC_CHANNEL_Enable( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_Disable( hri_dmac_channel_t channel );

static inline void HRI_DMAC_CHANNEL_Reset( hri_dmac_channel_t channel );

static inline void HRI_DMAC_CHANNEL_SoftwareTrigger( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_Suspend( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_Resume( hri_dmac_channel_t channel );

static inline void HRI_DMAC_CHANNEL_TriggerAction_Set( hri_dmac_channel_t channel, hri_dmac_trigger_action_t action );
static inline void HRI_DMAC_CHANNEL_TriggerSource_Set( hri_dmac_channel_t channel, hri_dmac_trigger_source_t source );
static inline void HRI_DMAC_CHANNEL_ArbitrationLevel_Set( hri_dmac_channel_t channel, hri_dmac_priority_level_t level );

static inline void HRI_DMAC_CHANNEL_EventOutput_Enable( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_EventOutput_Disable( hri_dmac_channel_t channel );

static inline void HRI_DMAC_CHANNEL_EventInput_Enable( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_EventInput_Disable( hri_dmac_channel_t channel );
static inline void HRI_DMAC_CHANNEL_EventInputAction_Set( hri_dmac_channel_t channel, hri_dmac_event_input_action_t action );

void HRI_DMAC_CHANNEL_InterruptCallback_Set( hri_dmac_channel_t channel, hri_dmac_interrupt_callback_t callback );
static inline void HRI_DMAC_CHANNEL_Interrupt_Enable( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt );
static inline void HRI_DMAC_CHANNEL_Interrupt_Disable( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt );
static inline bool HRI_DMAC_CHANNEL_InterruptFlag_Get( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt );
static inline void HRI_DMAC_CHANNEL_InterruptFlag_Clear( hri_dmac_channel_t channel, hri_dmac_interrupt_t interrupt );

static inline bool HRI_DMAC_CHANNEL_isBusy( hri_dmac_channel_t channel );
static inline bool HRI_DMAC_CHANNEL_isPending( hri_dmac_channel_t channel );

hri_dmac_descriptor_t* HRI_DMAC_CHANNEL_Descriptor_Get( hri_dmac_channel_t channel );
hri_dmac_descriptor_t* HRI_DMAC_CHANNEL_Writeback_Get( hri_dmac_channel_t channel );

static inline void HRI_DMAC_DESCRIPTOR_SourceAddress_Set( hri_dmac_descriptor_t* descriptor, const void* address );
static inline void HRI_DMAC_DESCRIPTOR_DestinationAddress_Set( hri_dmac_descriptor_t* descriptor, const void* address );

static inline void HRI_DMAC_DESCRIPTOR_SourceIncrement_Enable( hri_dmac_descriptor_t* descriptor );
static inline void HRI_DMAC_DESCRIPTOR_SourceIncrement_Disable( hri_dmac_descriptor_t* descriptor );

static inline void HRI_DMAC_DESCRIPTOR_DestinationIncrement_Enable( hri_dmac_descriptor_t* descriptor );
static inline void HRI_DMAC_DESCRIPTOR_DestinationIncrement_Disable( hri_dmac_descriptor_t* descriptor );

static inline void HRI_DMAC_DESCRIPTOR_IncrementStepSize_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_step_selection_t selection, hri_dmac_addr_inc_step_size_t size );

static inline void HRI_DMAC_DESCRIPTOR_BeatSize_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_beat_size_t size );

static inline void HRI_DMAC_DESCRIPTOR_BlockAction_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_block_action_t action );

static inline void HRI_DMAC_DESCRIPTOR_EventOutput_Set( hri_dmac_descriptor_t* descriptor, hri_dmac_event_output_selection_t output );

// BlockSize_Set MUST be called after setting Source Address, Destination
//   Address and Beat Size as it may need to modify address based on
//   increment settings, beat size, and block size.
static inline void HRI_DMAC_DESCRIPTOR_BlockSize_Set( hri_dmac_descriptor_t* descriptor, uint32_t size );

static inline void HRI_DMAC_DESCRIPTOR_NextDescriptor_Set( hri_dmac_descriptor_t* descriptor, const hri_dmac_descriptor_t* next );


#define INCLUDE_HRI_DMAC_INLINE_H
#include "src/hri_dmac_inline.h"
#undef INCLUDE_HRI_DMAC_INLINE_H


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_DMAC_H
