%% Test Class Definition
classdef OptimiserTests < matlab.unittest.TestCase
    properties
        Value
    end
 
    %% Setup Block
    methods(TestMethodSetup)
        function include(testCase)
            coder.cinclude('process_optimiser.h');
        end
    end
    
    %% Test Method Block
    methods (Test)
        
        %% Test Function
        function test1(testCase)      
            %% Arrange
            box_points = [];
            item_points = [];
            item_indices = [];
            result = zeros(3);

            %% Act
            coder.ceval("process_optimiser_main", box_points, item_points, length(item_points), item_indices, length(item_indices), coder.wref(result))
            
            %% Assert
            testCase.verifyEqual(result, [1; 2; 3]);
        end
    end
end