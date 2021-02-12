%% Test Class Definition
classdef ExampleTest < matlab.unittest.TestCase
    properties
        Value
    end
 
    %% Setup Block
    methods(TestMethodSetup)
        function createFigure(testCase)
            testCase.Value = 1;
        end
    end

    %% Teardown Block
    methods(TestMethodTeardown)
        function closeFigure(testCase)
            testCase.Value = 0;
        end
    end
    
    %% Test Method Block
    methods (Test)
        
        %% Test Function
        function test1(testCase)      
            %% Arrange
            delta = 10;

            %% Act
            new_value = testCase.Value + delta;
            
            %% Assert
            testCase.verifyEqual(new_value, 11);
        end
    end
end