


#include "pm_std.h"
#include "pm_default_allocator.h"
#include "sm_ssci_KinematicsSolverData.h"
#include "sm_CTarget.h"


 






#define pm_allocator_alloc(_allocator, _m, _n) ((_allocator)->mCallocFcn((_allocator), (_m), (_n)))
#define PM_ALLOCATE_ARRAY(_name, _type, _size, _allocator)\
 _name = (_type *) pm_allocator_alloc(_allocator, sizeof(_type), _size)


int_T pm_create_real_vector_fields(PmRealVector *, size_t, PmAllocator *);







void main_computeRuntimeParameters(
  const double *runtimeRootVariables,
  double *runtimeParameters);

void main_validateRuntimeParameters(
  const double *runtimeParameters,
  int32_T *assertSatisfactionFlags);

void main_computeAsmRuntimeDerivedValues(
  const double *runtimeParameters,
  RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle);



boolean_T main_getTargetStatus(
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  const double *stateVector,
  const size_t targetIndex);

void main_setTargets(
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  CTarget *targets);

void main_resetAsmStateVector(const void *mech, double *stateVector);

void main_mapStatesToVariableViewerValues(
  const double *stateVector,
  const int *modeVector,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  double *targetValuesVector,
  double *variableViewerValuesVector);

void main_initializeTrackedAngleState(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  const int *modeVector,
  const double *motionData,
  double *stateVector);

void main_computeDiscreteState(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  double *stateVector);

void main_adjustPosition(
  const void *mech,
  const double *dofDeltas,
  double *stateVector);

void main_perturbAsmJointPrimitiveState(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  double magnitude,
  boolean_T doPerturbVelocity,
  double *stateVector);

void main_computePosDofBlendMatrix(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  const double *stateVector,
  int partialType,
  double *matrix);

void main_computeVelDofBlendMatrix(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  const double *stateVector,
  int partialType,
  double *matrix);

void main_projectPartiallyTargetedPos(
  const void *mech,
  size_t stageIdx,
  size_t primitiveIdx,
  const double *origStateVector,
  int partialType,
  double *stateVector);

void main_propagateMotion(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  const double *stateVector,
  double *motionData);

size_t main_computeAssemblyError(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  size_t constraintIdx,
  const int *modeVector,
  const double *motionData,
  double *error);

size_t main_computeAssemblyJacobian(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  size_t constraintIdx,
  boolean_T forVelocitySatisfaction,
  const double *stateVector,
  const int *modeVector,
  const double *motionData,
  double *J);
size_t main_computeFullAssemblyJacobian(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  const double *stateVector,
  const int *modeVector,
  const double *motionData,
  double *J);

int main_isInKinematicSingularity(
  const void *mech,
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle,
  size_t constraintIdx,
  const int *modeVector,
  const double *motionData);






static void checkMemAllocStatus(int_T status)
{
  
  (void) status;

  
}










