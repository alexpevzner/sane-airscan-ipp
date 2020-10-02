#include <cups/cups.h>

//Creating a request
ipp_t *newRequesthandler;
ipp_op_t operation_code = IPP_PRINT_URI;
newRequesthandler = ippNewRequest(operation_code); //The new request message is initialized with the attributes-charset and attributes-natural-language attributes added. The attributes-natural-language value is derived from the current locale.


ipp_state_t ippWriteIO( void * dst, ipp_iocb_t cb, int blocking, ipp_t * parent, ipp_t * ipp); //Write data for an IPP message.

//To parse a response:

ipp_t * ippNew(void); //Allocate a new IPP message.
ipp_state_t ippReadIO( void * src, ipp_iocb_t cb, int blocking, ipp_t * parent, ipp_t * ipp); //Read data for an IPP message.
ipp_attribute_t * ippFindAttribute( ipp_t * ipp, const char * name, ipp_tag_t type); //Find a named attribute in a request...





