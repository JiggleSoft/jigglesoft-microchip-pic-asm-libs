;==============================================================================
; Copyright (c) 2020 Justin Lane. All rights reserved.
;------------------------------------------------------------------------------
;   Licensed under the Apache License, Version 2.0 (the "License");
;   you may not use this file except in compliance with the License.
;   You may obtain a copy of the License at
;
;       http://www.apache.org/licenses/LICENSE-2.0
;
;   Unless required by applicable law or agreed to in writing, software
;   distributed under the License is distributed on an "AS IS" BASIS,
;   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;   See the License for the specific language governing permissions and
;   limitations under the License.
;==============================================================================

;==============================================================================
; Project:      JiggleSoft Microchip PIC Libraries.
; Module:       JiggleSoft Microchip XC8 PIC Assembler Common Language Library.
; Title:        XC8 PIC Assembler MPASM Compatible Pseudo Instructions Test.
;------------------------------------------------------------------------------
; Filename:     jgl-xc8-pic-as-lang-mpasm-test.s
;------------------------------------------------------------------------------
; Target:       Microchip PIC 8-bit MCU.
; IDE:          MPLAB X (v5.40+).
; Toolchain:    XC8 (v2.20+).
; Language:     Microchip PIC 8-bit Assembler (pic-as).
;------------------------------------------------------------------------------
; Home URL:     https://github.com/JiggleSoft/jigglesoft-microchip-pic-asm-libs
; Contact:      Justin Lane (pic.asm.libs@jigglesoft.co.uk)
;==============================================================================

                #include        "jgl-xc8-pic-as-lang-mpasm.inc"


		psect		code
 
                org             0x000


;------------------------------------------------------------------------------


movfw_begin:                
                MOVFW           PORTA
movfw_end:

    
tstf_begin:
                TSTF            PORTA
tstf_end:


;------------------------------------------------------------------------------


clrc_begin:
                CLRC
clrc_end:


setc_begin:
                SETC
setc_end:


clrdc_begin:
                CLRDC
clrdc_end:


setdc_begin:
                SETDC
setdc_end:


clrz_begin:
                CLRZ
clrz_end:


setz_begin:
                SETZ
setz_end:


;------------------------------------------------------------------------------


skp_begin:
                SKP             3
                nop
                nop
                nop
skp_end:


skpc_begin:
                SKPC
skpc_end:
                nop


skpnc_begin:
                SKPNC
skpnc_end:
                nop


skpdc_begin:
                SKPDC
skpdc_end:
                nop


skpndc_begin:
                SKPNDC
skpndc_end:
                nop

                
skpz_begin:
                SKPZ
skpz_end:
                nop

                
skpnz_begin:
                SKPNZ
skpnz_end:
                nop


;------------------------------------------------------------------------------


b_begin:
                B               b_exit
b_end:
                nop
b_exit:


bc_begin:
                BC              bc_exit
bc_end:
                nop
bc_exit:


bnc_begin:
                BNC             bnc_exit
bnc_end:
                nop
bnc_exit:


bdc_begin:
                BDC             bdc_exit
bdc_end:
                nop
bdc_exit:

//
bndc_begin:
                BNDC            bndc_exit
bndc_end:
                nop
bndc_exit:


bz_begin:
                BZ              bz_exit
bz_end:
                nop
bz_exit:


bnz_begin:
                BNZ             bnz_exit
bnz_end:
                nop
bnz_exit:


;------------------------------------------------------------------------------


lgoto_begin:
                LGOTO           lgoto_exit
lgoto_end:
                nop
lgoto_exit:


lcall_begin:
                LCALL           lcall_exit
lcall_end:
                nop
lcall_exit:


lgoto_begin2:
                PAGESEL         (lgoto_exit2)
                goto            lgoto_exit2
lgoto_end2:
                nop
lgoto_exit2:


lcall_begin2:
                PAGESEL         (lcall_exit2)
                call            lcall_exit2
lcall_end2:
                nop
lcall_exit2:


;------------------------------------------------------------------------------


negf_w_begin:
                NEGF            PORTA,w
negf_w_end:


negf_f_begin:
                NEGF            PORTA,f
negf_f_end:


addcf_w_begin:
                ADDCF           PORTA,w
addcf_w_end:


addcf_f_begin:
                ADDCF           PORTA,f
addcf_f_end:


adddcf_w_begin:
                ADDDCF          PORTA,w
adddcf_w_end:


adddcf_f_begin:
                ADDDCF          PORTA,f
adddcf_f_end:


subcf_w_begin:
                SUBCF           PORTA,w
subcf_w_end:


subcf_f_begin:
                SUBCF           PORTA,f
subcf_f_end:


subdcf_w_begin:
                SUBDCF          PORTA,w
subdcf_w_end:


subdcf_f_begin:
                SUBDCF          PORTA,f
subdcf_f_end:


;------------------------------------------------------------------------------
