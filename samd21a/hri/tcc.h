#ifndef ECLAY_HRI_TCC_H
#define ECLAY_HRI_TCC_H

#include "hri/sam.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
  HRI_TCC_INSTANCE_TCC0 = 0,
  HRI_TCC_INSTANCE_TCC1,
  HRI_TCC_INSTANCE_TCC2,
#ifdef TCC3
  HRI_TCC_INSTANCE_TCC3,
#endif
  HRI_TCC_NUM_INSTANCES,
  HRI_TCC_NOT_A_INSTANCE = HRI_TCC_NUM_INSTANCES
} hri_tcc_instance_t;

typedef enum {
  HRI_TCC_CHANNEL_MC0 = 0,
  HRI_TCC_CHANNEL_MC1,
  HRI_TCC_CHANNEL_MC2,
  HRI_TCC_CHANNEL_MC3,
  HRI_TCC_NUM_CHANNELS,
  HRI_TCC_NOT_A_CHANNEL = HRI_TCC_NUM_CHANNELS
} hri_tcc_channel_t;

typedef enum {
  HRI_TCC_OUTPUT_WO0 = 0,
  HRI_TCC_OUTPUT_WO1,
  HRI_TCC_OUTPUT_WO2,
  HRI_TCC_OUTPUT_WO3,
  HRI_TCC_OUTPUT_WO4,
  HRI_TCC_OUTPUT_WO5,
  HRI_TCC_OUTPUT_WO6,
  HRI_TCC_OUTPUT_WO7,
  HRI_TCC_NUM_OUTPUTS,
  HRI_TCC_NOT_A_OUTPUT = HRI_TCC_NUM_OUTPUTS
} hri_tcc_output_t;

typedef enum {
  HRI_TCC_PRESCALE_DIV1    = TCC_CTRLA_PRESCALER_DIV1_Val,
  HRI_TCC_PRESCALE_DIV2    = TCC_CTRLA_PRESCALER_DIV2_Val,
  HRI_TCC_PRESCALE_DIV4    = TCC_CTRLA_PRESCALER_DIV4_Val,
  HRI_TCC_PRESCALE_DIV8    = TCC_CTRLA_PRESCALER_DIV8_Val,
  HRI_TCC_PRESCALE_DIV16   = TCC_CTRLA_PRESCALER_DIV16_Val,
  HRI_TCC_PRESCALE_DIV64   = TCC_CTRLA_PRESCALER_DIV64_Val,
  HRI_TCC_PRESCALE_DIV256  = TCC_CTRLA_PRESCALER_DIV256_Val,
  HRI_TCC_PRESCALE_DIV1024 = TCC_CTRLA_PRESCALER_DIV1024_Val,
} hri_tcc_prescale_t;

typedef enum {
  HRI_TCC_DIRECTION_UP   = 0x0,
  HRI_TCC_DIRECTION_DOWN = 0x1,
} hri_tcc_direction_t;

typedef enum {
  HRI_TCC_WAVEFORM_NORMAL_FREQUENCY    = TCC_WAVE_WAVEGEN_NFRQ_Val,
  HRI_TCC_WAVEFORM_MATCH_FREQUENCY     = TCC_WAVE_WAVEGEN_MFRQ_Val,
  HRI_TCC_WAVEFORM_NORMAL_PWM          = TCC_WAVE_WAVEGEN_NPWM_Val,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_CRITICAL = TCC_WAVE_WAVEGEN_DSCRITICAL_Val,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_BOTTOM   = TCC_WAVE_WAVEGEN_DSBOTTOM_Val,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_BOTH     = TCC_WAVE_WAVEGEN_DSBOTH_Val,
  HRI_TCC_WAVEFORM_DUAL_SLOPE_TOP      = TCC_WAVE_WAVEGEN_DSTOP_Val,
} hri_tcc_waveform_t;

