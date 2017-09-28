#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

#define MAX_PATH 4096

extern "C"
{
	char * traceFilename = NULL;
	char traceFile[ MAX_PATH ];
	char traceFilePattern[ MAX_PATH ] = "";
	char * setTraceFile(char * traceFile)
	{
		traceFilename = traceFile;
		return traceFilename;
	}
	void setPattern(char*p)
	{
	}
	void trace(const char*s,const char * format,va_list & vlist)
	{
		time_t timer;
		struct tm  * tbuf;
		char buffer2[ 512 ];
		char buffer3[ 128 ];
		struct timeval tval;
		struct timezone tz;
		char buffer[8192];
		//va_list(vlist);
		//va_start(vlist,format);
		vsnprintf(buffer,sizeof(buffer),format,vlist);
		va_end(vlist);
		gettimeofday(&tval,&tz);
		tbuf = gmtime(&tval.tv_sec);
		strftime( buffer2 , sizeof(buffer2) ,
					"%Y%m%d %H%M%S",tbuf);
		sprintf(buffer3,"%04d",getpid());
		FILE * fp = fopen(traceFilename,"a");
		if(fp)
		{
			try
			{
			fprintf(fp,"\n%s%02d:%s:%3s:%s",buffer2,
					(int)(tval.tv_usec%1000)/10,buffer3,s,buffer);
			}
			catch(...)
			{
				printf("Logger error\n");
			}
			fclose(fp);
		}
	}

}
