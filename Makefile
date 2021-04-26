NM_DIR = ./nm
OTOOL_DIR = ./otool
SHARED_DIR = ./shared

all: shared nm otool

shared:
	$(MAKE) -C $(SHARED_DIR)

nm: shared
	$(MAKE) -C $(NM_DIR)

otool: shared
	$(MAKE) -C $(OTOOL_DIR)

clean:
	$(MAKE) -C $(SHARED_DIR) clean
	$(MAKE) -C $(NM_DIR) clean
	$(MAKE) -C $(OTOOL_DIR) clean

fclean:
	$(MAKE) -C $(SHARED_DIR) fclean
	$(MAKE) -C $(NM_DIR) fclean
	$(MAKE) -C $(OTOOL_DIR) fclean

re:
	$(MAKE) -C $(SHARED_DIR) re
	$(MAKE) -C $(NM_DIR) re
	$(MAKE) -C $(OTOOL_DIR) re

.PHONY: all shared nm otool
