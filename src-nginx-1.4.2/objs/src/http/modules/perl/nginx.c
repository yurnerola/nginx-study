/*
 * This file was generated automatically by ExtUtils::ParseXS version 2.2203 from the
 * contents of nginx.xs. Do not edit this file, edit nginx.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "nginx.xs"

/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#define PERL_NO_GET_CONTEXT

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_http_perl_module.h>

#include "XSUB.h"


#define ngx_http_perl_set_request(r)                                          \
    r = INT2PTR(ngx_http_request_t *, SvIV((SV *) SvRV(ST(0))))


#define ngx_http_perl_set_targ(p, len)                                        \
                                                                              \
    SvUPGRADE(TARG, SVt_PV);                                                  \
    SvPOK_on(TARG);                                                           \
    sv_setpvn(TARG, (char *) p, len)


static ngx_int_t
ngx_http_perl_sv2str(pTHX_ ngx_http_request_t *r, ngx_str_t *s, SV *sv)
{
    u_char  *p;
    STRLEN   len;

    if (SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PV) {
        sv = SvRV(sv);
    }

    p = (u_char *) SvPV(sv, len);

    s->len = len;

    if (SvREADONLY(sv) && SvPOK(sv)) {
        s->data = p;

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "perl sv2str: %08XD \"%V\"", sv->sv_flags, s);

        return NGX_OK;
    }

    s->data = ngx_pnalloc(r->pool, len);
    if (s->data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->data, p, len);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "perl sv2str: %08XD \"%V\"", sv->sv_flags, s);

    return NGX_OK;
}


static ngx_int_t
ngx_http_perl_output(ngx_http_request_t *r, ngx_buf_t *b)
{
    ngx_chain_t           out;
#if (NGX_HTTP_SSI)
    ngx_chain_t          *cl;
    ngx_http_perl_ctx_t  *ctx;

    ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);

    if (ctx->ssi) {
        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NGX_ERROR;
        }

        cl->buf = b;
        cl->next = NULL;
        *ctx->ssi->last_out = cl;
        ctx->ssi->last_out = &cl->next;

        return NGX_OK;
    }
#endif

    out.buf = b;
    out.next = NULL;

    return ngx_http_output_filter(r, &out);
}


#line 108 "nginx.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(pTHX_ const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
            Perl_croak(aTHX_ "Usage: %s::%s(%s)", hvname, gvname, params);
        else
            Perl_croak(aTHX_ "Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
        Perl_croak(aTHX_ "Usage: CODE(0x%"UVxf")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#ifdef PERL_IMPLICIT_CONTEXT
#define croak_xs_usage(a,b)	S_croak_xs_usage(aTHX_ a,b)
#else
#define croak_xs_usage		S_croak_xs_usage
#endif

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#line 160 "nginx.c"

XS(XS_nginx_status); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_status)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "r, code");
    {
#line 105 "nginx.xs"
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);

    r->headers_out.status = SvIV(ST(1));

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "perl status: %d", r->headers_out.status);

    XSRETURN_UNDEF;
#line 184 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_send_http_header); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_send_http_header)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1)
       croak_xs_usage(cv,  "r, ...");
    {
#line 121 "nginx.xs"
    ngx_http_request_t  *r;
    SV                  *sv;

    ngx_http_perl_set_request(r);

    if (r->headers_out.status == 0) {
        r->headers_out.status = NGX_HTTP_OK;
    }

    if (items != 1) {
        sv = ST(1);

        if (ngx_http_perl_sv2str(aTHX_ r, &r->headers_out.content_type, sv)
            != NGX_OK)
        {
            XSRETURN_EMPTY;
        }

        r->headers_out.content_type_len = r->headers_out.content_type.len;

    } else {
        if (ngx_http_set_content_type(r) != NGX_OK) {
            XSRETURN_EMPTY;
        }
    }

    (void) ngx_http_send_header(r);
#line 229 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_header_only); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_header_only)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 154 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);

    sv_upgrade(TARG, SVt_IV);
    sv_setiv(TARG, r->header_only);

    ST(0) = TARG;
#line 256 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_uri); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_uri)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 169 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);
    ngx_http_perl_set_targ(r->uri.data, r->uri.len);

    ST(0) = TARG;
#line 281 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_args); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_args)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 182 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);
    ngx_http_perl_set_targ(r->args.data, r->args.len);

    ST(0) = TARG;
#line 306 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_request_method); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_request_method)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 195 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);
    ngx_http_perl_set_targ(r->method_name.data, r->method_name.len);

    ST(0) = TARG;
#line 331 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_remote_addr); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_remote_addr)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 208 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);
    ngx_http_perl_set_targ(r->connection->addr_text.data,
                           r->connection->addr_text.len);

    ST(0) = TARG;
#line 357 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_header_in); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_header_in)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "r, key");
    {
#line 222 "nginx.xs"
    dXSTARG;
    ngx_http_request_t         *r;
    SV                         *key;
    u_char                     *p, *lowcase_key, *value, sep;
    STRLEN                      len;
    ssize_t                     size;
    ngx_uint_t                  i, n, hash;
    ngx_array_t                *a;
    ngx_list_part_t            *part;
    ngx_table_elt_t            *h, **ph;
    ngx_http_header_t          *hh;
    ngx_http_core_main_conf_t  *cmcf;

    ngx_http_perl_set_request(r);

    key = ST(1);

    if (SvROK(key) && SvTYPE(SvRV(key)) == SVt_PV) {
        key = SvRV(key);
    }

    p = (u_char *) SvPV(key, len);

    /* look up hashed headers */

    lowcase_key = ngx_pnalloc(r->pool, len);
    if (lowcase_key == NULL) {
        XSRETURN_UNDEF;
    }

    hash = ngx_hash_strlow(lowcase_key, p, len);

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    hh = ngx_hash_find(&cmcf->headers_in_hash, hash, lowcase_key, len);

    if (hh) {

        if (hh->offset == offsetof(ngx_http_headers_in_t, cookies)) {
            sep = ';';
            goto multi;
        }

        if (hh->offset == offsetof(ngx_http_headers_in_t, x_forwarded_for)) {
            sep = ',';
            goto multi;
        }

        if (hh->offset) {

            ph = (ngx_table_elt_t **) ((char *) &r->headers_in + hh->offset);

            if (*ph) {
                ngx_http_perl_set_targ((*ph)->value.data, (*ph)->value.len);

                goto done;
            }

            XSRETURN_UNDEF;
        }

    multi:

        /* Cookie, X-Forwarded-For */

        a = (ngx_array_t *) ((char *) &r->headers_in + hh->offset);

        n = a->nelts;

        if (n == 0) {
            XSRETURN_UNDEF;
        }

        ph = a->elts;

        if (n == 1) {
            ngx_http_perl_set_targ((*ph)->value.data, (*ph)->value.len);

            goto done;
        }

        size = - (ssize_t) (sizeof("; ") - 1);

        for (i = 0; i < n; i++) {
            size += ph[i]->value.len + sizeof("; ") - 1;
        }

        value = ngx_pnalloc(r->pool, size);
        if (value == NULL) {
            XSRETURN_UNDEF;
        }

        p = value;

        for (i = 0; /* void */ ; i++) {
            p = ngx_copy(p, ph[i]->value.data, ph[i]->value.len);

            if (i == n - 1) {
                break;
            }

            *p++ = sep; *p++ = ' ';
        }

        ngx_http_perl_set_targ(value, size);

        goto done;
    }

    /* iterate over all headers */

    part = &r->headers_in.headers.part;
    h = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            h = part->elts;
            i = 0;
        }

        if (len != h[i].key.len
            || ngx_strcasecmp(p, h[i].key.data) != 0)
        {
            continue;
        }

        ngx_http_perl_set_targ(h[i].value.data, h[i].value.len);

        goto done;
    }

    XSRETURN_UNDEF;

    done:

    ST(0) = TARG;
