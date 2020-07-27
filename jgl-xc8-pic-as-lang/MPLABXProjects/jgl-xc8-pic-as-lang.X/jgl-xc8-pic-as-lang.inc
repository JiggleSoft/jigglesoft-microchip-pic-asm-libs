;==============================================================================
; Copyright (c) 2020 Justin Lane. All rights reserved.
;==============================================================================
                #ifndef         __JGL_XC8_PIC_AS_LANG_MPASM_PSEUDO__INC__FIXME1
                #define         __JGL_XC8_PIC_AS_LANG_MPASM_PSEUDO__INC__FIXME1
;==============================================================================
; Project:      JiggleSoft Microchip PIC Libraries.
; Module:       JiggleSoft Microchip XC8 PIC Assembler Common Language Library.
; Title:        XC8 PIC Assembler MPASM Compatible Pseudo Instructions.
;------------------------------------------------------------------------------
; Filename:     jgl-xc8-pic-as-common-lang-macros.inc
;------------------------------------------------------------------------------
; Target:       Microchip PIC 8-bit MCU.
; IDE:          MPLAB X (v5.40+).
; Toolchain:    XC8 (v2.20+).
; Language:     Microchip PIC 8-bit Assembler (pic-as).
;------------------------------------------------------------------------------
; Home URL:     https://github.com/jigglesoft/jigglesoft-pic-libraries
; Contact:      Justin Lane (jigglesoft-pic-libraries@jigglesoft.co.uk)
;------------------------------------------------------------------------------
; Provides the following MPASM compatible pseudo instructions (cast in stone).
;
;   Name                        Mnemonic    Operands    Status  Words   Notes
;   ---------------------------------------------------------------------------
;   Move File to W              MOVFW       f           Z       1       MPASM
;   Test File                   TSTF        f           Z       1       MPASM
;
;   Clear Carry                 CLRC        -           -       1       MPASM
;   Set Carry                   SETC        -           -       1       MPASM
;   Clear Digit Carry           CLRDC       -           -       1       MPASM
;   Set Digit Carry             SETDC       -           -       1       MPASM
;   Clear Zero                  CLRZ        -           -       1       MPASM
;   Set Zero                    SETZ        -           -       1       MPASM
;
;   Skip on Carry               SKPC        -           -       1       MPASM
;   Skip on No Carry            SKPNC       -           -       1       MPASM
;   Skip on Digit Carry         SKPDC       -           -       1       MPASM
;   Skip on No Digit Carry      SKPNDC      -           -       1       MPASM
;   Skip on Zero                SKPZ        -           -       1       MPASM
;   Skip on Non Zero            SSKPNZ      -           -       1       MPASM
;
;   Branch                      B           k           -       1       MPASM
;   Branch on Carry             BC          k           -       2       MPASM
;   Branch on No Carry          BNC         k           -       2       MPASM
;   Branch on Digit Carry       BDC         k           -       2       MPASM
;   Branch on No Digit Carry    BNDC        k           -       2       MPASM
;   Branch on Zero              BZ          k           -       2       MPASM
;   Branch on Non Zero          BNZ         k           -       2       MPASM
;
;   Long Call                   LCALL       k           ?TODO   ?TODO   MPASM
;   Long Goto                   LGOTO       k           ?TODO   ?TODO   MPASM
;
;   Negate File                 NEGF        f,d         Z       2       MPASM
;   Add Cary to File            ADDCF       f,d         Z       2       MPASM
;   Add Digit Carry to File     ADDDCF      f,d         Z       2       MPASM
;   Subtract Carry from File    SUBCF       f,d         Z       2       MPASM
;   Subtract Digit Carry 
;       from File               SUBDCF      f,d         Z       2       MPASM
;------------------------------------------------------------------------------
; WARNING: Some pseudo instructions and macros produce multiple instructions so
;          you cannot skip over them with the skip instructions e.g. do not do
;          this:-
;                   btfss   STATUS,STATUS_C_POSN
;                   NEGF    REG
;          as the skip will skip into the second instruction of the NEGF macro.      
;==============================================================================

                #include <xc.inc>

;------------------------------------------------------------------------------
; COMMON PSEUDO INSTRUCTIONS
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Move File to W (single instruction, status Z=(f==0))
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------

                #endif          /*__JGL_XC8_PIC_AS_LANG_MPASM_PSEUDO__INC__FIXME1*/

;------------------------------------------------------------------------------
