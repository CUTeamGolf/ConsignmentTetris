classdef tetromino
    %TETROMINO An object to be packed in the box
    %   Named after a single tetris 'piece'.
    %   Contains mesh info as well as helper methods to 
    %   determine collisions and packings
    
    properties (GetAccess=private)
        Mesh
    end
    
    methods
        function obj = tetromino(mesh)
            %TETROMINO Construct an instance of this class
            %   Takes a mesh (or predicted mesh from sensors)
            obj.Mesh = mesh;
        end
        
        function collides = intersectsWith(obj, other)
            %DOESCOLLIDEWITH Checks if the other tetromino collides
            %with this one.
            collides = obj.Mesh.checkIntersect(other.Mesh);
        end
    end
end