#line 517 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_has_request_body); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_has_request_body)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "r, next");
    {
#line 372 "nginx.xs"
    dXSTARG;
    ngx_http_request_t   *r;
    ngx_http_perl_ctx_t  *ctx;

    ngx_http_perl_set_request(r);

    if (r->headers_in.content_length_n <= 0 && !r->headers_in.chunked) {
        XSRETURN_UNDEF;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);
    ctx->next = SvRV(ST(1));

    r->request_body_in_single_buf = 1;
    r->request_body_in_persistent_file = 1;
    r->request_body_in_clean_file = 1;

    if (r->request_body_in_file_only) {
        r->request_body_file_log_level = 0;
    }

    ngx_http_read_client_request_body(r, ngx_http_perl_handle_request);

    sv_upgrade(TARG, SVt_IV);
    sv_setiv(TARG, 1);

    ST(0) = TARG;
#line 562 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_request_body); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_request_body)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 405 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;
    u_char              *p, *data;
    size_t               len;
    ngx_buf_t           *buf;
    ngx_chain_t         *cl;

    ngx_http_perl_set_request(r);

    if (r->request_body == NULL
        || r->request_body->temp_file
        || r->request_body->bufs == NULL)
    {
        XSRETURN_UNDEF;
    }

    cl = r->request_body->bufs;
    buf = cl->buf;

    if (cl->next == NULL) {
        len = buf->last - buf->pos;
        data = buf->pos;
        goto done;
    }

    len = buf->last - buf->pos;
    cl = cl->next;

    for ( /* void */ ; cl; cl = cl->next) {
        buf = cl->buf;
        len += buf->last - buf->pos;
    }

    p = ngx_pnalloc(r->pool, len);
    if (p == NULL) {
        XSRETURN_UNDEF;
    }

    data = p;
    cl = r->request_body->bufs;

    for ( /* void */ ; cl; cl = cl->next) {
        buf = cl->buf;
        p = ngx_cpymem(p, buf->pos, buf->last - buf->pos);
    }

    done:

    if (len == 0) {
        XSRETURN_UNDEF;
    }

    ngx_http_perl_set_targ(data, len);

    ST(0) = TARG;
#line 635 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_request_body_file); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_request_body_file)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 466 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);

    if (r->request_body == NULL || r->request_body->temp_file == NULL) {
        XSRETURN_UNDEF;
    }

    ngx_http_perl_set_targ(r->request_body->temp_file->file.name.data,
                           r->request_body->temp_file->file.name.len);

    ST(0) = TARG;
#line 666 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_discard_request_body); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_discard_request_body)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 485 "nginx.xs"
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);

    ngx_http_discard_request_body(r);
