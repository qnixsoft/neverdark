# include ${METAL_PATH}/mk/wasm.mk
# LDLIBS = ${PROG_LDLIBS}
obj-y := view.o tty.o main.o
CFLAGS += -DCLIENT -Wno-initializer-overrides -I/usr/X11R6/include
LDFLAGS += -lncurses -lX11 -L/usr/X11R6/lib -lGL -lGLU
exe := neverdarkc