typedef enum {
  HRI_TCC_INTERRUPT_MC0 = 0,
  HRI_TCC_INTERRUPT_MC1,
  HRI_TCC_INTERRUPT_MC2,
  HRI_TCC_INTERRUPT_MC3,
  HRI_TCC_INTERRUPT_FAULT_0,
  HRI_TCC_INTERRUPT_FAULT_1,
  HRI_TCC_INTERRUPT_FAULT_A,
  HRI_TCC_INTERRUPT_FAULT_B,
  HRI_TCC_INTERRUPT_FAULT_DEBUG,
  HRI_TCC_INTERRUPT_ERROR,
  HRI_TCC_INTERRUPT_COUNTER,
  HRI_TCC_INTERRUPT_RETRIGGER,
  HRI_TCC_INTERRUPT_OVERFLOW,
} hri_tcc_interrupt_t;

typedef enum {
  HRI_TCC_EVENT_INPUT_MC0 = 0,
  HRI_TCC_EVENT_INPUT_MC1,
  HRI_TCC_EVENT_INPUT_MC2,
  HRI_TCC_EVENT_INPUT_MC3,
  HRI_TCC_EVENT_INPUT_EV0,
  HRI_TCC_EVENT_INPUT_EV0_INVERTED,
  HRI_TCC_EVENT_INPUT_EV1,
  HRI_TCC_EVENT_INPUT_EV1_INVERTED
} hri_tcc_event_input_t;

typedef enum {
  HRI_TCC_EVENT_INPUT0_ACTION_OFF          = TCC_EVCTRL_EVACT0_OFF_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_RETRIGGER    = TCC_EVCTRL_EVACT0_RETRIGGER_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_COUNT_EVENT  = TCC_EVCTRL_EVACT0_COUNTEV_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_START        = TCC_EVCTRL_EVACT0_START_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_INCREMENT    = TCC_EVCTRL_EVACT0_INC_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_COUNT_ASYNC  = TCC_EVCTRL_EVACT0_COUNT_Val,
  HRI_TCC_EVENT_INPUT0_ACTION_FAULT        = TCC_EVCTRL_EVACT0_FAULT_Val,
} hri_tcc_event_input_0_action_t;

typedef enum {
  HRI_TCC_EVENT_INPUT1_ACTION_OFF          = TCC_EVCTRL_EVACT1_OFF_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_RETRIGGER    = TCC_EVCTRL_EVACT1_RETRIGGER_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_DIR_ASYNC    = TCC_EVCTRL_EVACT1_DIR_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_STOP         = TCC_EVCTRL_EVACT1_STOP_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_DECREMENT    = TCC_EVCTRL_EVACT1_DEC_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_PPW          = TCC_EVCTRL_EVACT1_PPW_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_PWP          = TCC_EVCTRL_EVACT1_PWP_Val,
  HRI_TCC_EVENT_INPUT1_ACTION_FAULT        = TCC_EVCTRL_EVACT1_FAULT_Val,
} hri_tcc_event_input_1_action_t;

typedef enum {
  HRI_TCC_EVENT_OUTPUT_MC0 = 0,
  HRI_TCC_EVENT_OUTPUT_MC1,
  HRI_TCC_EVENT_OUTPUT_MC2,
  HRI_TCC_EVENT_OUTPUT_MC3,
  HRI_TCC_EVENT_OUTPUT_COUNT,
  HRI_TCC_EVENT_OUTPUT_RETRIGGER,
  HRI_TCC_EVENT_OUTPUT_OVERFLOW,
} hri_tcc_event_output_t;

typedef enum {
  HRI_TCC_EVENT_COUNT_MODE_BEGIN    = TCC_EVCTRL_CNTSEL_START_Val,
  HRI_TCC_EVENT_COUNT_MODE_END      = TCC_EVCTRL_CNTSEL_END_Val,
  HRI_TCC_EVENT_COUNT_MODE_BETWEEN  = TCC_EVCTRL_CNTSEL_BETWEEN_Val,
  HRI_TCC_EVENT_COUNT_MODE_BOUNDARY = TCC_EVCTRL_CNTSEL_BOUNDARY_Val,
} hri_tcc_event_count_mode_t;


typedef void (*hri_tcc_interrupt_callback_t)( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );


