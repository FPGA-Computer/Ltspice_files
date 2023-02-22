#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SEARCH_PARM	argv[1]
#define INFILE 			argv[2]
#define OUTFILE 		argv[3]

int main(int argc,char *argv[])
{
	FILE *infile, *outfile;
	char buffer[10000], *start, *parm, *parm_end;
	int parm_len, sub;

	if (argc!=4)
	{
		printf("Move macro model <parameter> to front\n",argv[0]);
		printf("Usage: %s <parameter> <infile> <outfile>\n",argv[0]);
		return 0;
	}

	if((infile=fopen(INFILE,"r")) && (outfile=fopen(OUTFILE,"w")))
	{
		parm_len = strlen(SEARCH_PARM);

		while(!feof(infile))
		{
			if(!fgets(buffer,sizeof(buffer)-1,infile))
				break;

			start = strchr(buffer,'(');
			parm = start;
			sub = 0;

			while(parm)
			{
				// case insensitive strstr
				parm = _stristr(parm,SEARCH_PARM);

				if(!parm)
					break;

				// try to match parameter that starts with ( or space
				if(((parm[-1]=='(')||(parm[-1]==' '))&&(parm[parm_len] == '='))
				{	
					char *p1;

					// scan for end of parm to either space or )
					for(p1 = parm; (*p1 != ' ') && (*p1 != ')'); p1++)
						;
					parm_end = p1;

					// output before start
					for(p1 = buffer;p1!=start+1;p1)
						putc(*p1++,outfile);

					// output parm first
					for(p1 = parm;p1!=parm_end+1;p1)
						putc(*p1++,outfile);

					// output what was just before parm
					for(p1 = start+1;p1!=parm;p1)
						putc(*p1++,outfile);

					// output after parm
					for(p1 = parm_end+1;*p1;p1)
						putc(*p1++,outfile);

					sub = 1;
					break;
				}
				else
					parm++;
			}

			if(!sub)
				fprintf(outfile,"%s",buffer);
		}
	}
	else
	{
		printf("can't open file(s) %s\n",infile?argv[3]:argv[2]);

		if(infile)
			fclose(infile);

		return 0;
	}

	fclose(infile);
	fclose(outfile);	
}
