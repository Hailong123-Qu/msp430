// Copyright (C) [2013] [AB2 Technologies] [Austin Beam, Alan Bullick]
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

// MSP430F5510 ISR Dispatcher
// Manage all device ISRs centrally. Allow installation of callbacks as ISRs in
// order to allow dynamic allocation of each interrupt vector. This ensures the
// most efficient use of interrupt vectors and also helps make libraries be
// configuration-independent.
#pragma once
#define AB2_ISR_D

#include <msp430f5510.h>
#include "msp/ab2.h"
#include "pin_fw.h"
#include "timerA_fw.h"

// Definitions that can be used to disable dispatching for various interrupts
// #define DISABLE_RTC_ID
// #define DISABLE_PORT2_ID
// #define DISABLE_TA2_1_ID
// #define DISABLE_TA2_0_ID
// #define DISABLE_USCI_B1_ID
// #define DISABLE_USCI_A1_ID
// #define DISABLE_PORT1_ID
// #define DISABLE_TA1_1_ID
// #define DISABLE_TA1_0_ID
// #define DISABLE_DMA_ID
// #define DISABLE_USB_UBM_ID
// #define DISABLE_TA0_1_ID
// #define DISABLE_ADC10_ID
// #define DISABLE_USCI_B0_ID
// #define DISABLE_USCI_A0_ID
// #define DISABLE_TB0_1_ID
// #define DISABLE_TB0_0_ID
// #define DISABLE_COMP_B_ID
// #define DISABLE_UNMI_ID
// #define DISABLE_SYSNMI_ID

// The following interrupt vectors are allocated to the clock library that is
// always used with AB2 components. Since these have no need to be dynamically
// allocated, they are not enabled by default. Fully enabling support for these
// vectors will require definition of both the corresponding ID and VECTOR
// for that vector.
// #define ENABLE_TA0_0_ID
// #define ENABLE_WDT_ID

// The reset vector is disabled by default from the ISR dispatcher. The
// following definition will enable it (though it's likely not useful).
// #define ENABLE_RESET_ID

// Definition of the above will disable dispatching, but will still result in a
// default handler being created for that interrupt. To disable both
// dispatching and default handling of a given interrupt, use the following
// definitions instead:
// #define DISABLE_RTC_VECTOR
// #define DISABLE_PORT2_VECTOR
// #define DISABLE_TA2_1_VECTOR
// #define DISABLE_TA2_0_VECTOR
// #define DISABLE_USCI_B1_VECTOR
// #define DISABLE_USCI_A1_VECTOR
// #define DISABLE_PORT1_VECTOR
// #define DISABLE_TA1_1_VECTOR
// #define DISABLE_TA1_0_VECTOR
// #define DISABLE_DMA_VECTOR
// #define DISABLE_USB_UBM_VECTOR
// #define DISABLE_TA0_1_VECTOR
// #define DISABLE_ADC10_VECTOR
// #define DISABLE_USCI_B0_VECTOR
// #define DISABLE_USCI_A0_VECTOR
// #define DISABLE_TB0_1_VECTOR
// #define DISABLE_TB0_0_VECTOR
// #define DISABLE_COMP_B_VECTOR
// #define DISABLE_UNMI_VECTOR
// #define DISABLE_SYSNMI_VECTOR

// The following interrupt vectors are allocated to the clock library that is
// always used with AB2 components. Since these have no need to be dynamically
// allocated, they are not enabled by default. Fully enabling support for these
// vectors will require definition of both the corresponding ID and VECTOR
// for that vector.
// #define ENABLE_TA0_0_VECTOR
// #define ENABLE_WDT_VECTOR

// Since a default RESET handler is already installed, the ISR dispatcher won't
// (and shouldn't) install one

// Define a type that should be used to specify the return type of an ISR that
// will be dispatched by the ISR dispatcher. Primary objective of this is to
// ensure the callback has taken into account the requirements of the ISR
// dispatcher.
typedef void isr_t;