#line 689 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_header_out); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_header_out)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 3)
       croak_xs_usage(cv,  "r, key, value");
    {
#line 496 "nginx.xs"
    ngx_http_request_t  *r;
    SV                  *key;
    SV                  *value;
    ngx_table_elt_t     *header;

    ngx_http_perl_set_request(r);

    key = ST(1);
    value = ST(2);

    header = ngx_list_push(&r->headers_out.headers);
    if (header == NULL) {
        XSRETURN_EMPTY;
    }

    header->hash = 1;

    if (ngx_http_perl_sv2str(aTHX_ r, &header->key, key) != NGX_OK) {
        XSRETURN_EMPTY;
    }

    if (ngx_http_perl_sv2str(aTHX_ r, &header->value, value) != NGX_OK) {
        XSRETURN_EMPTY;
    }

    if (header->key.len == sizeof("Content-Length") - 1
        && ngx_strncasecmp(header->key.data, (u_char *) "Content-Length",
                           sizeof("Content-Length") - 1) == 0)
    {
        r->headers_out.content_length_n = (off_t) SvIV(value);
        r->headers_out.content_length = header;
    }

    if (header->key.len == sizeof("Content-Encoding") - 1
        && ngx_strncasecmp(header->key.data, (u_char *) "Content-Encoding",
                           sizeof("Content-Encoding") - 1) == 0)
    {
        r->headers_out.content_encoding = header;
    }
#line 746 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_filename); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_filename)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 541 "nginx.xs"
    dXSTARG;
    size_t                root;
    ngx_http_request_t   *r;
    ngx_http_perl_ctx_t  *ctx;

    ngx_http_perl_set_request(r);

    ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);
    if (ctx->filename.data) {
        goto done;
    }

    if (ngx_http_map_uri_to_path(r, &ctx->filename, &root, 0) == NULL) {
        XSRETURN_UNDEF;
    }

    ctx->filename.len--;
    sv_setpv(PL_statname, (char *) ctx->filename.data);

    done:

    ngx_http_perl_set_targ(ctx->filename.data, ctx->filename.len);

    ST(0) = TARG;
