#ifndef __SP7350_CM4_H
#define __SP7350_CM4_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#define __CM4_REV                 0x0001U  /*!< Core revision r0p1                            */
#define __MPU_PRESENT             0U       /*!< SP7350 devices provide an MPU */
#define __NVIC_PRIO_BITS          8U       /*!< SP7350 devices use 8 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0U       /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U       /*!< SP7350 devices provide an FPU */

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ***********************************************/
  NonMaskableInt_IRQn              = -14,    /*!< 2 Non Maskable Interrupt                      */
  HardFault_IRQn                   = -13,    /*!< 3 Cortex-M4 Hard Fault Interrupt              */
  MemoryManagement_IRQn            = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt       */
  BusFault_IRQn                    = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt               */
  UsageFault_IRQn                  = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt             */
  SVCall_IRQn                      = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                */
  DebugMonitor_IRQn                = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt          */
  PendSV_IRQn                      = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                */
  SysTick_IRQn                     = -1,     /*!< 15 Cortex-M4 System Tick Interrupt            */
/******  SP645 specific Interrupt Numbers ***************************************************/
  MAIN_PWR_UP_REQ_IRQn             = 0,      /*!< MAIN POWER UP REQUESET Interrupt               */
  MAIN_PWR_DOWN_IRQn               = 1,      /*!< MAIN POWER DOWN Interrupt                      */
  RTC_WAKEUPKEY_IRQn               = 2,      /*!< WAKYUP BY RTC  Interrupt                       */
  RESERVED_3                       = 3,      /*!< RESERVED interrupt                             */
  RESERVED_4                       = 4,      /*!< RESERVED interrupt                             */
  RESERVED_5                       = 5,      /*!< RESERVED interrupt                             */
  RESERVED_6                       = 6,      /*!< RESERVED interrupt                             */
  RESERVED_7                       = 7,      /*!< RESERVED interrupt                             */
  I2C_MASTER0_IRQ                  = 8,      /*!< I2C 0  interrupt                               */
  IPC_CA552CM4_INT0_IRQn           = 9,      /*!< Mailbox CA55 notify to CM4 interrupt 0         */
  IPC_CA552CM4_INT1_IRQn           = 10,     /*!< Mailbox CA55 notify to CM4 interrupt 1         */
  RTC_2HZ_IRQn                     = 11,     /*!< RTC 2HZ interrupt                              */
  RESERVED_12                      = 12,     /*!< RESERVED interrupt                             */
  IPC_CA552CM4_INT2_IRQn           = 13,     /*!< Mailbox CA55 notify to CM4 interrupt 2         */
  IPC_CA552CM4_INT3_IRQn           = 14,     /*!< Mailbox CA55 notify to CM4 interrupt 3         */
  RESERVED_15                      = 15,     /*!< RESERVED interrupt                             */
  RESERVED_16                      = 16,     /*!< RESERVED interrupt                             */
  RESERVED_17                      = 17,     /*!< RESERVED interrupt                             */
  RESERVED_18                      = 18,     /*!< RESERVED interrupt                             */
  RESERVED_19                      = 19,     /*!< RESERVED interrupt                             */
  RESERVED_20                      = 20,     /*!< RESERVED interrupt                             */
  RESERVED_21                      = 21,     /*!< RESERVED interrupt                             */
  I2C_MASTER6_IRQ                  = 22,     /*!< I2C 6  interrupt                               */
  RESERVED_23                      = 23,     /*!< RESERVED interrupt                             */
  RESERVED_24                      = 24,     /*!< RESERVED interrupt                             */
  IPC_CA552CM4_INT4_IRQn           = 25,     /*!< Mailbox CA55 notify to CM4 interrupt 4         */
  IPC_CA552CM4_INT5_IRQn           = 26,     /*!< Mailbox CA55 notify to CM4 interrupt 5         */
  SPI_MASTER0_IRQn                 = 27,     /*!< SPI Combo0 Master interrupt                    */
  SPI_MASTER1_IRQn                 = 28,     /*!< SPI Combo1 Master interrupt                    */
  SPI_MASTER2_IRQn                 = 29,     /*!< SPI Combo2 Master interrupt                    */
  SPI_MASTER3_IRQn                 = 30,     /*!< SPI Combo3 Master interrupt                    */
  SPI_MASTER4_IRQn                 = 31,     /*!< SPI Combo4 Master interrupt                    */
  SPI_MASTER5_IRQn                 = 32,     /*!< SPI Combo5 Master interrupt                    */
  THERMAL_S_IRQn                   = 33,     /*!< THERMAL S Interrupt                            */
  THERMAL_A_IRQn                   = 34,     /*!< THERMAL A interrupt                            */
  UADBG_IRQn                       = 35,     /*!< UART to AXI for Debug Interrupt                */
  EXTI0_IRQn                       = 36,      /*!< GPIO AO EXIT0 Interrupt                       */
  EXTI1_IRQn                       = 37,      /*!< GPIO AO EXIT1 Interrupt                       */
  EXTI2_IRQn                       = 38,      /*!< GPIO AO EXIT2 Interrupt                       */
  EXTI3_IRQn                       = 39,      /*!< GPIO AO EXIT3 Interrupt                       */
  EXTI4_IRQn                       = 40,      /*!< GPIO AO EXIT4 Interrupt                       */
  EXTI5_IRQn                       = 41,      /*!< GPIO AO EXIT5 Interrupt                       */
  EXTI6_IRQn                       = 42,      /*!< GPIO AO EXIT6 Interrupt                       */
  EXTI7_IRQn                       = 43,      /*!< GPIO AO EXIT7 Interrupt                       */
  EXTI8_IRQn                       = 44,      /*!< GPIO AO EXIT8 Interrupt                       */
  EXTI9_IRQn                       = 45,      /*!< GPIO AO EXIT9 Interrupt                       */
  EXTI10_IRQn                      = 46,      /*!< GPIO AO EXIT10 Interrupt                      */
  EXTI11_IRQn                      = 47,      /*!< GPIO AO EXIT11 Interrupt                      */
  EXTI12_IRQn                      = 48,      /*!< GPIO AO EXIT12 Interrupt                      */
  EXTI13_IRQn                      = 49,      /*!< GPIO AO EXIT13 Interrupt                      */
  EXTI14_IRQn                      = 50,      /*!< GPIO AO EXIT14 Interrupt                      */
  EXTI15_IRQn                      = 51,      /*!< GPIO AO EXIT15 Interrupt                      */
  EXTI16_IRQn                      = 52,      /*!< GPIO AO EXIT16 Interrupt                      */
  EXTI17_IRQn                      = 53,      /*!< GPIO AO EXIT17 Interrupt                      */
  EXTI18_IRQn                      = 54,      /*!< GPIO AO EXIT18 Interrupt                      */
  EXTI19_IRQn                      = 55,      /*!< GPIO AO EXIT19 Interrupt                      */
  EXTI20_IRQn                      = 56,      /*!< GPIO AO EXIT20 Interrupt                      */
  EXTI21_IRQn                      = 57,      /*!< GPIO AO EXIT21 Interrupt                      */
  EXTI22_IRQn                      = 58,      /*!< GPIO AO EXIT22 Interrupt                      */
  RESERVED_59                      = 59,      /*!< RESERVED interrupt                            */
  UART0_IRQn                       = 60,      /*!< UART0 Interrupt                               */
  UART1_IRQn                       = 61,      /*!< UART1 Interrupt                               */
  RESERVED_62                      = 62,      /*!< RESERVED interrupt                            */
  PWM_USER_INT0_IRQn               = 63,      /*!< PWM User Interrupt0                           */
  PWM_END_INT0_IRQn                = 64,      /*!< PWM End Interrupt0                            */
  PWM_USER_INT1_IRQn               = 65,      /*!< PWM User Interrupt1                           */
  PWM_END_INT1_IRQn                = 66,      /*!< PWM End Interrupt1                            */
  PWM_USER_INT2_IRQn               = 67,      /*!< PWM User Interrupt2                           */
  PWM_END_INT2_IRQn                = 68,      /*!< PWM End Interrupt2                            */
  PWM_USER_INT3_IRQn               = 69,      /*!< PWM User Interrupt3                           */
  PWM_END_INT3_IRQn                = 70,      /*!< PWM End Interrupt3                            */
  RESERVED_71                      = 71,      /*!< RESERVED Interrupt                            */
  RBUS_IRQn                        = 72,      /*!< RBUS Interrupt                                */
  RESERVED_73                      = 73,      /*!< RESERVED interrupt                            */
  RESERVED_74                      = 74,      /*!< RESERVED interrupt                            */
  RESERVED_75                      = 75,      /*!< RESERVED interrupt                            */
  RESERVED_76                      = 76,      /*!< RESERVED interrupt                            */
  RESERVED_77                      = 77,      /*!< RESERVED interrupt                            */
  IPC_CA552CM4_INT6_IRQn           = 78,      /*!< Mailbox CA55 notify to CM4 interrupt 6        */
  IPC_CA552CM4_INT7_IRQn           = 79,      /*!< Mailbox CA55 notify to CM4 interrupt 7        */
  EXTI23_IRQn                      = 80,      /*!< GPIO AO EXIT23 Interrupt                      */
  EXTI24_IRQn                      = 81,      /*!< GPIO AO EXIT24 Interrupt                      */
  EXTI25_IRQn                      = 82,      /*!< GPIO AO EXIT25 Interrupt                      */
  EXTI26_IRQn                      = 83,      /*!< GPIO AO EXIT26 Interrupt                      */
  EXTI27_IRQn                      = 84,      /*!< GPIO AO EXIT27 Interrupt                      */
  EXTI28_IRQn                      = 85,      /*!< GPIO AO EXIT28 Interrupt                      */
  EXTI29_IRQn                      = 86,      /*!< GPIO AO EXIT29 Interrupt                      */
  EXTI30_IRQn                      = 87,      /*!< GPIO AO EXIT30 Interrupt                      */
  EXTI31_IRQn                      = 88,      /*!< GPIO AO EXIT31 Interrupt                      */
  RESERVED_89                      = 89,      /*!< RESERVED interrupt                            */
  RESERVED_90                      = 90,      /*!< RESERVED interrupt                            */
  RESERVED_91                      = 91,      /*!< RESERVED interrupt                            */
  RESERVED_92                      = 92,      /*!< RESERVED interrupt                            */
  RESERVED_93                      = 93,      /*!< RESERVED interrupt                            */
  I2C_MASTER1_IRQ                  = 94,      /*!< I2C 1  interrupt                              */
  I2C_MASTER2_IRQ                  = 95,      /*!< I2C 2  interrupt                              */
  I2C_MASTER3_IRQ                  = 96,      /*!< I2C 3  interrupt                              */
  I2C_MASTER4_IRQ                  = 97,      /*!< I2C 4  interrupt                              */
  I2C_MASTER5_IRQ                  = 98,      /*!< I2C 5  interrupt                              */
  RTC_PREIODIC_IRQ                 = 99,      /*!< RTC Prediodic interrupt                       */
  AUD_LOSD_IRQ                     = 100,     /*!< Audio LOSD interrupt                          */
  AUD_FIFO_IRQ                     = 101,     /*!< Audio FIFO interrupt                          */
  AUD_TWS_LATCH_IRQ                = 102,     /*!< Audio TWS Latch interrupt                     */
  AUD_TWS_SAMPLE_IRQ               = 103,     /*!< Audio TWS Sample interrupt                    */
  RESERVED_104                     = 104,       /*!< RESERVED interrupt                          */
  RESERVED_105                     = 105,       /*!< RESERVED interrupt                          */
  RESERVED_106                     = 106,       /*!< RESERVED interrupt                          */
  RESERVED_107                     = 107,       /*!< RESERVED interrupt                          */
  RESERVED_108                     = 108,       /*!< RESERVED interrupt                          */
  RESERVED_109                     = 109,       /*!< RESERVED interrupt                          */
  I2C_MASTER7_IRQ                  = 110,       /*!< I2C 7  interrupt                            */
  I2C_MASTER8_IRQ                  = 111,       /*!< I2C 8  interrupt                            */
  I2C_MASTER9_IRQ                  = 112,       /*!< I2C 9  interrupt                            */
  RESERVED_113                     = 113,       /*!< RESERVED interrupt                          */
  RESERVED_114                     = 114,       /*!< RESERVED interrupt                          */
  RESERVED_115                     = 115,       /*!< RESERVED interrupt                          */
  RESERVED_116                     = 116,       /*!< RESERVED interrupt                          */
  RESERVED_117                     = 117,       /*!< RESERVED interrupt                          */
  IPC_CM42CA55_INT0_IRQn           = 118,       /*!< Mailbox CM4 notify to CA55 interrupt 0      */
  IPC_CM42CA55_INT1_IRQn           = 119,       /*!< Mailbox CM4 notify to CA55 interrupt 1      */
  IPC_CM42CA55_INT2_IRQn           = 120,       /*!< Mailbox CM4 notify to CA55 interrupt 2      */
  IPC_CM42CA55_INT3_IRQn           = 121,       /*!< Mailbox CM4 notify to CA55 interrupt 3      */
  IPC_CM42CA55_INT4_IRQn           = 122,       /*!< Mailbox CM4 notify to CA55 interrupt 4      */
  IPC_CM42CA55_INT5_IRQn           = 123,       /*!< Mailbox CM4 notify to CA55 interrupt 5      */
  IPC_CM42CA55_INT6_IRQn           = 124,       /*!< Mailbox CM4 notify to CA55 interrupt 6      */
  IPC_CM42CA55_INT7_IRQn           = 125,       /*!< Mailbox CM4 notify to CA55 interrupt 7      */
  IPC_CM42CA55_NORMAL_INT_IRQn     = 126,       /*!< Mailbox CM4 normal notify to CA55 interrupt */
  IPC_CA552CM4_NORMAL_INT_IRQn     = 127,       /*!< Mailbox CA55 normal notify to CM4 interrupt */
  STC_TIMER_W_IRQn                 = 128,       /*!< STC Watchdog interrupt                      */
  STC_TIMER0_IRQn                  = 129,       /*!< STC timer0 interrupt                        */
  STC_TIMER1_IRQn                  = 130,       /*!< STC timer1 interrupt                        */
  STC_TIMER2_IRQn                  = 131,       /*!< STC timer2 interrupt                        */
  STC_TIMER3_IRQn                  = 132,       /*!< STC timer3 interrupt                        */
  STC_AV0_TIMER0_IRQn              = 133,       /*!< STC timer0 interrupt                        */
  STC_AV0_TIMER1_IRQn              = 134,       /*!< STC timer1 interrupt                        */
  STC_AV0_TIMER2_IRQn              = 135,       /*!< STC timer2 interrupt                        */
  STC_AV0_TIMER3_IRQn              = 136,       /*!< STC timer3 interrupt                        */
  STC_AV1_TIMER0_IRQn              = 137,       /*!< STC timer0 interrupt                        */
  STC_AV1_TIMER1_IRQn              = 138,       /*!< STC timer1 interrupt                        */
  STC_AV1_TIMER2_IRQn              = 139,       /*!< STC timer2 interrupt                        */
  STC_AV1_TIMER3_IRQn              = 140,       /*!< STC timer3 interrupt                        */
  SYS_RTC_IRQn                     = 141,       /*!< RTC Alarm interrupt                         */
  STC_AV2_TIMER0_IRQn              = 142,       /*!< STC timer0 interrupt                        */
  STC_AV2_TIMER1_IRQn              = 143,       /*!< STC timer1 interrupt                        */
  STC_AV2_TIMER2_IRQn              = 144,       /*!< STC timer2 interrupt                        */
  STC_AV2_TIMER3_IRQn              = 145,       /*!< STC timer3 interrupt                        */
  STC_AV0_TIMER_W_IRQn             = 146,       /*!< STC Watchdog interrupt                      */
  STC_AV1_TIMER_W_IRQn             = 147,       /*!< STC Watchdog interrupt                      */
  RESERVED_148                     = 148,       /*!< RESERVED interrupt                          */
  RESERVED_149                     = 149,       /*!< RESERVED interrupt                          */
  RESERVED_150                     = 150,       /*!< RESERVED interrupt                          */
  AHB_DMA0_CH0_IRQn                = 151,       /*!< AHB DMA0 CH0 interrupt                      */
  AHB_DMA0_CH1_IRQn                = 152,       /*!< AHB DMA0 CH1 interrupt                      */
  AHB_DMA0_CH2_IRQn                = 153,       /*!< AHB DMA0 CH2 interrupt                      */
  AHB_DMA0_CH3_IRQn                = 154,       /*!< AHB DMA0 CH3 interrupt                      */
  AHB_DMA0_CH4_IRQn                = 155,       /*!< AHB DMA0 CH4 interrupt                      */
  AHB_DMA0_CH5_IRQn                = 156,       /*!< AHB DMA0 CH5 interrupt                      */
  UART2_IRQn                       = 157,       /*!< UART2 Interrupt                             */
  UART3_IRQn                       = 158,       /*!< UART3 Interrupt                             */
  UART7_IRQn                       = 159,       /*!< UART4 Interrupt                             */
  AHB_DMA0_CH6_IRQn                = 160,       /*!< AHB DMA0 CH6 Interrupt                      */
  AHB_DMA0_CH7_IRQn                = 161,       /*!< AHB DMA0 CH7 Interrupt                      */
  UART6_IRQn                       = 162,       /*!< UART6 Interrupt                             */
  KEY_SCAN_SAR_IRQn                = 163,       /*!< KEY SCAN SAR Interrupt                      */
  RES_TOUCH_IRQn                   = 164,       /*!< TOUCH PANEL Interrupt                       */
  PMC_CA55_SCUL3_PDENY_IRQn        = 165,       /*!< PMC CA55 SCUL3 PDENY Interrupt              */
  PMC_CA55_CORE3_PDENY_IRQn        = 166,       /*!< PMC CA55 CORE3 PDENY interrupt              */
  PMC_CA55_CORE2_PDENY_IRQn        = 167,       /*!< PMC CA55 CORE2 PDENY Interrupt              */
  PMC_CA55_CORE1_PDENY_IRQn        = 168,       /*!< PMC CA55 CORE1 PDENY interrupt              */
  PMC_CA55_CORE0_PDENY_IRQn        = 169,       /*!< PMC CA55 CORE0 PDENY Interrupt              */
  PMC_CA55_SCUL3_PACCEPT_IRQn      = 170,       /*!< PMC CA55 SCUL3 PACCEPT Interrupt            */
  PMC_CA55_CORE3_PACCEPT_IRQn      = 171,       /*!< PMC CA55 CORE3 PACCEPT Interrupt            */
  PMC_CA55_CORE2_PACCEPT_IRQn      = 172,       /*!< PMC CA55 CORE2 PACCEPT Interrupt            */
  PMC_CA55_CORE1_PACCEPT_IRQn      = 173,       /*!< PMC CA55 CORE1 PACCEPT Interrupt            */
  PMC_CA55_CORE0_PACCEPT_IRQn      = 174,       /*!< PMC CA55 CORE0 PACCEPT Interrupt            */
  RESERVED_175                     = 175,       /*!< RESERVED Interrupt                          */
  RESERVED_176                     = 176,       /*!< RESERVED Interrupt                          */
  RESERVED_177                     = 177,       /*!< RESERVED Interrupt                          */
  AHB_DMA1_CH0_IRQn                = 178,       /*!< AHB DMA1 CH0 Interrupt                      */
  RESERVED_179                     = 179,       /*!< USB30C1 Interrupt                           */
  AHB_DMA1_CH1_IRQn                = 180,       /*!< AHB DMA1 CH1 Interrupt                      */
  RESERVED_181                     = 181,       /*!< USBC0_OTG Interrupt                         */
  RESERVED_182                     = 182,       /*!< USBC0_DEVIC interrupt                       */
  RESERVED_183                     = 183,       /*!< USBC0_EHCI Interrupt                        */
  RESERVED_184                     = 184,       /*!< USBC0_OHCI interrupt                        */
  STC_AV4_TIMERW_IRQn              = 185,       /*!< STC4 Watchdog Interrupt                     */
  STC_AV4_TIMER0_IRQn              = 186,       /*!< STC4 timer0 Interrupt                       */
  STC_AV4_TIMER1_IRQn              = 187,       /*!< STC4 timer1 Interrupt                       */
  STC_AV4_TIMER2_IRQn              = 188,       /*!< STC4 timer2 Interrupt                       */
  STC_AV4_TIMER3_IRQn              = 189,       /*!< STC4 timer3 Interrupt                       */
  RESERVED_190                     = 190,       /*!< RESERVED Interrupt                          */
  RESERVED_191                     = 191,       /*!< RESERVED Interrupt                          */
  AHB_DMA1_CH2_IRQn                = 192,       /*!< AHB DMA1 CH2 Interrupt                      */
  AHB_DMA1_CH3_IRQn                = 193,       /*!< AHB DMA1 CH3 Interrupt                      */
  AHB_DMA1_CH4_IRQn                = 194,       /*!< AHB DMA1 CH4 Interrupt                      */
  AHB_DMA1_CH5_IRQn                = 195,       /*!< AHB DMA1 CH5 Interrupt                      */
  AHB_DMA1_CH6_IRQn                = 196,       /*!< AHB DMA1 CH6 Interrupt                      */
  RESERVED_197                     = 197,       /*!< RESERVED Interrupt                          */
  RESERVED_198                     = 198,       /*!< RESERVED Interrupt                          */
  AHB_DMA1_CH7_IRQn                = 199,       /*!< AHB DMA1 CH7 Interrupt                      */
  MAX_IRQ_n
} IRQn_Type;

