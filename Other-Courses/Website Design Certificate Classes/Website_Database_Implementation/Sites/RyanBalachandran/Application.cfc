component {

            this.name = 'RyanBalachandran';
            this.dsource = 'RyanBalachandran';
            this.sessionmanagement = 'true';
        
            public function onApplicationStart() {
                application.hiddenFolders = 'myFinalProject,exp1,aspnet_client,weiping_zhen,includes,courseitems,createalong,dcard,followalong,sources,sdemo1,.git,.idea,john_doe';
                application.dsource = this.dsource;
            }
        
        }
        