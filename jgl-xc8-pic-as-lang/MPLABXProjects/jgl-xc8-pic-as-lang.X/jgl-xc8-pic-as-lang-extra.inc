;==============================================================================
; Copyright (c) 2020 Justin Lane. All rights reserved.
;==============================================================================
                #ifndef         __JGL_XC8_PIC_AS_LANG_EXTRA_PSEUDO__INC__FIXME2
                #define         __JGL_XC8_PIC_AS_LANG_EXTRA_PSEUDO__INC__FIXME2
;==============================================================================
; Project:      JiggleSoft Microchip PIC Assembler Libraries.
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
;
;   Move File to W              MOVFW       f           Z       1       MPASM
;
;   Test File                   TSTF        f           Z       1       MPASM
;------------------------------------------------------------------------------
; Provides the following additional macros (subject to change until advised).
;
;   Name                        Mnemonic    Operands    Status  Words   Notes
;   ---------------------------------------------------------------------------
;   Jump to Sub Routine         JSR         k                           LCALL
;   Jump                        JMP         k                           LGOTO
;   Jump on Carry               JMPC        k           
;   Jump on No Carry            JMPNC       k           
;   Jump on Digit Carry         JMPDC       k           
;   Jump on No Digit Carry      JMPNDC      k           
;   Jump on Zero                JMPZ        k           
;   Jump on Non Zero            JMPNZ       k           
;
;   Compare Literal to W
;   Compare Literal to File
;   Compare File to W
;   Compare File to File
;
;   Clear W and File            CLRWF or FW? f          ?       1       JGL
;   Clear W and Multiple File   CLRWMF      f,n         ?       (1+n)   JGL
;   Clear Multiple File         CLRMF       f,n         ?       (n)     JGL
;
;   Move W to Multiple File     MOVWMF      f,n         ?       (n)     JGL
;   Move Literal to W and File  MOVLWF      l,f         ?       2       JGL
;   Move Literal to W 
;       then to Multiple File   MOVLWMF     l,f,n       ?       (1+n)   JGL
;   Move File to W and File     MOVFWF                  ?       ?       JGL
;   Move File to W 
;       and Multiple File       MOVFWMF     f1,f2,n     ?       ?       JGL
:
;   Test W                      TSTW        -           ?       1       JGL
;
;   Increment W                 INCW        -           ?       1       JGL
;   Decrement W                 DECW        -           ?       1       JGL
;
;   Exchange File with W        EXFW        f           TODO    3       JGL
;   Exchange File with File     EXFF        f1,f2       TODO    9       JGL
;   Exchange File with File
;       W set to File 1         EXFWF       f1,f2       TODO,W  5       JGL
;   Exchange File with File
;       W set to File 2         EXFFW       f1,f2       TODO,W  5       JGL
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
; JUMP ACROSS PAGE BOUNDARY
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Far Jump (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

LGOTO           MACRO           far_addr
                messg           "Consider instead the use of the XC8 pic-as 'ljmp' assembler pseudo instruction!"
                PAGESEL         (far_addr)
                goto            far_addr
                ENDM

;------------------------------------------------------------------------------
; Far Call (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

;LCALL           MACRO           far_addr
;                messg "Deprecated 'LCALL', use XC8 pic-as 'fcall' assembler pseudo instruction!" 
                ;fcall            far_addr
;                ENDM

;LJUMP           MACRO           far_addr
;                ljmp            far_addr
;           pagesel ((k & 0xFF00)>>8)
;                call            k
;                ENDM
;                //fcall , ljmp built in

;------------------------------------------------------------------------------
; CaALL ACCROSS PAGE BOUNDARY (multiple instructions, status unaffected)
;------------------------------------------------------------------------------

LzCALL           MACRO           far_addr
           pagesel ((k & 0xFF00)>>8)
                call            k
                ENDM
;                //fcall , ljmp built in

;------------------------------------------------------------------------------
; FIXME
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Test File (single instruction, status Z=(r==0))
;------------------------------------------------------------------------------

TSTF            MACRO           file_reg
                movf            file_reg,f
                ENDM

;------------------------------------------------------------------------------
; Move File to W (single instruction, status Z=(r==0))
;------------------------------------------------------------------------------

MOVFW           MACRO           file_reg
                movf            file_reg,w
                ENDM

;------------------------------------------------------------------------------
; Negate File                NEGF f,d
;------------------------------------------------------------------------------

NEGF            MACRO           file_reg,dest
                comf            file_reg,f
                incf            file_reg,d
                ENDM

;------------------------------------------------------------------------------
; Add Carry to File          ADDCF f,d   BTFSC    3,0
;                                       INCF     f,d        Z
;------------------------------------------------------------------------------

ADDCF              MACRO           k
                ENDM

;------------------------------------------------------------------------------
; Subtract Carry from File   SUBCF f,d   BTFSC    3,0
;                                       DECF     f,d        Z
;------------------------------------------------------------------------------

SUBCF               MACRO           k
                ENDM

;------------------------------------------------------------------------------
; Add Digit Carry to File    ADDDCF f,d  BTFSC    3,1
;                                       INCF     f,d        Z
;------------------------------------------------------------------------------

ADDDCF               MACRO           k
                ENDM

;------------------------------------------------------------------------------
; Subtract Digit             SUBDCF f,d  BTFSC    3,1
;Carry from File                        DECF     f,d        Z
;------------------------------------------------------------------------------

SUBDCF               MACRO           k
                ENDM


;------------------------------------------------------------------------------
; FIXME
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

BXXX6               MACRO           k
                goto            k
                ENDM


;------------------------------------------------------------------------------
; Test File (single instruction, status Z=(r==0))
;------------------------------------------------------------------------------

CMP             MACRO           literal_val,file_reg
                 movlw  CompTo      ; put the value to compare with in W
          subwf  SomeVar,W   ; subtract W from the File Register
                             ;  you want to compare with and put
                                                          ; result in W (this preserve file register)

                ENDM




;------------------------------------------------------------------------------
; FIXME
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

CLRM            MACRO           r,n
            local i
            i set 0
                REPT            n
                clrf            BANKMASK(r+i)
                i set (i+1)
                ENDM
                ENDM
/*
;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------
; movfw 3
;zMOVFW           MACRO           f
;                movf            f,w
;                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

MOVLWF          MACRO           l,f
                movlw           l
                movwf           f
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

MOVWFM          MACRO           f,n
                REPT            n
                B               k
                ENDM
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

MOVLWFM         MACRO           l,f,n
                movlw           l
                MOVWFM          f,n
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM


;------------------------------------------------------------------------------
; Fixme
;------------------------------------------------------------------------------

ZXY             MACRO           k
                SKPZ
                B               k
                ENDM




                psect code    
                CLRC

*/


;------------------------------------------------------------------------------
; Test W
;------------------------------------------------------------------------------

TSTW            MACRO          file_reg
                iorlw          0x00
                ENDM

;------------------------------------------------------------------------------
; Increment W
;------------------------------------------------------------------------------

INCW            MACRO          file_reg
                addlw          0x01
                ENDM

;------------------------------------------------------------------------------
; Decrement W
;------------------------------------------------------------------------------

DECW            MACRO          file_reg
                addlw           0xFF
                ENDM

;------------------------------------------------------------------------------
; Exchange W with File
;------------------------------------------------------------------------------

EXCHWF          MACRO          file_reg
                xorwf           file_reg,f
                xorwf           file_reg,w
                xorwf           file_reg,f
                ENDM

;------------------------------------------------------------------------------
; Exchange File with File
;------------------------------------------------------------------------------

EXCHFF          MACRO           file_reg1,file_reg2
                movf            file_reg2,w
                EXCHWF          file_reg1
                movwf           file_reg2
                ENDM


;------------------------------------------------------------------------------

                #ifdef      ADC_ENABLE_LIB

;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------

                #endif

;------------------------------------------------------------------------------

                #endif          /*__JGL_XC8_PIC_AS_LANG_EXTRA_PSEUDO__INC__FIXME2*/

;------------------------------------------------------------------------------
