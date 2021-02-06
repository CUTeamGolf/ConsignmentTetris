pipeline {
  agent any
  stages {
    stage('Build & test') {
      steps {
        runMATLABTests(codeCoverageCobertura: '/artifacts/cobertura.xml', modelCoverageCobertura: '/artifacts/model-cobertura.xml', testResultsJUnit: '/artifacts/junittestresults.xml', testResultsPDF: '/artifacts/test-results.pdf', testResultsSimulinkTest: '/artifacts/simulinktestresults.mldatx', testResultsTAP: '/artifacts/taptestresults.tap')
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