static void initStateVector(KinematicsSolverData *ksData)
{
  PmAllocator *alloc = pm_default_allocator();
  const CTarget targets[118] = {
      {0, 201, 0, false, 0, 2, "deg", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 201, 0, false, 0, 2, "deg/s", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 202, 0, false, 0, 2, "deg", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 202, 0, false, 0, 2, "deg/s", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 203, 0, false, 0, 2, "deg", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 203, 0, false, 0, 2, "deg/s", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 211, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 211, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 225, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 225, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 229, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 229, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 231, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 231, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 233, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 233, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 248, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 248, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 262, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 262, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 266, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 266, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 268, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 268, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 270, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 270, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 285, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 285, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 299, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 299, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 303, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 303, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 305, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 305, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 307, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 307, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 317, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 317, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 318, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 318, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 319, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 319, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 510, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 510, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 511, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 511, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 512, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 512, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 513, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 513, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 514, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 514, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1060, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1060, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1061, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1061, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1062, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1062, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1063, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1063, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1064, 0, false, 0, 0, "1", false, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1064, 0, false, 0, 0, "1", true, true, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1225, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1225, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1225, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1239, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1239, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1239, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1240, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1240, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1240, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1241, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1241, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1241, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1242, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1242, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1242, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 0, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 1, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 2, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1243, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1243, 3, false, 0, 0, "1", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1243, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 0, false, 0, 1, "m", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 0, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 1, false, 0, 1, "m", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 1, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 2, false, 0, 1, "m", false, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {0, 1245, 2, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 1, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {1, 1245, 3, false, 0, 2, "deg", false, false, +1.000000000000000000e+00, true, 4, {+1.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}},
      {2, 1245, 3, false, 0, 0, "1", true, false, +1.000000000000000000e+00, true, 3, {+0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00, +0.000000000000000000e+00}, {+0.000000000000000000e+00}}
    };
  const size_t numTargets = 118;
  int_T status;
  size_t i;

  
  status = pm_create_real_vector_fields(
    &ksData->mAssemblyFullStateVector, 153, alloc);
  checkMemAllocStatus(status);

  
  PM_ALLOCATE_ARRAY(ksData->mTargets, CTarget, numTargets, alloc);
  for (i = 0; i < numTargets; ++i)
    sm_compiler_CTarget_copy(targets + i, ksData->mTargets + i);
}



static void initRuntimeParameters(KinematicsSolverData *ksData)
{
  PmAllocator *alloc = pm_default_allocator();
  int_T status = 0;
  size_t i = 0;

  
  status = pm_create_real_vector_fields(
    &ksData->mRuntimeParameterScalars, 
    12,
    alloc);
  checkMemAllocStatus(status);
  for (i = 0; i < ksData->mRuntimeParameterScalars.mN; ++i)
    ksData->mRuntimeParameterScalars.mX[i] = 0.0;

  
  sm_core_RuntimeDerivedValuesBundle_create(
    &ksData->mAsmRuntimeDerivedValuesBundle,
    28,
    0);
}



static void initAssemblyDelegate(SmMechanismDelegate *delegate)
{
  SmMechanismDelegateScratchpad *scratchpad = NULL;
  const SmSizePair jointToStageIdx[32] = {
      {201, 10}, {202, 14}, {203, 18}, {211, 11}, {231, 12}, {233, 13},
      {248, 15}, {268, 16}, {270, 17}, {285, 19}, {305, 20}, {307, 21},
      {317, 2}, {318, 3}, {319, 4}, {510, 22}, {511, 23}, {512, 24},
      {513, 25}, {514, 26}, {1060, 27}, {1061, 28}, {1062, 29}, {1063, 30},
      {1064, 31}, {1225, 0}, {1239, 5}, {1240, 6}, {1241, 7}, {1242, 8},
      {1243, 9}, {1245, 1}
    };
  const size_t primitiveIndices[32 + 1] = {
      0, 4, 8, 9, 10, 11, 15, 19, 23, 27,
      31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
      51, 52, 53
    };
  const SmSizePair stateOffsets[53] = {
      {0, 7}, {1, 8}, {2, 9}, {3, 10}, {13, 20}, {14, 21},
      {15, 22}, {16, 23}, {26, 27}, {28, 29}, {30, 31}, {32, 39},
      {33, 40}, {34, 41}, {35, 42}, {45, 52}, {46, 53}, {47, 54},
      {48, 55}, {58, 65}, {59, 66}, {60, 67}, {61, 68}, {71, 78},
      {72, 79}, {73, 80}, {74, 81}, {84, 91}, {85, 92}, {86, 93},
      {87, 94}, {97, 98}, {99, 100}, {101, 102}, {103, 104}, {105, 106},
      {107, 108}, {109, 110}, {111, 112}, {113, 114}, {115, 116}, {117, 118},
      {119, 120}, {121, 122}, {123, 124}, {125, 126}, {127, 128}, {129, 130},
      {131, 132}, {133, 134}, {135, 136}, {137, 138}, {139, 140}
    };
  const SmSizePair dofOffsets[53] = {
      {0, 1}, {1, 2}, {2, 3}, {3, 6}, {6, 7}, {7, 8},
      {8, 9}, {9, 12}, {12, 13}, {13, 14}, {14, 15}, {15, 16},
      {16, 17}, {17, 18}, {18, 21}, {21, 22}, {22, 23}, {23, 24},
      {24, 27}, {27, 28}, {28, 29}, {29, 30}, {30, 33}, {33, 34},
      {34, 35}, {35, 36}, {36, 39}, {39, 40}, {40, 41}, {41, 42},
      {42, 45}, {45, 46}, {46, 47}, {47, 48}, {48, 49}, {49, 50},
      {50, 51}, {51, 52}, {52, 53}, {53, 54}, {54, 55}, {55, 56},
      {56, 57}, {57, 58}, {58, 59}, {59, 60}, {60, 61}, {61, 62},
      {62, 63}, {63, 64}, {64, 65}, {65, 66}, {66, 67}
    };
  const size_t *flexibleStages = NULL;
  const size_t remodIndices[25] = {
      26, 28, 30, 97, 99, 101, 103, 105, 107, 109,
      111, 113, 115, 117, 119, 121, 123, 125, 127, 129,
      131, 133, 135, 137, 139
    };
  const size_t equationsPerConstraint[6] = {
      5, 5, 5, 5, 5, 5
    };
  const size_t dofToVelSlot[67] = {
      7, 8, 9, 10, 11, 12, 20, 21, 22, 23,
      24, 25, 27, 29, 31, 39, 40, 41, 42, 43,
      44, 52, 53, 54, 55, 56, 57, 65, 66, 67,
      68, 69, 70, 78, 79, 80, 81, 82, 83, 91,
      92, 93, 94, 95, 96, 98, 100, 102, 104, 106,
      108, 110, 112, 114, 116, 118, 120, 122, 124, 126,
      128, 130, 132, 134, 136, 138, 140
    };
  const size_t constraintDofs[60] = {
      45, 46, 47, 6, 7, 8, 9, 10, 11, 12,
      45, 46, 48, 6, 7, 8, 9, 10, 11, 12,
      49, 50, 51, 6, 7, 8, 9, 10, 11, 13,
      49, 50, 52, 6, 7, 8, 9, 10, 11, 13,
      53, 54, 55, 6, 7, 8, 9, 10, 11, 14,
      53, 54, 56, 6, 7, 8, 9, 10, 11, 14
    };
  const size_t constraintDofOffsets[6 + 1] = {
      0, 10, 20, 30, 40, 50, 60
    };
  const size_t Jm = 30; 
  const size_t Jn = 67;                        

  SmSizePair zeroSizePair;
  zeroSizePair.mFirst = zeroSizePair.mSecond = 0;

  sm_core_MechanismDelegate_allocScratchpad(delegate);
  scratchpad = delegate->mScratchpad;

  

  delegate->mTargetStrengthFree        = 0;
  delegate->mTargetStrengthSuggested   = 1;
  delegate->mTargetStrengthDesired     = 2;
  delegate->mTargetStrengthRequired    = 3;
  delegate->mConsistencyTol            = +1.000000000000000082e-05;
  delegate->mTreeJointDof              = 67;
  delegate->mDof                       = 67;
  delegate->mStateSize                 = 153;
  delegate->mContinuousStateSize       = 153;
  delegate->mNumStages                 = 32;
  delegate->mNumConstraints            = 6;
  delegate->mNumAllConstraintEquations = 30;


  

  sm_core_SmSizePairVector_create(
    &delegate->mJointToStageIdx, 32, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mJointToStageIdx),
         jointToStageIdx, 32 * sizeof(SmSizePair));

  sm_core_SmSizeTVector_create(
    &delegate->mPrimitiveIndices, delegate->mNumStages + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mPrimitiveIndices),
         primitiveIndices, (delegate->mNumStages + 1) * sizeof(size_t));

  sm_core_SmSizePairVector_create(
    &delegate->mStateOffsets, 53, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mStateOffsets),
         stateOffsets, 53 * sizeof(SmSizePair));

  sm_core_SmSizePairVector_create(
    &delegate->mDofOffsets, 53, &zeroSizePair);
  memcpy(sm_core_SmSizePairVector_nonConstValues(&delegate->mDofOffsets),
         dofOffsets, 53 * sizeof(SmSizePair));

  sm_core_SmSizeTVector_create(
    &delegate->mFlexibleStages, 0, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mFlexibleStages),
         flexibleStages, 0 * sizeof(size_t));

  sm_core_SmSizeTVector_create(
    &delegate->mRemodIndices, 25, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mRemodIndices),
         remodIndices, 25 * sizeof(size_t));

  sm_core_SmSizeTVector_create(
    &delegate->mEquationsPerConstraint, delegate->mNumConstraints, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mEquationsPerConstraint),
         equationsPerConstraint, delegate->mNumConstraints * sizeof(size_t));

  
  sm_core_SmIntVector_create(
    &delegate->mRunTimeEnabledEquations,
    delegate->mNumAllConstraintEquations, 1);

  sm_core_SmSizeTVector_create(
    &delegate->mDofToVelSlot, delegate->mDof, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mDofToVelSlot),
         dofToVelSlot, delegate->mDof * sizeof(size_t));

  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofs, 60, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofs),
         constraintDofs, 60 * sizeof(size_t));

  sm_core_SmSizeTVector_create(
    &delegate->mConstraintDofOffsets, delegate->mNumConstraints + 1, 0);
  memcpy(sm_core_SmSizeTVector_nonConstValues(&delegate->mConstraintDofOffsets),
         constraintDofOffsets, (delegate->mNumConstraints + 1) * sizeof(size_t));


  

  sm_core_SmBoundedSet_create(&scratchpad->mPosRequired,    67);
  sm_core_SmBoundedSet_create(&scratchpad->mPosDesired,     67);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggested,   67);
  sm_core_SmBoundedSet_create(&scratchpad->mPosFree,        67);
  sm_core_SmBoundedSet_create(&scratchpad->mPosNonRequired, 67);
  sm_core_SmBoundedSet_create(&scratchpad->mPosSuggAndFree, 67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelRequired,    67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelDesired,     67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggested,   67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelFree,        67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelNonRequired, 67);
  sm_core_SmBoundedSet_create(&scratchpad->mVelSuggAndFree, 67);
  sm_core_SmBoundedSet_create(&scratchpad->mConstraintFilter, 6);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveConstraints, 6);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs,     67);
  sm_core_SmBoundedSet_create(&scratchpad->mActiveDofs0,    67);
  sm_core_SmBoundedSet_create(&scratchpad->mNewConstraints, 6);
  sm_core_SmBoundedSet_create(&scratchpad->mNewDofs,        67);
  sm_core_SmBoundedSet_create(&scratchpad->mUnsatisfiedConstraints, 6);

  sm_core_SmSizeTVector_create(&scratchpad->mActiveConstraintsVect,
                               6, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mActiveDofsVect,  67, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mFullDofToActiveDof, 67, 0);
  
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyPosTargetedPrims, 53, &zeroSizePair);
  sm_core_SmSizePairVector_create(
    &scratchpad->mPartiallyVelTargetedPrims, 53, &zeroSizePair);
  sm_core_SmSizeTVector_create(&scratchpad->mPosPartialTypes, 53, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mVelPartialTypes, 53, 0);
  sm_core_SmSizeTVector_create(&scratchpad->mPartiallyActivePrims, 53, 0);

  
  sm_core_SmSizePairVector_create(
    &scratchpad->mBaseFrameVelOffsets, 7, &zeroSizePair);
  
  sm_core_SmSizePairVector_create(
    &scratchpad->mCvVelOffsets, 53, &zeroSizePair);
  sm_core_SmRealVector_create(
    &scratchpad->mCvAzimuthValues, 53, 0.0);

  
  sm_core_SmRealVector_create(&scratchpad->mInitialState, 153, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mStartState,   153, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mTestState,    153, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mFullStateVector, 153, 0.0);

  
  sm_core_SmRealVector_create(&scratchpad->mJacobianRowMaj, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobian, Jm * Jn, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mJacobianPrimSubmatrix, Jm * 6, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintNonhomoTerms, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mConstraintError, Jm, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mBestConstraintError, Jm, 0.0);

  
  sm_core_SmRealVector_create(&scratchpad->mDeltas,
                              Jn * (Jm <= Jn ? Jm : Jn), 0.0);
  sm_core_SmRealVector_create(&scratchpad->mSvdWork, 9664, 0.0);

  
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchScaledDeltaVect, 67, 0.0);
  sm_core_SmRealVector_create(
    &scratchpad->mLineSearchTestStateVect, 153, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mLineSearchErrorVect, Jm, 0.0);

  
  sm_core_SmRealVector_create(&scratchpad->mActiveDofVelsVect, 67, 0.0);
  sm_core_SmRealVector_create(&scratchpad->mVelSystemRhs, Jm, 0.0);

  
  sm_core_SmRealVector_create(&scratchpad->mMotionData, 542, 0.0);


  

  delegate->mSetTargets                  = main_setTargets;
  delegate->mResetStateVector            = main_resetAsmStateVector;
  delegate->mInitializeTrackedAngleState = main_initializeTrackedAngleState;
  delegate->mComputeDiscreteState        = main_computeDiscreteState;
  delegate->mAdjustPosition              = main_adjustPosition;
  delegate->mPerturbJointPrimitiveState  = main_perturbAsmJointPrimitiveState;
  delegate->mPerturbFlexibleBodyState    = NULL;
  delegate->mComputePosDofBlendMatrix    = main_computePosDofBlendMatrix;
  delegate->mComputeVelDofBlendMatrix    = main_computeVelDofBlendMatrix;
  delegate->mProjectPartiallyTargetedPos = main_projectPartiallyTargetedPos;
  delegate->mPropagateMotion             = main_propagateMotion;
  delegate->mComputeAssemblyError        = main_computeAssemblyError;
  delegate->mComputeAssemblyJacobian     = main_computeAssemblyJacobian;
  delegate->mComputeFullAssemblyJacobian = main_computeFullAssemblyJacobian;
  delegate->mIsInKinematicSingularity    = main_isInKinematicSingularity;
  delegate->mConvertStateVector          = NULL;
  delegate->mConstructStateVector        = NULL;
  delegate->mExtractSolverStateVector    = NULL;
  delegate->mIsPositionViolation         = NULL;
  delegate->mIsVelocityViolation         = NULL;
  delegate->mProjectStateSim             = NULL;
  delegate->mComputeConstraintError      = NULL;


  

  delegate->mMech = NULL;

}






