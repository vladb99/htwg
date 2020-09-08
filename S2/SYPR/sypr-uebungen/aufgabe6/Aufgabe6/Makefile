#
# Makefile
#
# Autor: Vlad Bratulescu
# Erstellt am: 12.07.2020
#

PACKAGES=lib bin
.PHONY: all clean
all clean:
	for p in $(PACKAGES); do \
		(cd $$p && $(MAKE) $@); \
	done
