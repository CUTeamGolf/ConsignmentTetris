function [outputVals, status, targetSuccess, actTargetVals] = main_solveKinematics(expTargetVals, initGuessVals)
%MAIN_SOLVEKINEMATICS Kinematics code-generation build configuration file for model main
% This function is not meant to be invoked from MATLAB.
% Call the function CODEGEN with this file as input to build the generated code.
% ex: codegen -config:mex main_solveKinematics
% Only C code generation for MEX, DLL and LIB targets on Windows, Linux, and Mac OS platforms is supported.


%Setup targets input variable type and size : [1 x 9] or [9 x 1] vector
assert(isa(expTargetVals,'double'));
assert(all(size(expTargetVals) <= [9 9]));
assert(numel(expTargetVals) == 9);
assert(isvector(expTargetVals));

%Setup initial guesses input variable type and size : [1 x 3] or [3 x 1] vector
assert(isa(initGuessVals,'double'));
assert(all(size(initGuessVals) <= [3 3]));
assert(numel(initGuessVals) == 3);
assert(isvector(initGuessVals));

%Setup output variable types and sizes
outputVals = zeros(6,1,'double');
status = 0.0; %#ok<NASGU>
targetSuccess = zeros(9,1,'logical');
actTargetVals = zeros(9,1,'double');

%Adding Custom Source Files
coder.updateBuildInfo('addSourceFiles','main_asm_delegate.c');
coder.updateBuildInfo('addSourceFiles','main_asserts.c');
coder.updateBuildInfo('addSourceFiles','main_setParameters.c');
coder.updateBuildInfo('addSourceFiles','main_kinematics.c');
coder.updateBuildInfo('addSourceFiles','main_variableViewerValues.c');
coder.updateBuildInfo('addSourceFiles','pm_printf.c');

%Adding Custom Source Paths
coder.updateBuildInfo('addSourcePaths','N:\GitHub\ConsignmentTetris\main_codegen_kinematics');

%Adding Custom Include Paths
coder.updateBuildInfo('addIncludePaths','N:\GitHub\ConsignmentTetris\main_codegen_kinematics');

%Adding Custom Code
coder.cinclude('main_kinematics.h');

[outputVals, status, targetSuccess, actTargetVals] = ...
  simscape.multibody.internal.KinematicsSolverCodeGenAPI.solveKinematics( ...
    'main_solve_kinematics', ...
     expTargetVals, initGuessVals, outputVals, targetSuccess, actTargetVals);
