SRC_FILES = csapp_forks.c exec_argv1.c exec_argv1_err.c exec_psd.c exec_psd_imp.c fork_simple.c fork_exam_eg.c fork_exam_eg_imp.c print_exec_args.c printsleepdie.c simple_shell1.c simple_shell2.c sighandler1.c 07pr2.c fork1.c sighandler12.c
EXECS     = ${SRC_FILES:.c=}
O_FILES   = $(SRC_FILES:%.c=%.o)

CC        = gcc
CFLAGS    = -Wall -O2
LDFLAGS   = 
LDLIBS    = 

all: $(EXECS)

clean:
	rm -f $(EXECS)