static void kinematicsSolverData_create(KinematicsSolverData *ksData)
{
  
  initStateVector        (ksData);
  initRuntimeParameters  (ksData);
  initAssemblyDelegate   (&ksData->mAssemblyDelegate);
}


static void runtimeRootVarsFromInputs(
  const size_t *rootVarVecTargetIndices,
  const size_t *rootVarVecInitialGuessIndices,
  const double *targetVar2SpecifiedUnitConversions,
  const double *initialGuessVar2SpecifiedUnitConversions,
  const double *targetVals,
  const double *initialGuessVals,
  double *runtimeRootVariables)
{
  for(size_t tInd = 0; tInd < 9; ++tInd)
  {
    runtimeRootVariables[rootVarVecTargetIndices[tInd]] =
      targetVals[tInd] * targetVar2SpecifiedUnitConversions[tInd];
  }
  for(size_t iInd = 0; iInd < 3; ++iInd)
  {
    runtimeRootVariables[rootVarVecInitialGuessIndices[iInd]] =
      initialGuessVals[iInd] * initialGuessVar2SpecifiedUnitConversions[iInd];
  }
}


static void processRuntimeParameters(const double *runtimeRootVariables,
                                     KinematicsSolverData *ksData)
{
  
  if (ksData->mRuntimeParameterScalars.mN == 0)
    return;

  
  main_computeRuntimeParameters(
    runtimeRootVariables,
    ksData->mRuntimeParameterScalars.mX);

  
  main_computeAsmRuntimeDerivedValues(
    ksData->mRuntimeParameterScalars.mX,
    &ksData->mAsmRuntimeDerivedValuesBundle);
}


