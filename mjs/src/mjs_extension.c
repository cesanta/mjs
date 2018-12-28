#include "common/str_util.h"
#include "frozen/frozen.h"
#include "mjs/src/mjs_array.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_conversion.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_util.h"

#include "reef.h"

static void mjs_op_time_systime(struct mjs *jsm)
{
    mjs_val_t ret = MJS_UNDEFINED;

    char timestr[25] = {0};
    struct timeval tv;
    struct tm *tm;

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    strftime(timestr, 25, "%Y-%m-%d %H:%M:%S", tm);
    timestr[24] = '\0';

    ret = mjs_mk_object(jsm);
    mjs_set(jsm, ret, "localtime", ~0, mjs_mk_string(jsm, timestr, ~0, 1));
    mjs_set(jsm, ret, "timestamp", ~0, mjs_mk_number(jsm, time(NULL)));

    mjs_set(jsm, ret, "year", ~0, mjs_mk_number(jsm, tm->tm_year + 1900));
    mjs_set(jsm, ret, "month", ~0, mjs_mk_number(jsm, tm->tm_mon + 1));
    mjs_set(jsm, ret, "day", ~0, mjs_mk_number(jsm, tm->tm_mday));

    mjs_set(jsm, ret, "hour", ~0, mjs_mk_number(jsm, tm->tm_hour));
    mjs_set(jsm, ret, "minute", ~0, mjs_mk_number(jsm, tm->tm_min));
    mjs_set(jsm, ret, "second", ~0, mjs_mk_number(jsm, tm->tm_sec));

    mjs_set(jsm, ret, "weekid", ~0, mjs_mk_number(jsm, (int)((tm->tm_yday + 6) / 7)));

    mjs_return(jsm, ret);
}

static void mjs_op_os_usleep(struct mjs *jsm)
{
    if (mjs_nargs(jsm) < 1) {
        mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "missing a value to usleep");
    } else {
        int usec = 0;
        mjs_val_t val = mjs_arg(jsm, 0);
        if (mjs_is_number(val)) {
            usec = mjs_get_int(jsm, val);
            if (usec > 0) usleep(usec);
        }
    }

    mjs_return(jsm, MJS_UNDEFINED);
}

static void mjs_op_sys_parseInt(struct mjs *jsm)
{
    mjs_val_t ret = MJS_UNDEFINED;

    if (mjs_nargs(jsm) < 1) {
        mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "missing a value");
    } else {
        mjs_val_t p = mjs_arg(jsm, 0);
        if (mjs_is_number(p)) {
            ret = mjs_mk_number(jsm, mjs_get_int(jsm, p));
        } else if (mjs_is_string(p)) {
            const char *nums = mjs_get_string(jsm, &p, NULL);
            int64_t num = 0;
            if (nums) num = to64(nums);
            ret = mjs_mk_number(jsm, num);
        }
    }

    mjs_return(jsm, ret);
}

static void mjs_op_sys_delete(struct mjs *jsm)
{
    mjs_val_t ret = MJS_UNDEFINED;

    if (mjs_nargs(jsm) < 2) {
        mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "missing argument");
    } else {
        mjs_val_t obj = mjs_arg(jsm, 0);
        mjs_val_t prop = mjs_arg(jsm, 1);
        if (mjs_is_object(obj) && mjs_is_string(prop)) {
            ret = obj;
            mjs_del(jsm, obj, mjs_get_string(jsm, &prop, NULL), ~0);
        } else {
            mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "type mismatch");
        }
    }

    mjs_return(jsm, ret);
}

static void mjs_op_sys_regMatch(struct mjs *jsm)
{
    mjs_val_t ret = MJS_UNDEFINED;

    if (mjs_nargs(jsm) < 2) {
        mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "missing argument");
    } else {
        mjs_val_t s = mjs_arg(jsm, 0);
        mjs_val_t r = mjs_arg(jsm, 1);

        if (!mjs_is_string(s) || !mjs_is_string(s)) {
            mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "argument not string");
            goto done;
        }

        const char *ps = mjs_get_cstring(jsm, &s);
        const char *pr = mjs_get_cstring(jsm, &r);

        mtc_mt_dbg("%s ===> %s", ps, pr);

        ret = mjs_mk_array(jsm);

        MRE *reo = mre_init();
        MERR *err;
        err = mre_compile(reo, pr);
        if (err) {
            mjs_prepend_errorf(jsm, MJS_TYPE_ERROR, "compile reg %s error %s", r, merr_meanful_desc(err));
            merr_destroy(&err);
            mre_destroy(&reo);
            goto done;
        }

        if (mre_match(reo, ps, false)) {
            for (uint32_t i = 0; i < mre_sub_count(reo, 0); i++) {
                const char *sp, *ep;
                if (mre_sub_get(reo, 0, i, &sp, &ep)) {
                    mjs_val_t sub = mjs_mk_string(jsm, sp, (ep - sp), 1);
                    mjs_array_push(jsm, ret, sub);
                }
            }
        }

        mre_destroy(&reo);
    }

done:
    mjs_return(jsm, ret);
}

void mjs_init_local(struct mjs *jsm, mjs_val_t o)
{
    mjs_val_t time = mjs_mk_object(jsm);
    mjs_val_t os = mjs_mk_object(jsm);
    mjs_val_t sys = mjs_mk_object(jsm);

    mjs_set(jsm, o, "TIME", ~0, time);
    mjs_set(jsm, time, "systime", ~0, mjs_mk_foreign(jsm, mjs_op_time_systime));

    mjs_set(jsm, o, "OS", ~0, os);
    mjs_set(jsm, os, "usleep", ~0, mjs_mk_foreign(jsm, mjs_op_os_usleep));

    mjs_set(jsm, o, "SYS", ~0, sys);
    mjs_set(jsm, sys, "parseInt", ~0, mjs_mk_foreign(jsm, mjs_op_sys_parseInt));
    mjs_set(jsm, sys, "objDelete", ~0, mjs_mk_foreign(jsm, mjs_op_sys_delete));
    mjs_set(jsm, sys, "regMatch", ~0, mjs_mk_foreign(jsm, mjs_op_sys_regMatch));
}
