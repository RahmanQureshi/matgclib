#include "gclib.h"
#include "mex.h"
#include "matrix.h"

/*
* GCLIB_DLL_EXPORTED GReturn GCALL GOpen(GCStringIn address, GCon* g);
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if (nrhs!=1) {
	    mexErrMsgIdAndTxt("matgclib:GOpen:nrhs",
	                      "One input required.");
	}
	if (nlhs==0) {
	    mexErrMsgIdAndTxt("matgclib:GOpen:nrhs",
	                      "At least one output required.");
	}

	char address[1024];
	GReturn rc = -1;
	GCon con = -1;

	mxGetString(prhs[0], address, sizeof(address));
	rc = GOpen(address, &con);

	if(rc!=0) {
	    mexErrMsgIdAndTxt("matgclib:GOpen:ConnectionError",
	                      "Unable to Connect.");
	}

	plhs[0] = (mxArray*) mxCreateDoubleScalar(con);
	plhs[1] = (mxArray*) mxCreateDoubleScalar(rc);

}