## Contains the classes that define Csound score events.

# Import the note-method classes.
from . import Note_methods as NM

# Instantiate the note method classes
Spctrm  = NM.Spctrm()
StrtTms = NM.StrtTms()
Durs    = NM.Durs()
Amps    = NM.Amps()
Pan             = NM.Pan()
Env             = NM.Env()



class AgentNote(object):
        """ Note class for the sound played when an agent is born.
        """
        def mkBirthString(self):
                """ Generates a string suitible to be fed to Csound as
                a score statement. The resulting sound is a birth sound.
                return  --> a note-statement string.
                """
                scoStatement    = ''.join(['i1 0 ', str(self.dur), ' ', str(self.ptch1),
                                                                        ' ', str(self.ptch2), ' ', str(self.vibr),
                                                                        ' ', str(self.IDeviation), ' ',
                                                                        str(self.ADeviation), ' ', '0 ',
                                                                        str(self.pan), ' ', '0'])
                return scoStatement


        def mkEatString(self):
                """ Generates a string suitible to be fed to Csound as
                a score statement. The resulting sound is an eating sound.
                return  --> a note-statement string.
                """
                scoStatement    = ''.join(['i1 0 ', str(self.dur), ' ', str(self.ptch1),
                                                                        ' ', str(self.ptch2), ' ', '0 ', '0 ', '0 ',
                                                                        str(self.ODeviation), ' ', str(self.pan),
                                                                        ' ', '1'])
                return scoStatement


        def mkDeathString(self):
                """ Generates a string suitible to be fed to Csound as
                a score statement. The resulting sound is a birth sound.
                return  --> a note-statement string.
                """
                scoStatement    = ''.join(['i1 0 ', str(self.dur), ' ', str(self.ptch1),
                                                                        ' ', str(self.ptch2), ' ', str(self.vibr),
                                                                        ' ', str(self.IDeviation), ' ',
                                                                        str(self.ADeviation), ' ', '0 ',
                                                                        str(self.pan), ' ', '2'])
                return scoStatement



class BckgrndNote(object):
        """ Note class for the background sound.
        """
        def __init__(self, instrNos, fundFreq, numOfPartls, spectType, distor,
                                        distor2, pan, dur):
                """ Atributes used to construct a set of csound score
                statements, which constitute a spectral note.
                instrNos                ---> Csound instrument numbers
                fundFreq        ---> the fundamental frequency
                numOfPartls     ---> number of partials that the note will have
                spectType       ---> type of spectrum (0=odd partls, 1=even partls,
                                                        2=fibonacci partls and 3=prime partls)
                distor          ---> note's spectral distortion factor
                distor2         ---> distortion factor towards the end of the note
                                                        (the partials will do a glissando to reach
                                                        the second spectrum)
                pan                     ---> note's over-all panning
                dur                     ---> note's total duration
                """
                self.instrNos           = instrNos
                self.fundFreqNew        = fundFreq
                self.fundFreqOld        = fundFreq
                self.numOfPartls        = numOfPartls
                self.spectType          = spectType
                self.distor                     = distor
                self.distor2            = distor2
                self.pan                        = pan
                self.dur                        = dur


        def mkspectData(self):
                """ Constructs the neccesary data for each partial of the
                spectrum.
                return  --> A list of tuples, each tuple is a full list of
                                        parameters to construct a Csound note-statement
                """
                self.partls                     = Spctrm.mkPartls(self.spectType, self.numOfPartls)
                self.dSpect                     = Spctrm.dSpect(self.fundFreqOld, self.partls,
                                                                                                self.distor)
                self.partls                     = Spctrm.mkPartls(self.spectType, self.numOfPartls)
                self.dSpect2            = Spctrm.dSpect(self.fundFreqNew, self.partls,
                                                                                                self.distor2)
                self.fundFreqOld = self.fundFreqNew

                # Ensure that both spectra will have the same number of
                # partials, since the spectrum construction method
                # discards harmonics over 20,000hz.
                if len(self.dSpect) > len(self.dSpect2):
                        xtra = self.dSpect[-1]
                        self.dSpect2.append(xtra)
                if len(self.dSpect) < len(self.dSpect2):
                        xtra = self.dSpect2[-1]
                        self.dSpect.append(xtra)

                self.strts                      = StrtTms.expoSpct(self.dSpect)
                self.durs                       = Durs.spectDurs(self.strts, self.dur)
                self.amps                       = Amps.spectUnifrmAmps(self.dSpect)
                self.spectPan           = Pan.spctrlPans(self.pan, self.dSpect)

                return list(zip(self.instrNos, self.strts, self.durs, self.amps, self.dSpect,
                                         self.dSpect2, self.spectPan))


        def mkScoStrings(self):
                """ Generates a set of Csound score statements (notes) that
                comprehend a spectral note.
                return  --> a list of strings, each of which is a note statement
                """
                data                    = self.mkspectData()
                formatString    = ''.join(['i%-8s ', '%-8s ' * (len(data[0]) -1)])
                spectrSco               = []

                for x in data:
                        scoNote = (formatString %x)
                        spectrSco.append(scoNote)
                return spectrSco
