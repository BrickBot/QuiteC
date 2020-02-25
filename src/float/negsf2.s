/*
 *  negsf2.s
 *
 *  Floating point negate, single precision: -r0r1
 *
 *  The contents of this file are subject to the Mozilla Public License
 *  Version 1.0 (the "License"); you may not use this file except in
 *  compliance with the License. You may obtain a copy of the License at
 *  http://www.mozilla.org/MPL/
 *
 *  Software distributed under the License is distributed on an "AS IS"
 *  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *  License for the specific language governing rights and limitations
 *  under the License.
 *
 *  The Original Code is Librcx floating point code, released May 27, 1999.
 *
 *  The Initial Developer of the Original Code is Kekoa Proudfoot.
 *  Portions created by Kekoa Proudfoot are Copyright (C) 1999
 *  Kekoa Proudfoot. All Rights Reserved.
 *
 *  Contributor(s): Kekoa Proudfoot <kekoa@graphics.stanford.edu>
 */

; possible optimizations
;  - remove NaN check

;;
;; function: negsf2
;; input: float in r0r1
;; output: float in r0r1
;;

    .section .text

    .global ___negsf2

___negsf2:

    ; Assume r2 saved by caller

    ; Is the input a NaN ((input & 7fffffff) > 7f800000) ?
    ; If yes, return input unchanged
    ; This check is not strictly needed (IEEE specs describe it as a "should")
    ; Specs also say "This standard does not interpret the sign of an NaN"...

    mov.w   r0,r2               ; copy upper word to r2
    and.b   #0x7f,r2h           ; mask off upper bit
    add.b   #0,r1l              ; subtract 7f800000 from r2r1
    addx.b  #0,r1h              ; do subtract by adding -7f800000=80800000
    addx.b  #0x80,r2l
    addx.b  #0x80,r2h
    bgt     return              ; greater than indicates true (NaN)

    ; Negate operand

    xor.b   #0x80,r0h           ; flip sign bit of operand

return:

    rts