typedef enum {
/*G2.1*/
  SYSTEM                           = 0,        /*!< System bus moudle ID*/
  CA55CORE0                        = 1,        /*!< CA55 CORE 0 moudle ID */
  CA55CORE1                        = 2,        /*!< CA55 CORE 1 moudle ID */
  CA55CORE2                        = 3,        /*!< CA55 CORE 2 moudle ID */
  CA55CORE3                        = 4,        /*!< CA55 CORE 3 moudle ID */
  CA55SCUL3                        = 5,        /*!< CA55 SCUL 3 moudle ID */
  CA55                             = 6,        /*!< CA55 moudle ID */
  IOP                              = 7,        /*!< IOP moudle ID */
  PBUS0                            = 8,        /*!< PBUS0 moudle ID */
  PBUS1                            = 9,        /*!< PBUS1 moudle ID */
  PBUS2                            = 10,       /*!< PBUS2 moudle ID */
  PBUS3                            = 11,       /*!< PBUS3 moudle ID */
  BR0                              = 12,       /*!< Bootrom 0 moudle ID */
  CARD_CTL0                        = 13,       /*!< Emmc moudle ID */
  CARD_CTL1                        = 14,       /*!< SDCARD 0 moudle ID */
  CARD_CTL2                        = 15,       /*!< SDCARD 2 moudle ID */
/*G2.2*/
  CBDMA0                           = 16,       /*!< CBDMA moudle ID */
  CPIOL                            = 17,       /*!< CPIO L moudle ID */
  CPIOR                            = 18,       /*!< CPIO R moudle ID */
  DDR_PHY0                         = 19,       /*!< SDCTRL0 moudle ID */
  SDCTRL0                          = 20,       /*!< SDCTRL0 moudle ID */
  DUMMY_MASTER0                    = 21,       /*!< DUMMY_MASTER0 moudle ID */
  DUMMY_MASTER1                    = 22,       /*!< DUMMY_MASTER1 moudle ID */
  DUMMY_MASTER2                    = 23,       /*!< DUMMY_MASTER2 moudle ID */
  EVDN                             = 24,       /*!< EVDN moudle ID */
  SDPOART0                         = 25,       /*!< SDPOART0 moudle ID */
  UMCTL2                           = 26,       /*!< UMCTL2 moudle ID */
  GPU                              = 27,       /*!< GPU moudle ID */
  HSM                              = 28,       /*!< HSM moudle ID */
  RESERVE1                         = 29,       /*!< moudle ID */
  SPACC                            = 30,       /*!< SPACC moudle ID */
  INTERRUPT                        = 31,       /*!< INTERRUPT moudle ID */
/*G2.3*/
  N78                              = 32,       /*!< N78 moudle ID */
  SYSTOP                           = 33,       /*!< SYSTOP moudle ID */
  OTPRX                            = 34,       /*!< OTPRX moudle ID */
  PMC                              = 35,       /*!< PMC moudle ID */
  RBUS_BLOCKA                      = 36,       /*!< RBUS_BLOCKA moudle ID */
  RBUS_BLOCKB                      = 37,       /*!< RBUS_BLOCKB moudle ID */
  RESERVE2                         = 38,       /*!< moudle ID */
  RESERVE3                         = 39,       /*!< moudle ID */
  RTC                              = 40,       /*!< RTC moudle ID */
/*G2.4*/
  MIPZ                             = 41,       /*!< MIPZ moudle ID */
/*G2.5*/
/*G2.6*/
  SPIFL                            = 42,       /*!< SPIFL moudle ID */
  BCH                              = 43,       /*!< BCH moudle ID */
  SPIND                            = 44,       /*!< SPIND moudle ID */
  UADMA01                          = 45,       /*!< UADMA01 moudle ID */
  UADMA23                          = 46,       /*!< UADMA23 moudle ID */
  UART0                            = 47,       /*!< UART0 moudle ID */
  UART1                            = 48,        /*!< UART1 moudle ID */
  UART2                            = 49,        /*!< UART2 moudle ID */
  UART3                            = 50,        /*!< UART3 moudle ID */
  UART4                            = 51,        /*!< UART4 moudle ID */
  UART5                            = 52,        /*!< UART5 moudle ID */
  UART_DBG                         = 53,        /*!< UART_DBG moudle ID */
  UART2AXI                         = 54,        /*!< UART2AXI moudle ID */
  GDMAUA                           = 55,        /*!< GDMAUA moudle ID */
  UPHY0                            = 56,        /*!< UPHY0 moudle ID */
  USB30C0                          = 57,        /*!< USB30C0 moudle ID */
  USB30C1                          = 58,        /*!< USB30C1 moudle ID */
  U3PHY0                           = 59,        /*!< U3PHY0 moudle ID */
  U3PHY1                           = 60,        /*!< U3PHY1 moudle ID */
  USBC0                            = 61,        /*!< USBC0 moudle ID */
/*G2.7*/
  VCD                              = 62,        /*!< VCD moudle ID */
  VCE                              = 63,        /*!< VCE moudle ID */
/*G0.25*/
  CM4                              = 64,        /*!< CM4 moudle ID */
  STC_0                            = 65,        /*!< STC0 moudle ID */
  STC_AV0                          = 66,        /*!< STC_AV0 moudle ID */
  STC_AV1                          = 67,        /*!< STC_AV1 moudle ID */
  STC_AV2                          = 68,        /*!< STC_AV2 SEL moudle ID */
  MAILBOX                          = 69,        /*!< MAILBOX moudle ID */
  PAI                              = 70,        /*!< PAI moudle ID */
  PAII                             = 71,        /*!< PAII moudle ID */
  DDRPHY                           = 72,        /*!< DDRPHY moudle ID */
  DDRCTL                           = 73,        /*!< DDRCTL moudle ID */
  I2CM0                            = 74,        /*!< I2CM0 moudle ID */
/*G2.8*/
  SPICOMBO0                        = 75,        /*!< SPICOMBO0 moudle ID */
  SPICOMBO1                        = 76,        /*!< SPICOMBO1 moudle ID */
  SPICOMBO2                        = 77,        /*!< SPICOMBO2 moudle ID */
  SPICOMBO3                        = 78,        /*!< SPICOMBO3 moudle ID */
  SPICOMBO4                        = 79,        /*!< SPICOMBO4 moudle ID */
/*G2.9*/
  SPICOMBO5                        = 80,        /*!< SPICOMBO5 moudle ID */
  CSIIW0                           = 81,        /*!< CSIIW0 moudle ID */
  MIPICSI0                         = 82,        /*!< MIPICSI0 moudle ID */
  CSIIW1                           = 83,        /*!< CSIIW1 moudle ID */
  MIPICSI1                         = 84,        /*!< MIPICSI1 moudle ID */
  CSIIW2                           = 85,        /*!< CSIIW2 moudle ID */
  MIPICSI2                         = 86,        /*!< MIPICSI2 moudle ID */
  CSIIW3                           = 87,        /*!< CSIIW3 moudle ID */
  MIPICSI3                         = 88,        /*!< MIPICSI3 moudle ID */
  VCL                              = 89,        /*!< VCL moudle ID */
  DISP_PWM                         = 90,        /*!< DISP_PWM moudle ID */
  I2CM1                            = 91,        /*!< I2CM1 moudle ID */
  I2CM2                            = 92,        /*!< I2CM2 moudle ID */
  I2CM3                            = 93,        /*!< I2CM3 moudle ID */
/*G2.10*/
  I2CM4                            = 94,        /*!< I2CM4 moudle ID */
  I2CM5                            = 95,        /*!< I2CM5 moudle ID */
/*G2.11*/
  UART6                            = 96,        /*!< UART6 moudle ID */
/*G2.12*/
  UART7                            = 97,        /*!< UART7 moudle ID */
  UART8                            = 98,        /*!< UART8 moudle ID */
  AUD                              = 99,        /*!< AUD moudle ID */
  VIDEO_CODEC                      = 100,       /*!< VIDEO_CODEC moudle ID */
  AXIM_PAI                         = 101,       /*!< AXIM_PAI moudle ID */
  AXIM_PAII                        = 102,       /*!< STC AXIM_PAII moudle ID */
  AXIM_TOP                         = 103,       /*!< AXIM_TOP AV3 moudle ID */
}MODULE_ID_Type;

