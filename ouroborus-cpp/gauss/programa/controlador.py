from visual import *
from visual.controls import *

#esta clase se encarga de manejar el "feel" de la aplicacion
#es decir maneja los pedidos del usuario, el controlador es el encargado
#de poner los botones y levantar las banderas que le dicen a pantalla
#que un evento se a registrado en un boton
class controlador:
    
    def __init__(self):
        
        self.c = controls(title='pelotas',x=0, y=300, width=250, height=150, range=50)
    
        self.startB = button  (pos=(-20,-10), width=20, height=10,
                      text='start', action=lambda: self.start() )

        self.stopB = button  (pos=(0,-10), width=20, height=10,
                      text='stop', action=lambda: self.stop() )
    
        self.limpiaB = button  (pos=(20,-10), width=20, height=10,
                      text='limpia', action=lambda: self.limpia() )

        self.masB = button  (pos=(-20,0), width=20, height=10,
                      text='+ bol', action=lambda: self.mas() )

        self.menosB = button  (pos=(0,0), width=20, height=10,
                      text='- bol', action=lambda: self.menos() )

        self.bolasB = button  (pos=(20,0), width=20, height=10,
                      text='0')
        
        self.masNivel = button  (pos=(20,10), width=20, height=10,
                      text='+ Niv', action = lambda: self.masN() )
        
        self.menosNivel = button  (pos=(0,10), width=20, height=10,
                      text='- Niv', action = lambda: self.menosN() )

        self.nivelB = button  (pos=(-20,10), width=20, height=10,
                      text='0')


        self.cantidad = 0
        self.corriendo = false
        self.limpiado = false
        self.masF = false
        self.menosF = false
        self.niveles = 0
        self.masNiv = false
        self.menosNiv = false

    #metodo que levanta la bandera de comienzo    
    def start(self):        
        self.corriendo = true
        self.startB.text = "corriendo"

    #metodo que levanta la bandera de stop                 
    def stop(self):
        self.corriendo = false 
        self.startB.text = "start"
        self.limpiado = true
        self.cantidad = 0
        self.bolasB.text = `self.cantidad`

    #metodo que levanta la bandera para quitar las pelotas      
    def limpia(self):
        if self.corriendo == false :           
            self.cantidad = 0
            self.bolasB.text = `self.cantidad`
            self.limpiado = true
            
    #metodo que levanta la bandera para que el fondo ponga un nivel mas        
    def masN(self):
        if self.corriendo == false :
            self.masNiv = true
            self.niveles += 1
            self.nivelB.text =  `self.niveles`
            self.bolasB.text = "0"
            self.cantidad = 0

    #levanta la bandera para fondo, para quitar un nivel                
    def menosN(self):
        if self.corriendo == false :
            if(self.niveles > 1):
                self.menosNiv = true
                self.niveles -= 1
                self.nivelB.text =  `self.niveles`
                self.bolasB.text = "0"
                self.cantidad = 0

    #metodo que levanta la bandera para que el pelotero ponga una bola mas
    def mas(self):
        if self.corriendo == false : 
            self.cantidad += 1
            self.bolasB.text = `self.cantidad`
            self.limpiado = false
            self.masF = true

    #metodo que levanta la bandera para que el pelotero quite una pelota
    def menos(self):
        if self.corriendo == false :  
            if(self.cantidad > 1):        
                self.cantidad -= 1
                self.bolasB.text = `self.cantidad`
                self.limpiado = false
                self.menosF = true

    #metodo que regresa la cantidad de pelotas en el juego    
    def getCantidad(self):        
        return self.cantidad

    