void HRI_TCC_Initialize( void );

static inline void HRI_TCC_SoftwareReset( hri_tcc_instance_t timer );

static inline void HRI_TCC_Enable( hri_tcc_instance_t timer );
static inline void HRI_TCC_Disable( hri_tcc_instance_t timer );

static inline void HRI_TCC_Prescaler_Set( hri_tcc_instance_t timer, hri_tcc_prescale_t prescale );

static inline void HRI_TCC_RunInStandby_Enable( hri_tcc_instance_t timer );
static inline void HRI_TCC_RunInStandby_Disable( hri_tcc_instance_t timer );

static inline void HRI_TCC_Capture_Enable( hri_tcc_instance_t timer, hri_tcc_channel_t channel );
static inline void HRI_TCC_Capture_Disable( hri_tcc_instance_t timer, hri_tcc_channel_t channel );

static inline void HRI_TCC_Direction_Set( hri_tcc_instance_t timer, hri_tcc_direction_t direction );
static inline hri_tcc_direction_t HRI_TCC_Direction_Get( hri_tcc_instance_t timer );

static inline void HRI_TCC_Oneshot_Enable( hri_tcc_instance_t timer );
static inline void HRI_TCC_Oneshot_Disable( hri_tcc_instance_t timer );

static inline void HRI_TCC_Command_Retrigger( hri_tcc_instance_t timer );
static inline void HRI_TCC_Command_Stop( hri_tcc_instance_t timer );
static inline void HRI_TCC_Command_Update( hri_tcc_instance_t timer );
static inline void HRI_TCC_Command_ReadSync( hri_tcc_instance_t timer );

static inline void HRI_TCC_OutputInvert_Enable( hri_tcc_instance_t timer, hri_tcc_output_t output );
static inline void HRI_TCC_OutputInvert_Disable( hri_tcc_instance_t timer, hri_tcc_output_t output );

static inline void HRI_TCC_EventInput_Enable( hri_tcc_instance_t timer, hri_tcc_event_input_t event );
static inline void HRI_TCC_EventInput_Disable( hri_tcc_instance_t timer, hri_tcc_event_input_t event );
static inline void HRI_TCC_EventInput0_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_0_action_t action );
static inline void HRI_TCC_EventInput1_Action_Set( hri_tcc_instance_t timer, hri_tcc_event_input_1_action_t action );

static inline void HRI_TCC_EventOutput_Enable( hri_tcc_instance_t timer, hri_tcc_event_output_t event );
static inline void HRI_TCC_EventOutput_Disable( hri_tcc_instance_t timer, hri_tcc_event_output_t event );
static inline void HRI_TCC_EventCountMode_Set( hri_tcc_instance_t timer, hri_tcc_event_count_mode_t mode );

static inline void HRI_TCC_Interrupt_Enable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );
static inline void HRI_TCC_Interrupt_Disable( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );
static inline bool HRI_TCC_InterruptFlag_Get( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );
static inline void HRI_TCC_InterruptFlag_Clear( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );

static inline bool HRI_TCC_isStopped( hri_tcc_instance_t timer );
static inline bool HRI_TCC_isRunning( hri_tcc_instance_t timer );

static inline void HRI_TCC_Count_Set( hri_tcc_instance_t timer, uint32_t count );
static inline uint32_t HRI_TCC_Count_Get( hri_tcc_instance_t timer );

static inline void HRI_TCC_Pattern_Set( hri_tcc_instance_t timer, uint8_t enable, uint8_t value );
static inline void HRI_TCC_PatternEnable_Set( hri_tcc_instance_t timer, uint8_t enable );
static inline void HRI_TCC_PatternValue_Set( hri_tcc_instance_t timer, uint8_t value );

static inline __IO uint16_t* HRI_TCC_PatternRegister( hri_tcc_instance_t timer );
static inline __IO uint8_t* HRI_TCC_PatternRegisterEnable( hri_tcc_instance_t timer );
static inline __IO uint8_t* HRI_TCC_PatternRegisterValue( hri_tcc_instance_t timer );

