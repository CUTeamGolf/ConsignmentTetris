#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"

void main_computeRuntimeParameters(real_T (*t0)[12], real_T (*out)[12])
{
    real_T t22[3];
    real_T t9[3];
    real_T t12[1];
    real_T t13[1];
    real_T t14[1];
    real_T t15[1];
    real_T t16[1];
    real_T t17[1];
    real_T t18[1];
    real_T t19[1];
    real_T t20[1];
    real_T t21[1];
    real_T t41;
    real_T t42;
    real_T t43;
    real_T t44;
    real_T t45;
    real_T t46;
    real_T t47;
    real_T t48;
    real_T t49;
    real_T t50;
    real_T t51;
    real_T t52;
    t14[0ULL] = (*t0)[0ULL];
    t16[0ULL] = (*t0)[1ULL];
    t18[0ULL] = (*t0)[2ULL];
    t15[0ULL] = (*t0)[3ULL];
    t17[0ULL] = (*t0)[4ULL];
    t19[0ULL] = (*t0)[5ULL];
    t9[0ULL] = (*t0)[6ULL];
    t9[1ULL] = (*t0)[7ULL];
    t9[2ULL] = (*t0)[8ULL];
    t20[0ULL] = (*t0)[9ULL];
    t21[0ULL] = (*t0)[10ULL];
    t12[0ULL] = (*t0)[11ULL];
    memcpy(&t13[0], &t14[0], 8U);
    memcpy(&t14[0], &t15[0], 8U);
    memcpy(&t15[0], &t16[0], 8U);
    memcpy(&t16[0], &t17[0], 8U);
    memcpy(&t17[0], &t18[0], 8U);
    memcpy(&t18[0], &t19[0], 8U);
    memcpy(&t19[0], &t20[0], 8U);
    memcpy(&t20[0], &t21[0], 8U);
    memcpy(&t21[0], &t12[0], 8U);
    memcpy(&t22[0], &t9[0], 24U);
    t41 = t13[0ULL];
    t42 = t14[0ULL];
    t43 = t15[0ULL];
    t44 = t16[0ULL];
    t45 = t17[0ULL];
    t46 = t18[0ULL];
    t47 = t19[0ULL];
    t48 = t20[0ULL];
    t49 = t21[0ULL];
    t50 = t22[0ULL];
    t51 = t22[1ULL];
    t52 = t22[2ULL];
    (*out)[0] = t41;
    (*out)[1] = t42;
    (*out)[2] = t43;
    (*out)[3] = t44;
    (*out)[4] = t45;
    (*out)[5] = t46;
    (*out)[6] = t47;
    (*out)[7] = t48;
    (*out)[8] = t49;
    (*out)[9] = t50;
    (*out)[10] = t51;
    (*out)[11] = t52;
}
void main_computeAsmRuntimeDerivedValuesDoubles(const double *rtp, double *rtdvd)
{
  boolean_T bb[1];
  int ii[3];
  double xx[30];
  xx[0] = 0.0174532925199433;
  xx[1] = 0.0;
  xx[2] = !pmf_is_inf(rtp[0]) && !pmf_is_nan(rtp[0]) ? xx[0] * rtp[0] : xx[1];
  xx[3] = !pmf_is_inf(rtp[1]) && !pmf_is_nan(rtp[1]) ? xx[0] * rtp[1] : xx[1];
  xx[4] = !pmf_is_inf(rtp[2]) && !pmf_is_nan(rtp[2]) ? xx[0] * rtp[2] : xx[1];
  xx[5] = !pmf_is_inf(rtp[3]) && !pmf_is_nan(rtp[3]) ? xx[0] * rtp[3] : xx[1];
  xx[6] = !pmf_is_inf(rtp[4]) && !pmf_is_nan(rtp[4]) ? xx[0] * rtp[4] : xx[1];
  xx[7] = !pmf_is_inf(rtp[5]) && !pmf_is_nan(rtp[5]) ? xx[0] * rtp[5] : xx[1];
  xx[8] = !pmf_is_inf(rtp[6]) && !pmf_is_nan(rtp[6]) ? rtp[6] : xx[1];
  xx[9] = !pmf_is_inf(rtp[7]) && !pmf_is_nan(rtp[7]) ? rtp[7] : xx[1];
  xx[10] = !pmf_is_inf(rtp[8]) && !pmf_is_nan(rtp[8]) ? rtp[8] : xx[1];
  xx[11] = 0.5;
  bb[0] = !(pmf_is_inf(rtp[9]) || pmf_is_inf(rtp[10]) || pmf_is_inf(rtp[11])) && !(pmf_is_nan(rtp[9]) || pmf_is_nan(rtp[10]) || pmf_is_nan(rtp[11]));
  xx[12] = bb[0] ? xx[0] * rtp[11] : xx[1];
  xx[13] = xx[11] * xx[12];
  xx[14] = cos(xx[13]);
  xx[15] = bb[0] ? xx[0] * rtp[9] : xx[1];
  xx[16] = xx[11] * xx[15];
  xx[17] = cos(xx[16]);
  xx[18] = bb[0] ? xx[0] * rtp[10] : xx[1];
  xx[0] = xx[11] * xx[18];
  xx[1] = cos(xx[0]);
  xx[19] = xx[17] * xx[1];
  xx[20] = sin(xx[16]);
  xx[16] = sin(xx[0]);
  xx[0] = xx[20] * xx[16];
  xx[21] = sin(xx[13]);
  xx[13] = xx[14] * xx[19] - xx[0] * xx[21];
  xx[22] = xx[1] * xx[20];
  xx[1] = xx[17] * xx[16];
  xx[16] = xx[14] * xx[22] + xx[1] * xx[21];
  xx[17] = xx[14] * xx[1] - xx[22] * xx[21];
  xx[1] = xx[19] * xx[21] + xx[14] * xx[0];
  xx[0] = 57.29577951308232;
  xx[14] = xx[16] * xx[1];
  xx[19] = xx[13] * xx[17];
  xx[20] = 2.0;
  xx[21] = (xx[14] + xx[19]) * xx[20];
  xx[22] = fabs(xx[21]) - 0.99999999999999;
  if (xx[22] < 0.0)
    ii[0] = -1;
  else if (xx[22] > 0.0)
    ii[0] = +1;
  else
    ii[0] = 0;
  ii[1] = ii[0];
  if (0 > ii[1])
    ii[1] = 0;
  bb[0] = !(ii[1] == 1);
  xx[22] = xx[13] * xx[13];
  xx[23] = 1.0;
  xx[24] = (xx[22] + xx[1] * xx[1]) * xx[20] - xx[23];
  xx[25] = - (xx[20] * (xx[1] * xx[17] - xx[16] * xx[13]));
  xx[24] = (xx[25] == 0.0 && xx[24] == 0.0) ? 0.0 : atan2(xx[25], xx[24]);
  xx[25] = xx[16] * xx[17];
  xx[26] = xx[1] * xx[13];
  xx[27] = fabs(xx[21]) > 1.0 ? atan2(xx[21], 0.0)  : asin(xx[21]);
  if (xx[27] < 0.0)
    xx[21] = -1.0;
  else if (xx[27] > 0.0)
    xx[21] = +1.0;
  else
    xx[21] = 0.0;
  xx[28] = - (xx[20] * (xx[14] - xx[19]) * xx[21]);
  xx[29] = (xx[25] + xx[26]) * xx[20] * xx[21];
  xx[28] = (xx[29] == 0.0 && xx[28] == 0.0) ? 0.0 : atan2(xx[29], xx[28]);
  xx[14] = bb[0] ? xx[24] : xx[11] * xx[28];
  xx[11] = (xx[22] + xx[16] * xx[16]) * xx[20] - xx[23];
  xx[19] = - (xx[20] * (xx[25] - xx[26]));
  xx[11] = (xx[19] == 0.0 && xx[11] == 0.0) ? 0.0 : atan2(xx[19], xx[11]);
  rtdvd[0] = xx[2];
  rtdvd[1] = xx[3];
  rtdvd[2] = xx[4];
  rtdvd[3] = xx[5];
  rtdvd[4] = xx[6];
  rtdvd[5] = xx[7];
  rtdvd[6] = xx[8];
  rtdvd[7] = xx[9];
  rtdvd[8] = xx[10];
  rtdvd[9] = xx[13];
  rtdvd[10] = xx[16];
  rtdvd[11] = xx[17];
  rtdvd[12] = xx[1];
  rtdvd[13] = xx[15];
  rtdvd[14] = xx[18];
  rtdvd[15] = xx[12];
  rtdvd[16] = xx[8];
  rtdvd[17] = xx[9];
  rtdvd[18] = xx[10];
  rtdvd[19] = xx[0] * xx[14];
  rtdvd[20] = xx[0] * xx[27];
  rtdvd[21] = xx[0] * (bb[0] ? xx[11] : xx[21] * xx[14]);
  rtdvd[22] = xx[0] * xx[2];
  rtdvd[23] = xx[0] * xx[3];
  rtdvd[24] = xx[0] * xx[4];
  rtdvd[25] = xx[0] * xx[5];
  rtdvd[26] = xx[0] * xx[6];
  rtdvd[27] = xx[0] * xx[7];
}

void main_computeAsmRuntimeDerivedValuesInts(const double *rtp, int *rtdvi)
{
  (void) rtp;
  (void) rtdvi;
}

void main_computeAsmRuntimeDerivedValues(const double *rtp, RuntimeDerivedValuesBundle *rtdv)
{
  main_computeAsmRuntimeDerivedValuesDoubles(rtp, rtdv->mDoubles.mValues);
  main_computeAsmRuntimeDerivedValuesInts(rtp, rtdv->mInts.mValues);
}

