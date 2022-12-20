import groovy.json.JsonOutput

node {
    def codeDir = 'study_code'
    def teamsUrl = 'https://o365hanbat.webhook.office.com/webhookb2/5371f5fd-f356-4ec5-8ebb-20dca50659d1@3109d4ab-a27d-423a-9e49-89bd4003003a/IncomingWebhook/e4717b77bde143099c89f90c0d401d6e/c0dae810-7805-4765-b4fb-25219cdadd79'
    def extentionUrl = 'https://schema.org/extensions'
    def lastDeployCommitId
    def nowDeployCommitId
    def curUserName
    def curWorkDir
    def userCounter = 0
    def dirCounter = 0

    stage('Git Clone') {
        git branch:env.BRANCH_NAME, url:'https://github.com/dfx-open-study/network_security_study.git'
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
            lastDeployCommitId = powershell(script:'git rev-parse HEAD^^', returnStdout: true).trim()

            println('lastDeployCommitId='+lastDeployCommitId)
            println('nowDeployCommitId='+nowDeployCommitId)

            bat(script: """git diff --name-only --output=modifiedList --diff-filter=AM ${lastDeployCommitId}..${nowDeployCommitId}""")

            bat(script: """git diff --name-only --output=deletedList --diff-filter=D ${lastDeployCommitId}..${nowDeployCommitId}""")
            
            isModified = (readFile(file: 'modifiedList', encoding: 'UTF-8')).trim()
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

                            def jsonData = [
                                '@type' : "MessageCard",
                                '@context' : extentionUrl,
                                summary : curUserName + " Build FAIL",
                                themeColor : "0072C6",
                                title : curUserName + " Build FAIL",
                                sections:[
                                    [
                                        facts:[
                                            [
                                                name: "Result",
                                                value: "FAIL"
                                            ],
                                            [
                                                name: "Reason",
                                                value: "other user directory use!"
                                            ]
                                        ],
                                        text : "Commit ID : " + nowDeployCommitId
                                    ]
                                ]
                            ]

                            def json_str = JsonOutput.toJson(jsonData)
                            def json_beauty = JsonOutput.prettyPrint(json_str)
                            writeFile(file: 'jsonResult', text:json_beauty, encoding: 'UTF-8')
                            bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")

                            println('other user directory use!')
                            writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
                            error("Build failed because of other user directory use")
                        }
                        userCounter++
                    }
                    curUserName = ModifiedSplitted[1]
                    
                    if(curWorkDir != ModifiedSplitted[2]) {
                        if(dirCounter != 0) {

                            def jsonData = [
                                '@type' : "MessageCard",
                                '@context' : extentionUrl,
                                summary : curUserName + " Build FAIL",
                                themeColor : "0072C6",
                                title : curUserName + " Build FAIL",
                                sections:[
                                    [
                                        facts:[
                                            [
                                                name: "Result",
                                                value: "FAIL"
                                            ],
                                            [
                                                name: "Reason",
                                                value: "mutiple work directory use!"
                                            ]
                                        ],
                                        text : "Commit ID : " + nowDeployCommitId
                                    ]
                                ]
                            ]

                            def json_str = JsonOutput.toJson(jsonData)
                            def json_beauty = JsonOutput.prettyPrint(json_str)
                            writeFile(file: 'jsonResult', text:json_beauty, encoding: 'UTF-8')
                            bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")

                            println('mutiple work directory use!')
                            writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
                            error("Build failed because of mutiple work directory use")
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

                def jsonData = [
                    '@type' : "MessageCard",
                    '@context' : extentionUrl,
                    summary : curUserName + " Build SUCCESS",
                    themeColor : "0072C6",
                    title : curUserName + " Build SUCCESS",
                    sections:[
                        [
                            facts:[
                                [
                                    name: "Result",
                                    value: "SUCCESS"
                                ],
                                [
                                    name: "Reason",
                                    value: "you are the best!"
                                ]
                            ],
                            text : "Commit ID : " + nowDeployCommitId
                        ]
                    ]
                ]

                def json_str = JsonOutput.toJson(jsonData)
                def json_beauty = JsonOutput.prettyPrint(json_str)
                writeFile(file: 'jsonResult', text: json_beauty, encoding: 'UTF-8')
                bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")

                println('Build Success!!')
            }
            else {
                def jsonData = [
                    '@type' : "MessageCard",
                    '@context' : extentionUrl,
                    summary : curUserName + " Build FAIL",
                    themeColor : "0072C6",
                    title : curUserName + " Build FAIL",
                    sections:[
                        [
                            facts:[
                                [
                                    name: "Result",
                                    value: "FAIL"
                                ],
                                [
                                    name: "Reason",
                                    value: "compile or linking error!"
                                ]
                            ],
                            text : "Commit ID : " + nowDeployCommitId
                        ]
                    ]
                ]

                def json_str = JsonOutput.toJson(jsonData)
                def json_beauty = JsonOutput.prettyPrint(json_str)
                writeFile(file: 'jsonResult', text: json_beauty, encoding: 'UTF-8')
                bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")

                println('Build Fail!!')
                writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
                error("Build failed because of compile or linking error")
            }
            
        } else {
            def jsonData = [
                '@type' : "MessageCard",
                '@context' : extentionUrl,
                summary : curUserName + " Build PENDING",
                themeColor : "0072C6",
                title : curUserName + " Build PENDING",
                sections:[
                    [
                        facts:[
                            [
                                name: "Result",
                                value: "PENDING"
                            ],
                            [
                                name: "Reason",
                                value: "this commit not include source file change"
                            ]
                        ],
                        text : "Commit ID : " + nowDeployCommitId
                    ]
                ]
            ]

            def json_str = JsonOutput.toJson(jsonData)
            def json_beauty = JsonOutput.prettyPrint(json_str)
            writeFile(file: 'jsonResult', text: json_beauty, encoding: 'UTF-8')
            bat(script: """curl -d @jsonResult -H "Content-Type: Application/JSON" -X POST ${teamsUrl}""")

            println('not have solution file')
        }
        writeFile(file: 'lastDeployCommitId', text:nowDeployCommitId, encoding: 'UTF-8')
    }
    
}