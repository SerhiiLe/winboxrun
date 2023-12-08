#include <windows.h>
#include <stdio.h>
#include "url_parser.h"

bool isFile(LPSTR strFileName) {
	DWORD ret = GetFileAttributes(strFileName);
	return ((ret != INVALID_FILE_ATTRIBUTES) && !(ret & FILE_ATTRIBUTE_DIRECTORY));
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	const char version[] = "Winbox runner for CCS billing. Version 1.4";
	const char url_help[] = "\nwinbox://username:password@host_ip\nor\nwinbox://host_ip/username/pasword";
	const int MAX_STR = _MAX_PATH + 64;
	int i;
	struct parsed_url *purl;
	int writed;
	
	int argc;
	LPWSTR *argv;

	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
   	if( NULL == argv ) {
		MessageBox(NULL, "error in parse CMDLINE","Winbox runner",MB_ICONEXCLAMATION|MB_OK);
		return 1;	
	}

	char *s = (char*)malloc(MAX_STR);

	// Check the number of parameters
	if (argc < 2) {
		// Tell the user how to run the program
		snprintf(s,255,"Usage: %ls URL\nURL is:%s",argv[0],url_help);
		MessageBox(NULL, s, version, MB_OK);
		/* "Usage messages" are a conventional way of telling the user
		* how to run a program if they enter the command incorrectly.
		*/
		return 1;
	}

	snprintf(s,MAX_STR,"%ls",argv[1]);
	purl = parse_url(s);
	if( NULL == purl ) {
		snprintf(s,MAX_STR,"Wrong URL format: \"%ls\"\nMust be:%s",argv[1],url_help);
		MessageBox(NULL, s, version, MB_ICONEXCLAMATION|MB_OK);
		return 1;
	}

	char *path = (char*)malloc(MAX_STR);

	snprintf(path,_MAX_PATH,"%ls",argv[0]);
	char *path_end = strrchr(path,'\\');
	if( NULL == path_end ) {
		path_end = path+1;
		strcpy(path,".\\");
	}
	if (path) {
		strncpy(path_end+1,"winbox.exe",MAX_STR-(path_end-path)-1);
		if( ! isFile(path) ) {
			*(path_end+1) = 0;
			snprintf(s,MAX_STR,"The winbox.exe is not finded in %s",path);
			MessageBox(NULL, s, version, MB_ICONEXCLAMATION|MB_OK);
			return 1;
		}
		*path_end = 0;
	}
	
	writed = snprintf(s,MAX_STR,"%s",purl->host);
	if( NULL != purl->port ) {
		writed += snprintf(s+writed,MAX_STR-writed,":%s",purl->port);
	}
	if( NULL != purl->username ) {
		writed += snprintf(s+writed,MAX_STR-writed," %s",purl->username);
		if( NULL != purl->password ) {
			writed += snprintf(s+writed,MAX_STR-writed," %s",purl->password);
		}
	}
	if( NULL != purl->path ) {
		for(i = 0; i < strlen(purl->path); i++) {
			if( purl->path[i] == 47 ) {
				purl->path[i] = 32;
			}
		}
		snprintf(s+writed,MAX_STR-writed," %s",purl->path);
	}

	//MessageBox(NULL, s, version, MB_ICONEXCLAMATION|MB_OK);
	ShellExecute(NULL,"open","winbox.exe",s,path,SW_SHOWNORMAL);

	free(path);
	free(s);
	parsed_url_free(purl);
  	return 0;
}

