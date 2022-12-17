node {
    def codeDir = 'study_code'
    def teamsUrl = 'https://o365hanbat.webhook.office.com/webhookb2/5371f5fd-f356-4ec5-8ebb-20dca50659d1@3109d4ab-a27d-423a-9e49-89bd4003003a/IncomingWebhook/7a88e98ec41047a9bcd9a04c86537f37/c0dae810-7805-4765-b4fb-25219cdadd79'
    def extentionUrl = 'https://schema.org/extensions'
    def lastDeployCommitId
    def nowDeployCommitId
    def curUserName
    def curWorkDir
    def userCounter = 0
    def dirCounter = 0
    JsonBuilder builder = new JsonBuilder()

    builder {
        '@type'('MessageCard')
        '@context'(extentionUrl)
        themeColor('0072C6')
        title
        sections(
            [
                {
                    facts(
                        [
                            {
                                name
                                value
                            }
                            {
                                name
                                value
                            }
                        ]
                    )
                }
            ]
        )
    }

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
            nowDeployCommitId = powershell(script:'git rev-parse HEAD', returnStdout: true).trim()

            println('nowDeployCommitId='+nowDeployCommitId)
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
                            builder.title = curUserName + ' Build FAIL' + nowDeployCommitId
                            builder.sections[0].facts[0].name = 'Result'
                            builder.sections[0].facts[0].value = 'FAIL'
                            builder.sections[0].facts[1].name = 'Reason'
                            builder.sections[0].facts[1].value = 'other user directory use!'
                            writeFile(file: 'jsonResult', text:builder.toPrettyString(), encoding: 'UTF-8')
                            bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
                            println('other user directory use!')
                            currentBuild.result = 'FAILURE'
                            return 1
                        }
                        userCounter++
                    }
                    curUserName = ModifiedSplitted[1]
                    
                    if(curWorkDir != ModifiedSplitted[2]) {
                        if(dirCounter != 0) {
                            notiTitle = curUserName + ' Build Result' + nowDeployCommitId
                            notiText = 'Result : FAIL\n' + 'reason : mutiple work directory use!\n'
                            bat(script: """curl -d "{\"@context\":\"${extentionUrl}\",\"@type\":\"MessageCard\",\"themeColor\":\"0072C6\",\"title\":\"${notiTitle}\",\"text\":\"${notiText}\"}" -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
                            println('mutiple work directory use!')
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

            buildState = powershell(script:"""MSBuild.exe ${fileName}""", returnStatus: true)

            if(buildState == 0) {
                builder.title = curUserName + ' Build SUCCESS' + nowDeployCommitId
                builder.sections[0].facts[0].name = 'Result'
                builder.sections[0].facts[0].value = 'SUCCESS'
                builder.sections[0].facts[1].name = 'Reason'
                builder.sections[0].facts[1].value = 'good'
                writeFile(file: 'jsonResult', text:builder.toPrettyString(), encoding: 'UTF-8')
                bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
                //notiTitle = curUserName + ' Build Result' + nowDeployCommitId
                //notiText = 'Result : SUCCESS\n'
                //bat(script: """curl -d "{\"@context\":\"${extentionUrl}\",\"@type\":\"MessageCard\",\"themeColor\":\"0072C6\",\"title\":\"${notiTitle}\",\"text\":\"${notiText}\"}" -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
                println('Build Success!!')
            }
            else {
                notiTitle = curUserName + ' Build Result' + nowDeployCommitId
                notiText = 'Result : FAIL\n' + 'reason : build fail\n'
                bat(script: """curl -d "{\"@context\":\"${extentionUrl}\",\"@type\":\"MessageCard\",\"themeColor\":\"0072C6\",\"title\":\"${notiTitle}\",\"text\":\"${notiText}\"}" -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
                println('Build Fail!!')
            }
            
        } else {
            notiTitle = curUserName + ' Build Result' + nowDeployCommitId
            notiText = 'Result : PENDING\n' + 'reason : not include source change\n'
            bat(script: """curl -d "{\"@context\":\"${extentionUrl}\",\"@type\":\"MessageCard\",\"themeColor\":\"0072C6\",\"title\":\"${notiTitle}\",\"text\":\"${notiText}\"}" -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")
            println('not have solution file')
        }
        writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
    }
    
}