/*! \file gclibo.h
*
* Open-source convenience functions for Galil C Lib.
* Please email softwarefeedback@galil.com with suggestions for useful/missing functions.
*
*/
#ifndef I_007AD0AF_C956_4B96_ADE2_AD04FAFFEE99
#define I_007AD0AF_C956_4B96_ADE2_AD04FAFFEE99

//set library visibility for gcc and msvc
#if BUILDING_GCLIB && HAVE_VISIBILITY
#define GCLIB_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_GCLIB && defined _MSC_VER
#define GCLIB_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define GCLIB_DLL_EXPORTED __declspec(dllimport)
#else
#define GCLIB_DLL_EXPORTED
#endif

#define _CRT_SECURE_NO_WARNINGS //use traditional C calls like strncpy()

#include "gclib.h" //Galil's C Library
#include <stdlib.h> //atoi, atof
#include <string.h> //strcpy
#include <stdio.h> //fopen
#include <math.h> //log()

#ifdef _WIN32
#define GCALL __stdcall
#else
#define GCALL  /* nothing */
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SMALLBUF 256 //size for a small buffer response.
#define MALLOCBUF 500000 //malloc used for large program and array uploads.
#define MAXPROG MALLOCBUF //maximum size for a program.
#define MAXARRAY MALLOCBUF //maximum size for an array table upload.
#define POLLINGINTERVAL 100 //interval for polling commands, in miliseconds.

	//! Uses GUtility() and `G_UTIL_SLEEP` to provide a blocking sleep call which can be useful for timing-based chores.
	GCLIB_DLL_EXPORTED void GCALL GSleep(unsigned int timeout_ms);
	/*!<
	*  \param timeout_ms The timeout, in milliseconds, to block before returning.
	*
	*  See GMotionComplete() for an example.
	*/


	//! Uses GUtility() and `G_UTIL_VERSION` to provide the library version number.
	GCLIB_DLL_EXPORTED GReturn GCALL GVersion(GCStringOut ver, GSize ver_len);
	/*!<
	*  \param ver Buffer to hold the output string. Buffer will be null terminated, even if the data must be truncated to do so.
	*  \param ver_len Length of buffer.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_examples.cpp for an example.
	*/

	//! Uses GUtility() and `G_UTIL_ADDRESSES` to provide a listing of all available connection addresses.
	GCLIB_DLL_EXPORTED GReturn GCALL GAddresses(GCStringOut addresses, GSize addresses_len);
	/*!<
	*  \note Serial ports are listed, e.g. COM1. It may be necesary to specify a baud rate for the controller, e.g. `--baud 19200`.
	*        Default baud is 115200. See GOpen().
	*
	*  \param addresses Buffer to hold the output string. Buffer will be null terminated, even if the data must be truncated to do so.
	*  \param addresses_len Length of buffer.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*/

	//! Uses GUtility() and `G_UTIL_INFO` to provide a useful connection string.
	GCLIB_DLL_EXPORTED GReturn GCALL GInfo(GCon g, GCStringOut info, GSize info_len);
	/*!<
	*  \param g Connection's handle.
	*  \param info Buffer to hold the output string. Buffer will be null terminated, even if the data must be truncated to do so.
	*  \param info_len Length of buffer.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_examples.cpp for an example.
	*/


	//! Uses GUtility() and `G_UTIL_TIMEOUT_OVERRIDE` to set the library timeout.
	GCLIB_DLL_EXPORTED GReturn GCALL GTimeout(GCon g, short timeout_ms);
	/*!<
	*  \param g Connection's handle.
	*  \param timeout_ms The value to be used for the timeout. Use `G_USE_INITIAL_TIMEOUT` to set the timeout back to the initial GOpen() value, `--timeout`.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gcommand.cpp and x_gread_gwrite.cpp for examples.
	*/


	//! Wrapper around GCommand for use when the return value is not desired.
	GCLIB_DLL_EXPORTED GReturn GCALL GCmd(GCon g, GCStringIn command);
	/*!<
	*  The returned data is still checked for error, e.g. `?` or timeout, but is not brought out through the prototype.
	*
	*  \param g Connection's handle.
	*  \param command Null-terminated command string to send to the controller.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gcommand.cpp for an example.
	*/


	//! Wrapper around GCommand that trims the response.
	GCLIB_DLL_EXPORTED GReturn GCALL GCmdT(GCon g, GCStringIn command, GCStringOut trimmed_response, GSize response_len, GCStringOut* front);
	/*!<
	*  For use when the return value is desired, is ASCII (not binary), and the response should be trimmed of trailing colon, whitespace, and optionally leading space.
	*
	*  \param g Connection's handle.
	*  \param command Null-terminated command string to send to the controller.
	*  \param trimmed_response The trimmed response from the controller. Trailing space is trimmed by null terminating any trailing spaces, carriage returns, or line feeds.
	*  \param response_len The length of the trimmed_response buffer.
	*  \param front If non-null, upon return *front will point to the first non-space character in trimmed_response.
	*          This allows trimming the front of the string without modifying the user's buffer pointer, which may be allocated on the heap.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gcommand.cpp for an example.
	*/


	//! Wrapper around GCommand that provides the return value of a command parsed into an int.
	GCLIB_DLL_EXPORTED GReturn GCALL GCmdI(GCon g, GCStringIn command, int* value);
	/*!<
	*  Use this function to get most values including TP, RP, TE, Digital I/O states, etc.
	*
	*  \param g Connection's handle.
	*  \param command Null-terminated command string to send to the controller.
	*  \param value Pointer to an int that will be filled with the return value.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gcommand.cpp for an example.
	*/


	//! Wrapper around GCommand that provides the return value of a command parsed into a double.
	GCLIB_DLL_EXPORTED GReturn GCALL GCmdD(GCon g, GCStringIn command, double* value);
	/*!<
	*  Use this function to retrieve the full Galil 4.2 range, e.g. for a variable value with fractional data,
	*  or the value of an Analog input or Output.
	*
	*  \param g Connection's handle.
	*  \param command Null-terminated command string to send to the controller.
	*  \param value Pointer to a double that will be filled with the return value.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gcommand.cpp for an example.
	*/


	//! Blocking call that returns once all axes specified have completed their motion.
	GCLIB_DLL_EXPORTED GReturn GCALL GMotionComplete(GCon g, GCStringIn axes);
	/*!<
	*  \note This function uses a profiled motion indicator, not the position of the encoder. E.G. see the difference between AM (profiled) and MC (encoder-based).
	*
	*  Although using the _BGm operand is the most generally compatible method,
	*  there are higher-performance ways to check for motion complete by using
	*  the data record, or interrupts. See examples x_dr_motioncomplete() and x_ei_motioncomplete().
	*
	*  \param g Connection's handle.
	*  \param axes A null-terminated string containing a multiple-axes mask. Every character in the string should be a valid argument to MG_BGm, i.e. XYZWABCDEFGHST.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_gmotioncomplete.cpp for an example.
	*/


	//! Sets the asynchronous data record to a user-specified period via `DR`.
	GCLIB_DLL_EXPORTED GReturn GCALL GRecordRate(GCon g, double period_ms);
	/*!<
	*  Takes TM and product type into account and sets the `DR` period to the period requested by the user, if possible.
	*
	*  \param g Connection's handle.
	*  \param period_ms Period, in milliseconds, to set up for the asynchronous data record.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_grecord.cpp for an example.
	*/


	//! Program download from file.
	GCLIB_DLL_EXPORTED GReturn GCALL GProgramDownloadFile(GCon g, GCStringIn file_path, GCStringIn preprocessor);
	/*!<
	*  \param g Connection's handle.
	*  \param file_path Null-terminated string containing the path to the program file.
	*  \param preprocessor Options string for preprocessing the program before sending it to the controller. See GProgramDownload().
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_programs.cpp for an example.
	*/


	//! Program upload to file.
	GCLIB_DLL_EXPORTED GReturn GCALL GProgramUploadFile(GCon g, GCStringIn file_path);
	/*!<
	*  \param g Connection's handle.
	*  \param file_path Null-terminated string containing the path to the program file, file will be overwritten if it exists.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_programs.cpp for an example.
	*/


	//! Array download from file.
	GCLIB_DLL_EXPORTED GReturn GCALL GArrayDownloadFile(GCon g, GCStringIn file_path);
	/*!<
	*  Downloads a csv file containing array data at `file_path`.
	*
	*  \param g Connection's handle.
	*  \param file_path Null-terminated string containing the path to the array file.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_arrays.cpp for an example.
	*/


	//! Array upload to file.
	GCLIB_DLL_EXPORTED GReturn GCALL GArrayUploadFile(GCon g, GCStringIn file_path, GCStringIn names);
	/*!<
	*  Uploads the entire controller array table or a subset and saves the data as a csv file specified by `file_path`.
	*
	*  \param g Connection's handle.
	*  \param file_path Null-terminated string containing the path to the array file, file will be overwritten if it exists.
	*  \param names Null-terminated string containing the arrays to upload, delimited with space. "" or null uploads all arrays listed in LA.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  See x_arrays.cpp for an example.
	*/

	
	//! Provides a list of all Galil controllers requesting IP addresses via BOOT-P or DHCP.
	GCLIB_DLL_EXPORTED GReturn GCALL GIpRequests(GCStringOut requests, GSize requests_len);
	/*!<
	*  \param requests The buffer to hold the list of requesting controllers. Data will be null terminated, even if the data must be truncated to do so.
	*  \param requests_len The length of the requests buffer.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values.
	*
	*  GIpRequests() will block about 5 seconds while listening for requests.
	*
	*  \note Linux users must be root to use GIpRequests() and have UDP access to bind and listen on port 67.
	*
	*  \code{.cpp}
	*  //example of listening for controllers needing IP addresses
	*  GIpRequests(listen_buf, sizeof(listen_buf));
	*  cout << listen_buf << '\n';
	*  \endcode
	*
	*  Each line of the returned data will be of the form *model, serial_number, mac*.
	*  \code{.unparsed}
	*  DMC4000, 291, 00:50:4c:20:01:23
	*  DMC30000, 4184, 00:50:4c:40:10:58
	*  \endcode
	* 
	*/


	//! Assigns IP address over the Ethernet to a controller at a given MAC address.
	GCLIB_DLL_EXPORTED GReturn GCALL GAssign(char* ip, char* mac);
	/*!< 
	*  \param ip The null-terminated ip address to assign. The hardware should not yet have an IP address.
	*  \param mac The null-terminated MAC address of the hardware.
	*
	*  \return The success status or error code of the function. See gclib_errors.h for possible values. 
	*  The desired IP address will be pinged prior to the assigment. If the ping is returned, GAssign() will return G_GCLIB_UTILITY_IP_TAKEN.
	*
	*  \note Linux users must be root to use GAssign() and have UDP access to send on port 68.
	*
	*  \code{.cpp}
	*  //example of assigning an IP address.
	*  GAssign("10.1.3.178", "00:50:4c:40:10:58"); //Assign 10.1.3.178 to 00:50:4c:40:10:58
	*  \endcode
	*/
		

	//! Provides a human-readable description string for return codes.
	GCLIB_DLL_EXPORTED void GCALL GError(GReturn rc, GCStringOut error, GSize error_len);
	/*!<
	*  \param rc The return code to lookup.
	*  \param error The buffer to fill with the error text. Buffer will be null terminated, even if the data must be truncated to do so.
	*  \param error_len The length of the error buffer.
	*
	*  See x_examples.cpp for an example.
	*/

#ifdef __cplusplus
} //extern "C"
#endif

#endif //I_007AD0AF_C956_4B96_ADE2_AD04FAFFEE99
