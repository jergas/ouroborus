sr = 44100	; sample rate
kr = 4410	; control rate
ksmps = 10	; sr/kr
nchnls = 2	; # de canales


; instrument 1: Stereo sinusoidal oscilator with linear envelope 

    instr 1
ileft = sqrt(p6)
iright = sqrt (1-p6)
kctrl	linen p4, p7, p3, p8
asig	oscili kctrl,p5,1
    outs asig * ileft, asig * iright
    endin

; p1 instrument n.
; p2 start time
; p3 duration
; p4 amplitude (0-32767)
; p5 frquency (en hz)
; p6 panning (0-1, 1 es izquierda)
; p7 attack time
; p8 decay time

