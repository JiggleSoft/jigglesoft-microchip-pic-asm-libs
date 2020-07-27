;==============================================================================
; Copyright (c) 2020 Justin Lane. All rights reserved.
;==============================================================================
                #ifndef         __JGL_XC8_PIC_AS_LANG_MPASM__INC__
                #define         __JGL_XC8_PIC_AS_LANG_MPASM__INC__
;==============================================================================
; Project:      JiggleSoft Microchip PIC Assembler Libraries.
; Module:       JiggleSoft Microchip XC8 PIC Assembler Common Language Library.
; Title:        XC8 PIC Assembler MPASM Compatible Pseudo Instructions.
;------------------------------------------------------------------------------
; Filename:     jgl-xc8-pic-as-lang-mpasm.inc
;------------------------------------------------------------------------------
; Target:       Microchip PIC 8-bit MCU.
; IDE:          MPLAB X (v5.40+).
; Toolchain:    XC8 (v2.20+).
; Language:     Microchip PIC 8-bit Assembler (pic-as).
;------------------------------------------------------------------------------
; Home URL:     https://github.com/jigglesoft/jigglesoft-pic-libraries
; Contact:      Justin Lane (jigglesoft-pic-libraries@jigglesoft.co.uk)
;------------------------------------------------------------------------------
; Provides the following MPASM compatible pseudo instructions.
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
;   Long Goto                   LGOTO       k           -       2-3     MPASM
;   Long Call                   LCALL       k           -       2-3     MPASM
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
;------------------------------------------------------------------------------
; Note that the MPASM LGOTO pseudo instruction is good but the XC8 pic-as LJMP
; pseudo instruction creates a set restore page instruction(s) but this is 
; after a goto so totally unnecessary, so LGOTO is probably a better choice as
; it will save instruction memory.
;------------------------------------------------------------------------------
; Note that the MPASM LCALL pseudo instruction does not restore the page 
; selection bits PCLH but it does return to the calling page (next instruction 
; following the 'call'. The XC8 pic-as FCALL pseudo instruction also does the 
; restore of PCLH after the call.
;------------------------------------------------------------------------------
; Also note that the XC8 pic-as does implement an undocumented LCALL pseudo 
; instruction that appears to be a synonym of the XC8 pic-as FCALL pseudo 
; instruction. This file will implement the LCALL (all uppercase) as per the
; MPASM LCALL pseudo instruction. The XC8 pic-as 'lcall' (not uppercase) pseudo
; instruction will use the XC8 pic-as implementation (same as FCALL).
;------------------------------------------------------------------------------
; Note that the XC8 pic-as NEGF pseudo instructions on PIC18 high end cores 
; will not be available as the PIC18 has a native NEGF instruction and it also 
; behaves differently. It is unable to write to the W register and has the 
; option of using the Bank Select Register (BSR).
;------------------------------------------------------------------------------
; When used with PIC18 devices LGOTO and LCALL pseudo instructions will not 
; generate the page selection code. Also the NEGF pseudo instruction will use 
; the PIC18 'negf' instruction and will report a warning as this file is 
; included.
;------------------------------------------------------------------------------
; Please see the JiggleSoft extra macros that address the above concerns.
;==============================================================================

                #include <xc.inc>

;------------------------------------------------------------------------------
; COMMON PSEUDO INSTRUCTIONS
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Move File to W (single instruction, status Z=(f==0))
;------------------------------------------------------------------------------

MOVFW           MACRO           file_reg
                movf            file_reg,w
                ENDM

;------------------------------------------------------------------------------
; Test File (single instruction, status Z=(f==0))
;------------------------------------------------------------------------------

TSTF            MACRO           file_reg
                movf            file_reg,f
                ENDM


;------------------------------------------------------------------------------
; SET OR CLEAR STATUS FLAGS
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Clear Carry (single instruction, status C=0)
;------------------------------------------------------------------------------

CLRC            MACRO
                bcf             STATUS,STATUS_C_POSN
                ENDM

;------------------------------------------------------------------------------
; Set Carry (single instruction, status C=1)
;------------------------------------------------------------------------------

SETC            MACRO
                bsf             STATUS,STATUS_C_POSN
                ENDM

;------------------------------------------------------------------------------
; Clear Digit Carry (single instruction, status DC=0)
;------------------------------------------------------------------------------

CLRDC           MACRO
                bcf             STATUS,STATUS_DC_POSN
                ENDM

;------------------------------------------------------------------------------
; Set Digit Carry (single instruction, status DC=1)
;------------------------------------------------------------------------------

SETDC           MACRO
                bsf             STATUS,STATUS_DC_POSN
                ENDM

;------------------------------------------------------------------------------
; Clear Zero (single instruction, status Z=0)
;------------------------------------------------------------------------------

CLRZ            MACRO
                bcf             STATUS,STATUS_Z_POSN
                ENDM

;------------------------------------------------------------------------------
; Set Zero (single instruction, status Z=1)
;------------------------------------------------------------------------------

SETZ            MACRO
                bsf             STATUS,STATUS_Z_POSN
                ENDM


;------------------------------------------------------------------------------
; SKIP DEPENDANT ON STATUS FLAGS
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Skip (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKP             MACRO           skip_count
                goto            ($+skip_count)
                ENDM

;------------------------------------------------------------------------------
; Skip on Carry (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPC            MACRO
                btfss           STATUS,STATUS_C_POSN
                ENDM

;------------------------------------------------------------------------------
; Skip on No Carry (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPNC           MACRO
                btfsc           STATUS,STATUS_C_POSN
                ENDM

;------------------------------------------------------------------------------
; Skip on Digit Carry (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPDC           MACRO
                btfss           STATUS,STATUS_DC_POSN
                ENDM

;------------------------------------------------------------------------------
; Skip on No Digit Carry (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPNDC          MACRO
                btfsc           STATUS,STATUS_DC_POSN
                ENDM

;------------------------------------------------------------------------------
; Skip on Zero (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPZ            MACRO
                btfss           STATUS,STATUS_Z_POSN
                ENDM

;------------------------------------------------------------------------------
; Skip on Non Zero (single instruction, status unaffected)
;------------------------------------------------------------------------------

SKPNZ           MACRO
                btfsc           STATUS,STATUS_Z_POSN
                ENDM


;------------------------------------------------------------------------------
; BRANCH DEPENDANT ON STATUS FLAGS
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Branch (single instruction, status unaffected, constrained same page).
;------------------------------------------------------------------------------

B               MACRO           near_addr
                goto            near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on Carry (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BC              MACRO           near_addr
                SKPNC
                B               near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on No Carry (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BNC             MACRO           near_addr
                SKPC
                B               near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on Digit Carry (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BDC             MACRO           near_addr
                SKPNDC
                B               near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on No Digit Carry (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BNDC            MACRO           near_addr
                SKPDC
                B               near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on Zero (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BZ              MACRO           near_addr
                SKPNZ
                B               near_addr
                ENDM

;------------------------------------------------------------------------------
; Branch on Non Zero (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

BNZ             MACRO           near_addr
                SKPZ
                B               near_addr
                ENDM


;------------------------------------------------------------------------------
; GOTO / CALL ACROSS PAGE BOUNDARY
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Long Goto (multiple instructions, status unaffected)
;------------------------------------------------------------------------------
LGOTO           MACRO           far_addr
                #ifndef         _PIC18
                PAGESEL         (far_addr)
                goto            far_addr
                #else
                goto            far_addr
                #endif
                ENDM

;------------------------------------------------------------------------------
; Long Goto (multiple instructions, status unaffected)
;------------------------------------------------------------------------------
#define         LCALL           LCALL_MPASM
LCALL_MPASM     MACRO           far_addr
                #ifndef         _PIC18
                PAGESEL         (far_addr)
                call            far_addr
                #else
                call            far_addr,FAST
                #endif
                ENDM


;------------------------------------------------------------------------------
; EXTENDED MATH
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Negate File (multiple instructions, status Z=0)
;------------------------------------------------------------------------------
NEGF            MACRO           file_reg,dest
                #ifndef         _PIC18
                comf            file_reg,f
                incf            file_reg,dest
                #else
                messg           "WARNING: Using PIC18 NEGF instruction and not the MPASM NEGF pseudo instruction!"
                negf            file_reg,dest
                #endif
                ENDM

;------------------------------------------------------------------------------
; Add Carry to File (multiple instructions, status Z=(f==0))
;------------------------------------------------------------------------------

ADDCF           MACRO           file_reg,dest
                SKPNC
                incf            file_reg,dest
                ENDM

;------------------------------------------------------------------------------
; Add Digit Carry to File (multiple instructions, status Z=(f==0))
;------------------------------------------------------------------------------

ADDDCF          MACRO           file_reg,dest
                SKPNDC
                incf            file_reg,dest
                ENDM

;------------------------------------------------------------------------------
; Subtract Carry from File (multiple instructions, status Z=(f==0))
;------------------------------------------------------------------------------

SUBCF           MACRO           file_reg,dest
                SKPNC
                decf            file_reg,dest
                ENDM

;------------------------------------------------------------------------------
; Subtract Digit Carry from File (multiple instructions, status Z=(f==0))
;------------------------------------------------------------------------------

SUBDCF          MACRO           file_reg,dest
                SKPNDC
                decf            file_reg,dest
                ENDM


;------------------------------------------------------------------------------

                #endif          /*__JGL_XC8_PIC_AS_LANG_MPASM__INC__*/

;------------------------------------------------------------------------------