static void main_outputsFromVariableViewerBuffer(
  const double *variableViewerBuffer,
  const size_t *variableViewerOutputIndices,
  const double *internal2OutputVarUnitConversions,
  double *outputVector)
{
  for(int i = 0; i < 6; ++i)
  {
    outputVector[i] = variableViewerBuffer[variableViewerOutputIndices[i]]
                        * internal2OutputVarUnitConversions[i];
  }
}


static boolean_T main_targetStatuses(
  const RuntimeDerivedValuesBundle* runtimeDerivedValuesBundle,
  const double* stateVector,
  const size_t* targetStatusIndices,
  boolean_T* targetSuccess)
{
  boolean_T allTgtStatus = true;
  for(size_t tInd = 0; tInd < 9; ++tInd)
  {
    targetSuccess[tInd] = main_getTargetStatus(
      runtimeDerivedValuesBundle,
      stateVector,
      targetStatusIndices[tInd]);
    allTgtStatus = allTgtStatus && targetSuccess[tInd];
  }
  return allTgtStatus;
}


static void main_targetsFromVariableViewerBuffer(
  const double* variableViewerBuffer,
  const size_t* variableViewerTargetIndices,
  const double* internal2TargetVarUnitConversions,
  double* targetVector)
{
  for(int i = 0; i < 9; ++i)
  {
    targetVector[i] = variableViewerBuffer[variableViewerTargetIndices[i]]
                        * internal2TargetVarUnitConversions[i];
  }
}


