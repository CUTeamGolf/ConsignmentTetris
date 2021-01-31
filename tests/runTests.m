testFiles = [
    "exampleTests"
    "tetrominoTests"
];

for i = 1:length(testFiles)
    result = runtests(testFiles(i));
end
