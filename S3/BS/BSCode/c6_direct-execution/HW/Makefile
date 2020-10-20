#
# Makefile
#
# Autor: Vlad Bratulescu
# Erstellt am: 19.10.2020
#
CC = gcc -o
CFLAGS = -std=$(STD) -Wall -Wextra -Wpedantic
STD = gnu11

all: get_time_syscall get_overhead_func get_resolutions get_cost_context_switch get_cost_switch_cpu_usage

clean:
	rm -f *.o get_time_syscall get_overhead_func get_resolutions get_cost_context_switch get_cost_switch_cpu_usage

get_time_syscall: get_time_syscall.c
	$(CC) $@ $< $(CFLAGS)

get_overhead_func: get_overhead_func.c
	$(CC) $@ $< $(CFLAGS)

get_resolutions: get_resolutions.c
	$(CC) $@ $< $(CFLAGS)

get_cost_context_switch: get_cost_context_switch.c
	$(CC) $@ $< $(CFLAGS)

get_cost_switch_cpu_usage: get_cost_switch_cpu_usage.c
	$(CC) $@ $< $(CFLAGS)