#define PINMUX_DFMP_2BIT            (0x10000)
#define PINMUX_DFMP_3BIT            (0x20000)
#define PINMUX_DFMP_4BIT            (0x40000)

typedef enum{
  /*G1.1*/
  PINMUX_SPI_FLASH=16,
  PINMUX_EMMC1,
  PINMUX_SPI_NAND=18|PINMUX_DFMP_2BIT,
  PINMUX_SDCARD=20,
  PINMUX_SDIO,
  PINMUX_P_NAND,
  PINMUX_USB0_OTG,
  PINMUX_CA55_JTAG,
  PINMUX_GMAC,
  PINMUX_PWM_CH0=26|PINMUX_DFMP_2BIT,
  PINMUX_PWM_CH1=28|PINMUX_DFMP_2BIT,
  PINMUX_PWM_CH2=30|PINMUX_DFMP_2BIT,

  /*G1.2*/
  PINMUX_PWM_CH3=32|PINMUX_DFMP_2BIT,
  PINMUX_UART0=34|PINMUX_DFMP_2BIT,
  PINMUX_UART1=36|PINMUX_DFMP_2BIT,
  PINMUX_UART1_FC=38|PINMUX_DFMP_2BIT,
  PINMUX_UART2=40|PINMUX_DFMP_2BIT,
  PINMUX_UART2_FC=42|PINMUX_DFMP_2BIT,
  PINMUX_UART3=44|PINMUX_DFMP_2BIT,
  PINMUX_UA2AXI=46,
  PINMUX_RESERVE_1,

  /*G1.3*/
  PINMUX_UART6=48|PINMUX_DFMP_2BIT,
  PINMUX_UART7=50,
  PINMUX_I2C_0=51|PINMUX_DFMP_2BIT,
  PINMUX_I2C_1=53,
  PINMUX_I2C_2=54|PINMUX_DFMP_2BIT,
  PINMUX_I2C_3=56,
  PINMUX_I2C_4,
  PINMUX_I2C_5,
  PINMUX_I2C_6=59|PINMUX_DFMP_2BIT,
  PINMUX_I2C_7=61|PINMUX_DFMP_2BIT,
  PINMUX_RESERVE_2,

  /*G1.4*/
  PINMUX_I2C_8=64|PINMUX_DFMP_2BIT,
  PINMUX_I2C_9=66|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_MCU=68|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_WIFI=70|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_RTC=72|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_PHY=74|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_GNCMA=76|PINMUX_DFMP_2BIT,
  PINMUX_CLKGEN_DGO_MST=78|PINMUX_DFMP_2BIT,

  /*G1.5*/
  PINMUX_CM4_JTAG=80,
  PINMUX_SPI_COM1_MST=81|PINMUX_DFMP_2BIT,
  PINMUX_SPI_COM2_MST=83,
  PINMUX_SPI_COM3_MST=84|PINMUX_DFMP_2BIT,
  PINMUX_SPI_COM4_MST=86,
  PINMUX_SPI_COM5_SLV=87|PINMUX_DFMP_2BIT,
  PINMUX_AUD_TDMTX_XCK=89,
  PINMUX_AUD_DAC_CLK_XCK1,
  PINMUX_AUD_DAC_CLK_XCK,
  PINMUX_AUD_AU2_DATA0,
  PINMUX_AUD_AU1_DATA0,
  PINMUX_AUD_AU2_CK,
  PINMUX_AUD_AU1_CK,

  /*G1.6*/
  PINMUX_AUD_AU_ADC_DATA0=96|PINMUX_DFMP_2BIT,
  PINMUX_AUD_ADC2_DATA0=98,
  PINMUX_AUD_ADC1_DATA0,
  PINMUX_AUD_TDM,
  PINMUX_SPDIF_IN=101|PINMUX_DFMP_3BIT,
  PINMUX_SPDIF_OUT=104|PINMUX_DFMP_3BIT,
  PINMUX_SAR_ADC_PROBE=107,
  PINMUX_VCL_EXT_INTR0=108|PINMUX_DFMP_2BIT,
  PINMUX_VCL_EXT_INTR1=110|PINMUX_DFMP_2BIT,
  /*G1.7*/
  PINMUX_VCL_EXT_INTR2=112|PINMUX_DFMP_2BIT,
  PINMUX_VCL_EXT_INTR3=114|PINMUX_DFMP_2BIT,
  PINMUX_CPIOR_I2C=116,
  PINMUX_GPIO_INT0=117|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_INT1=121|PINMUX_DFMP_4BIT,
  PINMUX_RESERVE_3=125|PINMUX_DFMP_3BIT,
  /*G1.8*/
  PINMUX_GPIO_INT2=128|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_INT3=132|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_INT4=136|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_INT5=140|PINMUX_DFMP_4BIT,
  /*G1.9*/
  PINMUX_GPIO_INT6=144|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_INT7=148|PINMUX_DFMP_4BIT,
  PINMUX_GPIO_AO_INT0=152|PINMUX_DFMP_2BIT,
  PINMUX_GPIO_AO_INT1=154|PINMUX_DFMP_2BIT,
  PINMUX_GPIO_AO_INT2=156|PINMUX_DFMP_2BIT,
  PINMUX_GPIO_AO_INT3=158|PINMUX_DFMP_2BIT,
  /*G1.10*/
  PINMUX_MO1_CLK27=160,
  PINMUX_U2PHY0_DEBUG,
  PINMUX_UPHY0_IF,
  PINMUX_U3PHY0_DEBUG,
  PINMUX_PROBE_PORT,
  PINMUX_RESERVE_4=165,

}PINMUX_Type;




