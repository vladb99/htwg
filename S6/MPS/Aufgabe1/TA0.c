/*
 * TA0.c
 *
 *  Created on: 22.04.2018
 *      Author: Admin
 */

#include <msp430.h>
#include "../base.h"
#include "TA0.h"
#include "event.h"
#include "GPIO.h"

#define MAX 4

/*
 * Man soll sich eine geeignete Datenstruktur �berlegen,
 * die eine laufzeiteffiziente Ausf�hrung der ISR erm�glicht.
 */

GLOBAL Void set_blink_muster(UInt arg) {
/*
 * Die Funktion muss so erweitert werden,
 * dass ein Blinkmuster selektiert wird.
 * Diese L�sung h�ngt stark von der gew�hlten
 * Datenstruktur ab.
 */
}

// Der Timer A0 ist bereits initialisiert
GLOBAL Void TA0_Init(Void) {
   TA0CCR0 = 0;                              // stopp Timer A
   CLRBIT(TA0CTL, TAIFG);                    // clear overflow flag
   CLRBIT(TA0CCR0, CCIFG);                   // clear CCI flag
   TA0CTL  = TASSEL__ACLK + MC__UP + ID__8;  // set up Timer A
   TA0EX0  = TAIDEX_7;                       // set up expansion register
   TA0CCR0 = 2*48;                           // set up CCR0 for 10 ms
   SETBIT(TA0CTL, TACLR);                    // clear and start Timer
   SETBIT(TA0CCTL0, CCIE);                   // enable Timer A interrupt
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt Void TA0_ISR(Void) {
    static volatile Bool is_s1_btn1 = FALSE;
    static volatile Bool is_s1_btn2 = FALSE;
    static volatile UInt cnt_btn1 = 0;
    static volatile UInt cnt_btn2 = 0;

    // Entprellen Button 1
    if (TSTBIT(P1IN, BIT1)) {
        if (!is_s1_btn1) {
            if (cnt_btn1 < MAX - 1) {
                cnt_btn1++;
            } else if (cnt_btn1 == MAX - 1) {
                is_s1_btn1 = TRUE;
                // Toggle
                set_event(EVENT_BTN1);
                __low_power_mode_off_on_exit();
            }
        } else if (cnt_btn1 < MAX - 1) {
            cnt_btn1++;
        }
    } else {
        if (!is_s1_btn1 && cnt_btn1 > 0) {
            cnt_btn1--;
        } else {
            if (cnt_btn1 > 0) {
                cnt_btn1--;
            } else if (cnt_btn1 == 0) {
                is_s1_btn1 = FALSE;
            }
        }
    }

    // Entprellen Button 2
    if (TSTBIT(P1IN, BIT0)) {
        if (!is_s1_btn2) {
            if (cnt_btn2 < MAX - 1) {
                cnt_btn2++;
            } else if (cnt_btn2 == MAX - 1) {
                is_s1_btn2 = TRUE;
                // Blinkmuster wechseln
                set_event(EVENT_BTN2);
                __low_power_mode_off_on_exit();
            }
        } else if (cnt_btn2 < MAX - 1) {
            cnt_btn2++;
        }
    } else {
        if (!is_s1_btn2 && cnt_btn2 > 0) {
            cnt_btn2--;
        } else {
            if (cnt_btn2 > 0) {
                cnt_btn2--;
            } else if (cnt_btn2 == 0) {
                is_s1_btn2 = FALSE;
            }
        }
    }
}