static inline void HRI_TCC_Waveform_Set( hri_tcc_instance_t timer, hri_tcc_waveform_t waveform );

static inline void HRI_TCC_Period_Set( hri_tcc_instance_t timer, uint32_t period );

static inline void HRI_TCC_Compare_Set( hri_tcc_instance_t timer, hri_tcc_channel_t channel,  uint32_t compare );

static inline uint32_t HRI_TCC_Capture_Get( hri_tcc_instance_t timer, hri_tcc_channel_t channel );


#define INCLUDE_HRI_TCC_INLINE_H
#include "src/hri_tcc_inline.h"
#undef INCLUDE_HRI_TCC_INLINE_H


// The following INTERRUPT_HANDLER macros can be used to assemble a custom
//   interrupt handler that includes only the desired interrupt flags
//   in whatever priority order is necessary.
//
// The generated interrupt handler will process only a single flag each time it
//   is executed.  It will exit immediately after handling the highest priority
//   pending flag. Priority is determined by the order of the indidual flag
//   handlers macros (highest priority first).
//
// For example:
//   void tcc0_callback( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );
//
//   HRI_TCC_INTERRUPT_HANDLER_BEGIN(TCC0)
//   HRI_TCC_INTERRUPT_HANDLER_OVERFLOW(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_RETRIGGER(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_COUNTER(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_ERROR(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_FAULT_DEBUG(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_FAULT_A(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_FAULT_B(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_FAULT_0(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_FAULT_1(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_MC0(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_MC1(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_MC2(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_MC3(TCC0,tcc0_callback)
//   HRI_TCC_INTERRUPT_HANDLER_END()
//
// Note that use of a single callback is shown as example, but each flag handler
//   can have its own unique callback function as needed.


typedef void (*hri_tcc_interrupt_callback_t)( hri_tcc_instance_t timer, hri_tcc_interrupt_t interrupt );


#define HRI_TCC_INTERRUPT_HANDLER_BEGIN(timer) \
  void timer##_Handler( void ) \
  { \
    uint32_t enable = timer->INTENSET.reg; \
    uint32_t flags = timer->INTFLAG.reg;

#define HRI_TCC_INTERRUPT_HANDLER_OVERFLOW(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_OVERFLOW, OVF, callback)

#define HRI_TCC_INTERRUPT_HANDLER_RETRIGGER(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_RETRIGGER, TRG, callback)

#define HRI_TCC_INTERRUPT_HANDLER_COUNTER(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_COUNTER, CNT, callback)

#define HRI_TCC_INTERRUPT_HANDLER_ERROR(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_ERROR, ERR, callback)

#define HRI_TCC_INTERRUPT_HANDLER_FAULT_DEBUG(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_FAULT_DEBUG, DFS, callback)

#define HRI_TCC_INTERRUPT_HANDLER_FAULT_A(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_FAULT_A, FAULTA, callback)

#define HRI_TCC_INTERRUPT_HANDLER_FAULT_B(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_FAULT_B, FAULTB, callback)

#define HRI_TCC_INTERRUPT_HANDLER_FAULT_0(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_FAULT_0, FAULT0, callback)

#define HRI_TCC_INTERRUPT_HANDLER_FAULT_1(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_FAULT_1, FAULT1, callback)

#define HRI_TCC_INTERRUPT_HANDLER_MC0(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_MC0, MC0, callback)

#define HRI_TCC_INTERRUPT_HANDLER_MC1(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_MC1, MC1, callback)

#define HRI_TCC_INTERRUPT_HANDLER_MC2(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_MC2, MC2, callback)

#define HRI_TCC_INTERRUPT_HANDLER_MC3(timer,callback) \
  HRI_TCC_INTERRUPT_HANDLER_FLAG(HRI_TCC_INSTANCE_##timer, HRI_TCC_INTERRUPT_MC3, MC3, callback)

#define HRI_TCC_INTERRUPT_HANDLER_END() \
  }


#ifdef __cplusplus
}
#endif

#endif  // ECLAY_HRI_TCC_H