#line 788 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_print); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_print)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 1)
       croak_xs_usage(cv,  "r, ...");
    {
#line 571 "nginx.xs"
    ngx_http_request_t  *r;
    SV                  *sv;
    int                  i;
    u_char              *p;
    size_t               size;
    STRLEN               len;
    ngx_buf_t           *b;

    ngx_http_perl_set_request(r);

    if (items == 2) {

        /*
         * do zero copy for prolate single read-only SV:
         *     $r->print("some text\n");
         */

        sv = ST(1);

        if (SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PV) {
            sv = SvRV(sv);
        }

        if (SvREADONLY(sv) && SvPOK(sv)) {

            p = (u_char *) SvPV(sv, len);

            if (len == 0) {
                XSRETURN_EMPTY;
            }

            b = ngx_calloc_buf(r->pool);
            if (b == NULL) {
                XSRETURN_EMPTY;
            }

            b->memory = 1;
            b->pos = p;
            b->last = p + len;
            b->start = p;
            b->end = b->last;

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "$r->print: read-only SV: %z", len);

            goto out;
        }
    }

    size = 0;

    for (i = 1; i < items; i++) {

        sv = ST(i);

        if (SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PV) {
            sv = SvRV(sv);
        }

        (void) SvPV(sv, len);

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "$r->print: copy SV: %z", len);

        size += len;
    }

    if (size == 0) {
        XSRETURN_EMPTY;
    }

    b = ngx_create_temp_buf(r->pool, size);
    if (b == NULL) {
        XSRETURN_EMPTY;
    }

    for (i = 1; i < items; i++) {
        sv = ST(i);

        if (SvROK(sv) && SvTYPE(SvRV(sv)) == SVt_PV) {
            sv = SvRV(sv);
        }

        p = (u_char *) SvPV(sv, len);
        b->last = ngx_cpymem(b->last, p, len);
    }

    out:

    (void) ngx_http_perl_output(r, b);
#line 896 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_sendfile); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_sendfile)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 2 || items > 4)
       croak_xs_usage(cv,  "r, filename, offset = -1, bytes = 0");
    {
#line 667 "nginx.xs"
    ngx_http_request_t        *r;
    char                      *filename;
    off_t                      offset;
    size_t                     bytes;
    ngx_str_t                  path;
    ngx_buf_t                 *b;
    ngx_open_file_info_t       of;
    ngx_http_core_loc_conf_t  *clcf;

    ngx_http_perl_set_request(r);

    filename = SvPV_nolen(ST(1));

    if (filename == NULL) {
        croak("sendfile(): NULL filename");
    }

    offset = items < 3 ? -1 : SvIV(ST(2));
    bytes = items < 4 ? 0 : SvIV(ST(3));

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        XSRETURN_EMPTY;
    }

    b->file = ngx_pcalloc(r->pool, sizeof(ngx_file_t));
    if (b->file == NULL) {
        XSRETURN_EMPTY;
    }

    path.len = ngx_strlen(filename);

    path.data = ngx_pnalloc(r->pool, path.len + 1);
    if (path.data == NULL) {
        XSRETURN_EMPTY;
    }

    (void) ngx_cpystrn(path.data, (u_char *) filename, path.len + 1);

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    ngx_memzero(&of, sizeof(ngx_open_file_info_t));

    of.read_ahead = clcf->read_ahead;
    of.directio = clcf->directio;
    of.valid = clcf->open_file_cache_valid;
    of.min_uses = clcf->open_file_cache_min_uses;
    of.errors = clcf->open_file_cache_errors;
    of.events = clcf->open_file_cache_events;

    if (ngx_http_set_disable_symlinks(r, clcf, &path, &of) != NGX_OK) {
        XSRETURN_EMPTY;
    }

    if (ngx_open_cached_file(clcf->open_file_cache, &path, &of, r->pool)
        != NGX_OK)
    {
        if (of.err == 0) {
            XSRETURN_EMPTY;
        }

        ngx_log_error(NGX_LOG_CRIT, r->connection->log, ngx_errno,
                      "%s \"%s\" failed", of.failed, filename);
        XSRETURN_EMPTY;
    }

    if (offset == -1) {
        offset = 0;
    }

    if (bytes == 0) {
        bytes = of.size - offset;
    }

    b->in_file = 1;

    b->file_pos = offset;
    b->file_last = offset + bytes;

    b->file->fd = of.fd;
    b->file->log = r->connection->log;
    b->file->directio = of.is_directio;

    (void) ngx_http_perl_output(r, b);
#line 998 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_flush); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_flush)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 757 "nginx.xs"
    ngx_http_request_t  *r;
    ngx_buf_t           *b;

    ngx_http_perl_set_request(r);

    b = ngx_calloc_buf(r->pool);
    if (b == NULL) {
        XSRETURN_EMPTY;
    }

    b->flush = 1;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "$r->flush");

    (void) ngx_http_perl_output(r, b);

    XSRETURN_EMPTY;
