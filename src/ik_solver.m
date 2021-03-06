function [actuatorPos, actuatorVel, newGuessVals, statusFlag] = ik_solver(eePos, eeVel, guessVals)
% Uses a persistent KinematicsSolver object to compute the inverse
% kinematics (position and velocity) of the delta robot.  Specifically,
% given the position and velocity of the end effector, computes the
% corresponding actuator positions and velocities.  Can optionally
% include an initial guess for the actuator positions.

% Copyright 2020 The MathWorks, Inc.

persistent ks guessIds guessInds actuatorPosInds actuatorVelInds

if isempty(ks)
    % Note that this code is only run first time this function is called or
    % if this function is cleared from memory.
    
    % Create KinematicsSolver object for inverse kinematics.  
    mdl = 'main';
    ks = simscape.multibody.KinematicsSolver(mdl);
    
    % Add frame variables (end effector position, orientation, and linear
    % velocity with respect to camera)
    base = mdl + "/Delta Robot/Camera Frame";
    fol = mdl + "/Delta Robot/End Effector Frame";
    addFrameVariables(ks, 'endEffector','Translation',base, fol);
    addFrameVariables(ks, 'endEffector','Rotation',base, fol);
    addFrameVariables(ks, 'endEffector','LinearVelocity',base, fol);
    
    % Define some useful ID arrays
    jointPosIds = ks.jointPositionVariables.ID;
    jointVelIds = ks.jointVelocityVariables.ID;
    jointPosPaths = ks.jointPositionVariables.BlockPath;
    jointVelPaths = ks.jointVelocityVariables.BlockPath;
    actuatorPosIds = jointPosIds(jointPosPaths.contains("Actuator"));
    actuatorVelIds = jointVelIds(jointVelPaths.contains("Actuator"));
    eePosIds = ks.frameVariables.ID(ks.frameVariables.ID.contains("Translation"));
    eeOrientIds = ks.frameVariables.ID(ks.frameVariables.ID.contains("Rotation"));
    eeVelIds = ks.frameVariables.ID(ks.frameVariables.ID.contains("LinearVelocity"));
    
    % Add target variables (end effector position, orientation and linear
    % velocity).
    targetIds = [eePosIds; eeVelIds; eeOrientIds];
    ks.addTargetVariables(targetIds);
    
    % Add initial guess variables (actuator positions)
    guessIds = actuatorPosIds;
    ks.addInitialGuessVariables(guessIds);
    
    % Add output variables (actuator positions and velocities)
    outputIds = [actuatorPosIds; actuatorVelIds];
    ks.addOutputVariables(outputIds);
    
    % Indices to get things out of output vector
    guessInds = ks.outputVariables.ID.contains(ks.initialGuessVariables.ID);
    actuatorPosInds = ks.outputVariables.ID.contains(actuatorPosIds);
    actuatorVelInds = ks.outputVariables.ID.contains(actuatorVelIds);
end

if nargin == 2
    guessVals = zeros(numel(guessIds), 1);
end
targetVals = [eePos; eeVel; [0;0;0]]; % end effector orientation angles always [0;0;0]

%generateCode(ks);
%codegen -config:mex main_solveKinematics

[outputVals, statusFlag] = solve(ks, targetVals, guessVals);

%[outputVals, statusFlag] = main_ik_solveKinematics_mex(targetVals, guessVals);
newGuessVals = outputVals(guessInds);
actuatorPos = outputVals(actuatorPosInds);
actuatorVel = outputVals(actuatorVelInds);