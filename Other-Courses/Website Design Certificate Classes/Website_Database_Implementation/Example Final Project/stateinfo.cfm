<cfset stateFunctions = createObject('stateInfo')/>

<cfif !session.keyExists('user')>
    <cfset session.user = stateFunctions.obtainUser()/>
</cfif>

<cfif form.keyExists('loginPass')>
    <cfset userData = stateFunctions.logMeIn(form.loginuser, form.loginpass)/>
    <cfif userData.recordCount == 1>
        <cfset session.user = stateFunctions.obtainUser(
            isLoggedIn = 1,
            firstname = userData.firstname,
            lastname = userData.lastname,
            email = userData.email,
            isAdmin = userData.isAdmin
        )/>
        <cfset p = 'carousel'>
    <cfelse>
        <cfset loginMessage = 'That login did not work.'/>
    </cfif>
</cfif>

<cfif url.keyExists('p') && url.p == 'logoff'>
    <cfset session.user = stateFunctions.obtainUser()/>
    <cfset p = 'carousel'/>
</cfif> 
                                