#line 1033 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_internal_redirect); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_internal_redirect)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 2)
       croak_xs_usage(cv,  "r, uri");
    {
#line 780 "nginx.xs"
    ngx_http_request_t   *r;
    SV                   *uri;
    ngx_uint_t            i;
    ngx_http_perl_ctx_t  *ctx;

    ngx_http_perl_set_request(r);

    uri = ST(1);

    ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);

    if (ngx_http_perl_sv2str(aTHX_ r, &ctx->redirect_uri, uri) != NGX_OK) {
        XSRETURN_EMPTY;
    }

    for (i = 0; i < ctx->redirect_uri.len; i++) {
        if (ctx->redirect_uri.data[i] == '?') {

            ctx->redirect_args.len = ctx->redirect_uri.len - (i + 1);
            ctx->redirect_args.data = &ctx->redirect_uri.data[i + 1];
            ctx->redirect_uri.len = i;

            XSRETURN_EMPTY;
        }
    }
#line 1076 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_allow_ranges); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_allow_ranges)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 1)
       croak_xs_usage(cv,  "r");
    {
#line 811 "nginx.xs"
    ngx_http_request_t  *r;

    ngx_http_perl_set_request(r);

    r->allow_ranges = 1;
#line 1099 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_unescape); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_unescape)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 2 || items > 3)
       croak_xs_usage(cv,  "r, text, type = 0");
    {
#line 822 "nginx.xs"
    dXSTARG;
    ngx_http_request_t  *r;
    SV                  *text;
    int                  type;
    u_char              *p, *dst, *src;
    STRLEN               len;

    ngx_http_perl_set_request(r);

    text = ST(1);

    src = (u_char *) SvPV(text, len);

    p = ngx_pnalloc(r->pool, len + 1);
    if (p == NULL) {
        XSRETURN_UNDEF;
    }

    dst = p;

    type = items < 3 ? 0 : SvIV(ST(2));

    ngx_unescape_uri(&dst, &src, len, (ngx_uint_t) type);
    *dst = '\0';

    ngx_http_perl_set_targ(p, dst - p);

    ST(0) = TARG;
#line 1145 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_variable); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_variable)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items < 2 || items > 3)
       croak_xs_usage(cv,  "r, name, value = NULL");
    {
#line 856 "nginx.xs"
    dXSTARG;
    ngx_http_request_t         *r;
    SV                         *name, *value;
    u_char                     *p, *lowcase;
    STRLEN                      len;
    ngx_str_t                   var, val;
    ngx_uint_t                  i, hash;
    ngx_http_perl_var_t        *v;
    ngx_http_perl_ctx_t        *ctx;
    ngx_http_variable_value_t  *vv;

    ngx_http_perl_set_request(r);

    name = ST(1);

    if (SvROK(name) && SvTYPE(SvRV(name)) == SVt_PV) {
        name = SvRV(name);
    }

    if (items == 2) {
        value = NULL;

    } else {
        value = ST(2);

        if (SvROK(value) && SvTYPE(SvRV(value)) == SVt_PV) {
            value = SvRV(value);
        }

        if (ngx_http_perl_sv2str(aTHX_ r, &val, value) != NGX_OK) {
            XSRETURN_UNDEF;
        }
    }

    p = (u_char *) SvPV(name, len);

    lowcase = ngx_pnalloc(r->pool, len);
    if (lowcase == NULL) {
        XSRETURN_UNDEF;
    }

    hash = ngx_hash_strlow(lowcase, p, len);

    var.len = len;
    var.data = lowcase;


    if (value) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "perl variable: \"%V\"=\"%V\"", &var, &val);
    } else {
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "perl variable: \"%V\"", &var);
    }


    vv = ngx_http_get_variable(r, &var, hash);
    if (vv == NULL) {
        XSRETURN_UNDEF;
    }

    if (vv->not_found) {

        ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);

        if (ctx->variables) {

            v = ctx->variables->elts;
            for (i = 0; i < ctx->variables->nelts; i++) {

                if (hash != v[i].hash
                    || len != v[i].name.len
                    || ngx_strncmp(lowcase, v[i].name.data, len) != 0)
                {
                    continue;
                }

                if (value) {
                    v[i].value = val;
                    XSRETURN_UNDEF;
                }

                ngx_http_perl_set_targ(v[i].value.data, v[i].value.len);

                goto done;
            }
        }

        if (value) {
            if (ctx->variables == NULL) {
                ctx->variables = ngx_array_create(r->pool, 1,
                                                  sizeof(ngx_http_perl_var_t));
                if (ctx->variables == NULL) {
                    XSRETURN_UNDEF;
                }
            }

            v = ngx_array_push(ctx->variables);
            if (v == NULL) {
                XSRETURN_UNDEF;
            }

            v->hash = hash;
            v->name.len = len;
            v->name.data = lowcase;
            v->value = val;

            XSRETURN_UNDEF;
        }

        XSRETURN_UNDEF;
    }

    if (value) {
        vv->len = val.len;
        vv->valid = 1;
        vv->no_cacheable = 0;
        vv->not_found = 0;
        vv->data = val.data;

        XSRETURN_UNDEF;
    }

    ngx_http_perl_set_targ(vv->data, vv->len);

    done:

    ST(0) = TARG;
