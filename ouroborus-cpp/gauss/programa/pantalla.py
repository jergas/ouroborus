from visual import *
import pelotero
import controlador
import fondo

#este modulo es el que se deve de llamar primero
# representa la pantalla
#en el se unen el controlador y la parte logica de los objetos en juego

back = fondo.fondo()
control = controlador.controlador()
pelo = pelotero.pelotero() 

# metodo que une la llamada por parte del controlador y el poner una pelota
# en clase pelotero "logica del programa"
def cargaPelota():    
    pelo.pon(back.dameInicioPelota(), back.dameIntersecciones())
    control.masF = false


#este metodo se llama justo cuando el controladro ddetecto un aumento o 
#disminucion de los niveles porloque la cantidad de cajas cambia
def cargaLasCajas():
    pelo.creaCajas(back.liCajas, back.damePosCajas())

    
# metodo que une la llamada del controlador con quitar una pelota en el
# en el pelotero "parte logica"
def quitaPelota():    
    pelo.quita()
    control.menosF = false


# metodo que une al controlador con limpiar a todas las pelotas que tenga
# el pelotero "parte logica"
def quitaTodas(): 
    control.limpiado = false
    if len(pelo.liPelotas) != 0:
        pelo.quitalas()

        
# metodo que conecta el controlador
# con el fondo para quitar otro nivel
def quitaNivel():
    control.menosNiv = false
    control.limpiado = true
    back.quitaNivel()

# metodo que conecta el controlador
# con el fondo para poner otro nivel
def ponNivel():
    control.masNiv = false
    control.limpiado = true
    back.ponNivel()

# metodo que conecta el controlador
# con pelotero "parte logica" para que este comienze a calcular la
# trallectoria de las esferas
def animaPelotas():
    pelo.muevePelotas(back.b, back.primeraYInterseccion)


# gracias a este while la pantalla puede modificar su imagen
#a una tasa rate(n)
# e interaccionar con el controlador con interact
# para mandar a pedir cosas al pelotero "parte logica"
while 1:
    rate(40)
    control.c.interact()
    
    if(control.masF):
        cargaPelota()
        
    if(control.menosF):
        quitaPelota()
        
    if(control.masNiv):
        ponNivel()
        cargaLasCajas()
        
    if(control.menosNiv):
        quitaNivel()
        cargaLasCajas()
                    
    if(control.corriendo):
        animaPelotas()
    
    if(control.limpiado):
        quitaTodas()
    
       
