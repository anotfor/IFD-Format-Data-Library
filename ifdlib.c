#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ystrlib.h"

char * readkey(FILE *stream, char * keyname) {
	char tlist[256];
	const char *ss="";
	int ii = 0;
	int jj = 0;
	int toggle = 0;
	int isn = 0;
	int isl = 0;
	for(int x = 0;; x++) {
		fgets(tlist, sizeof(tlist), stream); 
		if(0 != ystrstr(tlist, keyname)) {
			ss= ystrstr(tlist, "=");
			if(0 != ss) {
				break;
			}
		}
		if(0 == ystrcmp(tlist, "[endfile]")) {
			return 0;
		}
	}
	for(int cc = 0; 0 != ss[cc]; cc++) {
		if((ss[cc] == '\"') && (toggle == 0)) {
			toggle = 1;
		} else if((ss[cc] == '\"') && (toggle == 1)) {
			toggle = 0;
		}
		if(0 != isalpha(ss[cc])) {
			isl = 1;
		}
		if(0 != isdigit(ss[cc])) {
			isn = 1;
		}
		if((0 != isdigit(ss[cc])) && (toggle == 1)) {
			isl = 1;
		}
		if((isn == 1) && (isl == 1) && (toggle == 0)) {
			return 0;
		}
		if((0 != isalpha(ss[cc])) && (toggle == 0)) {
			return 0;
		}
	}
	char * value = malloc(sizeof(tlist+1));
	if(0 != ystrstr(ss, keyname)) {
		return 0;
	}
	for(;ss[ii+1] != '\n'; ii++, jj++) {
		value[jj] = ss[ii+1];
	}
	return value+1;
}

char * objreadkey(FILE *stream, char * keyname, int index) {
	char tlist[256];
	const char *ss="";
	int ii = 0;
	int jj = 0;
	int toggle = 0;
	int isn = 0;
	int isl = 0;
	int entindex = 0;
	for(int x = 0;; x++) {
		fgets(tlist, sizeof(tlist), stream); 
		if(0 != ystrstr(tlist, keyname)) {
			ss= ystrstr(tlist, "=");
			if(0 != ystrstr(tlist, "{")) {
				for(int counter = 0;; counter++) {
					fgets(tlist, sizeof(tlist), stream);
					if(counter == index) {
						goto found;
					}
					if(0 != ystrstr(tlist, "}")) {
						return 0;
					}
				}
			}
			if(0 != ss) {
				entindex += 1;
			}
			if((0 != ss) && (entindex == index)) {
				break;
			}
		}
		if(0 == ystrcmp(tlist, "[endfile]")) {
			return 0;
		}
	}
	for(int cc = 0; 0 != ss[cc]; cc++) {
		if((ss[cc] == '\"') && (toggle == 0)) {
			toggle = 1;
		} else if((ss[cc] == '\"') && (toggle == 1)) {
			toggle = 0;
		}
		if(0 != isalpha(ss[cc])) {
			isl = 1;
		}
		if(0 != isdigit(ss[cc])) {
			isn = 1;
		}
		if((0 != isdigit(ss[cc])) && (toggle == 1)) {
			isl = 1;
		}
		if((isn == 1) && (isl == 1) && (toggle == 0)) {
			return 0;
		}
		if((0 != isalpha(ss[cc])) && (toggle == 0)) {
			return 0;
		}
	}
	char * value = malloc(sizeof(tlist)+1);
	if(0 != ystrstr(ss, keyname)) {
		return 0;
	}
	for(;ss[ii+1] != '\n'; ii++, jj++) {
		value[jj] = ss[ii+1];
	}
	return value+1;
	found:;
	value = malloc(sizeof(tlist)+1);
	value = ystrdel(tlist);
	if(0 != ystrstr(tlist, "}")) {
		value = NULL;
	}
	return value;
}

char * readindex(FILE *stream, int index) {
	char tlist[256];
	const char *ss="";
	int ii = 0;
	int jj = 0;
	int toggle = 0;
	int isn = 0;
	int isl = 0;
	int entindex = 0;
	for(int x = 0;; x++) {
		fgets(tlist, sizeof(tlist), stream); 
		ss= ystrstr(tlist, "=");
		if(0 != ss) {
			entindex += 1;
		}
		if((0 != ss) && (entindex == index)) {
			break;
		}
		if(0 == ystrcmp(tlist, "[endfile]")) {
			return 0;
		}
	}
	for(int cc = 0; 0 != ss[cc]; cc++) {
		if((ss[cc] == '\"') && (toggle == 0)) {
			toggle = 1;
		} else if((ss[cc] == '\"') && (toggle == 1)) {
			toggle = 0;
		}
		if(0 != isalpha(ss[cc])) {
			isl = 1;
		}
		if(0 != isdigit(ss[cc])) {
			isn = 1;
		}
		if((0 != isdigit(ss[cc])) && (toggle == 1)) {
			isl = 1;
		}
		if((isn == 1) && (isl == 1) && (toggle == 0)) {
			return 0;
		}
		if((0 != isalpha(ss[cc])) && (toggle == 0)) {
			return 0;
		}
	}
	char * value = malloc(sizeof(tlist+1));
	for(;ss[ii+1] != '\n'; ii++, jj++) {
		value[jj] = ss[ii+1];
	}
	return value+1;
}
