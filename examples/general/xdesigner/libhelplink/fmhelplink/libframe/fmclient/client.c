#if defined(sonyriscV) || defined(OKI) || defined(USL)
#include <netinet/in.h>
#endif

#include <stdio.h>
#include <rpc/rpc.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>

#ifdef SUNVIEW_RECT
#include <sunwindow/notify.h>
#endif
#include <X11/Intrinsic.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <signal.h>

#include "stdfm_rpc.h"
#include "fm_commands.h"

#ifdef	USL
/* this means V.4 */
#define	BCOPY(s1, s2, n)	memcpy(s2, s1, n)
#define	BZERO(s, n)		memset(s, 0, n)
#else
#define	BCOPY(s1, s2, n)	bcopy(s1, s2, n)
#define	BZERO(s, n)		bzero(s, n)
#endif

#define Success 0
#define Failure -1

static struct timeval fiveSeconds = { 5, 0 };
static struct timeval halfMinute = { 30, 0 };
static FmRpcNiceErrorT xd_nice;
extern Display *d;
extern char *propName;
#define FRAME_RPC "_Frame_RPC"

/*
I call RPC's.
*/

/*
Utilities.
*/

getHostAndPort(host, portNum)
char *host;
int *portNum;
{
    Atom prop, actualType;
    int actualFormat;
    long itemCount, bytesAfter;
    unsigned char *data;
    
    if (strcmp(propName, "none") == 0) {
	strcpy(host, "localhost");
	*portNum = FM_RPC_PROG;
    } else  {
	if (strcmp(propName, "") == 0)
	    strcpy(propName, FRAME_RPC);

	prop = XInternAtom(d, propName, False);

	XGetWindowProperty(d, RootWindowOfScreen(DefaultScreenOfDisplay(d)), 
			   prop, 0, 256,
			   False, AnyPropertyType, &actualType, &actualFormat,
			   &itemCount, &bytesAfter, &data);

	*host = 0;
	*portNum = -1;

	if (actualType != None) {
	    while (*data != ':')
		*host++ = *data++;
	    *host = 0;
	    data++;
	    sscanf(data, "%d", portNum);
	}
    }
}


RegisterRPC(prog, vers)
int prog;
int vers;
{
char hostname[128];
char buf[256];
Atom prop;

	prop = XInternAtom(d, "_Frame_fmbitmapRPC", False);
	gethostname(hostname, sizeof(hostname));
	sprintf(buf,"%s:%d:%d",hostname, prog, vers);
	XChangeProperty(d, RootWindowOfScreen(DefaultScreenOfDisplay(d)),
		prop, XA_STRING, 8, PropModeReplace, buf, strlen(buf));
	XFlush(d);

}

static bool_t localCall(proc, inproc, in, outproc, out, total_timeout)
struct timeval total_timeout;
char *in, *out;
xdrproc_t inproc, outproc;
{
struct hostent *hp;
int addrlen, sock = RPC_ANYSOCK;
CLIENT *client;
enum clnt_stat clnt_stat;
struct sockaddr_in server_addr;
char rpcHost[128];
int  rpcPort;

getHostAndPort(rpcHost, &rpcPort);
hp = gethostbyname(rpcHost);
if (! hp)
	return (FALSE);

addrlen = sizeof(struct sockaddr_in);
BCOPY(hp->h_addr, (caddr_t)&server_addr.sin_addr, hp->h_length);
server_addr.sin_family = AF_INET;
server_addr.sin_port = 0;

client = clntudp_create(&server_addr, rpcPort, FM_RPC_VERS, total_timeout, &sock); 
if (! client)
	return (FALSE);
	
clnt_stat = clnt_call(client, proc, inproc, in, outproc, out, total_timeout);
if (clnt_stat != RPC_SUCCESS) {
	clnt_perror(client, "");
	return (FALSE);
}

close(sock);
clnt_destroy(client);
return (TRUE);
}

static freeReturn(returnp, freer)
char *returnp;
xdrproc_t freer; 
{
XDR anXdrStream;

xdrmem_create(&anXdrStream, returnp, 8 * 1024, XDR_FREE);
freer(&anXdrStream, returnp);
}

/*
RPC's.
*/

static void doFmCommands(doc, codes, num) 
unsigned int doc;
int *codes;
unsigned int num;
{
FmRpcCommandsArgT arg;

arg.doc = doc; 
arg.commands.FmRpcCommandsT_len = num;
arg.commands.FmRpcCommandsT_val = codes;
BZERO(&xd_nice, sizeof(xd_nice));
if (localCall(FM_RPC_COMMANDS, xdr_FmRpcCommandsArgT, &arg, xdr_FmRpcNiceErrorT, &xd_nice, halfMinute)) {
	if (xd_nice.code != Success)
		;
	freeReturn(&xd_nice, xdr_FmRpcNiceErrorT);
}
}

int CloseDoc(doc)
unsigned int doc;
{
int codes[12];

codes[0] = KBD_CLOSEWIN;
doFmCommands(doc, codes, 1);
}

int OpenDoc(doc)
char *doc;
{ 
FmRpcOpenDocArgT arg;
FmRpcOpenDocReturnT openDocReturn;
int handle;

arg.doc = doc;
BZERO(&openDocReturn, sizeof(openDocReturn));
handle = -1;
if (localCall(FM_RPC_OPEN_DOC, xdr_FmRpcOpenDocArgT, &arg, xdr_FmRpcOpenDocReturnT, &openDocReturn, halfMinute)) {
	if (openDocReturn.nice.code != Success) {
	}
	else handle = openDocReturn.doc;
	freeReturn(&openDocReturn, xdr_FmRpcOpenDocReturnT);
}
return (handle);
}

int GoToLink(src, dst, tag, isNewWindow)
unsigned int src;
char *dst;

/*
** Fixed by IST
** tag should be declared as char * to avoid compilation warning
*/
char *tag;

unsigned int isNewWindow;
{ 
FmRpcGoToLinkArgT arg;

arg.doc = src;
arg.dstDoc = dst;
arg.tag = tag;
arg.isNewWindow = isNewWindow;
BZERO(&xd_nice, sizeof(xd_nice));
if (localCall(FM_RPC_GO_TO_LINK, xdr_FmRpcGoToLinkArgT, &arg, xdr_FmRpcNiceErrorT, &xd_nice, halfMinute)) {
	if (xd_nice.code != Success) {
		freeReturn(&xd_nice, xdr_FmRpcNiceErrorT);
		return (-1);
	}
	freeReturn(&xd_nice, xdr_FmRpcNiceErrorT);
	return (0);
}
return (-1);
}

int Import(file) 
char *file;
{
FmRpcImportArgT arg;

arg.doc = NULL; 
arg.file = file; 
arg.isCurrentDoc = 1;
arg.isCopy = 0;
BZERO(&xd_nice, sizeof(xd_nice));
if (localCall(FM_RPC_IMPORT, xdr_FmRpcImportArgT, &arg, xdr_FmRpcNiceErrorT, &xd_nice, halfMinute)) {
	if (xd_nice.code != Success) {
		freeReturn(&xd_nice, xdr_FmRpcNiceErrorT);
		return (-1);
	}
	freeReturn(&xd_nice, xdr_FmRpcNiceErrorT);
	return (0);
}
return (-1);
}
