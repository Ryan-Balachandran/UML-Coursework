<cfparam name="whatView" default="proveit"/>
<cfparam name="ForgotMessage" default=""/>
<cfparam name="personid" default=""/>

<!--- The value of whatView will determine what form is shown or action is performed --->
<cfset whatView = bookstoreFunctions.processForgotPassword(form)>

<!--- This JS checks whether the password and the confirm password match before trying to submit the form - --->
<script>
    function validateNewAccount(){
        var originalPassword=document.getElementById('newaccountpassword').value;
        var confirmPassword=document.getElementById('newaccountpasswordconfirm').value;
        if(originalPassword===confirmPassword && originalPassword!==''){
            document.getElementById('submitnewaccountform').click();
            document.getElementById('ForgotMessage').innerHTML="";
        }
        else{
            document.getElementById('ForgotMessage').innerHTML="The two passwords do not match";
        }
    }
</script>

<!--- This is the sttrucure of the page with areas and individual functions for the two forms we will display --->
<cfoutput>
    <!--- This area will display any messages necessary --->
    <div id="ForgotMessage">&nbsp;#ForgotMessage#</div>
    <!--- If "proveit" comes baack from the processForms method, show the authentication form --->
    <cfif whatView eq 'proveit'>
        #authentictionForm()#
        <!--- Otherwise show the change password form --->
    <cfelseif whatView.len() eq 35>
        <cfset personid = whatView/>
        #newPasswordForm()#
    <cfelseif whatview eq 'goLogin'>
        <div>
            Success <a href="#cgi.script_name#?p=login">Go Log In</a>
        </div>
    </cfif>
</cfoutput>

<cffunction name="authentictionForm">
    <cfoutput>
        <form action="#cgi.script_name#?p=forgotPassword" method="post" class="form-horizontal">
            <div class="form-group">
                <label class="col-lg-3 control-label">Email Address:</label>
                <div class="col-lg-9">
                    <input type="email" name="email" placeholder="Email" class="form-control">
                </div>
            </div>
            <div class="form-group">
                <label class="col-lg-3 control-label">Last Name:</label>
                <div class="col-lg-9">
                    <input type="text" name="lastname" placeholder="Last (Family) Name" class="form-control">
                </div>
            </div>
            <div class="form-group">
                <label class="col-lg-3 control-label">&nbsp;</label>
                <div class="col-lg-9">
                    <input type="submit" value="Authenticate"/>
                </div>
            </div>
        </form>
    </cfoutput>
</cffunction>

<cffunction name="newPasswordForm">
    <cfoutput>
        <form action="#cgi.script_name#?p=forgotPassword" method="post" class="form-horizontal">
            <input type="hidden" name="personid" value="#personid#">
            <div class="form-group">
                <label class="col-lg-3 control-label">Password</label>
                <div class="col-lg-9">
                    <input type="password" class="form-control" name="password" id="newaccountpassword" required/>
                </div>
            </div>

            <div class="form-group">
                <label class="col-lg-3 control-label">Confirm Password</label>
                <div class="col-lg-9">
                    <input type="password" class="form-control" id="newaccountpasswordconfirm" required/>
                </div>
            </div>

            <div class="form-group">
                <label class="col-lg-3 control-label">&nbsp;</label>
                <div class="col-lg-9">
                    <!---
                        This button is visible and trggers the JS function to compare the password and password confirm.
                        If this passes, the JS function will click the hidden submit button and trigger the HTML5 validations
                    --->
                    <button type="button" id="newAccountButton" class="btn btn-warning" onclick="validateNewAccount()">Change Password</button>
                    <input type="submit" id="submitnewaccountform" style="display:none"/>
                </div>
            </div>
        </form>
    </cfoutput>
</cffunction> 
                                