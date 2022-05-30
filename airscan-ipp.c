/* AirScan (a.k.a. IPP) backend for SANE
*
* Copyright (C) 2019 and up by Rishabh Arya (rishabharya2799@gmail.com)
* See LICENSE for license terms and conditions
*
* IPP protocol handler
*/

#define NO_HTTP_STATUS

#include "airscan.h"
#include <cups/cups.h>

/* proto_handler_ipp represents IPP protocol handler
 */
typedef struct {
    proto_handler proto; /* Base class */
} proto_handler_ipp;

/* Create HTTP POST request
 */
static http_query*
ipp_http_post (const proto_ctx *ctx, void *body, size_t size)
{
    http_query *q;

    q = http_query_new_len(ctx->http, http_uri_clone(ctx->base_uri),
        "POST", body, size, "application/ipp");

    return q;
}

/* Query device capabilities
 */
static http_query*
ipp_devcaps_query (const proto_ctx *ctx)
{
    return ipp_http_post(ctx, NULL, 0);
}

/* Decode device capabilities
 */
static error
ipp_devcaps_decode (const proto_ctx *ctx, devcaps *caps)
{
    (void) ctx;
    (void) caps;
    return ERROR("not supported");
}

/* Initiate scanning
 */
static http_query*
ipp_scan_query (const proto_ctx *ctx)
{
    return ipp_http_post(ctx, NULL, 0);
}
/* Decode result of scan request
 */
static proto_result
ipp_scan_decode (const proto_ctx *ctx)
{
    proto_result result = {0};

    (void) ctx;

    result.next = PROTO_OP_FINISH;
    result.status = SANE_STATUS_UNSUPPORTED;
    result.err = ERROR("not supported");

    return result;
}

/* Initiate image downloading
 */
static http_query*
ipp_load_query (const proto_ctx *ctx)
{
    return ipp_http_post(ctx, NULL, 0);
}

/* Decode result of image request
 */
static proto_result
ipp_load_decode (const proto_ctx *ctx)
{
    proto_result result = {0};

    (void) ctx;

    result.next = PROTO_OP_FINISH;
    result.status = SANE_STATUS_UNSUPPORTED;
    result.err = ERROR("not supported");

    return result;
}

/* Request device status
 */
static http_query*
ipp_status_query (const proto_ctx *ctx)
{
    return ipp_http_post(ctx, NULL, 0);
}

/* Decode result of device status request
 */
static proto_result
ipp_status_decode (const proto_ctx *ctx)
{
    proto_result result = {0};

    (void) ctx;

    result.next = PROTO_OP_FINISH;
    result.status = SANE_STATUS_UNSUPPORTED;
    result.err = ERROR("not supported");

    return result;
}

/* Cancel scan in progress
 */
static http_query*
ipp_cancel_query (const proto_ctx *ctx)
{
    return ipp_http_post(ctx, NULL, 0);
}

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

    /*1*/ipp->proto.devcaps_query = ipp_devcaps_query;
    /*1*/ipp->proto.devcaps_decode = ipp_devcaps_decode;

    /*2*/ipp->proto.scan_query = ipp_scan_query;
    /*2*/ipp->proto.scan_decode = ipp_scan_decode;

    /*3*/ipp->proto.load_query = ipp_load_query;
    /*3*/ipp->proto.load_decode = ipp_load_decode;

    /*4*/ipp->proto.status_query = ipp_status_query;
    /*4*/ipp->proto.status_decode = ipp_status_decode;

    /*5*/ipp->proto.cleanup_query = ipp_cancel_query;
    /*6*/ipp->proto.cancel_query = ipp_cancel_query;

    return &ipp->proto;
}

/*
JUST FOR UNDERSTANDING TEMP
1 -> Query/decode scanner capabilities (devcaps_query/devcaps_decode)
2 -> Initiate scanning (create scan job) and decode result (scan_query/scan_decode)
3 -> Initiate downloading of scanned image and decode result 
4 -> Get device status and decode result (status_query/status_decode)
5 -> Cleanup after scan job (cleanup_query, there is no decode operation)
6 -> Cancel scan job (cancel_query, and also no decode operation)
*/

/* vim:ts=8:sw=4:et
 */
