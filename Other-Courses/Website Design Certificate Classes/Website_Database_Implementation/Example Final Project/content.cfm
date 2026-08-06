<cfparam name="id" default="4" />

<cfset contentFunctions = createObject("codebase.week9.management.content") />
<cfset myContent = contentFunctions.obtainArticle( id ) />

<cfoutput>
    <h1>#myContent.title#</h1>
    <h4>#dateformat(MyContent.dateWritten,"mm.dd.yyyy")#</h4>
    <p>#myContent.description#</p>
</cfoutput> 
                                