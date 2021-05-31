all: regedit
regedit: regedit.c
	gcc regedit.c -o regedit -lhivex

clean:
	rm regedit
