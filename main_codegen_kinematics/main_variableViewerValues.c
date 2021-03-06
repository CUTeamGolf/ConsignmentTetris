#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"

void main_mapStatesToVariableViewerValues(const double* stateVector, const int* modeVector, const RuntimeDerivedValuesBundle* rtdv, double* targetValuesVector, double* variableViewerValuesVector)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  boolean_T bb[2];
  int ii[3];
  double xx[19];
  (void) rtdvi;
  (void) modeVector;
  xx[0] = 0.0;
  xx[1] = 57.29577951308232;
  targetValuesVector[0] = xx[0];
  targetValuesVector[1] = xx[0];
  targetValuesVector[2] = xx[0];
  targetValuesVector[3] = xx[0];
  targetValuesVector[4] = xx[0];
  targetValuesVector[5] = xx[0];
  targetValuesVector[6] = xx[0];
  targetValuesVector[7] = xx[0];
  targetValuesVector[8] = xx[0];
  targetValuesVector[9] = xx[0];
  targetValuesVector[10] = xx[0];
  targetValuesVector[11] = xx[0];
  targetValuesVector[12] = xx[0];
  targetValuesVector[13] = rtdvd[6];
  targetValuesVector[14] = xx[0];
  targetValuesVector[15] = rtdvd[7];
  targetValuesVector[16] = xx[0];
  targetValuesVector[17] = rtdvd[8];
  targetValuesVector[18] = xx[0];
  targetValuesVector[19] = rtdvd[13];
  targetValuesVector[20] = rtdvd[14];
  targetValuesVector[21] = rtdvd[15];
  targetValuesVector[22] = xx[0];
  targetValuesVector[23] = xx[0];
  targetValuesVector[24] = xx[0];
  targetValuesVector[25] = xx[0];
  targetValuesVector[26] = xx[0];
  targetValuesVector[27] = xx[0];
  targetValuesVector[28] = xx[0];
  targetValuesVector[29] = xx[0];
  targetValuesVector[30] = xx[0];
  targetValuesVector[31] = xx[0];
  targetValuesVector[32] = xx[0];
  targetValuesVector[33] = xx[0];
  targetValuesVector[34] = xx[0];
  targetValuesVector[35] = xx[0];
  targetValuesVector[36] = xx[0];
  targetValuesVector[37] = xx[0];
  targetValuesVector[38] = xx[0];
  targetValuesVector[39] = xx[0];
  targetValuesVector[40] = xx[0];
  targetValuesVector[41] = xx[0];
  targetValuesVector[42] = xx[0];
  targetValuesVector[43] = xx[0];
  targetValuesVector[44] = xx[0];
  targetValuesVector[45] = xx[0];
  targetValuesVector[46] = xx[0];
  targetValuesVector[47] = xx[0];
  targetValuesVector[48] = xx[0];
  targetValuesVector[49] = xx[0];
  targetValuesVector[50] = xx[0];
  targetValuesVector[51] = xx[0];
  targetValuesVector[52] = xx[0];
  targetValuesVector[53] = xx[0];
  targetValuesVector[54] = xx[0];
  targetValuesVector[55] = xx[0];
  targetValuesVector[56] = xx[0];
  targetValuesVector[57] = xx[0];
  targetValuesVector[58] = xx[0];
  targetValuesVector[59] = xx[0];
  targetValuesVector[60] = xx[0];
  targetValuesVector[61] = xx[0];
  targetValuesVector[62] = xx[0];
  targetValuesVector[63] = xx[0];
  targetValuesVector[64] = xx[0];
  targetValuesVector[65] = xx[0];
  targetValuesVector[66] = xx[0];
  targetValuesVector[67] = xx[0];
  targetValuesVector[68] = xx[0];
  targetValuesVector[69] = xx[0];
  targetValuesVector[70] = xx[0];
  targetValuesVector[71] = xx[0];
  targetValuesVector[72] = xx[0];
  targetValuesVector[73] = xx[0];
  targetValuesVector[74] = xx[0];
  targetValuesVector[75] = xx[0];
  targetValuesVector[76] = xx[0];
  targetValuesVector[77] = xx[0];
  targetValuesVector[78] = xx[0];
  targetValuesVector[79] = xx[0];
  targetValuesVector[80] = xx[0];
  targetValuesVector[81] = xx[0];
  targetValuesVector[82] = xx[0];
  targetValuesVector[83] = xx[0];
  targetValuesVector[84] = xx[0];
  targetValuesVector[85] = xx[0];
  targetValuesVector[86] = xx[0];
  targetValuesVector[87] = xx[0];
  targetValuesVector[88] = xx[0];
  targetValuesVector[89] = xx[0];
  targetValuesVector[90] = xx[0];
  targetValuesVector[91] = xx[0];
  targetValuesVector[92] = xx[0];
  targetValuesVector[93] = xx[0];
  targetValuesVector[94] = xx[0];
  targetValuesVector[95] = xx[0];
  targetValuesVector[96] = xx[1] * rtdvd[0];
  targetValuesVector[97] = xx[1] * rtdvd[1];
  targetValuesVector[98] = xx[0];
  targetValuesVector[99] = xx[0];
  targetValuesVector[100] = xx[0];
  targetValuesVector[101] = xx[0];
  targetValuesVector[102] = xx[0];
  targetValuesVector[103] = xx[0];
  targetValuesVector[104] = xx[1] * rtdvd[2];
  targetValuesVector[105] = xx[1] * rtdvd[3];
  targetValuesVector[106] = xx[0];
  targetValuesVector[107] = xx[0];
  targetValuesVector[108] = xx[0];
  targetValuesVector[109] = xx[0];
  targetValuesVector[110] = xx[0];
  targetValuesVector[111] = xx[0];
  targetValuesVector[112] = xx[1] * rtdvd[4];
  targetValuesVector[113] = xx[1] * rtdvd[5];
  targetValuesVector[114] = xx[0];
  targetValuesVector[115] = xx[0];
  targetValuesVector[116] = xx[0];
  targetValuesVector[117] = xx[0];
  targetValuesVector[118] = xx[0];
  targetValuesVector[119] = xx[0];
  targetValuesVector[120] = xx[0];
  targetValuesVector[121] = xx[0];
  targetValuesVector[122] = xx[0];
  targetValuesVector[123] = xx[0];
  targetValuesVector[124] = xx[0];
  targetValuesVector[125] = xx[0];
  targetValuesVector[126] = xx[0];
  targetValuesVector[127] = xx[0];
  targetValuesVector[128] = xx[0];
  targetValuesVector[129] = xx[0];
  targetValuesVector[130] = xx[0];
  targetValuesVector[131] = xx[0];
  targetValuesVector[132] = xx[0];
  targetValuesVector[133] = xx[0];
  targetValuesVector[134] = xx[0];
  targetValuesVector[135] = xx[0];
  targetValuesVector[136] = xx[0];
  targetValuesVector[137] = xx[0];
  targetValuesVector[138] = xx[0];
  targetValuesVector[139] = xx[0];
  targetValuesVector[140] = xx[0];
  targetValuesVector[141] = xx[0];
  targetValuesVector[142] = xx[0];
  targetValuesVector[143] = xx[0];
  targetValuesVector[144] = xx[0];
  targetValuesVector[145] = xx[0];
  targetValuesVector[146] = xx[0];
  targetValuesVector[147] = xx[0];
  targetValuesVector[148] = xx[0];
  targetValuesVector[149] = xx[0];
  targetValuesVector[150] = xx[0];
  targetValuesVector[151] = xx[0];
  xx[0] = sqrt(stateVector[4] * stateVector[4] + stateVector[5] * stateVector[5] + stateVector[6] * stateVector[6]);
  xx[1] = 2.0;
  xx[2] = xx[0] == 0.0 ? 0.0 : 1.0 / xx[0];
  xx[3] = (stateVector[3] < 0.0 ? -1.0 : +1.0) * xx[2];
  xx[2] = stateVector[17] * stateVector[19];
  xx[4] = stateVector[16] * stateVector[18];
  xx[5] = (xx[2] + xx[4]) * xx[1];
  xx[6] = fabs(xx[5]) - 0.99999999999999;
  if (xx[6] < 0.0)
    ii[0] = -1;
  else if (xx[6] > 0.0)
    ii[0] = +1;
  else
    ii[0] = 0;
  ii[1] = ii[0];
  if (0 > ii[1])
    ii[1] = 0;
  bb[0] = ii[1] == 1;
  bb[1] = !bb[0];
  xx[6] = stateVector[16] * stateVector[16];
  xx[7] = 1.0;
  xx[8] = (xx[6] + stateVector[19] * stateVector[19]) * xx[1] - xx[7];
  xx[9] = - (xx[1] * (stateVector[18] * stateVector[19] - stateVector[16] * stateVector[17]));
  xx[8] = (xx[9] == 0.0 && xx[8] == 0.0) ? 0.0 : atan2(xx[9], xx[8]);
  xx[9] = stateVector[17] * stateVector[18];
  xx[10] = stateVector[16] * stateVector[19];
  xx[11] = fabs(xx[5]) > 1.0 ? atan2(xx[5], 0.0)  : asin(xx[5]);
  if (xx[11] < 0.0)
    xx[5] = -1.0;
  else if (xx[11] > 0.0)
    xx[5] = +1.0;
  else
    xx[5] = 0.0;
  xx[12] = - (xx[1] * (xx[2] - xx[4]) * xx[5]);
  xx[13] = (xx[9] + xx[10]) * xx[1] * xx[5];
  xx[12] = (xx[13] == 0.0 && xx[12] == 0.0) ? 0.0 : atan2(xx[13], xx[12]);
  xx[2] = bb[1] ? xx[8] : 0.5 * xx[12];
  xx[4] = ((cos(rtdvd[14])) < 0.0 ? -1.0 : +1.0);
  xx[8] = 1.570796326794897 * (xx[7] - xx[4]);
  xx[12] = (xx[6] + stateVector[17] * stateVector[17]) * xx[1] - xx[7];
  xx[13] = - (xx[1] * (xx[9] - xx[10]));
  xx[12] = (xx[13] == 0.0 && xx[12] == 0.0) ? 0.0 : atan2(xx[13], xx[12]);
  xx[6] = bb[1] ? xx[12] : xx[5] * xx[2];
  xx[5] = sqrt(stateVector[36] * stateVector[36] + stateVector[37] * stateVector[37] + stateVector[38] * stateVector[38]);
  xx[7] = xx[5] == 0.0 ? 0.0 : 1.0 / xx[5];
  xx[9] = (stateVector[35] < 0.0 ? -1.0 : +1.0) * xx[7];
  xx[7] = sqrt(stateVector[49] * stateVector[49] + stateVector[50] * stateVector[50] + stateVector[51] * stateVector[51]);
  xx[10] = xx[7] == 0.0 ? 0.0 : 1.0 / xx[7];
  xx[12] = (stateVector[48] < 0.0 ? -1.0 : +1.0) * xx[10];
  xx[10] = sqrt(stateVector[62] * stateVector[62] + stateVector[63] * stateVector[63] + stateVector[64] * stateVector[64]);
  xx[13] = xx[10] == 0.0 ? 0.0 : 1.0 / xx[10];
  xx[14] = (stateVector[61] < 0.0 ? -1.0 : +1.0) * xx[13];
  xx[13] = sqrt(stateVector[75] * stateVector[75] + stateVector[76] * stateVector[76] + stateVector[77] * stateVector[77]);
  xx[15] = xx[13] == 0.0 ? 0.0 : 1.0 / xx[13];
  xx[16] = (stateVector[74] < 0.0 ? -1.0 : +1.0) * xx[15];
  xx[15] = sqrt(stateVector[88] * stateVector[88] + stateVector[89] * stateVector[89] + stateVector[90] * stateVector[90]);
  xx[17] = xx[15] == 0.0 ? 0.0 : 1.0 / xx[15];
  xx[18] = (stateVector[87] < 0.0 ? -1.0 : +1.0) * xx[17];
  variableViewerValuesVector[0] = stateVector[0];
  variableViewerValuesVector[1] = stateVector[7];
  variableViewerValuesVector[2] = stateVector[1];
  variableViewerValuesVector[3] = stateVector[8];
  variableViewerValuesVector[4] = stateVector[2];
  variableViewerValuesVector[5] = stateVector[9];
  variableViewerValuesVector[6] = atan2(xx[0], fabs(stateVector[3])) * xx[1];
  variableViewerValuesVector[7] = xx[3] * stateVector[4];
  variableViewerValuesVector[8] = xx[3] * stateVector[5];
  variableViewerValuesVector[9] = xx[3] * stateVector[6];
  variableViewerValuesVector[10] = stateVector[10];
  variableViewerValuesVector[11] = stateVector[11];
  variableViewerValuesVector[12] = stateVector[12];
  variableViewerValuesVector[13] = stateVector[13];
  variableViewerValuesVector[14] = stateVector[20];
  variableViewerValuesVector[15] = stateVector[14];
  variableViewerValuesVector[16] = stateVector[21];
  variableViewerValuesVector[17] = stateVector[15];
  variableViewerValuesVector[18] = stateVector[22];
  variableViewerValuesVector[19] = rtdvd[13] + sm_core_canonicalAngle((bb[0] ? xx[2] : xx[2] - (xx[2] < 0.0 ? -1.0 : +1.0) * xx[8]) - rtdvd[13]);
  variableViewerValuesVector[20] = rtdvd[14] + sm_core_canonicalAngle((bb[0] ? xx[11] : xx[4] * xx[11] + (xx[11] < 0.0 ? -1.0 : +1.0) * xx[8]) - rtdvd[14]);
  variableViewerValuesVector[21] = rtdvd[15] + sm_core_canonicalAngle((bb[0] ? xx[6] : xx[6] - (xx[6] < 0.0 ? -1.0 : +1.0) * xx[8]) - rtdvd[15]);
  variableViewerValuesVector[22] = stateVector[23];
  variableViewerValuesVector[23] = stateVector[24];
  variableViewerValuesVector[24] = stateVector[25];
  variableViewerValuesVector[25] = stateVector[26];
  variableViewerValuesVector[26] = stateVector[27];
  variableViewerValuesVector[27] = stateVector[28];
  variableViewerValuesVector[28] = stateVector[29];
  variableViewerValuesVector[29] = stateVector[30];
  variableViewerValuesVector[30] = stateVector[31];
  variableViewerValuesVector[31] = stateVector[32];
  variableViewerValuesVector[32] = stateVector[39];
  variableViewerValuesVector[33] = stateVector[33];
  variableViewerValuesVector[34] = stateVector[40];
  variableViewerValuesVector[35] = stateVector[34];
  variableViewerValuesVector[36] = stateVector[41];
  variableViewerValuesVector[37] = atan2(xx[5], fabs(stateVector[35])) * xx[1];
  variableViewerValuesVector[38] = xx[9] * stateVector[36];
  variableViewerValuesVector[39] = xx[9] * stateVector[37];
  variableViewerValuesVector[40] = xx[9] * stateVector[38];
  variableViewerValuesVector[41] = stateVector[42];
  variableViewerValuesVector[42] = stateVector[43];
  variableViewerValuesVector[43] = stateVector[44];
  variableViewerValuesVector[44] = stateVector[45];
  variableViewerValuesVector[45] = stateVector[52];
  variableViewerValuesVector[46] = stateVector[46];
  variableViewerValuesVector[47] = stateVector[53];
  variableViewerValuesVector[48] = stateVector[47];
  variableViewerValuesVector[49] = stateVector[54];
  variableViewerValuesVector[50] = atan2(xx[7], fabs(stateVector[48])) * xx[1];
  variableViewerValuesVector[51] = xx[12] * stateVector[49];
  variableViewerValuesVector[52] = xx[12] * stateVector[50];
  variableViewerValuesVector[53] = xx[12] * stateVector[51];
  variableViewerValuesVector[54] = stateVector[55];
  variableViewerValuesVector[55] = stateVector[56];
  variableViewerValuesVector[56] = stateVector[57];
  variableViewerValuesVector[57] = stateVector[58];
  variableViewerValuesVector[58] = stateVector[65];
  variableViewerValuesVector[59] = stateVector[59];
  variableViewerValuesVector[60] = stateVector[66];
  variableViewerValuesVector[61] = stateVector[60];
  variableViewerValuesVector[62] = stateVector[67];
  variableViewerValuesVector[63] = atan2(xx[10], fabs(stateVector[61])) * xx[1];
  variableViewerValuesVector[64] = xx[14] * stateVector[62];
  variableViewerValuesVector[65] = xx[14] * stateVector[63];
  variableViewerValuesVector[66] = xx[14] * stateVector[64];
  variableViewerValuesVector[67] = stateVector[68];
  variableViewerValuesVector[68] = stateVector[69];
  variableViewerValuesVector[69] = stateVector[70];
  variableViewerValuesVector[70] = stateVector[71];
  variableViewerValuesVector[71] = stateVector[78];
  variableViewerValuesVector[72] = stateVector[72];
  variableViewerValuesVector[73] = stateVector[79];
  variableViewerValuesVector[74] = stateVector[73];
  variableViewerValuesVector[75] = stateVector[80];
  variableViewerValuesVector[76] = atan2(xx[13], fabs(stateVector[74])) * xx[1];
  variableViewerValuesVector[77] = xx[16] * stateVector[75];
  variableViewerValuesVector[78] = xx[16] * stateVector[76];
  variableViewerValuesVector[79] = xx[16] * stateVector[77];
  variableViewerValuesVector[80] = stateVector[81];
  variableViewerValuesVector[81] = stateVector[82];
  variableViewerValuesVector[82] = stateVector[83];
  variableViewerValuesVector[83] = stateVector[84];
  variableViewerValuesVector[84] = stateVector[91];
  variableViewerValuesVector[85] = stateVector[85];
  variableViewerValuesVector[86] = stateVector[92];
  variableViewerValuesVector[87] = stateVector[86];
  variableViewerValuesVector[88] = stateVector[93];
  variableViewerValuesVector[89] = atan2(xx[15], fabs(stateVector[87])) * xx[1];
  variableViewerValuesVector[90] = xx[18] * stateVector[88];
  variableViewerValuesVector[91] = xx[18] * stateVector[89];
  variableViewerValuesVector[92] = xx[18] * stateVector[90];
  variableViewerValuesVector[93] = stateVector[94];
  variableViewerValuesVector[94] = stateVector[95];
  variableViewerValuesVector[95] = stateVector[96];
  variableViewerValuesVector[96] = stateVector[97];
  variableViewerValuesVector[97] = stateVector[98];
  variableViewerValuesVector[98] = stateVector[99];
  variableViewerValuesVector[99] = stateVector[100];
  variableViewerValuesVector[100] = stateVector[101];
  variableViewerValuesVector[101] = stateVector[102];
  variableViewerValuesVector[102] = stateVector[103];
  variableViewerValuesVector[103] = stateVector[104];
  variableViewerValuesVector[104] = stateVector[105];
  variableViewerValuesVector[105] = stateVector[106];
  variableViewerValuesVector[106] = stateVector[107];
  variableViewerValuesVector[107] = stateVector[108];
  variableViewerValuesVector[108] = stateVector[109];
  variableViewerValuesVector[109] = stateVector[110];
  variableViewerValuesVector[110] = stateVector[111];
  variableViewerValuesVector[111] = stateVector[112];
  variableViewerValuesVector[112] = stateVector[113];
  variableViewerValuesVector[113] = stateVector[114];
  variableViewerValuesVector[114] = stateVector[115];
  variableViewerValuesVector[115] = stateVector[116];
  variableViewerValuesVector[116] = stateVector[117];
  variableViewerValuesVector[117] = stateVector[118];
  variableViewerValuesVector[118] = stateVector[119];
  variableViewerValuesVector[119] = stateVector[120];
  variableViewerValuesVector[120] = stateVector[121];
  variableViewerValuesVector[121] = stateVector[122];
  variableViewerValuesVector[122] = stateVector[123];
  variableViewerValuesVector[123] = stateVector[124];
  variableViewerValuesVector[124] = stateVector[125];
  variableViewerValuesVector[125] = stateVector[126];
  variableViewerValuesVector[126] = stateVector[127];
  variableViewerValuesVector[127] = stateVector[128];
  variableViewerValuesVector[128] = stateVector[129];
  variableViewerValuesVector[129] = stateVector[130];
  variableViewerValuesVector[130] = stateVector[131];
  variableViewerValuesVector[131] = stateVector[132];
  variableViewerValuesVector[132] = stateVector[133];
  variableViewerValuesVector[133] = stateVector[134];
  variableViewerValuesVector[134] = stateVector[135];
  variableViewerValuesVector[135] = stateVector[136];
  variableViewerValuesVector[136] = stateVector[137];
  variableViewerValuesVector[137] = stateVector[138];
  variableViewerValuesVector[138] = stateVector[139];
  variableViewerValuesVector[139] = stateVector[140];
  variableViewerValuesVector[140] = stateVector[141];
  variableViewerValuesVector[141] = stateVector[142];
  variableViewerValuesVector[142] = stateVector[143];
  variableViewerValuesVector[143] = stateVector[144];
  variableViewerValuesVector[144] = stateVector[145];
  variableViewerValuesVector[145] = stateVector[146];
  variableViewerValuesVector[146] = stateVector[147];
  variableViewerValuesVector[147] = stateVector[148];
  variableViewerValuesVector[148] = stateVector[149];
  variableViewerValuesVector[149] = stateVector[150];
  variableViewerValuesVector[150] = stateVector[151];
  variableViewerValuesVector[151] = stateVector[152];
}

