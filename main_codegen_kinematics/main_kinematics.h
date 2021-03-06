
#ifndef __main_kinematics_h__
#define __main_kinematics_h__
#ifdef __cplusplus

extern "C" {

#endif

  extern double main_solve_kinematics(
      const double* expTargetVals,
      const double* initGuessVals,
      double* outputVals,
      boolean_T* targetSuccess,
      double* actTargetVals);

#ifdef __cplusplus

}
#endif
#endif
