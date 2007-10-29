from visual import *

#esta clase se encarga de crear el fondo es decir la parte azul que nos muestra
# la piramide, los palitos que cambian la ruta de las esferas "aunque aqui solo son adornos"
# y la figura de la cual salen las esferas

class fondo:
    li = []
    YCajas = 0
    niveles = 0
    b =0
    inicioPelota = 0
    posYCajas = 0
    liCajas = []
    liIntersecciones = []
    primeraYInterseccion = 0
    liPalitos = []
    liListas = []
   
    #este metodo se encarga de poner un nivel mas en respuesta del llamado del
    # controlador, devido a que al poner un nivel o quitarlo se deven de recalcular
    # sus posiciones ambos metodos ponNivel o quitaNivel llaman a cargaNiveles()
    # y ademas se deve de recalcular la cantidad y posicion de los palitos dentro del
    #fondo lo que se logra con cargaPalitos()
    def ponNivel(self):
        self.borra()        
        self.niveles += 1
        self.cargaNiveles()
        
    #este metodo se encarga de quitar un nivel "vease ponNivel()"
    def quitaNivel(self):
        self.borra()
        self.niveles -= 1
        self.cargaNiveles()
        
    # este metodo se utiliza para borrar la figura geometrica de la cual salen las
    # esferas
    def borra(self):
        j = 0 
        while(j < len(self.li) ):
            self.li[j].visible = 0
            j += 1
            
    #este metodo es el mas importante de esta clase y se encarga de crear las cajas que
    # en conjunto crean la piramide de fono sobre la cual las esferas caen
    def cargaNiveles(self):
        j = 0
        while j < len(self.liPalitos):
            self.liPalitos[j].visible = 0
            j += 1
        self.liPalitos = []
        i = 0
        x = 0
        y = 0
        z = -.1
        longitud = self.niveles # length  x
        ancho = 0.1    #width    z
        altura = 1   #height   y
        alturab = 1 
        j = 0
        self.b = -15
        self.posYCajas = self.b - .5
        self.liIntersecciones = []
        bandera = true
        self.liCajas = []
        while(j < self.niveles):             
            y = alturab*j +self.b
            self.liIntersecciones.append(y)
            if bandera:
                self.YCajas = self.b + ((altura/2)* (-1))
                bandera = false
                if self.niveles %2 == 0:
                    
                    i = 0
                    posX = 0
                    self.liCajas.append(posX)
                    cajas = self.niveles/2
                    while i < cajas:
                        posX += 1
                        self.liCajas.append(posX)
                        i += 1
                        
                    i = 0
                    posX  = -1
                    while i < cajas:
                        self.liCajas.append(posX)
                        i += 1
                        posX -= 1
                                                                                               
                else:
                    
                    i = 0
                    posX = .5
                    cajas = (self.niveles + 1)/2                    
                    while i < cajas:
                        i += 1                        
                        self.liCajas.append(posX)
                        posX += 1
                    i = 0
                    posX= -.5
                    while i < cajas:
                        i += 1
                        self.liCajas.append(posX)
                        posX -= 1 
                   
                    
            self.li.append(box(pos=(x,y,z), length=longitud, height = altura, width=ancho, color=color.blue))
            self.creaPalitos(y, longitud)
            j += 1   
            longitud = self.niveles- j 
        self.primeraYInterseccion = y    
        s = self.li.append(sphere (pos=(x,y+2,z), radius= 2, color=color.green ))
        self.inicioPelota = y + 1

    # este metodo es llamado cada ves que crea niveles() crea un nivel en este metodo
    # se crean los palillos insertados en los niveles azules
    # y determina la altura a la que seran colocados
    # mientras que cuantos nos dice cuantos palitos pondras todo en relacion con
    # que ancho sea el nivel azul al cual se le estan poniendo
    def creaPalitos(self, y, cuantos):
                       
            posY = y - .5
            posX = 0
            if cuantos % 2 == 0:                
                i = 0
                posX = .5
                while i < cuantos/2:
                    self.palito(posX, posY)
                    posX +=1                    
                    i+=1

                i = 0
                posX = -.5
                while i < cuantos/2:
                    self.palito(posX, posY)
                    posX -=1
                    i+=1
            else:                
                posX = 0
                self.palito(posX, posY)
                
                i = 0
                posX = 0
                while i < cuantos/2:
                    posX += 1
                    self.palito(posX, posY)
                    i += 1

                i = 0
                posX = 0
                while i < cuantos/2:                   
                    posX -= 1
                    self.palito(posX, posY)                    
                    i += 1
                                            
    def palito(self, posX, posY):
        self.liPalitos.append(cylinder(pos=(posX, posY, 0), axis=(0, 0, .7), radius=.1, color=color.white))
                            
    def dameInicioPelota(self):
        return self.inicioPelota
    
    def dameIntersecciones(self):
        return self.liIntersecciones
    
    def damePosCajas(self):
        return self.posYCajas
