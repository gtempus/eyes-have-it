all: 
	make -f MakefileAVR.mk all

flash:
	make -f MakefileAVR.mk flash

size:
	make -f MakefileAVR.mk size

clean:
	make -f MakefileAVR.mk clean
