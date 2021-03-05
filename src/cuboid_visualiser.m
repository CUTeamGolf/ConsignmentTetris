% Copy/paste from C++ output
input = [
10 5 0 10 20 10;
20 0 0 30 50 40;
63 13 0 5 5 10;
68 3 0 25 25 20;
53 28 0 25 25 20;
3 53 0 25 25 20;
28 53 0 25 25 20;
50 5 20 50 20 30;
78 28 0 10 50 60;
10 60 20 10 10 10;
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


    