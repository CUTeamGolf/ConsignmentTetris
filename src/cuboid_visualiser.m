% Copy past from C++ output
input = [
%0 0 60 100 100 40;
%0 0 10 10 100 90;
%0 0 10 100 10 90;
%20 0 10 80 100 90;
%0 20 10 100 80 90;
%0 0 0 10 100 100;
%20 0 0 30 100 100;
%0 0 0 100 10 100;
%20 0 0 80 50 100;
60 0 0 40 100 100;
0 20 0 50 80 100;
0 20 0 100 30 100;
0 60 0 100 40 100;
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
plotcube([10 10 10], [50 50 0], 0.8, [1, 1, 1]);
plotcube([10 10 10], [10 10 50], 0.8, [1, 1, 1])


for i =1:size(input, 1)
    pause(1)
    plotcube(input(i, 4:6) - rand(1, 3), input(i, 1:3) + rand(1, 3), .3, colors(mod(i, size(colors, 1)) + 1, 1:3));
end


    