static boolean_T checkTargets_0(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[97] - rtdvd[0]) < 1.0e-5;
}

static boolean_T checkTargets_1(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[98] - rtdvd[1]) < 1.0e-5;
}

static boolean_T checkTargets_2(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[105] - rtdvd[2]) < 1.0e-5;
}

static boolean_T checkTargets_3(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[106] - rtdvd[3]) < 1.0e-5;
}

static boolean_T checkTargets_4(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[113] - rtdvd[4]) < 1.0e-5;
}

static boolean_T checkTargets_5(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  return fabs(state[114] - rtdvd[5]) < 1.0e-5;
}

static boolean_T checkTargets_116(const RuntimeDerivedValuesBundle *rtdv, const double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[2];
  (void) rtdvi;
  xx[0] = rtdvd[9] * state[16] + rtdvd[10] * state[17] + rtdvd[11] * state[18] + rtdvd[12] * state[19];
  if (xx[0] < 0.0)
    xx[0] = -1.0;
  else if (xx[0] > 0.0)
    xx[0] = +1.0;
  else
    xx[0] = 0.0;
  xx[1] = 1.0e-5;
  return fabs(xx[0] * state[16] - rtdvd[9]) < xx[1] && fabs(xx[0] * state[17] - rtdvd[10]) < xx[1] && fabs(xx[0] * state[18] - rtdvd[11]) < xx[1] && fabs(xx[0] * state[19] - rtdvd[12]) < xx[1];
}

boolean_T main_getTargetStatus(const RuntimeDerivedValuesBundle *rtdv, const double *state, const size_t targetIndex)
{
  switch(targetIndex)
  {
    case 0:
      return checkTargets_0(rtdv, state);
    case 1:
      return checkTargets_1(rtdv, state);
    case 2:
      return checkTargets_2(rtdv, state);
    case 3:
      return checkTargets_3(rtdv, state);
    case 4:
      return checkTargets_4(rtdv, state);
    case 5:
      return checkTargets_5(rtdv, state);
    case 116:
      return checkTargets_116(rtdv, state);
  }
  return true;
}