typedef enum
{
#if !defined(DISABLE_RTC_VECTOR) && !defined(DISABLE_RTC_ID)
  RTC_ID,          // RTC_VECTOR
#endif

#if !defined(DISABLE_PORT2_VECTOR) && !defined(DISABLE_PORT2_ID)
#ifdef MSP430F5510_EXT
  PORT2_7_ID,
  PORT2_6_ID,
  PORT2_5_ID,
  PORT2_4_ID,
  PORT2_3_ID,
  PORT2_2_ID,
  PORT2_1_ID,
#endif
  PORT2_0_ID,      // PORT2_VECTOR
#endif

#if !defined(DISABLE_TA2_1_VECTOR) && !defined(DISABLE_TA2_1_ID)
  TA2_IFG_ID,
  TA2_2_ID,
  TA2_1_ID,        // TIMER2_A1_VECTOR
#endif

#if !defined(DISABLE_TA2_0_VECTOR) && !defined(DISABLE_TA2_0_ID)
  TA2_0_ID,        // TIMER2_A0_VECTOR
#endif

#if !defined(DISABLE_USCI_B1_VECTOR) && !defined(DISABLE_USCI_B1_ID)
  USCI_B1_ID,      // USCI_B1_VECTOR
#endif

#if !defined(DISABLE_USCI_A1_VECTOR) && !defined(DISABLE_USCI_A1_ID)
  USCI_A1_ID,      // USCI_A1_VECTOR
#endif

#if !defined(DISABLE_PORT1_VECTOR) && !defined(DISABLE_PORT1_ID)
  PORT1_7_ID,
  PORT1_6_ID,
  PORT1_5_ID,
  PORT1_4_ID,
  PORT1_3_ID,
  PORT1_2_ID,
  PORT1_1_ID,
  PORT1_0_ID,      // PORT1_VECTOR
#endif

#if !defined(DISABLE_TA1_1_VECTOR) && !defined(DISABLE_TA1_1_ID)
  TA1_IFG_ID,
  TA1_2_ID,
  TA1_1_ID,        // TIMER1_A1_VECTOR
#endif

#if !defined(DISABLE_TA1_0_VECTOR) && !defined(DISABLE_TA1_0_ID)
  TA1_0_ID,        // TIMER1_A0_VECTOR
#endif

#if !defined(DISABLE_DMA_VECTOR) && !defined(DISABLE_DMA_ID)
  DMA_ID,          // DMA_VECTOR
#endif

#if !defined(DISABLE_USB_UBM_VECTOR) && !defined(DISABLE_USB_UBM_ID)
  USB_UBM_ID,      // USB_UBM_VECTOR
#endif

#if !defined(DISABLE_TA0_1_VECTOR) && !defined(DISABLE_TA0_1_ID)
  TA0_IFG_ID,
  TA0_4_ID,
  TA0_3_ID,
  TA0_2_ID,
  TA0_1_ID,        // TIMER0_A1_VECTOR
#endif

#if defined(ENABLE_TA0_0_VECTOR) || defined(ENABLE_TA0_0_ID)
  TA0_0_ID,        // TIMER0_A0_VECTOR
#endif

#if !defined(DISABLE_ADC10_VECTOR) && !defined(DISABLE_ADC10_ID)
  ADC10_ID,        // ADC10_VECTOR
#endif

#if !defined(DISABLE_USCI_B0_VECTOR) && !defined(DISABLE_USCI_B0_ID)
  USCI_B0_ID,      // USCI_B0_VECTOR
#endif

#if !defined(DISABLE_USCI_A0_VECTOR) && !defined(DISABLE_USCI_A0_ID)
  USCI_A0_ID,      // USCI_A0_VECTOR
#endif

#if defined(ENABLE_WDT_VECTOR) || defined(ENABLE_WDT_ID)
  WDT_ID,          // WDT_VECTOR
#endif

#if !defined(DISABLE_TB0_1_VECTOR) && !defined(DISABLE_TB0_1_ID)
  TB0_IFG_ID,
  TB0_6_ID,
  TB0_5_ID,
  TB0_4_ID,
  TB0_3_ID,
  TB0_2_ID,
  TB0_1_ID,        // TIMER0_B1_VECTOR
#endif

#if !defined(DISABLE_TB0_0_VECTOR) && !defined(DISABLE_TB0_0_ID)
  TB0_0_ID,        // TIMER0_B0_VECTOR
#endif

#if !defined(DISABLE_COMP_B_VECTOR) && !defined(DISABLE_COMP_B_ID)
  COMP_B_ID,       // COMP_B_VECTOR
#endif

#if !defined(DISABLE_UNMI_VECTOR) && !defined(DISABLE_UNMI_ID)
  UNMI_ID,         // UNMI_VECTOR
#endif

#if !defined(DISABLE_SYSNMI_VECTOR) && !defined(DISABLE_SYSNMI_ID)
  SYSNMI_ID,       // SYSNMI_VECTOR
#endif

#ifdef ENABLE_RESET_ID
  RESET_ID,        // RESET_VECTOR
#endif

  NUM_ISR_VECTORS
} isr_vector_t;

