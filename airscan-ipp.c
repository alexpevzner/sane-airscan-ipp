/* AirScan (a.k.a. IPP) backend for SANE
 *
 * 
 * 
 *
 * IPP protocol handler
 */

#include "airscan.h"


/* proto_handler_ipp represents IPP protocol handler
 */
typedef struct {
    proto_handler proto; /* Base class */
} proto_handler_ipp;






/* Free IPP protocol handler
 */
static void
ipp_free (proto_handler *proto)
{
    mem_free(proto);
}

/* proto_handler_ipp_new creates new IPP protocol handler
 */
proto_handler*
proto_handler_ipp_new (void)
{
    proto_handler_ipp *ipp = mem_new(proto_handler_ipp, 1);

    ipp->proto.name = "IPP";
    ipp->proto.free = ipp_free;

    ipp->proto.devcaps_query = ipp_devcaps_query;
    ipp->proto.devcaps_decode = ipp_devcaps_decode;

    ipp->proto.scan_query = ipp_scan_query;
    ipp->proto.scan_decode = ipp_scan_decode;

    ipp->proto.load_query = ipp_load_query;
    ipp->proto.load_decode = ipp_load_decode;

    ipp->proto.status_query = ipp_status_query;
    ipp->proto.status_decode = ipp_status_decode;

    ipp->proto.cancel_query = ipp_cancel_query;

    return &ipp->proto;
}