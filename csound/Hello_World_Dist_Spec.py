## Method to test the Distorted Harmonic Spectrum.
import csnd

from Csound_Note import note

def HelloWorld():
## It makes an instance of the Csound Api, sets a string that works as a
#CSD file with the appropriate options, exports it to csound, compiles
#the CSD, starts a performance thread, and
#starts playing.
    csound = csnd.CppSound()
    csound.setPythonMessageCallback()
    csound.setCSD('''
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b8192 -B8192 -m0 -d temp.orc temp.sco
</CsOptions>

<CsInstruments>
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

</CsInstruments>
<CsScore>
f1 0 4096 10 1       ; use GEN10 to compute a sine wave

; ten hours of silence:
i1	0	36000	0	3000	0	0	0
e ; end of the score
</CsScore>
</CsoundSynthesizer>

    ''')
    csound.exportForPerformance()
    csound.compile()
    perf = csnd.CsoundPerformanceThread(csound)
    perf.Play()
##Displays options for the next set of partials to be used in the next
#note, waits for the user's instructions and sends the selected parameters
#to Csound. These instructions are repeated while the user choses a valid
#option.
    try:
        true_loop = 1
        while true_loop == 1:
            fundamental = float(raw_input("""
            - Enter the frequency for the fundamental (floats between 53.0 and 1696.0hz)
            """))
            fundamental = fundamental * 1.0
            while fundamental < 53.0 or fundamental > 1696.0:
                fundamental = float(raw_input("""
            - Please enter a valid parameter
            """))
            noOfHarmonics = int(raw_input("""
            - Enter the number of harmonics to be present in the note (integer between 1 and 32)
            """))
            while noOfHarmonics < 1 or noOfHarmonics > 100:
                noOfHarmonics = int(raw_input("""
            - Please enter a valid parameter
            """))
            spectrum_type = int(raw_input("""
            -Enter 1 for an even-partials distorted harmonic spectrum
            -Enter 2 for an odd-partials distorted harmonic spectrum
            -Enter 3 for a fibonacci-partials distorted harmonic spectrum
            -Enter 4 for a prime-partials distorted harmonic spectrum
            """))
            while spectrum_type < 1 or spectrum_type >4:
                spectrum_type = int(raw_input("""
            - Please enter a valid parameter
            """))
            spectrum_type = spectrum_type - 1
            distortion = float(raw_input("""
            - Enter the spectral distortion factor (float between .5 and 1.5)
            """))
            distortion = distortion * 1.0
            while distortion < .5 or distortion >1.5:
                distortion = float(raw_input("""
            - Please enter a valid parameter
            """))
            overallPanning = float(raw_input("""
            - Enter the panning value (float between 0 and 1, 1 is left)
            """))
            overallPanning = overallPanning * 1.0
            while overallPanning < 0.0 or overallPanning >1.0:
                overallPanning = float(raw_input("""
            - Please enter a valid parameter
            """))
            duration = float(raw_input("""
            - Enter a duration in seconds (as float)
            """))
            duration = duration * 1.0
         
            spectrum = note(fundamental, noOfHarmonics, spectrum_type,
                    distortion, overallPanning, duration)
            while len(spectrum) > 0:
                partial = spectrum.pop(0)
                perf.InputMessage(partial)
            true_loop = int(raw_input("""
            - Enter 1 for another note, or 0 to exit
            """))
            while true_loop != 1 and true_loop != 0:
                spectrum_type = int(raw_input("""
            - Please enter a valid parameter
            """))    
    except:
        print """
Invalid data input...

Applying the GIGO (garbag in garbage out) rule.'

"""
        perf.Stop()
        perf.Join()
    perf.Stop()
    perf.Join()
    print 'Goodbye'
if __name__ == "__main__":
    HelloWorld()
