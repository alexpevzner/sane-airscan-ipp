#include <cups/cups.h>

typedef struct _ippdata_t
{
  size_t	rpos,			/* Read position */
		wused,			/* Bytes used */
		wsize;			/* Max size of buffer */
  ipp_uchar_t	*wbuffer;		/* Buffer */
} _ippdata_t;

void generateRequest(){
//Creating a request
ipp_t *newRequesthandler;
ipp_op_t operation_code = IPP_OP_GET_PRINTER_ATTRIBUTES;
newRequesthandler = ippNewRequest(operation_code);

//Adding Attributes
const char *uri = "http://192.168.1.102:631";
const char *charset = "utf-8";
const char *language = "en-US";
_ippdata_t	data;		/* IPP buffer */
ipp_uchar_t	buffer[8192];	/* Write buffer data */

static const char * const requested_attrs[] =
{	
    "job-template",
    "printer-description"
};
ippAddString(newRequesthandler, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "attributes-charset", NULL, charset); //might not be needing this
ippAddString(newRequesthandler, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE, "attributes-natural-language", NULL, "en-US");	//might not be needing this
ippAddString(newRequesthandler, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, uri);
ippAddStrings(newRequesthandler, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "requested-attributes", (int)(sizeof(requested_attrs) / sizeof(requested_attrs[0])), NULL, requested_attrs);

//Writing ippWriteIO
data.wused   = 0;
data.wsize   = sizeof(buffer);
data.wbuffer = buffer;

ippWriteIO(&data, (ipp_iocb_t)write_cb, 1, NULL, newRequesthandler);

ippDelete(newRequesthandler);
}
//To parse a response:

void generateResponse(){
    ipp_t *newResponsehandler;
    newResponsehandler = ippNew();
    
    data.rpos = 0;
    ippReadIO( &data, (ipp_iocb_t)read_cb, 1, NULL, newResponsehandler);

    //Getting Attributes values    
    const char *uri_value, *charset_value, *language_value,*description_value, *job_value;

    charset_value = ippFindAttribute( newResponsehandler, "attributes-charset", IPP_TAG_CHARSET);
    language_value = ippFindAttribute( newResponsehandler, "attributes-natural-language", IPP_TAG_LANGUAGE);
    uri_value = ippFindAttribute( newResponsehandler, "printer-uri", IPP_TAG_URI);
    description_value = ippFindAttribute( newResponsehandler, "printer-description", IPP_TAG_KEYWORD);
    job_value = ippFindAttribute( newResponsehandler, "job-template", IPP_TAG_KEYWORD);
    
    debug_printf("DEBUG: printer-uri =\"%s\", attributes-charset=\"%s\", attributes-natural-language=\"%s\", job-template=\"%s\", printer-description=\"%s\"", 
    uri_value, charset_value, language_value, job_value, description_value);
    
    ippDelete(newResponsehandler);
}

void main()
{
    generateRequest();
    generateResponse();
}

ssize_t					/* O - Number of bytes written */
write_cb(_ippdata_t   *data,		/* I - Data */
         ipp_uchar_t *buffer,		/* I - Buffer to write */
	 size_t      bytes)		/* I - Number of bytes to write */
{
  size_t	count;			/* Number of bytes */


 /*
  * Loop until all bytes are written...
  */

  if ((count = data->wsize - data->wused) > bytes)
    count = bytes;

  memcpy(data->wbuffer + data->wused, buffer, count);
  data->wused += count;

 /*
  * Return the number of bytes written...
  */

  return ((ssize_t)count);
}

ssize_t					/* O - Number of bytes read */
read_cb(_ippdata_t   *data,		/* I - Data */
        ipp_uchar_t *buffer,		/* O - Buffer to read */
	size_t      bytes)		/* I - Number of bytes to read */
{
  size_t	count;			/* Number of bytes */


 /*
  * Copy bytes from the data buffer to the read buffer...
  */

  if ((count = data->wsize - data->rpos) > bytes)
    count = bytes;

  memcpy(buffer, data->wbuffer + data->rpos, count);
  data->rpos += count;

 /*
  * Return the number of bytes read...
  */

  return ((ssize_t)count);
}