/** Macro to write new value to the bits in register */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))


#include "core_cm4.h"
#include <stdint.h>
#include "system_sp7350.h"

typedef struct {
    __IOM uint32_t sft_cfg[32];
}MOON_REG_Type;

typedef struct{
    __IOM uint32_t clock_enable[12];   /*!< \brief devices clock enable bit*/
}Module_Clock_En_type;

typedef struct{
    __IOM uint32_t clock_gate_enable[12]; /*!< \brief devices clock gate enable bit*/
}Module_Clock_Gate_Type;

typedef struct{
    __IOM uint32_t reset[15];         /*!< \brief devices clock gate enable bit*/
}Module_Reset_Type;

typedef struct{
    __IOM uint32_t dr;                /* data register */
    __IOM uint32_t lsr;               /* line status register */
    __IOM uint32_t msr;               /* modem status register */
    __IOM uint32_t lcr;               /* line control register */
    __IOM uint32_t mcr;               /* modem control register */
    __IOM uint32_t div_l;
    __IOM uint32_t div_h;
    __IOM uint32_t isc;              /* interrupt status/control */
    __IOM uint32_t txr;              /* tx residue */
    __IOM uint32_t rxr;              /* rx residue */
    __IOM uint32_t thr;              /* rx threshold */
    __IOM uint32_t clk_src;
}UART_CTRL_Type;

typedef struct {
   __IOM uint32_t rxdma_enable_sel;
   __IOM uint32_t rxdma_start_addr;
   __IOM uint32_t rxdma_timeout_set;
   __IOM uint32_t rxdma_reserved;
   __IOM uint32_t rxdma_wr_adr;
   __IOM uint32_t rxdma_rd_adr;
   __IOM uint32_t rxdma_length_thr;
   __IOM uint32_t rxdma_end_addr;
   __IOM uint32_t rxdma_databytes;
   __IOM uint32_t rxdma_debug_info;
}UART_Rxdma;

typedef struct {
   __IOM uint32_t txdma_enable;
   __IOM uint32_t txdma_sel;
   __IOM uint32_t txdma_start_addr;
   __IOM uint32_t txdma_end_addr;
   __IOM uint32_t txdma_wr_adr;
   __IOM uint32_t txdma_rd_adr;
   __IOM uint32_t txdma_status;
   __IOM uint32_t txdma_tmr_unit;
   __IOM uint32_t txdma_tmr_cnt;
   __IOM uint32_t txdma_rst_done;
}UART_Txdma;

typedef struct {
   __IOM uint32_t gdma_hw_ver;
   __IOM uint32_t gdma_config;
   __IOM uint32_t gdma_length;
   __IOM uint32_t gdma_addr;
   __IOM uint32_t gdma_port_mux;
   __IOM uint32_t gdma_int_flag;
   __IOM uint32_t gdma_int_en;
   __IOM uint32_t gdma_software_reset_status;
   __IOM uint32_t txdma_tmr_cnt;
}UART_TxGdma;

typedef struct{
	__IOM uint32_t stc_31_0;			/*!< \brief  standard time clock counter, 0~15 bit */
	__IOM uint32_t stc_63_32;			/*!< \brief  standard time clock counter, 16~31 bit */
	__IOM uint32_t stc_64;				/*!< \brief  standard time clock counter, the MSB 64 bit, when write the bit ,clear the stc counter at once */
	__IOM uint32_t stc_prescale_val;
	__IOM uint32_t stc_config;
	RESERVED(0[19], uint32_t)
	__IOM uint32_t stcl_31_0;
	__IOM uint32_t stcl_32;
}STC_TypeDef;


typedef struct{
   // SPI_MASTER
   __IOM uint32_t mst_tx_data_addr;
   __IOM uint32_t mst_tx_data_3_2_1_0;
   __IOM uint32_t mst_tx_data_7_6_5_4;
   __IOM uint32_t mst_tx_data_11_10_9_8;
   __IOM uint32_t mst_tx_data_15_14_13_12;
   RESERVED(0[4], uint32_t);
   __IOM uint32_t mst_rx_data_3_2_1_0;
   __IOM uint32_t mst_rx_data_7_6_5_4;
   __IOM uint32_t mst_rx_data_11_10_9_8;
   __IOM uint32_t mst_rx_data_15_14_13_12;
   __IOM uint32_t fifo_data;
   __IOM uint32_t spi_status;
   __IOM uint32_t spi_config;
  RESERVED(1[1], uint32_t);
   __IOM uint32_t spi_ctl_clk_sel;
   __IOM uint32_t spi_byte_no;
   __IOM uint32_t spi_int_busy;
   __IOM uint32_t spi_dma_ctrl;
   __IOM uint32_t spi_dma_length;
   __IOM uint32_t spi_dma_addr;
   RESERVED(2[1], uint32_t);
   __IOM uint32_t spi_dma_status;
   RESERVED(3[1], uint32_t);
   __IOM uint32_t uart_dma_ctrl;
   RESERVED(4[1], uint32_t);
   __IOM uint32_t spi_mst_debug_sel;
   __IOM uint32_t spi_combo_debug_sel;
   __IOM uint32_t spi_extra_cycle;
   __IOM uint32_t spi_dma_data_rdy;
}SPI_TypeDef;

typedef struct
{
	__IOM uint32_t control0;      /* 00 */
	__IOM uint32_t control1;      /* 01 */
	__IOM uint32_t control2;      /* 02 */
	__IOM uint32_t control3;      /* 03 */
	__IOM uint32_t control4;      /* 04 */
	__IOM uint32_t control5;      /* 05 */
	__IOM uint32_t i2cm_status0;  /* 06 */
	__IOM uint32_t interrupt;     /* 07 */
	__IOM uint32_t int_en0;       /* 08 */
	__IOM uint32_t i2cm_mode;     /* 09 */
	__IOM uint32_t i2cm_status1;  /* 10 */
	__IOM uint32_t i2cm_status2;  /* 11 */
	__IOM uint32_t control6;      /* 12 */
	__IOM uint32_t int_en1;       /* 13 */
	__IOM uint32_t i2cm_status3;  /* 14 */
	__IOM uint32_t i2cm_status4;  /* 15 */
	__IOM uint32_t int_en2;       /* 16 */
	__IOM uint32_t control7;      /* 17 */
	__IOM uint32_t control8;      /* 18 */
	__IOM uint32_t control9;      /* 19 */
	RESERVED(0[3], uint32_t)      /* 20~22 */
	__IOM uint32_t version;       /* 23 */
	__IOM uint32_t data00_03;     /* 24 */
	__IOM uint32_t data04_07;     /* 25 */
	__IOM uint32_t data08_11;     /* 26 */
	__IOM uint32_t data12_15;     /* 27 */
	__IOM uint32_t data16_19;     /* 28 */
	__IOM uint32_t data20_23;     /* 29 */
	__IOM uint32_t data24_27;     /* 30 */
	__IOM uint32_t data28_31;     /* 31 */
} I2C_TypeDef;

typedef struct
{
	__IOM uint32_t hw_version;                /* 00 */
	__IOM uint32_t dma_config;                /* 01 */
	__IOM uint32_t dma_length;                /* 02 */
	__IOM uint32_t dma_addr;                  /* 03 */
	__IOM uint32_t port_mux;                  /* 04 */
	__IOM uint32_t int_flag;                  /* 05 */
	__IOM uint32_t int_en;                    /* 06 */
	__IOM uint32_t sw_reset_state;            /* 07 */
	RESERVED(0[2], uint32_t)                  /* 08~09 */
	__IOM uint32_t sg_dma_index;              /* 10 */
	__IOM uint32_t sg_dma_config;             /* 11 */
	__IOM uint32_t sg_dma_length;             /* 12 */
	__IOM uint32_t sg_dma_addr;               /* 13 */
	RESERVED(1, uint32_t)                     /* 14 */
	__IOM uint32_t sg_setting;                /* 15 */
	__IOM uint32_t threshold;                 /* 16 */
	RESERVED(2, uint32_t)                     /* 17 */
	__IOM uint32_t gdma_read_timeout;         /* 18 */
	__IOM uint32_t gdma_write_timeout;        /* 19 */
	__IOM uint32_t ip_read_timeout;           /* 20 */
	__IOM uint32_t ip_write_timeout;          /* 21 */
	__IOM uint32_t write_cnt_debug;           /* 22 */
	__IOM uint32_t w_byte_en_debug;           /* 23 */
	__IOM uint32_t sw_reset_write_cnt_debug;  /* 24 */
	__IOM uint32_t sw_reset_read_cnt_debug;   /* 25 */
	RESERVED(3[6], uint32_t)                  /* 26~31 */
} GDMA_TypeDef;


typedef struct
{
	__IOM uint32_t control;           /*!< \brief timer control register for >*/
	__IOM uint32_t counter_val;       /*!< \brief 16-bit counter, it down to 0, the timer will generate the interrupt*/
	__IOM uint32_t reload_val;        /*!< \brief when count reaches to 0, the value will reload to the count >*/
	__IOM uint32_t prescale_val;      /*!< \brief 16-bit prescale for timer>*/
}TIM_TypeDef;

typedef struct
{
	__IOM uint32_t control;           /*!< \brief write command to this register to control the watchdog */
	__IOM uint32_t counter_val;       /*!< \brief 16-bit counter, it down to 0, the wathcdog will generate the interrupt */
	RESERVED(0[18], uint32_t);
	__IOM uint32_t mode;              /*!< \brief set watchdog interrupt mode */
	__IOM uint32_t intr_counter_val;  /*!< \brief 32-bit counter for watchdog interrupt and reset mode */
}WDG_TypeDef;

