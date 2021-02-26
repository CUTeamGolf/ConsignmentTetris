% Copy/paste from C++ output
input = [
    0 0 0 12 12 12;
    12 0 0 50 50 50;
    62 0 0 30 30 30;
    62 30 0 30 30 30;
    0 50 0 40 40 40;
    40 50 0 20 20 40;
    60 60 0 40 40 60;
    0 0 50 40 60 30;
    40 70 0 10 10 10;
    40 0 50 50 50 5;
];

colors = [
    1 0 0
    0 1 0
    0 0 1
    0.5 0.5 0
    0 0.5 0.5
    0.5 0 0.5
    0.2 0.2 0
    0 0.2 0.2
    0.2 0.2 0
];

figure
hold on

% Plot the packing box boundaries
h1 = plot3(0, 0, 0);
% set(h1, 'Visible', 'off')
plot3(100, 100, 100);

% our cubes
%plotcube([10 10 10], [50 50 0], 0.8, [1, 1, 1]);
%plotcube([10 10 10], [10 10 50], 0.8, [1, 1, 1])


for i =1:size(input, 1)
    pause(2)
    plotcube(input(i, 4:6) - rand(1, 3) * 0, input(i, 1:3) + rand(1, 3) * 0, .3, colors(mod(i, size(colors, 1)) + 1, 1:3));
end


    