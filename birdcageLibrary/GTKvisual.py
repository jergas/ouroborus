import pygtk; pygtk.require('2.0')
import gtk
import Image
import ImageDraw

class GtkVisual:
     def __init__(self):
          self.window = gtk.Window()
          self.vbox = gtk.VBox()
          self.title = gtk.Label("Circadian")
          self.image = gtk.Image()
          self.vbox.pack_start(self.title)
          self.vbox.pack_start(self.image)
          self.window.add(self.vbox)
          self.window.show_all()
          self.gtk = gtk
          
     def generate(self, automaton, environment, side=100, output='buffer.tiff'):
          '''This function generates a buffer image that will be the main visual feature of the viewer
          it requires an automaton coded as a list, an environment value and an image size (default is 100). Note that the number of pixels
          on the image must be equal to the number of cells on the automaton'''
          self.picture = Image.new("RGB", (side,side))
          self.draw = ImageDraw.Draw(self.picture)
          
          for i in range(0,side):
               for j in range(0,side):
                    if automaton[(side*i)+j]-5<= environment <= automaton[(side*i)+j]+5:
				     self.draw.point((i,j),(0,255,0))
                    else:
				     self.draw.point((i,j),(0,0,0))
				     
          self.picture = self.picture.resize((5*self.picture.size[0],5*self.picture.size[1]), Image.NEAREST)
          self.picture.save(output)
		
     def update(self, inputIm='buffer.tiff'):
	     '''Updates the image inside the viewer'''
	     self.image.set_from_file(inputIm)
             return True

    # def main(self):
          #gtk.main()
