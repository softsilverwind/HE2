#include <stdio.h>
#include "serror.h"

void serror(int severity, const char *message)
{
	switch(severity)
	{
		case 1:
			fprintf(stderr, SE_COLOR_GREEN "Notification: ");
			break;
		case 2:
			fprintf(stderr, SE_COLOR_YELLOW "Warning: ");
			break;
		case 3:
			fprintf(stderr, SE_COLOR_RED "Error: ");
			break;
		case 4:
			fprintf(stderr, SE_COLOR_BLUE "Internal error: ");
			break;
		default:
			break;
	}

	fprintf(stderr, SE_COLOR_WHITE "%s\n", message);
}
