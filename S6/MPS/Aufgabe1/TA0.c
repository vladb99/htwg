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
#define TIMER_COUNT 25

/*
 * Man soll sich eine geeignete Datenstruktur �berlegen,
 * die eine laufzeiteffiziente Ausf�hrung der ISR erm�glicht.
 */

// 10ms Schritte
static const Char MUSTER_1[] = {8, 2, 0};
static const Char MUSTER_2[] = {3, 3, 0};
static const Char MUSTER_3[] = {1, 1, 0};
static const Char MUSTER_4[] = {2, 8, 0};
static const Char MUSTER_5[] = {2, 2, 2, 8, 0};
static const Char MUSTER_6[] = {2, 2, 2, 2, 2, 8, 0};
static const Char* P[] = {MUSTER_1, MUSTER_2, MUSTER_3, MUSTER_4, MUSTER_5, MUSTER_6};

static Bool is_s1_btn1;
static Bool is_s1_btn2;
static UChar cnt_btn1;
static UChar cnt_btn2;
static UChar step_count;
static UChar array_index;
static UChar cnt_led;
static UChar pattern_index;
static UChar current_pattern_value;
static UChar pattern_index_new;

GLOBAL Void set_blink_muster(UInt arg) {
/*
 * Die Funktion muss so erweitert werden,
 * dass ein Blinkmuster selektiert wird.
 * Diese L�sung h�ngt stark von der gew�hlten
 * Datenstruktur ab.
 */
    pattern_index_new = arg;
}

// Der Timer A0 ist bereits initialisiert
GLOBAL Void TA0_Init(Void) {
    is_s1_btn1 = FALSE;
    is_s1_btn2 = FALSE;
    cnt_btn1 = 0;
    cnt_btn2 = 0;
    step_count = TIMER_COUNT;
    array_index = 0;
    cnt_led = 0;
    pattern_index = 0;
    current_pattern_value = 0;
    pattern_index_new = 0;

    TA0CCR0 = 0;                              // stopp Timer A
    CLRBIT(TA0CTL, TAIFG);                    // clear overflow flag
    CLRBIT(TA0CCR0, CCIFG);                   // clear CCI flag
    TA0CTL  = TASSEL__ACLK + MC__UP + ID__8;  // set up Timer A
    TA0EX0  = TAIDEX_7;                       // set up expansion register
    TA0CCR0 = 2*48;                           // set up CCR0 for 10 ms
    SETBIT(TA0CTL, TACLR);                    // clear and start Timer
    SETBIT(TA0CCTL0, CCIE);                   // enable Timer A interrupt

    // Set LED2 once
    SETBIT(P1OUT, BIT2);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt Void TA0_ISR(Void) {
    //static volatile Int test = 0;
    // Timer logic for 250ms step
    if (--step_count EQ 0) {
        //test = sizeof(MUSTER_1);
        step_count = TIMER_COUNT;
        current_pattern_value = P[pattern_index][array_index];
        cnt_led++;

        // LED2 Flash logic
        if (cnt_led EQ current_pattern_value) {
            TGLBIT(P1OUT, BIT2);
            array_index++;
            cnt_led = 0;
            if (P[pattern_index][array_index] EQ 0) {
                array_index = 0;
                pattern_index = pattern_index_new;
            }
        }
    }

    // Debouncing BTN1
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

    // Debouncing BTN2
    if (TSTBIT(P1IN, BIT0)) {
        if (!is_s1_btn2) {
            if (cnt_btn2 < MAX - 1) {
                cnt_btn2++;
            } else if (cnt_btn2 == MAX - 1) {
                is_s1_btn2 = TRUE;
                // Change flash pattern
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