typedef struct
{
	__IOM uint32_t type[7];              /*!< \brief  interrupt type 1:level-type, 0: edge-type */
	__IOM uint32_t polarity[7];          /*!< \brief  interrupt polarity 0:high-active(default) 1:low-active*/
	__IOM uint32_t priority[7];          /*!< \brief  interrupt piority 0:fiq, 1:irq(default) */
	__IOM uint32_t mask[7];              /*!< \brief  mask interrupt bit 0:masked(default) 1:pass */
}IRQ_Ctrl_Type;

typedef struct {
	__IOM uint32_t C2M_normal_trigger;		//CA55 tiger the INT to CM4
	__IOM uint32_t C2M_write_monitor_status;
	__IOM uint32_t C2M_over_write_monitor_status;
	RESERVED(0, uint32_t);
	__IOM uint32_t C2M_normal_data[20];
	__IOM uint32_t C2M_direct_data[8];

	__IOM uint32_t M2C_normal_trigger;		//CM4 tiger the INT to CA55
	__IOM uint32_t M2C_write_monitor_status;
	__IOM uint32_t M2C_over_write_monitor_status;
	RESERVED(1, uint32_t);
	__IOM uint32_t M2C_normal_data[20];
	__IOM uint32_t M2C_direct_data[8];
}IPCC_Typedef;

#define STATIC_ASSERT(b) extern int _static_assert[b ? 1 : -1]

struct _PWM_DD_REG_ {
   union {
      struct {
         uint32_t dd             :18;//b(0-17)
         uint32_t :14;
      };
      __IOM uint32_t _pwm_dd_ctrl;
   };
};
STATIC_ASSERT(sizeof(struct _PWM_DD_REG_) == 4);

struct _PWM_DU_REG_ {
   union {
      struct {
         uint32_t pwm_duty       :12;   //b(0-11)
         uint32_t reserve_du     :4;    //b(12-15)
         uint32_t pwm_du_dd_sel  :2;    //b(16-17)
         uint32_t                :14;   //b(18-31)
      };
      __IOM uint32_t _pwm_chx_cfg;
   };
};
STATIC_ASSERT(sizeof(struct _PWM_DU_REG_) == 4);

typedef struct {
    union {
      struct {
         uint32_t pwm_en            :8;   //b(0-7)
         uint32_t pwm_bypass        :8;   //b(8-15)
         uint32_t reserve           :4;   //b(16-19)
         uint32_t pwm_resolution    :4;   //b(20-23)
         uint32_t :8;
      };
      __IOM uint32_t pwm_mode;
   };
    struct _PWM_DU_REG_ pwm_chx_cfg[4];
    __IOM uint32_t reserve_1[11];
    __IOM uint32_t pwm_version;
    struct _PWM_DD_REG_ pwm_dd_ctrl[4];
    __IOM uint32_t reserve_2[11];
}PWM_TypeDef;

#define REG_BASE                     0xF8000000
#define REG_BASE_AO                  0xF8800000

#define RF_GRP_AO(_grp, _reg)        ((((_grp) * 32 + (_reg)) * 4) + REG_BASE_AO)
#define RF_GRP(_grp, _reg)           ((((_grp) * 32 + (_reg)) * 4) + REG_BASE)
#define RF_MASK_V(_mask, _val)       (((_mask) << 16) | (_val))
#define RF_MASK_V_SET(_mask)         (((_mask) << 16) | (_mask))
#define RF_MASK_V_CLR(_mask)         (((_mask) << 16) | 0)

/* MOON REG */
#define MOON0_REG                    ((volatile MOON_REG_Type *)RF_GRP_AO(0, 0))
#define MOON1_REG                    ((volatile MOON_REG_Type *)RF_GRP_AO(1, 0))
#define MOON2_REG                    ((volatile MOON_REG_Type *)RF_GRP_AO(2, 0))
#define MOON3_REG                    ((volatile MOON_REG_Type *)RF_GRP_AO(3, 0))
#define MOON4_REG                    ((volatile MOON_REG_Type *)RF_GRP_AO(4, 0))

/* IRQ */
#define SP_IRQ_CTRL                  ((volatile IRQ_Ctrl_Type*) RF_GRP(9, 0))

/* IPCC Mailbox */
#define IPC_MAILBOX                  ((volatile IPCC_Typedef *)RF_GRP(255, 0))

/*SP654 module clock enable bit*/
#define CLK_EN                       ((Module_Clock_En_type*)RF_GRP_AO(2, 1))

/*SP654 module clock enable bit*/
#define CLK_GATE                     ((Module_Clock_Gate_Type*)RF_GRP_AO(2, 15))

/*SP654 module rest bit*/
#define MODULE_REST                  ((Module_Reset_Type*)RF_GRP_AO(0, 1))


typedef struct{
	__IOM uint32_t cpu_to_cpu_int_trigger;
	__IOM uint32_t cpu_to_cpu_writelock_flag;
	__IOM uint32_t cpu_to_cpu_overwrite_flag;
	RESERVED(0[1], uint32_t)
	__IOM uint32_t normal_transation[20];
	__IOM uint32_t direct_transation[8];
}Cpu_Mailbox_TypeDef;
#define CA55_TO_CM4_MAILBOX          ((Cpu_Mailbox_TypeDef *)RF_GRP(258, 0))
#define CM4_TO_CA55_MAILBOX          ((Cpu_Mailbox_TypeDef *)RF_GRP(259, 0))
typedef struct{
	__IOM uint32_t pmc_ctrl;
	__IOM uint32_t pmc_timer;
	__IOM uint32_t pmc_timer2;
	__IOM uint32_t pmc_main_dowmain_pwd_1;
	__IOM uint32_t pmc_main_dowmain_pwd_11;
	__IOM uint32_t pmc_reserve5;
	__IOM uint32_t pmc_reserve6;
	__IOM uint32_t pmc_xtal27m_pwd_h;
	__IOM uint32_t pmc_xtal27m_pwd_l;
	__IOM uint32_t pmc_wakeup_latch;
	__IOM uint32_t pmc_ivmx_reg;
	__IOM uint32_t pmc_reserve11;
	__IOM uint32_t pmc_reserve12;
	__IOM uint32_t pmc_reserve13;
	__IOM uint32_t pmc_reserve14;
	__IOM uint32_t pmc_main_pwr_ctrl;
	__IOM uint32_t pmc_corepsw_pwd ;
	__IOM uint32_t pmc_corepsw_en;
	__IOM uint32_t pmc_coremem_sdpwd;
	__IOM uint32_t pmc_coremem_sden;
	__IOM uint32_t pmc_lvs_pwd;
	__IOM uint32_t pmc_lvs_disable;
	__IOM uint32_t pmc_iso_pwd;
	__IOM uint32_t pmc_iso_en;
	__IOM uint32_t pmc_reserve24;
	__IOM uint32_t pmc_reserve25;
	__IOM uint32_t pmc_reserve26;
	__IOM uint32_t pmc_reset_vector;
	__IOM uint32_t pmc_ca55_reset_state;
	__IOM uint32_t pmc_pctl_reg;
	__IOM uint32_t pmc_pctl_int_clr;
	__IOM uint32_t pmc_reserve31;
}Pmc_TypeDef;
#define PMC_REGS                    ((Pmc_TypeDef *)RF_GRP_AO(36, 0))
typedef struct{
	RESERVED(0[1], uint32_t);
	__IOM uint32_t rtc_ctrl;
	__IOM uint32_t rtc_timer;
	__IOM uint32_t rtc_ontime_set;
	__IOM uint32_t rtc_clock_set;
	__IOM uint32_t rtc_macro_ctrl;
	__IOM uint32_t rtc_periodic_set;
	__IOM uint32_t rtc_int_status;
	RESERVED(1[2], uint32_t); ;
	__IOM uint32_t rtc_system_cnt_31_0;
	__IOM uint32_t rtc_system_cnt_63_32;
	__IOM uint32_t rtc_tml_sd_disable_bypass;
	__IOM uint32_t rtc_stall_cnt;
	__IOM uint32_t rtc_stall;
	__IOM uint32_t rtc_pwr_chk_cnt;
	__IOM uint32_t rtc_pwr_chk_dbg_sel;
	RESERVED(2[1], uint32_t);
	__IOM uint32_t rtc_pwr_chk_dbg;
	__IOM uint32_t rtc_pwr_ctl_dbg_sel;
	__IOM uint32_t rtc_pwr_ctl_dbg;
	__IOM uint32_t rtc_ao_power_off_req;
	__IOM uint32_t rtc_wakeupkey_int_status;
	RESERVED(3[9], uint32_t);
}RTC_TypeDef;
#define RTC_REGS                    ((RTC_TypeDef *)RF_GRP_AO(35, 0))
/********************  Bit definition for STC register  ********************/
/*  STC register */
#define _STC_BASE                    RF_GRP_AO(23, 0)
#define _STC_AV0_BASE                RF_GRP_AO(24, 0)
#define _STC_AV1_BASE                RF_GRP_AO(25, 0)
#define _STC_AV2_BASE                RF_GRP_AO(26, 0)
#define _STC_AV4_BASE                RF_GRP_AO(38, 0)

#define STC0                         ((STC_TypeDef *)_STC_BASE)
#define STC1                         ((STC_TypeDef *)_STC_AV0_BASE)
#define STC2                         ((STC_TypeDef *)_STC_AV1_BASE)
#define STC3                         ((STC_TypeDef *)_STC_AV2_BASE)
#define STC4                         ((STC_TypeDef *)_STC_AV4_BASE)

#define STC_PRESCALER_Pos            (0U)
#define STC_PRESCALER_Msk            (0x7FFFU << STC_PRESCALER_Pos)    /*0x000007FF*/
#define STC_PRESCALER                STC_PRESCALER_Msk                 /*STC prescale value */
#define STC_TRIG_SRC_Pos             (15U)
#define STC_TRIG_SRC_Msk             (1U << STC_TRIG_SRC_Pos)          /*0x00008000*/
#define STC_TRIG_SRC                 STC_TRIG_SRC_Msk                  /*The triger source of the STC counter. 0:system clock; 1:externl clock*/

#define STC_EXT_DIV_Pos              (0U)
#define STC_EXT_DIV_Msk              (0xFFU << STC_EXT_DIV_Pos)        /*0x000000FF*/
#define STC_EXT_DIV                  (STC_EXT_DIV_Msk)                 /*The external clock divder for STC*/
#define STC_EXT_SRC_SEL_Pos          (8U)
#define STC_EXT_SRC_SEL_Msk          (1U << STC_EXT_SRC_SEL_Pos)       /*0x00000100*/
#define STC_EXT_SRC_SEL              (STC_EXT_SRC_SEL_Msk)             /*The external clock source selection. 0:25MHz; 1:32KHz*/
#define STC_EXT_PRESCALER_EN_Pos     (9U)
#define STC_EXT_PRESCALER_EN_Msk     (1U << STC_EXT_PRESCALER_EN_Pos)  /*0x00000200*/
#define STC_EXT_PRESCALER_EN         (STC_EXT_PRESCALER_EN_Msk)        /*The external clock prescaler. 0:disable; 1:enable*/

/****************** STC Instances : All supported instances *******************/
#define IS_STC_INSTANCE(INSTANCE)    (((INSTANCE) == STC0)   || \
                                      ((INSTANCE) == STC1)   || \
                                      ((INSTANCE) == STC2)   || \
                                      ((INSTANCE) == STC3)   || \
                                      ((INSTANCE) == STC4))

