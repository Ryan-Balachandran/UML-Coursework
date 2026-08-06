<cfparam name="newAccountMessage" default=""/>
<cfparam name="LoginMessage" default=""/>

<cfif form.keyExists('firstname')>
    <cfset newAccountResult = stateFunctions.processNewAccount(form)/>
    <cfif newAccountResult.success>
        <cfset newAccountMessage = newAccountResult.message/>
    <cfelse>
        <cfset newAccountMessage = newAccountResult.message/>
    </cfif>
</cfif>

<script type="text/javascript">
    function validateNewAccount(){
        let originalPassword = document.getElementById('password').value;
        let confirmPassword = document.getElementById('confirmPassword').value;

        if(originalPassword !== "" && originalPassword === confirmPassword){
            document.getElementById("submitnewaccountform").click();
            document.getElementById("newAccountMessage").innerHTML="";
        } else {
            document.getElementById("newAccountMessage").innerHTML="The passwords do not match!";
        }
    }
</script>

<cfoutput>
    <div class="row">
        <div class="col-lg-6">
            <legend>New User</legend>
            <div id="newAccountMessage"> #newAccountMessage# </div>
            <form action="#cgi.script_name#?p=login" method="post">
                <div class="form-floating mb-3">
                    <input type="text" required id="firstname" name="firstname" name="pages" class="form-control" laceholder="Please Enter First Name"/>
                    <label for="firstname">First Name: </label>
                </div>
                <div class="form-floating mb-3">
                    <input type="text" required id="lastname" name="lastname" class="form-control" placeholder="Please Enter Last Name"/>
                    <label for="lastname">Last Name: </label>
                </div>
                <div class="form-floating mb-3">
                    <input type="email" required id="email" name="email" class="form-control" placeholder="Please Enter Email"/>
                    <label for="email">Email: </label>
                </div>
                <div class="form-floating mb-3">
                    <input type="password" required id="password" name="password" class="form-control" placeholder="Please Enter Password"/>
                    <label for="email">Password: </label>
                </div>
                <div class="form-floating mb-3">
                    <input type="password" required id="confirmPassword" class="form-control" placeholder="Please Enter Password"/>
                    <label for="confirmPassword">Password: </label>
                </div>
                <button
                    type="button" id="newAccountButton" onclick="validateNewAccount()"
                    class="btn btn-warning" style="width: 100%">Make Account</button>
                <button type="submit" id="submitnewaccountform" style="display:none">Add Book</button>
            </form>
        </div>
        
        <div class="col-lg-6">
            <legend>Login</legend>
            <div id="loginMessage">#loginmessage#</div>
            <form action="#cgi.script_name#?p=login" method="post">
                <div class="form-floating mb-3">
                    <input type="text" required name="loginUser" class="form-control" placeholder="Please Enter Username"/>
                    <label for="confirmPassword">Username: </label>
                </div>
                <div class="form-floating mb-3">
                    <input type="password" required name="loginPass" class="form-control" placeholder="Please Enter Password"/>
                    <label for="confirmPassword">Username: </label>
                </div>
                <button type="submit" id="submitnewaccountform" class="btn btn-primary" style="width:100%"> Login </button>
            </form>
            <div>
                <a href="#cgi.script_name#?p=forgotPassword">Forgot Password</a>
            </div>
        </div>
    </div>
</cfoutput> 
                                