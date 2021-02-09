pipeline {
	agent any
	environment {
		PATH = "/usr/local/MATLAB/R2020b/bin:${PATH}"
	}
	stages {
		stage('Version') {
			steps {
				sh 'whoami'
				runMATLABCommand "version"
			}
		} 
  
		stage('Build & test') {
			steps {
				runMATLABTests(selectByFolder: ["tests"], sourceFolder: ["src"], codeCoverageCobertura: 'artifacts/cobertura.xml', modelCoverageCobertura: 'artifacts/model-cobertura.xml', testResultsJUnit: 'artifacts/junittestresults.xml', testResultsPDF: 'artifacts/test-results.pdf', testResultsSimulinkTest: 'artifacts/simulinktestresults.mldatx', testResultsTAP: 'artifacts/taptestresults.tap')
			}
		}
	}
}