'''This is an enviromentally responsive cellular automaton. It is under very early development. For this to work propperly you will need a device that can provide information about the current enviroment. This was developed using an arduino (http://www.arduino.cc/) with a light sensitive resistor (the circuit used can be found here: http://www.ladyada.net/learn/sensors/cds.html). If you do not have an arduino or a similar device change line 96 to enviro=random.randint(0,1000) this will not behave the same as using an arduino but it will work.

The rules for the automaton are derived from Conways game of life. This code is incomplete and currently needs to be integrated with birdcage topology, neighbourhood and visuals.

Written by Diego January 2009'''

import Image
import ImageDraw
import serial

def getEnviro(port):
    sensor =  serial.Serial(str(port), 9600)
    enviro = []
    while len(enviro) < 1:
        enviro = sensor.readline()
        enviro = enviro.split()
    enviro = int(enviro[0])
    return enviro

def initials(fractON,side,enviro):
    '''Generates the initial condition of the automaton, it requires a proportion of initially living individuals, the length of the sides of the automaton and a serial port to read the sensors'''
    
    import random
    espacio = [0]*(side**2)
    onindivs = (side**2)*fractON
    
    '''Set up living and dead'''
    for i in range(0,int(onindivs)):
        espacio[random.randint(0,len(espacio)-1)] = enviro
    for i in range(0,side):
        for j in range(0,side):
            if espacio[(side*i)+j] == 0:
                espacio[(side*i)+j] = random.randint(1,1000)
    print "percentage living = %d, #of cells = %d,#of living %d" %(fractON*100,len(espacio),len(espacio)*fractON)
    return espacio
    
def visuals(input_list,side,enviro,generation):
    '''This module generates all the visual data of the automaton as still images, this module is under development and will hopefully be substituted by abirdcage visuals  module to allow realtime playback of the automaton. It requires a list of states for each pixel, the dimensions of the sides (currently it only draws squares) an enviromental condition and a generation number'''
    im = Image.new("RGB",(side,side))
    draw = ImageDraw.Draw(im)
    for i in range(0,side):
        for j in range(0,side):
            if input_list[(side*i)+j]-5<= enviro <= input_list[(side*i)+j]+5:
                draw.point((i,j),(255,255,0))
            else:
                draw.point((i,j),(0,0,255))
    im.save("generacion"+str(generation)+".tiff")
   

def rules(input_list,side,enviro):
    ONneighbours = 0
    espacio2 ={}
    state = 0
    
    for i in range(0,side):
        for j in range(0,side):
            if enviro-5 <= input_list[(side*i)+j] <= enviro+5:
                state = 1
                ONneighbours = -1
            else:
                state = 0
                ONneighbours = 0
                         
            if (side-1)>i>0 and (side-1)>j>0:
                for k in range(-1,2):
                    for l in range(-1,2):
                        if enviro-5<= input_list[(side*(i+k))+(j+l)] <=enviro+5:
                                ONneighbours = ONneighbours+1
                
                if state==1:
                    if ONneighbours<2 or ONneighbours >=4:
                        if (input_list[(side*i)+j]-enviro) > 1:
                            espacio2[i,j] = enviro-10
                        elif (input_list[(side*i)+j]-enviro) < 1:
                            espacio2[i,j] = enviro+10
                        else:
                            if input_list[(side*i)+j]<500:
                                espacio2[i,j]= enviro+10
                            if input_list[(side*i)+j]>500:
                                espacio2[i,j]= enviro-10
                    

                    elif 1< ONneighbours <4:
                        espacio2[i,j] = enviro
                      
                        
                elif state == 0:
                    if ONneighbours == 3:
                        espacio2[i,j]= enviro
                    else:
                        espacio2[i,j]=input_list[(side*i)+j]

    for i in range(1,side-1):
        for j in range(1,side-1):
            input_list[(side*i)+j] = espacio2[i,j]
    
    return input_list 
    
sideL = 100
enviro = getEnviro('/dev/ttyUSB0')
cells = initials(0.15,sideL,enviro)
for t in range(0,300):
    visuals(cells,sideL,enviro,t)
    cells = rules(cells,sideL,enviro)
    enviro = getEnviro('/dev/ttyUSB0')
    #print t,enviro