#line 1291 "nginx.c"
    }
    XSRETURN(1);
}


XS(XS_nginx_sleep); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_sleep)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 3)
       croak_xs_usage(cv,  "r, sleep, next");
    {
#line 992 "nginx.xs"
    ngx_http_request_t   *r;
    ngx_msec_t            sleep;
    ngx_http_perl_ctx_t  *ctx;

    ngx_http_perl_set_request(r);

    sleep = (ngx_msec_t) SvIV(ST(1));

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "perl sleep: %M", sleep);

    ctx = ngx_http_get_module_ctx(r, ngx_http_perl_module);

    ctx->next = SvRV(ST(2));

    ngx_add_timer(r->connection->write, sleep);

    r->write_event_handler = ngx_http_perl_sleep_handler;
    r->main->count++;
#line 1328 "nginx.c"
    }
    XSRETURN_EMPTY;
}


XS(XS_nginx_log_error); /* prototype to pass -Wmissing-prototypes */
XS(XS_nginx_log_error)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
    if (items != 3)
       croak_xs_usage(cv,  "r, err, msg");
    {
#line 1017 "nginx.xs"
    ngx_http_request_t  *r;
    SV                  *err, *msg;
    u_char              *p;
    STRLEN               len;
    ngx_err_t            e;

    ngx_http_perl_set_request(r);

    err = ST(1);

    if (SvROK(err) && SvTYPE(SvRV(err)) == SVt_PV) {
        err = SvRV(err);
    }

    e = SvIV(err);

    msg = ST(2);

    if (SvROK(msg) && SvTYPE(SvRV(msg)) == SVt_PV) {
        msg = SvRV(msg);
    }

    p = (u_char *) SvPV(msg, len);

    ngx_log_error(NGX_LOG_ERR, r->connection->log, e, "perl: %s", p);
#line 1371 "nginx.c"
    }
    XSRETURN_EMPTY;
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_nginx); /* prototype to pass -Wmissing-prototypes */
XS(boot_nginx)
{
#ifdef dVAR
    dVAR; dXSARGS;
#else
    dXSARGS;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    XS_VERSION_BOOTCHECK ;

        newXS("nginx::status", XS_nginx_status, file);
        newXS("nginx::send_http_header", XS_nginx_send_http_header, file);
        newXS("nginx::header_only", XS_nginx_header_only, file);
        newXS("nginx::uri", XS_nginx_uri, file);
        newXS("nginx::args", XS_nginx_args, file);
        newXS("nginx::request_method", XS_nginx_request_method, file);
        newXS("nginx::remote_addr", XS_nginx_remote_addr, file);
        newXS("nginx::header_in", XS_nginx_header_in, file);
        newXS("nginx::has_request_body", XS_nginx_has_request_body, file);
        newXS("nginx::request_body", XS_nginx_request_body, file);
        newXS("nginx::request_body_file", XS_nginx_request_body_file, file);
        newXS("nginx::discard_request_body", XS_nginx_discard_request_body, file);
        newXS("nginx::header_out", XS_nginx_header_out, file);
        newXS("nginx::filename", XS_nginx_filename, file);
        newXS("nginx::print", XS_nginx_print, file);
        newXS("nginx::sendfile", XS_nginx_sendfile, file);
        newXS("nginx::flush", XS_nginx_flush, file);
        newXS("nginx::internal_redirect", XS_nginx_internal_redirect, file);
        newXS("nginx::allow_ranges", XS_nginx_allow_ranges, file);
        newXS("nginx::unescape", XS_nginx_unescape, file);
        newXS("nginx::variable", XS_nginx_variable, file);
        newXS("nginx::sleep", XS_nginx_sleep, file);
        newXS("nginx::log_error", XS_nginx_log_error, file);
#if (PERL_REVISION == 5 && PERL_VERSION >= 9)
  if (PL_unitcheckav)
       call_list(PL_scopestack_ix, PL_unitcheckav);
#endif
    XSRETURN_YES;
}

