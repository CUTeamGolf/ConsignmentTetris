pipeline {
  agent {
	docker {
      image 'matlab:r2020b'
      args  '-i --mac-address 02:42:ac:11:ff:ff --entrypoint="chmod +777 -R /var/lib/jenkins/workspace/ConsignmentTetris_jenkins@tmp/ && " --user matlab:root' // Fix MAC address so that only one instance can run at once for licensing reasons, and disable entrypoint
    }
  }
  
  stages {
	stage('Version') {
	  steps {
	    sh 'matlab -batch "version"'
	  }
	}
  
    stage('Build & test') {
      steps {
        runMATLABTests(selectByFolder: ["tests"], sourceFolder: ["src"], codeCoverageCobertura: '/artifacts/cobertura.xml', modelCoverageCobertura: '/artifacts/model-cobertura.xml', testResultsJUnit: '/artifacts/junittestresults.xml', testResultsPDF: '/artifacts/test-results.pdf', testResultsSimulinkTest: '/artifacts/simulinktestresults.mldatx', testResultsTAP: '/artifacts/taptestresults.tap')
      }
    }

    stage('Publish') {
      steps {
        cobertura(coberturaReportFile: '/artifacts/cobertura.xml', sourceEncoding: 'ASCII')
        archiveArtifacts '/artifacts/**'
      }
    }
  }
}