classdef mesh
    %MESH A mesh made of vertices and edges
    
    properties (SetAccess=private)
        Vertices,
        Faces,
        CollisionMesh,
        Triangulation
    end
    
    methods
        function obj = mesh(vertices,faces)
            %MESH Construct an instance of a mesh from a set of
            %   vertices and triangle indices.
            obj.Vertices = vertices;
            obj.Faces = faces;
            obj.CollisionMesh = collisionMesh(vertices);
            obj.Triangulation = triangulation(faces,vertices);
        end
        
        function intersects = intersectsWith(obj, other)
            %DOESCOLLIDEWITH Checks if the other mesh collides
            %with this one.
            
            % Use convex collision for now but maybe go to more complex
            % collision some time in the future to allow for cooler shapes
            intersects = checkCollision(obj.CollisionMesh, other.CollisionMesh);
        end
        
        function plot(obj)
            trimesh(obj.Triangulation)
        end
    end
    
    methods(Static)
        function obj = fromObj(path)
            % We only care about vertices and triangles so skip normals
            v = [];
            f = [];

            file = fopen(path);
            while 1
                line = fgetl(file);
                if not(ischar(line))
                    break
                end
                type = sscanf(line,'%s',1);
                values = sscanf(line(2:end),'%f');
                switch type
                    case 'v'   % vertex
                        v = [v; values'];
                    case 'f'   % face
                        f = [f; values'];
                end
            end
            fclose(file);
            
            % Create mesh
            obj = mesh(v, f);
        end
    end
end

