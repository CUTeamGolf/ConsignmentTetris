%% Setup
bunny = mesh.fromObj("bunny.obj");
suzanne = mesh.fromObj("suzanne.obj");
teapot = mesh.fromObj("teapot.obj");

%% Test Constructor
bunny_tetromino = tetromino(bunny);

%% Test Collides With Self
assert(bunny_tetromino.intersectsWith(bunny_tetromino))