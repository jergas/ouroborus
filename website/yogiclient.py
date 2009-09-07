### This is a XML-RPC client which connects with the XML-RPC yogiserver
### which provides Web Services for interested yogis worldwide
### It was written in Python 2.3.4 and tested on WindowsXP on 22nd
### April 2006 by Sat Tara Singh Khalsa. Deg Teh Fateh!


import xmlrpclib
import sys

server = xmlrpclib.ServerProxy("http://spacemonkey.info:8080")

def main():
    print "\n ---- Yogiserver en spacemonkey.info ----"
    print "Teclea un numero y presiona Enter: \n"
    print "\t 1. Recibe un mantra."
    print "\t 2. Recibe una frase de Yogi Bhajan."
    print "\t 3. Agrega un mantra al servidor."
    print "\t 4. Agrega una frase de Yogi Bhajan al servidor."
    print "\t 5. Administra el servidor."
    print "\t 6. Termina la sesion. \n"
    try:
        procedure = raw_input("Escribe un numero: ")
    except:
        print "Esa opcion no es valida"
        return

    if procedure == "1":
        getMantra()
    elif procedure == "2":
        getTeaching()
    elif procedure == "3":
        addMantra()
    elif procedure == "4":
        addTeaching()
    elif procedure == "5":
        administrate()
    elif procedure == "6":
        end()
    else:
        print "Intenta de nuevo"
    return

def administrate():
        
    print "\n --- Menu de administracion del servidor. ---"
    print "Usa estas opciones con cuidado! \n"
    print "Teclea un numero y presiona Enter: \n"
    print "\t 1.  Cuenta los mantras."
    print "\t 2.  Cuenta las frases."
    print "\t 3.  Muestra la lista de mantras."
    print "\t 4.  Muestra la lista de frases."
    print "\t 5.  Elimina un mantra."
    print "\t 6.  Elimina una frase."
    print "\t 7.  Guarda los mantras en disco."
    print "\t 8.  Guarda las frases en disco."
    print "\t 9.  Recupera los mantras."
    print "\t 10. Recupera las frases."
    print "\t 11. Regresa al menu principal. \n"

    try:
        procedure = raw_input("Escribe un numero: ")
    except:
        print "Esa opcion no es valida"
        procedure = "0"

    if procedure == "1":
        countMantras()
    elif procedure == "2":
        countTeachings()
    elif procedure == "3":
        listMantras()
    elif procedure == "4":
        listTeachings()
    elif procedure == "5":
        deleteMantra()
    elif procedure == "6":
        deleteTeaching()
    elif procedure == "7":
        saveMantras()
    elif procedure == "8":
        saveTeachings()
    elif procedure == "9":
        loadMantras()
    elif procedure == "10":
        loadTeachings()
    elif procedure == "11":
        return
    else:
        print "Intenta de nuevo"
    administrate()

def getMantra():
    try:
        mantra = server.pick("mantra")
        print "\n", mantra, "\n"
    except xmlrpclib.Fault, fault:
        print fault.faultString

def getTeaching():
    try:
        teaching = server.pick("teaching")
        print "\n", teaching, "\n"
    except xmlrpclib.Fault, fault:
        print fault.faultString

def addMantra():
    try:
        mantra = raw_input("Escribe el mantra: \n")
        server.add("mantra", mantra)
    except xmlrpclib.Fault, fault:
        print fault.faultString
    

def addTeaching():
    try:
        teaching = raw_input("Escribe la frase: \n")
        server.add("teaching", teaching)
    except xmlrpclib.Fault, fault:
        print fault.faultString

def countMantras():
    try:
        count = server.count("mantra")
        print "\nHay", count, "mantras en el servidor"
    except xmlrpclib.Fault, fault:
        print fault.faultString

    
def countTeachings():
    try:
        count = server.count("teaching")
        print "\nHay", count, "frases en el servidor"
    except xmlrpclib.Fault, fault:
        print fault.faultString


def listMantras():
    try:
        list = server.list("mantra")
        print "\nLista de mantras en el servidor"
        for i in range(len(list)):
            print i,"\t",list[i]
        return list
    except xmlrpclib.Fault, fault:
        print fault.faultString


def listTeachings():
    try:
        list = server.list("teaching")
        print "\nLista de frases en el servidor"
        for i in range(len(list)):
            print i,"\t",list[i]
        return list
    except xmlrpclib.Fault, fault:
        print fault.faultString


def deleteMantra():
    list = listMantras()

    try:
        index = input("\nQue mantra quieres eliminar? ")
    except:
        print "Necesito el numero del mantra"
        administrate()

    if index < 0 or index >= len(list):
        print "El indice no es correcto"
        administrate()

    try:
        server.delete("mantra",index)
    except xmlrpclib.Fault, fault:
        print fault.faultString

def deleteTeaching():
    list = listTeachings()

    try:
        index = input("\nQue frase quieres eliminar? ")
    except:
        print "Necesito el numero de la frase"
        administrate()

    if index < 0 or index >= len(list):
        print "El indice no es correcto"
        administrate()

    try:
        server.delete("teaching",index)
    except xmlrpclib.Fault, fault:
        print fault.faultString

def saveMantras():
    try:
        server.make("mantras.bkp")
    except:
        pass

    try:
        server.save("mantra","mantras.bkp")
    except xmlrpclib.Fault, fault:
        print fault.faultString
        
def saveTeachings():
    try:
        server.make("teachings.bkp")
    except:
        pass

    try:
        server.save("teaching","teachings.bkp")
    except xmlrpclib.Fault, fault:
        print fault.faultString

def loadMantras():
    try:
        server.load("mantra","mantras.bkp")
    except xmlrpclib.Fault, fault:
        print fault.faultString

def loadTeachings():
    try:
        server.load("teaching","teachings.bkp")
    except xmlrpclib.Fault, fault:
        print fault.faultString

def end():
    sys.exit()    


while 1:
    main()

