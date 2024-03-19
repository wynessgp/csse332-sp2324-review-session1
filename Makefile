all: report.bin scout.bin armory.bin

CFLAGS+=-Wall 

%.bin: %.o
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^ -lm

.PHONY: clean all
clean:
	rm -rf *.bin *.o
