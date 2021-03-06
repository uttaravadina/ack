# $Id$

#PARAMS		do not remove this line!

OBJLIB=$(TARGET_HOME)/modules/lib/libobject.$(LIBSUF)

SRC_DIR = $(SRC_HOME)/mach/sun3/cv

all:	cv

cv:	cv.$(SUF)
	$(CC) $(LDOPTIONS) -o cv cv.$(SUF) $(OBJLIB)

Xcv:	Xcv.$(SUF)
	$(CC) $(LDOPTIONS) -o Xcv Xcv.$(SUF) $(OBJLIB)

cv.$(SUF):	$(SRC_DIR)/cv.c
	$(CC) $(COPTIONS) -DMACH=2 -I$(TARGET_HOME)/h -c $(SRC_DIR)/cv.c

Xcv.$(SUF):	$(SRC_DIR)/Xcv.c
	$(CC) $(COPTIONS) -DMACH=2 -I$(TARGET_HOME)/h -c $(SRC_DIR)/Xcv.c

install:	all
	-mkdir $(TARGET_HOME)/lib.bin/sun3
	cp cv $(TARGET_HOME)/lib.bin/sun3/cv

cmp:	all
	-cmp cv $(TARGET_HOME)/lib.bin/sun3/cv

clean:
	rm -f *.$(SUF) Out cv

lint:
	$(LINT) $(LINTOPTIONS) -DMACH=2 -I$(TARGET_HOME)/h $(SRC_DIR)/cv.c $(UTIL_HOME)/modules/lib/$(LINTPREF)object.$(LINTSUF)

pr:
	@pr $(SRC_DIR)/proto.make $(SRC_DIR)/cv.c $(SRC_DIR)/Xcv.c

opr:
	make pr | opr