// All members are static since this is a single-object instance class
class isr_d
{
public:
  // Emulate the compiler intrinsics by allowing installed ISRs to modify the
  // SR register on exit
#ifdef ENABLE_SR_CHECKING
  static void clr_sr_on_exit(uint16_t mask);
  static void set_sr_on_exit(uint16_t mask);
#endif
  // Install ISR -- callback method must be static if a class member, or else a
  // non-member function.
  //
  // The callback should return void and take a single parameter. For static
  // member wrapper functions, this will be a pointer to the object for which
  // the callback should reference. Otherwise, it should be ignored in the
  // context of the callback.
  //
  // If the desired function to be called is a non-static class member, the
  // callback must be a static wrapper around a non-static call which passes
  // the object ("this" pointer of arbitrary type) as a parameter. If it is a
  // static wrapper of a non-static function, the static wrapper must cast the
  // object pointer to the proper type. The reason for this limitation is due
  // to the structure of static versus non-static function calls and the
  // dependency of various callbacks on their respective object.
  static void install(isr_vector_t vect,
      void *pObject, isr_t (*pCallback)(void* pObj));

  // Return the Pin interrupt vector corresponding to the given pin
  static isr_vector_t pinVector(msp_pin_t pin);

  // Return the TA interrupt vector corresponding to the given timer
  static isr_vector_t taVector(msp_timerA_t timer);

  // Uninstall ISR -- remove installed ISR for a given ISR vector
  static void uninstall(isr_vector_t vect);

private:
  // We need to check for any potential SR changes before exiting each ISR.
  // This will unfortunately add some additional latency, but it's the only way
  // to allow callbacks to modify the SR (for example, exiting from LPM). Since
  // the SR _on_exit intrinsics must be called from a fully qualified ISR, not
  // even an inlined function can be used for this purpose. Thus, code
  // duplication will result. Also adding a compilation flag to disable all SR
  // handling by the ISR dispatcher since it adds substantial code size and
  // lower latency might be prioritized in some situations.
#ifdef ENABLE_SR_CHECKING
  static bool     clr_sr;
  static bool     set_sr;
  static uint16_t clr_sr_bits;
  static uint16_t set_sr_bits;
#endif

  static isr_t  defaultHandler(void *pObj);
  static isr_t (*isr[NUM_ISR_VECTORS])(void *);
  static void  (*obj[NUM_ISR_VECTORS]);

#ifndef DISABLE_RTC_VECTOR
  static void __interrupt isrRTC(void);
#endif
#ifndef DISABLE_PORT2_VECTOR
  static void __interrupt isrPORT2(void);
#endif
#ifndef DISABLE_TA2_1_VECTOR
  static void __interrupt isrTA2_1(void);
#endif
#ifndef DISABLE_TA2_0_VECTOR
  static void __interrupt isrTA2_0(void);
#endif
#ifndef DISABLE_USCI_B1_VECTOR
  static void __interrupt isrUSCI_B1(void);
#endif
#ifndef DISABLE_USCI_A1_VECTOR
  static void __interrupt isrUSCI_A1(void);
#endif
#ifndef DISABLE_PORT1_VECTOR
  static void __interrupt isrPORT1(void);
#endif
#ifndef DISABLE_TA1_1_VECTOR
  static void __interrupt isrTA1_1(void);
#endif
#ifndef DISABLE_TA1_0_VECTOR
  static void __interrupt isrTA1_0(void);
#endif
#ifndef DISABLE_DMA_VECTOR
  static void __interrupt isrDMA(void);
#endif
#ifndef DISABLE_USB_UBM_VECTOR
  static void __interrupt isrUSB_UBM(void);
#endif
#ifndef DISABLE_TA0_1_VECTOR
  static void __interrupt isrTA0_1(void);
#endif
#ifdef ENABLE_TA0_0_VECTOR
  static void __interrupt isrTA0_0(void);
#endif
#ifndef DISABLE_ADC10_VECTOR
  static void __interrupt isrADC10(void);
#endif
#ifndef DISABLE_USCI_B0_VECTOR
  static void __interrupt isrUSCI_B0(void);
#endif
#ifndef DISABLE_USCI_A0_VECTOR
  static void __interrupt isrUSCI_A0(void);
#endif
#ifdef ENABLE_WDT_VECTOR
  static void __interrupt isrWDT(void);
#endif
#ifndef DISABLE_TB0_1_VECTOR
  static void __interrupt isrTB0_1(void);
#endif
#ifndef DISABLE_TB0_0_VECTOR
  static void __interrupt isrTB0_0(void);
#endif
#ifndef DISABLE_COMP_B_VECTOR
  static void __interrupt isrCOMP_B(void);
#endif
#ifndef DISABLE_UNMI_VECTOR
  static void __interrupt isrUNMI(void);
#endif
#ifndef DISABLE_SYSNMI_VECTOR
  static void __interrupt isrSYSNMI(void);
#endif
#ifdef ENABLE_RESET_ID
  static void __interrupt isrRESET(void);
#endif
};
