# 1 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32_Startup.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32_Startup.s"
# 57 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32_Startup.s"
.macro ISR_HANDLER name=
  .section .vectors, "ax"
  .word \name
  .section .init, "ax"
  .thumb_func
  .weak \name
\name:
1: b 1b
.endm

.macro ISR_RESERVED
  .section .vectors, "ax"
  .word 0
.endm

  .syntax unified
  .global reset_handler

  .section .vectors, "ax"
  .code 16
  .global _vectors

_vectors:
  .word __stack_end__



  .word reset_wait

ISR_HANDLER NMI_Handler
ISR_HANDLER HardFault_Handler
ISR_HANDLER MemManage_Handler
ISR_HANDLER BusFault_Handler
ISR_HANDLER UsageFault_Handler
ISR_RESERVED
ISR_RESERVED
ISR_RESERVED
ISR_RESERVED
ISR_HANDLER SVC_Handler
ISR_HANDLER DebugMon_Handler
ISR_RESERVED
ISR_HANDLER PendSV_Handler
ISR_HANDLER SysTick_Handler
# 1 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32F103xB.vec" 1
ISR_HANDLER WWDG_IRQHandler
ISR_HANDLER PVD_IRQHandler
ISR_HANDLER TAMPER_IRQHandler
ISR_HANDLER RTC_IRQHandler
ISR_HANDLER FLASH_IRQHandler
ISR_HANDLER RCC_IRQHandler
ISR_HANDLER EXTI0_IRQHandler
ISR_HANDLER EXTI1_IRQHandler
ISR_HANDLER EXTI2_IRQHandler
ISR_HANDLER EXTI3_IRQHandler
ISR_HANDLER EXTI4_IRQHandler
ISR_HANDLER DMA1_Channel1_IRQHandler
ISR_HANDLER DMA1_Channel2_IRQHandler
ISR_HANDLER DMA1_Channel3_IRQHandler
ISR_HANDLER DMA1_Channel4_IRQHandler
ISR_HANDLER DMA1_Channel5_IRQHandler
ISR_HANDLER DMA1_Channel6_IRQHandler
ISR_HANDLER DMA1_Channel7_IRQHandler
ISR_HANDLER ADC1_2_IRQHandler
ISR_HANDLER USB_HP_CAN1_TX_IRQHandler
ISR_HANDLER USB_LP_CAN1_RX0_IRQHandler
ISR_HANDLER CAN1_RX1_IRQHandler
ISR_HANDLER CAN1_SCE_IRQHandler
ISR_HANDLER EXTI9_5_IRQHandler
ISR_HANDLER TIM1_BRK_IRQHandler
ISR_HANDLER TIM1_UP_IRQHandler
ISR_HANDLER TIM1_TRG_COM_IRQHandler
ISR_HANDLER TIM1_CC_IRQHandler
ISR_HANDLER TIM2_IRQHandler
ISR_HANDLER TIM3_IRQHandler
ISR_HANDLER TIM4_IRQHandler
ISR_HANDLER I2C1_EV_IRQHandler
ISR_HANDLER I2C1_ER_IRQHandler
ISR_HANDLER I2C2_EV_IRQHandler
ISR_HANDLER I2C2_ER_IRQHandler
ISR_HANDLER SPI1_IRQHandler
ISR_HANDLER SPI2_IRQHandler
ISR_HANDLER USART1_IRQHandler
ISR_HANDLER USART2_IRQHandler
ISR_HANDLER USART3_IRQHandler
ISR_HANDLER EXTI15_10_IRQHandler
ISR_HANDLER RTC_Alarm_IRQHandler
ISR_HANDLER USBWakeUp_IRQHandler
# 101 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32_Startup.s" 2
  .section .vectors, "ax"
_vectors_end:







  .section .init, "ax"
  .thumb_func

reset_handler:


  ldr r0, =__RAM_segment_end__
  mov sp, r0
  bl SystemInit
# 163 "C:/Users/Admnistrator/AppData/Local/Rowley Associates Limited/CrossWorks for ARM/v4/packages/targets/STM32/STM32_Startup.s"
  ldr r0, =0xE000ED08



  ldr r1, =_vectors

  str r1, [r0]


  b _start


  .thumb_func
  .weak SystemInit
SystemInit:
  bx lr



  .thumb_func
reset_wait:
1: b 1b
