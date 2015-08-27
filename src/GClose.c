#include "gclib.h"
#include "mex.h"
#include "matrix.h"

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GClose(GCon g);
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if (nrhs!=1) {
	    mexErrMsgIdAndTxt("matgclib:GClose:nrhs",
	                      "One input required.");
	}

	GReturn rc = 0;
	GCon con = -1;

	con = mxGetScalar(prhs[0]);
	rc = GClose(con);

	plhs[0] = (mxArray*) mxCreateDoubleScalar(rc);
}