/******************************************************************************/
/*                                                                            */
/*                        timer/counter                                       */
/*                                                                            */
/******************************************************************************/

/* Timer register */
#define _REG_GROUP_SIZE              (0x80)
#define _OFFSET_BETWEEN_TIMERS       (4 * 4)

#define TIM0_BASE                    RF_GRP(12, 18)
#define TIM1_BASE                    RF_GRP(12, 22)

/*TIMER2 & TIMER3 is a group*/
#define TIM2_BASE                    RF_GRP(96, 18)
#define TIM3_BASE                    RF_GRP(96, 22)

/*TIMER4 & TIMER5 is a group*/
#define TIM4_BASE                    RF_GRP(97, 18)
#define TIM5_BASE                    RF_GRP(97, 22)

/*TIMER6 & TIMER7 is a group*/
#define TIM6_BASE                    RF_GRP(99, 18)
#define TIM7_BASE                    RF_GRP(99, 22)

#define TIM0                         ((TIM_TypeDef *) TIM0_BASE)
#define TIM1                         ((TIM_TypeDef *) TIM1_BASE)
#define TIM2                         ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                         ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                         ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                         ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                         ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                         ((TIM_TypeDef *) TIM7_BASE)

/********************  Bit definition for timer register  ********************/
#define TIMER_GO_Pos                 (0)
#define TIMER_GO_Msk                 (1U << TIMER_GO_Pos)			/*0x00000001*/
#define TIMER_GO                     TIMER_GO_Msk					/*timer go. 1:start;0:stop*/
#define TIMER_RPT_pos                (1U)
#define TIMER_RPT_Msk                (1U << TIMER_RPT_pos)			/*0x00000002*/
#define TIMER_RPT                    TIMER_RPT_Msk					/*timer repeat operation. 0:one shot;1: repeation*/
#define TIMER_TRIG_SRC_Pos           (2U)
#define TIMER_TRIG_SRC_Msk           (0x3 << TIMER_TRIG_SRC_Pos)     /*0x00003000*/
#define TIMER_TRIG_SRC               TIMER_TRIG_SRC_Msk              /*timer triger source selection. 0:systemclock triger;1:stc triger;2:rtc_triger;3:external clk triger;*/


/****************** TIM Instances : All supported instances *******************/
#define IS_TIM_INSTANCE(INSTANCE)    (((INSTANCE) == TIM0)   || ((INSTANCE) == TIM1) ||  ((INSTANCE) == TIM2)  ||  ((INSTANCE) == TIM3)    ||\
                                      ((INSTANCE) == TIM4)   || ((INSTANCE) == TIM5)  ||  ((INSTANCE) == TIM6)  ||  ((INSTANCE) == TIM7)   )

/******************************************************************************/
/*                                                                            */
/*                        watchdog module                                     */
/*                                                                            */
/******************************************************************************/
#define WDG0_BASE                   RF_GRP(23, 7)
#define WDG1_BASE                   RF_GRP(24, 7)
#define WDG2_BASE                   RF_GRP(25, 7)
#define WDG3_BASE                   RF_GRP(38, 7)

#define WDG0                         ((WDG_TypeDef *) WDG0_BASE)
#define WDG1                         ((WDG_TypeDef *) WDG1_BASE)
#define WDG2                         ((WDG_TypeDef *) WDG2_BASE)
#define WDG3                         ((WDG_TypeDef *) WDG3_BASE)

/****************** WDG Instances : All supported instances *******************/
#define IS_WDG_INSTANCE(INSTANCE)    (((INSTANCE) == WDG0)   || \
                                      ((INSTANCE) == WDG1)   || \
                                      ((INSTANCE) == WDG2)   || \
                                      ((INSTANCE) == WDG3))

/******************************************************************************/
/*                                                                            */
/*                        pwm module                                          */
/*                                                                            */
/******************************************************************************/

#define PWM_BASE                      RF_GRP_AO(27, 0)
#define PWM_REG                       ((PWM_TypeDef *)PWM_BASE)

/******************************************************************************/
/*                        UART module                                          */
/******************************************************************************/

#define UART0_BASE      RF_GRP_AO(50, 0)
#define UART1_BASE      RF_GRP_AO(51, 0)
#define UART2_BASE      RF_GRP_AO(55, 0)
#define UART3_BASE      RF_GRP_AO(59, 0)
#define UART6_BASE      RF_GRP_AO(63, 0)
#define UART7_BASE      RF_GRP_AO(67, 0)
#define UARTDBG_BASE    RF_GRP(498, 0)

#define SP_UART0        ((UART_CTRL_Type *)UART0_BASE)
#define SP_UART1        ((UART_CTRL_Type *)UART1_BASE)
#define SP_UART2        ((UART_CTRL_Type *)UART2_BASE)
#define SP_UART3        ((UART_CTRL_Type *)UART3_BASE)
#define SP_UART4        ((UART_CTRL_Type *)0)/* define it for compile error, not used */
#define SP_UART6        ((UART_CTRL_Type *)UART6_BASE)
#define SP_UART7        ((UART_CTRL_Type *)UART7_BASE)
#define SP_UARTDBG      ((UART_CTRL_Type *)UARTDBG_BASE)

/*
UART LCR register BIT
*/
#define LCR_VOTE_BIT                (0x3 << 6)
#define LCR_BREAK_CONDITION_BIT     (0x1 << 5)
#define LCR_PARITY_BIT              (0x1 << 4)
#define LCR_PARITY_ENABLE_BIT       (0x1 << 3)
#define LCR_STOP_BIT_BIT            (0x1 << 2)
#define LCR_WORD_LEN_BIT            (0x3 << 0)

/* UART MCR register BIT */
#define MCR_AUTO_CALIBRATE_BIT         (0x1 << 7)
#define MCR_AUTO_CTS_BIT               (0x1 << 6)
#define MCR_AUTO_RTS_BIT               (0x1 << 5)
#define MCR_LOOP_BACK_BIT              (0x1 << 4)
#define MCR_RING_INDICATOR_BIT         (0x1 << 3)
#define MCR_DCD_BIT                    (0x1 << 2)
#define MCR_RTS_BIT                    (0x1 << 1)
#define MCR_DTS_BIT                    (0x1 << 0)

/* interrupt */
#define SP_UART_LSR_BC     (1 << 5) /* break condition */
#define SP_UART_LSR_FE     (1 << 4) /* frame error */
#define SP_UART_LSR_OE     (1 << 3) /* overrun error */
#define SP_UART_LSR_PE     (1 << 2) /* parity error */
#define SP_UART_LSR_RX     (1 << 1) /* 1: receive fifo not empty */
#define SP_UART_LSR_TX     (1 << 0) /* 1: transmit fifo is not full */

/* isc */
#define SP_UART_ISC_MSM    (1 << 7) /* Modem status ctrl */
#define SP_UART_ISC_LSM    (1 << 6) /* Line status interrupt */
#define SP_UART_ISC_RXM    (1 << 5) /* RX interrupt, when got some input data */
#define SP_UART_ISC_TXM    (1 << 4) /* TX interrupt, when trans start */
#define HAS_UART_ISC_FLAGMASK 0x0F
#define SP_UART_ISC_MS     (1 << 3)
#define SP_UART_ISC_LS     (1 << 2)
#define SP_UART_ISC_RX     (1 << 1)
#define SP_UART_ISC_TX     (1 << 0)

/* DMA-RX, dma_enable_sel */
#define DMA_INT            (1 << 31)
#define DMA_MSI_ID_SHIFT   12
#define DMA_MSI_ID_MASK    (0x7F << DMA_MSI_ID_SHIFT)
#define DMA_SEL_UARTX_SHIFT   8
#define DMA_SEL_UARTX_MASK (0x07 << DMA_SEL_UARTX_SHIFT)
#define DMA_SW_RST_B    (1 << 7)
#define DMA_INIT        (1 << 6)
#define DMA_GO          (1 << 5)
#define DMA_AUTO_ENABLE    (1 << 4)
#define DMA_TIMEOUT_INT_EN (1 << 3)
#define DMA_P_SAFE_DISABLE (1 << 2)
#define DMA_PBUS_DATA_SWAP (1 << 1)
#define DMA_ENABLE         (1 << 0)

#define UART_LSR_TRANSMIT_FIFO_STATUS        (1 << 0)
#define UART_LSR_RECEIVE_FIFO_STATUS         (1 << 1)


#define UART_TXDMA1        ((UART_Txdma *)RF_GRP_AO(54, 0))
#define UART_TXDMA2        ((UART_Txdma *)RF_GRP_AO(58, 0))
#define UART_TXDMA3        ((UART_Txdma *)RF_GRP_AO(62, 0))
#define UART_TXDMA6        ((UART_Txdma *)RF_GRP_AO(66, 0))
#define UART_TXDMA7        ((UART_Txdma *)RF_GRP_AO(70, 0))

#define UART_TXGDMA1       ((UART_TxGdma *)RF_GRP_AO(52, 0))
#define UART_TXGDMA2       ((UART_TxGdma *)RF_GRP_AO(56, 0))
#define UART_TXGDMA3       ((UART_TxGdma *)RF_GRP_AO(60, 0))
#define UART_TXGDMA6       ((UART_TxGdma *)RF_GRP_AO(64, 0))
#define UART_TXGDMA7       ((UART_TxGdma *)RF_GRP_AO(68, 0))

#define UART_RXDMA1        ((UART_Rxdma *)RF_GRP_AO(53, 0))
#define UART_RXDMA2        ((UART_Rxdma *)RF_GRP_AO(57, 0))
#define UART_RXDMA3        ((UART_Rxdma *)RF_GRP_AO(61, 0))
#define UART_RXDMA6        ((UART_Rxdma *)RF_GRP_AO(65, 0))
#define UART_RXDMA7        ((UART_Rxdma *)RF_GRP_AO(69, 0))
#define IS_UART_INSTANCE(__INSTANCE__) (((__INSTANCE__) == SP_UART1) || \
                                    ((__INSTANCE__) == SP_UART2) || \
                                    ((__INSTANCE__) == SP_UART3) || \
                                    ((__INSTANCE__) == SP_UART6)  || \
                                    ((__INSTANCE__) == SP_UART7)  || \
                                    ((__INSTANCE__) == SP_UARTDBG))
#define IS_UART_TXDMA_INSTANCE(__INSTANCE__) (((__INSTANCE__) == UART_TXDMA1) || \
                                    ((__INSTANCE__) == UART_TXDMA2) || \
                                    ((__INSTANCE__) == UART_TXDMA3) || \
                                    ((__INSTANCE__) == UART_TXDMA6) || \
                                    ((__INSTANCE__) == UART_TXDMA7))
#define IS_UART_TXGDMA_INSTANCE(__INSTANCE__) (((__INSTANCE__) == UART_TXGDMA1) || \
                                    ((__INSTANCE__) == UART_TXGDMA2) || \
                                    ((__INSTANCE__) == UART_TXGDMA3) || \
                                    ((__INSTANCE__) == UART_TXGDMA6) || \
                                    ((__INSTANCE__) == UART_TXGDMA7))
