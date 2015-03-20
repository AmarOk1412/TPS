REPERTOIRES = src plugins

.PHONY : all $(REPERTOIRES) clean

all : $(REPERTOIRES)

$(REPERTOIRES):
	$(MAKE) -k -C $@ all

clean :
	for rep in $(REPERTOIRES); do \
	  $(MAKE) -k -C $$rep clean; \
	done
