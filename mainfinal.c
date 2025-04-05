/* 
 * File:   mainfinal.c
 * Author: kguerns
 *
 * Created on November 30, 2023, 7:22 PM
 */

#include <xc.h>
#include <sys/attribs.h>

//This is here to make timing calculations easier!
#pragma config FPBDIV = DIV_2

//r is a Rest.  If r, do not toggle! (don't want noise to play) 
#define r 3000 
#define a 4545 
#define b 4050 
#define C 3817 
#define C_ 3610 
#define D 3402 
#define D_ 3216 
#define E 3031 
#define F 2866 
#define F_ 2703 
#define G 2551 
#define G_ 2410 
#define A 2273 
#define A_ 2146 
#define B 2025 
#define CC 1911 
#define q 3000 
#define qdot q * 1.5 
#define e q/2
#define s e/2 
#define t32 s/2 
#define sdot s+t32 
#define h q*2
#define hdot q+e
#define edot e+s
#define num_notes 52 

int i,j;

short delay[num_notes] = {t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,t32, 
							  t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,t32}; 
 

short music_notes[num_notes] = {C,C,D,C,F,E,C,C,D,C,G,F,
                                C,C,C_,A,G,E,D,A_,A_,A,F,
                                G,F};

//Interrupt Function
void __ISR(12) BuzzerInterrupt(void) {
    PR2 = music_notes[i];       // Set music note
    j++;
    if (music_notes[j] != r) {
        LATBbits.LATB0 ^= 1;    // Toggle output
    }
    IFS0bits.T3IF = 0;    // Clear flag in IFS0 register
}

main()
{
    //Setup Timers/Interrupts
    T2CONbits.ON = 0;           // Disable Timer 2
    T2CONbits.T32 = 1;          // 32-bit Timer
    T2CONbits.TCS = 0;          // Clock Source: Internal peripheral clock
    T2CONbits.TCKPS = 0;        // 1:1 Prescale Value
    
    IEC0bits.T3IE = 0;          // Disable
    IFS0bits.T3IF = 0;          // Clear flag?
    IPC3bits.T3IP = 1;          // Priority
    IEC0bits.T3IE = 1;          // Enable
    
    T2CONbits.ON = 1;           // Enable Timer 2
    TMR2 = 0;                   // Start timer at zero?
    PR2 = C;                    // Set first note to C
    
    INTCONbits.MVEC = 1;        // Multi-vectored mode
    __builtin_enable_interrupts();
    
    CFGCONbits.JTAGEN = 0;      // Disable JTAG
    TRISBbits.TRISB0 = 0;       // Set B0 to output
    ANSELBbits.ANSB0 = 0;       // Set B0 to digital pin
    LATBbits.LATB0 = 0;         // Set value of B0 to 0
    
    while(1)                     //Run Continuously
    {
        
        for(i=0; i < num_notes; i++) 
		{ 
            j = 0;
			while(j < delay[i]) // for length of time to play note 
			{
            } 
		} 
         
	
    }

}