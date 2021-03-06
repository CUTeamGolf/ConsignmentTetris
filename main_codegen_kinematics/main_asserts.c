#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"

void main_validateRuntimeParameters(const double *rtp, int32_T *satFlags)
{
  satFlags[0] = !pmf_is_inf(rtp[0]) ? 1 : 0;
  satFlags[1] = !pmf_is_nan(rtp[0]) ? 1 : 0;
  satFlags[2] = !pmf_is_inf(rtp[1]) ? 1 : 0;
  satFlags[3] = !pmf_is_nan(rtp[1]) ? 1 : 0;
  satFlags[4] = !pmf_is_inf(rtp[2]) ? 1 : 0;
  satFlags[5] = !pmf_is_nan(rtp[2]) ? 1 : 0;
  satFlags[6] = !pmf_is_inf(rtp[3]) ? 1 : 0;
  satFlags[7] = !pmf_is_nan(rtp[3]) ? 1 : 0;
  satFlags[8] = !pmf_is_inf(rtp[4]) ? 1 : 0;
  satFlags[9] = !pmf_is_nan(rtp[4]) ? 1 : 0;
  satFlags[10] = !pmf_is_inf(rtp[5]) ? 1 : 0;
  satFlags[11] = !pmf_is_nan(rtp[5]) ? 1 : 0;
  satFlags[12] = !pmf_is_inf(rtp[6]) ? 1 : 0;
  satFlags[13] = !pmf_is_nan(rtp[6]) ? 1 : 0;
  satFlags[14] = !pmf_is_inf(rtp[7]) ? 1 : 0;
  satFlags[15] = !pmf_is_nan(rtp[7]) ? 1 : 0;
  satFlags[16] = !pmf_is_inf(rtp[8]) ? 1 : 0;
  satFlags[17] = !pmf_is_nan(rtp[8]) ? 1 : 0;
  satFlags[18] = !(pmf_is_inf(rtp[9]) || pmf_is_inf(rtp[10]) || pmf_is_inf(rtp[11])) ? 1 : 0;
  satFlags[19] = !(pmf_is_nan(rtp[9]) || pmf_is_nan(rtp[10]) || pmf_is_nan(rtp[11])) ? 1 : 0;
}



const NeAssertData main_assertData[20] = {
      {"main/Delta Robot/Actuator 1", 0, 0, "Delta_Robot.Actuator_1", "", false, "The parameter Rz/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 1", 0, 0, "Delta_Robot.Actuator_1", "", false, "The parameter Rz/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"main/Delta Robot/Actuator 1", 0, 0, "Delta_Robot.Actuator_1", "", false, "The parameter Rz/Velocity contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 1", 0, 0, "Delta_Robot.Actuator_1", "", false, "The parameter Rz/Velocity contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"main/Delta Robot/Actuator 2", 0, 0, "Delta_Robot.Actuator_2", "", false, "The parameter Rz/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 2", 0, 0, "Delta_Robot.Actuator_2", "", false, "The parameter Rz/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"main/Delta Robot/Actuator 2", 0, 0, "Delta_Robot.Actuator_2", "", false, "The parameter Rz/Velocity contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 2", 0, 0, "Delta_Robot.Actuator_2", "", false, "The parameter Rz/Velocity contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"main/Delta Robot/Actuator 3", 0, 0, "Delta_Robot.Actuator_3", "", false, "The parameter Rz/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 3", 0, 0, "Delta_Robot.Actuator_3", "", false, "The parameter Rz/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"main/Delta Robot/Actuator 3", 0, 0, "Delta_Robot.Actuator_3", "", false, "The parameter Rz/Velocity contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"main/Delta Robot/Actuator 3", 0, 0, "Delta_Robot.Actuator_3", "", false, "The parameter Rz/Velocity contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Px/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Px/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Py/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Py/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Pz/Position contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter Pz/Position contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter S/Angles contains an Inf value, which is not allowed.", "sm:model:evaluate:InvalidValueInf"},
      {"", 0, 0, "x6_DOF_Joint1", "", false, "The parameter S/Angles contains a NaN value, which is not allowed.", "sm:model:evaluate:InvalidValueNaN"}
    };
