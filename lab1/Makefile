#------------------------------------------------------------------------------
# Ari Iramanesh, 1628897, 12M, Makefile, 
# Archives HelloUser.java and HelloUser2.java, creates a jar executable for 
# HelloUser2.java, and cleans the .class files.
#------------------------------------------------------------------------------
JAVASRC = HelloUser.java HelloUser2.java
SOURCES = README Makefile $(JAVASRC)
MAINCLASS = HelloUser2
CLASSES = HelloUser.class HelloUser2.class
JARFILE = Hello

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(CLASSES)
	rm Manifest
	chmod +x $(JARFILE)

$(CLASSES): $(JAVASRC)
	javac -Xlint $(JAVASRC)

clean:
	rm $(CLASSES)
