#include "gclib.h"
#include "mex.h"
#include "matrix.h"

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GCommand(GCon g, GCStringIn command, GBufOut buffer, GSize buffer_len, GSize* bytes_returned);
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if (nrhs!=2) {
	    mexErrMsgIdAndTxt("matgclib:GCommand:nrhs",
	                      "Two inputs required.");
	}

	GReturn rc = 0;
	GCon con = -1;
	char command[1024];
	char buffer[1024]; //traffic buffer

	mxGetString(prhs[1], command, sizeof(command));
	con = mxGetScalar(prhs[0]);
	
	rc = GCommand(con, command, buffer, sizeof(buffer), 0);

	plhs[0] = (mxArray*) mxCreateString(buffer);
	plhs[1] = (mxArray*) mxCreateDoubleScalar(rc);
}