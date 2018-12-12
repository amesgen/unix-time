#include "win_patch.h"

inline int isblank_l( int c, _locale_t _loc)
{
    return ( c == ' ' || c == '\t' );
}

inline int strncasecmp_l(const char *s1, const char *s2, int len, _locale_t _loc) {
    return strncasecmp(s1, s2, len);
}

inline struct tm *gmtime_r(const time_t *_time_t, struct tm *_tm) {
    errno_t err = gmtime_s(_tm, _time_t);
    if (err) {
        return NULL;
    }
    return _tm;
}

inline struct tm *localtime_r(const time_t *_time_t, struct tm *_tm) {
    errno_t err = localtime_s(_tm, _time_t);
    if (err) {
        return NULL;
    }
    return _tm;
}

const struct lc_time_T   _C_time_locale = {
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    }, {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    }, {
        "Sun", "Mon", "Tue", "Wed",
        "Thu", "Fri", "Sat"
    }, {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    },

    /* X_fmt */
    "%H:%M:%S",

    /*
     * x_fmt
     * Since the C language standard calls for
     * "date, using locale's date format," anything goes.
     * Using just numbers (as here) makes Quakers happier;
     * it's also compatible with SVR4.
     */
    "%m/%d/%y",

    /*
     * c_fmt
     */
    "%a %b %e %H:%M:%S %Y",

    /* am */
    "AM",

    /* pm */
    "PM",

    /* date_fmt */
    "%a %b %e %H:%M:%S %Z %Y",
    
    /* alt_month
     * Standalone months forms for %OB
     */
    {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    },

    /* md_order
     * Month / day order in dates
     */
    "md",

    /* ampm_fmt
     * To determine 12-hour clock format time (empty, if N/A)
     */
    "%I:%M:%S %p"
};


int _patch_setenv(const char *var, const char *val, int ovr) {
    BOOL b = SetEnvironmentVariableA(var, val);
    if (b) {
        return 0;
    } else {
        return 1;
    }
}

int _patch_unsetenv(const char *name) {
    int len = strlen(name);
    char *sname = (char *)malloc(len + 2);
    strcpy(sname, name);
    sname[len] = '=';
    sname[len + 1] = '\0';
    int r = _putenv(sname);
    free(sname);
    return r;
}