static void kin_cg_assemble_solve(const KinematicsSolverData *ksData,
                                  boolean_T hasVelocityVariables,
                                  boolean_T doPosSatPhase3,
                                  int32_T maxIters)
{
  const SmMechanismDelegate *delegate = &ksData->mAssemblyDelegate;
  const RuntimeDerivedValuesBundle *runtimeDerivedValuesBundle =
    &ksData->mAsmRuntimeDerivedValuesBundle;
  const size_t numTargets = 118;
  double *assemblyFullStateVector = ksData->mAssemblyFullStateVector.mX;
  PmfMessageId errorId = NULL;

  
  (*delegate->mSetTargets)(runtimeDerivedValuesBundle, ksData->mTargets);

  
  sm_core_computeStateVectorCustom(
    delegate,
    runtimeDerivedValuesBundle,
    NULL,
    numTargets,
    ksData->mTargets,
    false,
    doPosSatPhase3,
    hasVelocityVariables,
    maxIters,
    assemblyFullStateVector);
}





double main_solve_kinematics(
  const double *targetVals,
  const double *initialGuessVals,
  double *outputVals,
  boolean_T *targetSuccesses,
  double *actTargetVals)
{
   
  const size_t rootVarVecTargetIndices[9] = {
      0, 1, 2, 3, 4, 5, 6, 7, 8
    };
  const size_t rootVarVecInitialGuessIndices[3] = {
      9, 10, 11
    };
  const size_t variableViewerTargetIndices[9] = {
      96, 104, 112, 97, 105, 113, 19, 20, 21
    };
  const size_t variableViewerOutputIndices[6] = {
      13, 15, 17, 14, 16, 18
    };
  const double internal2TargetVarUnitConversions[9] = {
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01,
      +5.729577951308232286e+01
    };
  const double internal2OutputVarUnitConversions[6] = {
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00
    };
  const double targetVar2SpecifiedUnitConversions[9] = {
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00
    };
  const double initialGuessVar2SpecifiedUnitConversions[3] = {
      +1.000000000000000000e+00,
      +1.000000000000000000e+00,
      +1.000000000000000000e+00
    };
  const size_t targetStatusIndices[9] = {
      0, 2, 4, 1, 3, 5, 116, 116, 116
    };

  
  int32_T assertSatisfactionFlags[20] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
  double runtimeRootVariables[12] = {
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00
    };
  double variableViewerBuffer[152] = {
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00
    };
  double targetValuesBuffer[152] = {
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00,
      +0.000000000000000000e+00
    };
  boolean_T allTgtStatus = true;
  unsigned int asmStatus = 1;
  double statusFlag = 0;
  static KinematicsSolverData *ksData = NULL;

  
  if(ksData == NULL)
  {
    PmAllocator *alloc = pm_default_allocator();
    ksData =
      (KinematicsSolverData *)alloc->mCallocFcn(
        alloc, sizeof(KinematicsSolverData), 1);
    kinematicsSolverData_create(ksData);
  }

    
  runtimeRootVarsFromInputs(
    rootVarVecTargetIndices,
    rootVarVecInitialGuessIndices,
    targetVar2SpecifiedUnitConversions,
    initialGuessVar2SpecifiedUnitConversions,
    targetVals,
    initialGuessVals,
    runtimeRootVariables);
  processRuntimeParameters(runtimeRootVariables, ksData);

  
  kin_cg_assemble_solve(ksData, true, true, 100);

  
  main_mapStatesToVariableViewerValues(
    ksData->mAssemblyFullStateVector.mX,
    NULL,
    &ksData->mAsmRuntimeDerivedValuesBundle,
    targetValuesBuffer,
    variableViewerBuffer);

  
  main_outputsFromVariableViewerBuffer(
    variableViewerBuffer,
    variableViewerOutputIndices,
    internal2OutputVarUnitConversions,
    outputVals);

  
  main_targetsFromVariableViewerBuffer(
    variableViewerBuffer,
    variableViewerTargetIndices,
    internal2TargetVarUnitConversions,
    actTargetVals);

  
  allTgtStatus = main_targetStatuses(
    &ksData->mAsmRuntimeDerivedValuesBundle,
    ksData->mAssemblyFullStateVector.mX,
    targetStatusIndices,
    targetSuccesses);

  
  asmStatus = sm_core_checkAssembly(
    &ksData->mAssemblyDelegate,
    &ksData->mAsmRuntimeDerivedValuesBundle,
    ksData->mAssemblyFullStateVector.mX,
    NULL, NULL, NULL, NULL);

  
  main_validateRuntimeParameters(
    ksData->mRuntimeParameterScalars.mX,
    assertSatisfactionFlags);
  for(int i = 0; i < 20; ++i)
  {
    if(!assertSatisfactionFlags[i])
    {
      asmStatus = 2;
      break;
    }
  }

  
  switch(asmStatus)
  {
    case 1:
    {
      statusFlag = allTgtStatus ? 1 : -1;
      break;
    }

    case 2:
    {
      size_t i;
      for(i = 0; i < 9; ++i)
      {
        actTargetVals[i] = NAN;
      }
      for(i = 0; i < 6; ++i)
      {
        outputVals[i] = NAN;
      }
      statusFlag = -3;
      break;
    }

    case 3:
    {
      size_t i;
      for(i = 0; i < 9; ++i)
      {
        actTargetVals[i] = NAN;
      }
      for(i = 0; i < 6; ++i)
      {
        outputVals[i] = NAN;
      }
      statusFlag = -5;
      break;
    }

    case 4:
    {
      if(true)
      {
        size_t outIdx;
        for(outIdx = 0; outIdx < 6; ++outIdx)
        {
          outputVals[outIdx] = NAN;
        }
        size_t tgtIdx;
        for(tgtIdx = 0; tgtIdx < 9; ++tgtIdx)
        {
          actTargetVals[tgtIdx] = NAN;
        }
        statusFlag = -4;
      }
      else
      {
        statusFlag = allTgtStatus ? 2 : -2;
      }
      break;
    }

    default:
      break;
  }
  return statusFlag;
}





