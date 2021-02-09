pipeline {
	agent any
	environment {
		PATH = "/usr/local/MATLAB/R2020b/bin:${PATH}"
	}
	stages {
		stage('Run MATLAB Command') {
			steps {
				sh 'whoami'
				runMATLABCommand "disp('Hello World!')"
			}
		} 
	}
}