% change this to wherever you installed the library repo
% We should probably move the library folder to the ConsigmentTetris repo
%   such that this path can be relative and work without modifications.
base = "/home/ana/MATLAB/projects/ConsignmentTetrisSimulink/Simscape-Multibody-Contact-Forces-Library-20.2.5.0/";

% TODO: test if these UNIX-style paths work on Windows
items = [
    "Examples",
    "Examples/2D/Ball_Bearing",
    "Examples/2D/Ball_Bearing/Images",
    "Examples/2D/Ball_Bearing/Libraries",
    "Examples/2D/Ball_Bearing/Scripts_Data",
    "Examples/2D/Cam_Follower",
    "Examples/2D/Cam_Follower/Help",
    "Examples/2D/Cam_Follower/UI",
    "Examples/2D/Cam_Follower_Constraint",
    "Examples/2D/Conveyor_Belts",
    "Examples/2D/Geneva_Drive",
    "Examples/2D/Geneva_Drive/CAD",
    "Examples/2D/Geneva_Drive/CAD/Export",
    "Examples/2D/Geneva_Drive/CAD/Geometry",
    "Examples/2D/Geneva_Drive/Help",
    "Examples/2D/Geneva_Drive/Images",
    "Examples/2D/Mini_Golf",
    "Examples/2D/Mini_Golf/Images",
    "Examples/2D/Mini_Golf/Libraries",
    "Examples/2D/Mini_Golf/Scripts_Data",
    "Examples/2D/Mini_Golf/Slides_Recordings",
    "Examples/2D/Simple/Collision",
    "Examples/2D/Simple/Friction",
    "Examples/2D/Spinning_Boxes",
    "Examples/3D/Caster_4_Whl",
    "Examples/3D/Gripper_2Belts",
    "Examples/3D/MATLAB_Build",
    "Examples/3D/MATLAB_Build/Spheres_in_Sphere",
    "Examples/3D/Robot_2_Whl",
    "Examples/3D/Robot_6Legs_4Bar",
    "Examples/3D/Robot_6Legs_4Bar/Images",
    "Examples/3D/Robot_6Legs_4Bar/Libraries",
    "Examples/3D/Robot_6Legs_4Bar/Scripts_Data",
    "Examples/3D/Simple/Collision",
    "Examples/3D/Simple/Friction",
    "Examples/3D/Tread_Drive",
    "Scripts_Data",
    "Scripts_Data/Doc",
    "CFL_Core",
    "CFL_Core/Libraries",
    "CFL_Core/Libraries/Extrusions",
    "CFL_Core/Libraries/Help",
    "CFL_Core/Libraries/Help/html",
    "CFL_Core/Libraries/Images",
    "CFL_Core/Scripts_Data",
    "CFL_Core/Scripts_Data/Doc",
    "CFL_Core/Test_Models"
];

% add all the directories to the matlab PATH variable
for i = 1:length(items)
    addpath(strcat(base,items(i)));
end
