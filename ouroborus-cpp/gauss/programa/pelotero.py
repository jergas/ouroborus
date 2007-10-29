import random
from visual import *
import controlador
import fondo

#esta clase se encarga de manejar la creacion, movimiento, de las esferas
#incluidas las cajas que las reciven
class pelotero:
    liPelotas = []
    liIntersecciones = []
    liCajas = []
    liXposicion = []
    x = 0
    dt = .5
    subiendo = true
    b = 0.0
    radio = .4
    cajaAltura = 0
    bandera2 = true
    yInicialPelota = 0

    #este metodo se encarga de crear las cajas rojas que se encuentran en el fondo de la
    # piramide
    #este metodo es llamado cada ves que pones un nivel mas o quitas uno dentro de
    # las piramides azules
    def creaCajas(self, posCajas, posY):
        self.yCaja = posY        
        z = 0
        longitud = self.radio*2 # length  eje x
        ancho =  self.radio*2   #width  eje z
        altura =  0   #height  eje y        
        self.liXposicion = []
        self.liXposicion  = posCajas
        self.quitaLasCajas()
        ban = true
        j = 0
        if ban:
            while j < len(self.liXposicion) :
                self.liCajas.append(box(pos=(self.liXposicion[j], self.yCaja ,z), length=longitud, height = altura, width=ancho, color=color.red))            
                j += 1
            ban = false
            
    #este metodo es llamada cada ves que en el fondo se aumentan o disminullen los
    #niveles por lo cual se nesesita recalcular las cajas, pero antes de ello se
    #remueben las cajas viejas
    def quitaLasCajas(self):
        j = 0
        while j < len(self.liCajas):
            if self.liCajas[j].height != 0:
                self.liCajas[j].visible = 0#height = 0
            self.liCajas[j].visible = 0
            j += 1
        self.liCajas = []

        
    #este metodo se encarga de llamar al que crea la pelota ademas de actualizar 
    #las posiciones de interseccion 
    def pon(self, yInicial, posInterseccion):
        self.liIntersecciones = []
        self.bandera2 = true
        self.liIntersecciones = posInterseccion       
        self.liPelotas.append( self.crea(yInicial))

       
    #crea una esfera con vector de caida sin variar en "x" y "z"
    #y la coloca mas arriva que el fondo "en la esfera verde"        
    def crea(self, yInicial):
        s = sphere( pos=(0 ,yInicial,0.7), radius= self.radio, color=color.red)  
        s.velocity = vector(0, 0, 0)
        self.yInicialPelota = yInicial
        return s
    #este metodo se encarga de quitar una pelota de la lista, removiendola y
    #haciendola invisible
    def quita(self):
        if len(self.liPelotas)!= 0:
            self.liPelotas[0].visible = 0
            del self.liPelotas[0]
    #este metodo se encarga de quitar todas las esferas del juego
    def quitalas(self):
        for j in self.liPelotas:
            j.visible = 0
        self.liPelotas = []
            
            
    #este metodo es llamado en todo momento por la pantalla
    #y sirve para cambiar la posicion de las pelotas multiplicando la vel por
    #una tasa de cambio dt
    #ademas si la pelota se encuentra con una interseccion es decir con un "palito"
    #entonses se camvia el vector velocidad por uno de los vectores en movimiento
    #azaroso()
    #y ademas de todo esto aca se determina si la pelota a llegado a su final
    #con lo cual se pasa a pelotaCaja() con el fin de determinar cual caja es la
    #crecera
    def muevePelotas(self, elCero, primeraYInterseccion):
        j = 0
        self.b = elCero + 0.5        
        
        while j < len(self.liPelotas):            
            l = 0
            if self.bandera2:
                self.liPelotas[j].velocity = vector(0, -.5, 0)
                self.bandera2 = false
            while l < len(self.liIntersecciones):                
                
                if self.liPelotas[j].pos.y == self.liIntersecciones[l]:
                    if self.liPelotas[j].pos.y == primeraYInterseccion:
                        self.bandera2 = true
                    self.liPelotas[j].velocity = self.movimientoAzaroso()
                    
                if self.liPelotas[j].pos.y == self.b:
                    self.liPelotas[j].velocity = self.movimientoAzaroso()
                    
                if self.liPelotas[j].pos.y <= self.b -.5:                    
                    self.cajaPelota(self.liPelotas[j])
                        
                l += 1
                
            self.liPelotas[j].pos = self.liPelotas[j].pos + self.liPelotas[j].velocity * self.dt            
            j += 1
            

    #este metodo se encarga de cambiar el vector velocidad de la pelota que lo pida
    #escojiendo al azar entre las dos posivilidades con lo cual se simula que la pelota
    # pego con un palito
    def movimientoAzaroso(self):
        o_l = random.randint(0, 1)
        
        if o_l == 1:
            return vector(-.5, -1, 0)
        else :
            return vector(.5, -1, 0)
        
    #este metodo se encuentra de checar en cual de las cajas cayo la pelota
    #y hace crecer esta caja
    def cajaPelota(self, pelota):
        j = 0
        x= pelota.pos.x
        pelota.visible = 0
        pelota.pos.x = 2000
        while j < len(self.liXposicion):
           if self.liXposicion[j]+ .5 > x >= self.liXposicion[j]- .5 :
               self.liCajas[j].height += self.radio*2
               self.liCajas[j].y = self.yCaja - self.liCajas[j].height/2
           j += 1
           
    