#define IS_UART_RXDMA_INSTANCE(__INSTANCE__) (((__INSTANCE__) == UART_RXDMA1) || \
                                    ((__INSTANCE__) == UART_RXDMA2) || \
                                    ((__INSTANCE__) == UART_RXDMA3) || \
                                    ((__INSTANCE__) == UART_RXDMA6) || \
                                    ((__INSTANCE__) == UART_RXDMA7))
/******************************************************************************/
/*                        SPI module                                          */
/******************************************************************************/
#define SPI0_BASE      RF_GRP(91, 0)
#define SPI1_BASE      RF_GRP(489, 0)
#define SPI2_BASE      RF_GRP(492, 0)
#define SPI3_BASE      RF_GRP(495, 0)

#define SPI0        ((volatile SPI_TypeDef *)SPI0_BASE)
#define SPI1        ((volatile SPI_TypeDef *)SPI1_BASE)
#define SPI2        ((volatile SPI_TypeDef *)SPI2_BASE)
#define SPI3        ((volatile SPI_TypeDef *)SPI3_BASE)

#define CLK_DIVIDER(x)         (x<<16)
#define FINISH_FLAG_MASK       (1<<15)
#define RX_FULL_FLAG_MASK      (1<<14)
#define RX_EMP_FLAG_MASK       (1<<13)
#define TX_FULL_FLAG_MASK      (1<<12)
#define TX_EMP_FLAG_MASK       (1<<11)
#define WRITE_BYTE(x)          (x<<9)
#define READ_BYTE(x)           (x<<7)
#define FD_SEL                 (1<<6)
#define CS_SEL                 (1<<5)
#define LSB_SEL                (1<<4)
#define DELAY_ENABLE           (1<<3)
#define CPHA_W                 (1<<2)
#define CPHA_R                 (1<<1)
#define CPOL                   (1<<0)

#define CLEAR_MASTER_INT      (1<<6)

#define GET_LEN(x)            ((x>>24) & 0xFF)
#define GET_TX_LEN(x)         ((x>>16) & 0xFF)
#define GET_RX_CNT(x)         ((x>>12) & 0x0F)
#define GET_TX_CNT(x)         ((x>>8)  & 0x0F)

#define TOTAL_LENGTH(x)        (x<<24)
#define TX_LENGTH(x)           (x<<16)
#define RX_CNT                 (0x0F<<12)
#define TX_CNT                 (0x0F<<12)
#define SPI_BUSY               (1<<7)
#define FINISH_FLAG            (1<<6)
#define RX_FULL_FLAG           (1<<5)
#define RX_EMP_FLAG            (1<<4)
#define TX_FULL_FLAG           (1<<3)
#define TX_EMP_FLAG            (1<<2)
#define SPI_SW_RST             (1<<1)
#define SPI_START_FD           (1<<0)

#define SPI_TOTAL_SIZE         TOTAL_LENGTH(0xFF)
#define SPI_TX_SIZE            TX_LENGTH(0xFF)

/******************************************************************************/
/*                        I2C module                                          */
/******************************************************************************/
#define SP_I2CM0 	((volatile I2C_TypeDef *)RF_GRP(140, 0))
#define SP_I2CM1 	((volatile I2C_TypeDef *)RF_GRP(142, 0))
#define SP_I2CM2 	((volatile I2C_TypeDef *)RF_GRP(144, 0))
#define SP_I2CM3 	((volatile I2C_TypeDef *)RF_GRP(146, 0))
#define SP_I2CM4 	((volatile I2C_TypeDef *)RF_GRP(508, 0))
#define SP_I2CM5 	((volatile I2C_TypeDef *)RF_GRP(510, 0))

#define SP_GDMA0 	((volatile GDMA_TypeDef *)RF_GRP(141, 0))
#define SP_GDMA1 	((volatile GDMA_TypeDef *)RF_GRP(143, 0))
#define SP_GDMA2 	((volatile GDMA_TypeDef *)RF_GRP(145, 0))
#define SP_GDMA3 	((volatile GDMA_TypeDef *)RF_GRP(147, 0))
#define SP_GDMA4 	((volatile GDMA_TypeDef *)RF_GRP(509, 0))
#define SP_GDMA5 	((volatile GDMA_TypeDef *)RF_GRP(511, 0))
/******************************************************************************/
/*                                                                            */
/*                        gpio/pinmux define                                  */
/*                                                                            */
/******************************************************************************/
/* gpio register */


#define GPIO_I_PE(X)                 (RF_GRP_AO(102, (2+X)))
#define GPIO_I_PS(X)                 (RF_GRP_AO(102, (4+X)))
#define GPIO_I_SPU(X)                (RF_GRP_AO(102, (6+X)))
#define GPIO_I_PU(X)                 (RF_GRP_AO(102, (8+X)))
#define GPIO_I_PD(X)                 (RF_GRP_AO(102, (10+X)))
#define GPIO_O_DS(DS,X)              (RF_GRP_AO(101, (4+DS*4+X)))


#define GPIO_FIRST(X)                (RF_GRP_AO(101, (25+X)))
#define GPIO_MASTER(X)               (RF_GRP_AO(103, (0+X)))
#define GPIO_OE(X)                   (RF_GRP_AO(103, (13+X)))
#define GPIO_OUT(X)                  (RF_GRP_AO(103, (26+X)))
#define GPIO_IN(X)                   (RF_GRP_AO(104, (7+X)))
#define GPIO_I_INV(X)                (RF_GRP_AO(104, (15+X)))
#define GPIO_O_INV(X)                (RF_GRP_AO(104, (28+X)))
#define GPIO_OD(X)                   (RF_GRP_AO(105, (9+X)))

#define GPIO_MIN                     0
#define GPIO_MAX                     105

#define GPIO(X)                      (X)

#define IS_GPIO_PIN(pin)             (((pin) >= GPIO_MIN) && ((pin) <= GPIO_MAX))
#define IS_PINMUX_PIN(pin)           (((pin) >= GPIO_MIN) && ((pin) <= GPIO_MAX))
#define IS_VALID_PINMUX(pin)         (((pin) >= GPIO_MIN) && ((pin) <= GPIO_MAX))
#define GPIO_TO_PINMUX(x)            IS_PINMUX_PIN(x)?(x):-1




/******************************************************************************/
/*                                                                            */
/*                       IPC Mailbox  	                                      */
/*                                                                            */
/******************************************************************************/
/********************  Bit definition for IPC Mailbox register  ***************/


#define IS_IPCC_INSTANCE(INSTANCE)       (((INSTANCE) == IPC_MAILBOX))


#define NORMAL_LOCK_DATA0_Pos	(4)
#define NORMAL_LOCK_DATA0_Msk	(1<< NORMAL_LOCK_DATA0_Pos)
#define NORMAL_LOCK_DATA0		NORMAL_LOCK_DATA0_Msk

#define NORMAL_LOCK_DATA1_Pos	(5)
#define NORMAL_LOCK_DATA1_Msk	(1<< NORMAL_LOCK_DATA1_Pos)
#define NORMAL_LOCK_DATA1		NORMAL_LOCK_DATA1_Msk

#define NORMAL_LOCK_DATA2_Pos	(6)
#define NORMAL_LOCK_DATA2_Msk	(1<< NORMAL_LOCK_DATA2_Pos)
#define NORMAL_LOCK_DATA2		NORMAL_LOCK_DATA2_Msk

#define NORMAL_LOCK_DATA3_Pos	(7)
#define NORMAL_LOCK_DATA3_Msk	(1<< NORMAL_LOCK_DATA3_Pos)
#define NORMAL_LOCK_DATA3		NORMAL_LOCK_DATA3_Msk

#define NORMAL_LOCK_DATA4_Pos	(8)
#define NORMAL_LOCK_DATA4_Msk	(1<< NORMAL_LOCK_DATA4_Pos)
#define NORMAL_LOCK_DATA4		NORMAL_LOCK_DATA4_Msk

#define NORMAL_LOCK_DATA5_Pos	(9)
#define NORMAL_LOCK_DATA5_Msk	(1<< NORMAL_LOCK_DATA5_Pos)
#define NORMAL_LOCK_DATA5		NORMAL_LOCK_DATA5_Msk

#define NORMAL_LOCK_DATA6_Pos	(10)
#define NORMAL_LOCK_DATA6_Msk	(1<< NORMAL_LOCK_DATA6_Pos)
#define NORMAL_LOCK_DATA6		NORMAL_LOCK_DATA6_Msk

#define NORMAL_LOCK_DATA7_Pos	(11)
#define NORMAL_LOCK_DATA7_Msk	(1<< NORMAL_LOCK_DATA7_Pos)
#define NORMAL_LOCK_DATA7		NORMAL_LOCK_DATA7_Msk

#define NORMAL_LOCK_DATA8_Pos	(12)
#define NORMAL_LOCK_DATA8_Msk	(1<< NORMAL_LOCK_DATA8_Pos)
#define NORMAL_LOCK_DATA8		NORMAL_LOCK_DATA8_Msk

#define NORMAL_LOCK_DATA9_Pos	(13)
#define NORMAL_LOCK_DATA9_Msk	(1<< NORMAL_LOCK_DATA9_Pos)
#define NORMAL_LOCK_DATA9		NORMAL_LOCK_DATA9_Msk

#define NORMAL_LOCK_DATA10_Pos	(14)
#define NORMAL_LOCK_DATA10_Msk	(1<< NORMAL_LOCK_DATA10_Pos)
#define NORMAL_LOCK_DATA10		NORMAL_LOCK_DATA10_Msk

#define NORMAL_LOCK_DATA11_Pos	(15)
#define NORMAL_LOCK_DATA11_Msk	(1<< NORMAL_LOCK_DATA11_Pos)
#define NORMAL_LOCK_DATA11		NORMAL_LOCK_DATA11_Msk

#define NORMAL_LOCK_DATA12_Pos	(16)
#define NORMAL_LOCK_DATA12_Msk	(1<< NORMAL_LOCK_DATA12_Pos)
#define NORMAL_LOCK_DATA12		NORMAL_LOCK_DATA12_Msk

#define NORMAL_LOCK_DATA13_Pos	(17)
#define NORMAL_LOCK_DATA13_Msk	(1<< NORMAL_LOCK_DATA13_Pos)
#define NORMAL_LOCK_DATA13		NORMAL_LOCK_DATA13_Msk

#define NORMAL_LOCK_DATA14_Pos	(18)
#define NORMAL_LOCK_DATA14_Msk	(1<< NORMAL_LOCK_DATA14_Pos)
#define NORMAL_LOCK_DATA14		NORMAL_LOCK_DATA14_Msk

#define NORMAL_LOCK_DATA15_Pos	(19)
#define NORMAL_LOCK_DATA15_Msk	(1<< NORMAL_LOCK_DATA15_Pos)
#define NORMAL_LOCK_DATA15		NORMAL_LOCK_DATA15_Msk

#define NORMAL_LOCK_DATA16_Pos	(20)
#define NORMAL_LOCK_DATA16_Msk	(1<< NORMAL_LOCK_DATA16_Pos)
#define NORMAL_LOCK_DATA16		NORMAL_LOCK_DATA16_Msk

#define NORMAL_LOCK_DATA17_Pos	(21)
#define NORMAL_LOCK_DATA17_Msk	(1<< NORMAL_LOCK_DATA17_Pos)
#define NORMAL_LOCK_DATA17		NORMAL_LOCK_DATA17_Msk

