node {
    def codeDir = 'study_code'
    def lastDeployCommitId
    def nowDeployCommitId
    def curUserName
    def curWorkDir
    def userCounter = 0
    def dirCounter = 0
    stage('Git Clone') {
        git(url:'https://github.com/dfx-open-study/network_security_study.git')
    }

    stage('Check File change') {
        def existsFile = fileExists('lastDeployCommitId')
        if(existsFile) {
            println('Exist Last Commit Id!!')
            lastDeployCommitId = (readFile(file: 'lastDeployCommitId', encoding: 'UTF-8')).trim()

            nowDeployCommitId = powershell(script:'git rev-parse HEAD', returnStdout: true).trim()

            println('lastDeployCommitId='+lastDeployCommitId)
            println('nowDeployCommitId='+nowDeployCommitId)
            
            bat(script: """git diff --name-only --output=modifiedList --diff-filter=AM ${lastDeployCommitId}..${nowDeployCommitId}""")
            
            bat(script: """git diff --name-only --output=deletedList --diff-filter=D ${lastDeployCommitId}..${nowDeployCommitId}""")

            isModified = (readFile(file: 'modifiedList', encoding: 'UTF-8')).trim()

        } else {
            println('First build branch!')

            isModified = powershell(script:'git ls-files', returnStdout: true).trim()
        }
        
        ModifiedLine = isModified.split('\n')
        
        println(ModifiedLine.length)
        println(ModifiedLine[0])
        
        for(int i = 0; i < ModifiedLine.length; i++) {
            ModifiedSplitted = ModifiedLine[i].split('/')
            if(ModifiedSplitted.length > 2) {
                dirname = ModifiedSplitted[0]
                if(dirname == codeDir) {
                    if(curUserName != ModifiedSplitted[1]) {
                        if(userCounter != 0) {
                            println('other user directory use!')                            //after done, need to send push message
                            currentBuild.result = 'FAILURE'
                            return 1
                        }
                        userCounter++
                    }
                    curUserName = ModifiedSplitted[1]
                    
                    if(curWorkDir != ModifiedSplitted[2]) {
                        if(dirCounter != 0) {
                            println('mutiple work directory use!')                            //after done, need to send push message
                            currentBuild.result = 'FAILURE'
                            return 1
                        }
                        dirCounter++
                    }
                    curWorkDir = ModifiedSplitted[2]
                    
                }
                else {
                    println('not a code directory!')
                }
            }
        }
    }
    
    stage('Build') {
        fileName = codeDir + '/' + curUserName + '/' + curWorkDir + '/' + curWorkDir + '.sln'
        existsFile = fileExists(fileName)
        
        if(existsFile) {
            println('have solution file')

            buildState = powershell(script:"""MSBuild.exe ${fileName}""", returnStatus: true).trim()

            if(buildState == 0) {
                println('Build Success!!')
            }
            else {
                println('Build Fail!!')
            }
            
        } else {
            println('not have solution file')
        }
        writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
    }
    
}