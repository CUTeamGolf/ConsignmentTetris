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
		
		stage('Build C++') {
			steps {
                cmakeBuild buildDir: 'build', buildType: 'Debug', cleanBuild: true, installation: 'InSearchPath', steps: [[args: '--target install', withCmake: true]]
            }
		}
		
		stage('Test C++') {
			steps {
                ctest 'InSearchPath'
            }
		}
  
		stage('Test Matlab') {
			steps {
				runMATLABTests(selectByFolder: ["tests"], sourceFolder: ["src"], codeCoverageCobertura: 'artifacts/cobertura.xml', modelCoverageCobertura: 'artifacts/model-cobertura.xml', testResultsJUnit: 'artifacts/junittestresults.xml', testResultsPDF: 'artifacts/test-results.pdf', testResultsSimulinkTest: 'artifacts/simulinktestresults.mldatx', testResultsTAP: 'artifacts/taptestresults.tap')
			}
		}
	}
  
	post {
		always {
			archiveArtifacts artifacts: 'artifacts/*', fingerprint: true
			cobertura coberturaReportFile: 'artifacts/cobertura.xml'
			junit 'artifacts/junittestresults.xml'
			junit 'tests/report.xml'
		}
	}
}