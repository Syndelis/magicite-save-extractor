#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hivex.h>

// -lhivex

FILE *f;
const char *new_node_str = "\t<pref name=\"%s\" type=\"int\">%d</pref>\n";

int openFile() {

	f = fopen("extracted.prefs", "w");

	if (!f) return 0;
	fprintf(f, "<unity_prefs version_major=\"1\" version_minor=\"1\">\n");

	return 1;

}

void closeFile() {

	fprintf(f, "</unity_prefs>");
	fclose(f);

}

void addNewNode(char *name, int32_t value) {

	char *c;
	for (c = name; *c != '_'; c++);
	*c = '\0';

	fprintf(f, new_node_str, name, value);

	*c = '_';

}

int main(int argc, char **argv) {

	if (argc < 2) {
	
		printf(
			"Usage: \033[34mregedit\033[m [hkcu_file]\n"
			"Typically, this file is located at \033[33mC:\\Users\\[YOUR USER]\\NTUSER.DAT\033[m\n"
		);

		return 0;

	}

	if (!openFile()) {
	
		printf("\033[31mError:\033[m Couldn't create a new file in this directory.");
		return 1;

	}

	hive_h *h = hivex_open(argv[1], 0);
	if (!h) {
	
		printf(
			"\033[31mError:\033[m Couldn't open the registry file. "
			"Make sure you've passed in the right file name.\n"
		);

		fclose(f);
		return 2;

	}

	// hkcu/Software/SmashGames/Magicite
	hive_node_h key = hivex_root(h);

	key = hivex_node_get_child(h, key, "Software");
	key = hivex_node_get_child(h, key, "SmashGames");
	key = hivex_node_get_child(h, key, "Magicite");

	hive_value_h *values = hivex_node_values(h, key);
	char *s;
	
	for (hive_value_h *i = values; *i; i++) {

		s = hivex_value_key(h, *i);
		addNewNode(s, hivex_value_dword(h, *i));

		free(s);

	}

	free(values);
	closeFile();

	hivex_close(h);

	printf(
		"\033[32mSuccessfully\033[m extracted game save data into extracted.prefs\n\n"
		"Make sure to rename that file and place it into the right directory.\n"
		"For Linux users, that would be \033[33m~/.config/unity3d/SmashGames/Magicite/prefs\033[m\n"
	);

	return 0;

}
