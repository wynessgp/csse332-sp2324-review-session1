all: report.bin scout.bin

CFLAGS+=-Wall 

%.bin: %.o
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^ -lm

.PHONY: clean all
clean:
	rm -rf *.bin *.o
