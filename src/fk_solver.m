function [eePos, eeVel, newGuessVals, statusFlag] = fk_solver(actuatorPos, actuatorVel, guessVals)
% Uses a persistent KinematicsSolver object to compute the forward
% kinematics (position and velocity) of the delta robot.  Specifically,
% given the three actuator positions and velocities, computes the
% corresponding end effector position and linear velocity.  Can optionally
% include an initial guess for the end effector position.

% Copyright 2020 The MathWorks, Inc.

persistent ks guessIds guessInds eePosInds eeVelInds

if isempty(ks)
    % Note that this code is only run first time this function is called or
    % if this function is cleared from memory.
    
    % Create KinematicsSolver object for forward kinematics. 
    mdl = 'sm_pick_and_place_robot';
    ks = simscape.multibody.KinematicsSolver(mdl);
    
    % Add frame variables (end effector position position, orientation, and
    % linear velocity with respect to camera)
    base = mdl + "/Delta Robot/Camera Frame";
    fol = mdl + "/Delta Robot/End Effector Frame";
    addFrameVariables(ks, 'endEffector','Translation', base, fol);
    addFrameVariables(ks, 'endEffector','Rotation', base, fol);
    addFrameVariables(ks, 'endEffector','LinearVelocity', base, fol);
    
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
    
    % Add target variables (actuator positions and velocities and end
    % effector orientation)
    targetIds = [actuatorPosIds; actuatorVelIds; eeOrientIds];
    ks.addTargetVariables(targetIds);
    
    % Add initial guess variables (end effector position)
    guessIds = eePosIds;
    ks.addInitialGuessVariables(guessIds);
    
    % Add output variables (end effector position and velocity)
    outputIds = [eePosIds; eeVelIds];
    ks.addOutputVariables(outputIds);
    
    % Indices to get things out of output vector
    guessInds = ks.outputVariables.ID.contains(ks.initialGuessVariables.ID);
    eePosInds = ks.outputVariables.ID.contains(eePosIds);
    eeVelInds = ks.outputVariables.ID.contains(eeVelIds);
end

if nargin == 2
    guessVals = zeros(numel(guessIds), 1);
end
targetVals = [actuatorPos; actuatorVel; [0;0;0]]; % end effector orientation angles always [0;0;0]
[outputVals, statusFlag] = solve(ks, targetVals, guessVals);
newGuessVals = outputVals(guessInds);
eePos = outputVals(eePosInds);
eeVel = outputVals(eeVelInds);
