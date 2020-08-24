# include ${METAL_PATH}/mk/wasm.mk
# LDLIBS = ${PROG_LDLIBS}
obj-y := view.o tty.o main.o
CFLAGS += -DCLIENT -Wno-initializer-overrides
LDFLAGS += -lncurses
exe := neverdarkc
