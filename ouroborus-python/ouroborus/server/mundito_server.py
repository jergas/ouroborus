### This is a XML-RPC server which provides Web Services for interested
### yogis across the WorldWideWeb. It was written in Python 2.3.4 on 22nd
### April 2006 by Sat Tara Singh Khalsa. Deg Teh Fateh!


import SimpleXMLRPCServer, random

class Portal:
    """This is the basic server object"""

    grid = []

    def setGrid(self,list):
        self.grid = list
        return "done"

    def getGrid(self):
        return self.grid

# Now we construct the server:
print "attempting to start server"
OuroborusPortal = Portal()

OuroborusServer = SimpleXMLRPCServer.SimpleXMLRPCServer(("linux.ajusco.upn.mx/~panx",8080))

try:
    OuroborusServer.register_instance(OuroborusPortal)
except:
    print "unable to register methods"

print "server listening on port 8080"
OuroborusServer.serve_forever()
