% Copy/paste from C++ output
input = [
0 70 12 100 30 88;
0 0 12 20 100 88;
0 0 12 100 20 88;
60 0 12 40 100 88;
0 50 12 30 50 88;
0 50 12 100 10 88;
40 50 12 60 50 88;
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

% our 4 items cubes
plotcube([40 30 40], [20 20 0], 0.8, [1, 1, 1]);
plotcube([10 10 10], [25 30 40], 0.8, [1, 1, 1])
plotcube([15 10 12], [60 25 0], 0.8, [1, 1, 1])
plotcube([10 10 30], [30 60 0], 0.8, [1, 1, 1])

% the resulting position
%plotcube([30 30 30], [60 35 0], 1.0, [1, 1, 1]);
% and the MEC it's in
%plotcube([40 65 100], [60 35 0], 0.5,  [1, 1, 0]);

[mx, my] = meshgrid(0:1:100);

for i=-20:450
    if i == 1
        z = 0 .* mx + 0.* my + 4;
        s = surf(mx,my,z);
        s.FaceAlpha = 0.5;
    end
    % plane
    if and(i > 0, i < 88)
        s.ZData = 0 .* mx + 0.* my + (100 - i);
    end
    
    % first MEC
    for j=1:size(input,1)
        if i == (100+10*j)
            plotMEC(input(j,1:3), input(j,4:6), i, mx, my);
        end
    end
    
    if i == 180
        clf('reset')
        hold on
        z = 0 .* mx + 0.* my + 12 - (i - 179);
        s = surf(mx,my,z);
        s.FaceAlpha = 0.5;
        
        plot3(0, 0, 0);
        plot3(100, 100, 100);
        plotcube([40 30 40], [20 20 0], 0.8, [1, 1, 1]);
        plotcube([10 10 10], [25 30 40], 0.8, [1, 1, 1])
        plotcube([15 10 12], [60 25 0], 0.8, [1, 1, 1])
        plotcube([10 10 30], [30 60 0], 0.8, [1, 1, 1])
    end
    if and(i > 179, i < 179 + 13)
        s.ZData = 0 .* mx + 0.* my + 12 - (i - 179);
    end
    if i == 179 + 13
        clf('reset')
        hold on
       
        plot3(0, 0, 0);
        plot3(100, 100, 100);
        %plotcube([40 30 40], [20 20 0], 0.8, [1, 1, 1]);
        %plotcube([10 10 10], [25 30 40], 0.8, [1, 1, 1])
        %plotcube([15 10 12], [60 25 0], 0.8, [1, 1, 1])
        %plotcube([10 10 30], [30 60 0], 0.8, [1, 1, 1])
    end
    
    if i == 300
        % and the MEC it's in
        plotcube([40 65 100], [60 35 0], 0.5,  [1, 1, 0]);
    end
    if i == 320 
        %plotcube([30 30 30], [60 35 0], 1.0, [0, 1, 1]);
    end
    if i == 340
        % the resulting position
        %clf('reset')
        %hold on
        %plot3(0, 0, 0);
        %plot3(100, 100, 100);
        %plotcube([40 30 40], [20 20 0], 0.8, [1, 1, 1]);
        %plotcube([10 10 10], [25 30 40], 0.8, [1, 1, 1])
        %plotcube([15 10 12], [60 25 0], 0.8, [1, 1, 1])
        %plotcube([10 10 30], [30 60 0], 0.8, [1, 1, 1])
        %plotcube([30 30 30], [60 35 0], 1.0, [0, 1, 1]);
    end
    
    
    % rotate camera
    view(i, 30);
    pause(0.4);
end

%for i =1:size(input, 1)
%    pause(2)
%    plotcube(input(i, 4:6) - rand(1, 3) * 0, input(i, 1:3) + rand(1, 3) * 0, .3, colors(mod(i, size(colors, 1)) + 1, 1:3));
%end

function plotMEC(pos, dim, az, mx, my)
    % this is what we originally had
    clf('reset')
    hold on
    plot3(0, 0, 0);
    plot3(100, 100, 100);
    %s = surf(mx, my, 0 .* mx + 0.*my + 12);
    %s.FaceAlpha = 0.5;
    %plotcube([40 30 40], [20 20 0], 0.8, [1, 1, 1]);
    %plotcube([10 10 10], [25 30 40], 0.8, [1, 1, 1])
    %plotcube([15 10 12], [60 25 0], 0.8, [1, 1, 1])
    %plotcube([10 10 30], [30 60 0], 0.8, [1, 1, 1])
    
    
    % plot the new cube
    plotcube(dim, pos, 0.3, [1 1 0]);
    view(az, 30);
end