#define NORMAL_LOCK_DATA18_Pos	(22)
#define NORMAL_LOCK_DATA18_Msk	(1<< NORMAL_LOCK_DATA18_Pos)
#define NORMAL_LOCK_DATA18		NORMAL_LOCK_DATA18_Msk

#define NORMAL_LOCK_DATA19_Pos	(23)
#define NORMAL_LOCK_DATA19_Msk	(1<< NORMAL_LOCK_DATA19_Pos)
#define NORMAL_LOCK_DATA19		NORMAL_LOCK_DATA19_Msk


#define DIRECT_LOCK_DATA0_Pos	(24)
#define DIRECT_LOCK_DATA0_Msk	(1<< DIRECT_LOCK_DATA0_Pos)
#define DIRECT_LOCK_DATA0		DIRECT_LOCK_DATA0_Msk

#define DIRECT_LOCK_DATA1_Pos	(25)
#define DIRECT_LOCK_DATA1_Msk	(1<< DIRECT_LOCK_DATA1_Pos)
#define DIRECT_LOCK_DATA1		DIRECT_LOCK_DATA1_Msk

#define DIRECT_LOCK_DATA2_Pos	(26)
#define DIRECT_LOCK_DATA2_Msk	(1<< DIRECT_LOCK_DATA2_Pos)
#define DIRECT_LOCK_DATA2		DIRECT_LOCK_DATA2_Msk

#define DIRECT_LOCK_DATA3_Pos	(27)
#define DIRECT_LOCK_DATA3_Msk	(1<< DIRECT_LOCK_DATA3_Pos)
#define DIRECT_LOCK_DATA3		DIRECT_LOCK_DATA3_Msk

#define DIRECT_LOCK_DATA4_Pos	(28)
#define DIRECT_LOCK_DATA4_Msk	(1<< DIRECT_LOCK_DATA4_Pos)
#define DIRECT_LOCK_DATA4		DIRECT_LOCK_DATA4_Msk

#define DIRECT_LOCK_DATA5_Pos	(29)
#define DIRECT_LOCK_DATA5_Msk	(1<< DIRECT_LOCK_DATA5_Pos)
#define DIRECT_LOCK_DATA5		DIRECT_LOCK_DATA5_Msk

#define DIRECT_LOCK_DATA6_Pos	(30)
#define DIRECT_LOCK_DATA6_Msk	(1<< DIRECT_LOCK_DATA6_Pos)
#define DIRECT_LOCK_DATA6		DIRECT_LOCK_DATA6_Msk

#define DIRECT_LOCK_DATA7_Pos	(31)
#define DIRECT_LOCK_DATA7_Msk	(1<< DIRECT_LOCK_DATA7_Pos)
#define DIRECT_LOCK_DATA7		DIRECT_LOCK_DATA7_Msk

#define NORMAL_OVERWRITE_DATA0_Pos	(4)
#define NORMAL_OVERWRITE_DATA0_Msk	(1<< NORMAL_OVERWRITE_DATA0_Pos)
#define NORMAL_OVERWRITE_DATA0		NORMAL_LOCK_DATA0_Msk

#define NORMAL_OVERWRITE_DATA1_Pos	(5)
#define NORMAL_OVERWRITE_DATA1_Msk	(1<< NORMAL_OVERWRITE_DATA1_Pos)
#define NORMAL_OVERWRITE_DATA1		NORMAL_LOCK_DATA1_Msk

#define NORMAL_OVERWRITE_DATA2_Pos	(6)
#define NORMAL_OVERWRITE_DATA2_Msk	(1<< NORMAL_OVERWRITE_DATA2_Pos)
#define NORMAL_OVERWRITE_DATA2		NORMAL_LOCK_DATA2_Msk

#define NORMAL_OVERWRITE_DATA3_Pos	(7)
#define NORMAL_OVERWRITE_DATA3_Msk	(1<< NORMAL_OVERWRITE_DATA3_Pos)
#define NORMAL_OVERWRITE_DATA3		NORMAL_LOCK_DATA3_Msk

#define NORMAL_OVERWRITE_DATA4_Pos	(8)
#define NORMAL_OVERWRITE_DATA4_Msk	(1<< NORMAL_OVERWRITE_DATA4_Pos)
#define NORMAL_OVERWRITE_DATA4		NORMAL_LOCK_DATA4_Msk

#define NORMAL_OVERWRITE_DATA5_Pos	(9)
#define NORMAL_OVERWRITE_DATA5_Msk	(1<< NORMAL_OVERWRITE_DATA5_Pos)
#define NORMAL_OVERWRITE_DATA5		NORMAL_LOCK_DATA5_Msk

#define NORMAL_OVERWRITE_DATA6_Pos	(10)
#define NORMAL_OVERWRITE_DATA6_Msk	(1<< NORMAL_OVERWRITE_DATA6_Pos)
#define NORMAL_OVERWRITE_DATA6		NORMAL_LOCK_DATA6_Msk

#define NORMAL_OVERWRITE_DATA7_Pos	(11)
#define NORMAL_OVERWRITE_DATA7_Msk	(1<< NORMAL_OVERWRITE_DATA7_Pos)
#define NORMAL_OVERWRITE_DATA7		NORMAL_LOCK_DATA7_Msk

#define NORMAL_OVERWRITE_DATA8_Pos	(12)
#define NORMAL_OVERWRITE_DATA8_Msk	(1<< NORMAL_OVERWRITE_DATA8_Pos)
#define NORMAL_OVERWRITE_DATA8		NORMAL_LOCK_DATA8_Msk

#define NORMAL_OVERWRITE_DATA9_Pos	(13)
#define NORMAL_OVERWRITE_DATA9_Msk	(1<< NORMAL_OVERWRITE_DATA9_Pos)
#define NORMAL_OVERWRITE_DATA9		NORMAL_LOCK_DATA9_Msk

#define NORMAL_OVERWRITE_DATA10_Pos	(14)
#define NORMAL_OVERWRITE_DATA10_Msk	(1<< NORMAL_OVERWRITE_DATA10_Pos)
#define NORMAL_OVERWRITE_DATA10		NORMAL_LOCK_DATA10_Msk

#define NORMAL_OVERWRITE_DATA11_Pos	(15)
#define NORMAL_OVERWRITE_DATA11_Msk	(1<< NORMAL_OVERWRITE_DATA11_Pos)
#define NORMAL_OVERWRITE_DATA11		NORMAL_LOCK_DATA11_Msk

#define NORMAL_OVERWRITE_DATA12_Pos	(16)
#define NORMAL_OVERWRITE_DATA12_Msk	(1<< NORMAL_OVERWRITE_DATA12_Pos)
#define NORMAL_OVERWRITE_DATA12		NORMAL_LOCK_DATA12_Msk

#define NORMAL_OVERWRITE_DATA13_Pos	(17)
#define NORMAL_OVERWRITE_DATA13_Msk	(1<< NORMAL_OVERWRITE_DATA13_Pos)
#define NORMAL_OVERWRITE_DATA13		NORMAL_LOCK_DATA13_Msk

#define NORMAL_OVERWRITE_DATA14_Pos	(18)
#define NORMAL_OVERWRITE_DATA14_Msk	(1<< NORMAL_OVERWRITE_DATA14_Pos)
#define NORMAL_OVERWRITE_DATA14		NORMAL_LOCK_DATA14_Msk

#define NORMAL_OVERWRITE_DATA15_Pos	(19)
#define NORMAL_OVERWRITE_DATA15_Msk	(1<< NORMAL_OVERWRITE_DATA15_Pos)
#define NORMAL_OVERWRITE_DATA15		NORMAL_LOCK_DATA15_Msk

#define NORMAL_OVERWRITE_DATA16_Pos	(20)
#define NORMAL_OVERWRITE_DATA16_Msk	(1<< NORMAL_OVERWRITE_DATA16_Pos)
#define NORMAL_OVERWRITE_DATA16		NORMAL_LOCK_DATA16_Msk

#define NORMAL_OVERWRITE_DATA17_Pos	(21)
#define NORMAL_OVERWRITE_DATA17_Msk	(1<< NORMAL_OVERWRITE_DATA17_Pos)
#define NORMAL_OVERWRITE_DATA17		NORMAL_LOCK_DATA17_Msk

#define NORMAL_OVERWRITE_DATA18_Pos	(22)
#define NORMAL_OVERWRITE_DATA18_Msk	(1<< NORMAL_OVERWRITE_DATA18_Pos)
#define NORMAL_OVERWRITE_DATA18		NORMAL_LOCK_DATA18_Msk

#define NORMAL_OVERWRITE_DATA19_Pos	(23)
#define NORMAL_OVERWRITE_DATA19_Msk	(1<< NORMAL_OVERWRITE_DATA19_Pos)
#define NORMAL_OVERWRITE_DATA19		NORMAL_LOCK_DATA19_Msk


#define DIRECT_OVERWITE_DATA0_Pos	(24)
#define DIRECT_OVERWITE_DATA0_Msk	(1<< DIRECT_OVERWITE_DATA0_Pos)
#define DIRECT_OVERWITE_DATA0		DIRECT_OVERWITE_DATA0_Msk

#define DIRECT_OVERWITE_DATA1_Pos	(25)
#define DIRECT_OVERWITE_DATA1_Msk	(1<< DIRECT_OVERWITE_DATA1_Pos)
#define DIRECT_OVERWITE_DATA1		DIRECT_OVERWITE_DATA1_Msk

#define DIRECT_OVERWITE_DATA2_Pos	(26)
#define DIRECT_OVERWITE_DATA2_Msk	(1<< DIRECT_OVERWITE_DATA2_Pos)
#define DIRECT_OVERWITE_DATA2		DIRECT_OVERWITE_DATA2_Msk

#define DIRECT_OVERWITE_DATA3_Pos	(27)
#define DIRECT_OVERWITE_DATA3_Msk	(1<< DIRECT_OVERWITE_DATA3_Pos)
#define DIRECT_OVERWITE_DATA3		DIRECT_OVERWITE_DATA3_Msk

#define DIRECT_OVERWITE_DATA4_Pos	(28)
#define DIRECT_OVERWITE_DATA4_Msk	(1<< DIRECT_OVERWITE_DATA4_Pos)
#define DIRECT_OVERWITE_DATA4		DIRECT_OVERWITE_DATA4_Msk

#define DIRECT_OVERWITE_DATA5_Pos	(29)
#define DIRECT_OVERWITE_DATA5_Msk	(1<< DIRECT_OVERWITE_DATA5_Pos)
#define DIRECT_OVERWITE_DATA5		DIRECT_OVERWITE_DATA5_Msk

#define DIRECT_OVERWITE_DATA6_Pos	(30)
#define DIRECT_OVERWITE_DATA6_Msk	(1<< DIRECT_OVERWITE_DATA6_Pos)
#define DIRECT_OVERWITE_DATA6		DIRECT_OVERWITE_DATA6_Msk

#define DIRECT_OVERWITE_DATA7_Pos	(31)
#define DIRECT_OVERWITE_DATA7_Msk	(1<< DIRECT_OVERWITE_DATA7_Pos)
#define DIRECT_OVERWITE_DATA7		DIRECT_OVERWITE_DATA7_Msk


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined ( __CC_ARM   )
  #pragma push
#pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif

#ifdef __cplusplus
}
#endif

#endif


