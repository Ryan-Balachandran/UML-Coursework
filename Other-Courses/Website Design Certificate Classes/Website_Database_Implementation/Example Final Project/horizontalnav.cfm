<nav class="navbar navbar-expand-lg navbar-light bg-light">
     <a class="navbar-brand" href="#">
         <img src="../includes/classimages/rdb.png"/>
     </a>
     <button
         class="navbar-toggler"
         type="button"
         data-toggle="collapse"
         data-target="#navbarSupportedContent"
         aria-controls="navbarSupportedContent"
         aria-expanded="false"
         aria-label="Toggle navigation">
         <span class="navbar-toggler-icon"></span>
     </button>
 <cfoutput>
     <div class="collapse navbar-collapse" id="navbarSupportedContent">
         <ul class="navbar-nav mr-auto">
             <li class="nav-item active">
                 <a class="nav-link" href="/codebase/week9/">
                     Home <span class="sr-only">(current)</span>
                 </a>
             </li>
             <li class="nav-item">
                 <a class="nav-link" href="#cgi.scriptName#?p=content&id=A7EE957B-C14B-95E1-5D36844A4408C572">Store Information</a>
             </li>
             <li class="nav-item">
                 <a class="nav-link" href="#cgi.scriptName#?p=content&id=B52D2F2E-0751-CB27-C4F1A4971D5A0A7B">Highlighted Favorites</a>
             </li>
             <li class="nav-item">
                 <a class="nav-link" href="#cgi.scriptName#?p=content&id=B51F03A8-0EBD-1D72-580F45C2EBAD6096">Events</a>
             </li>
         </ul>
         <cfoutput>
             <form class="d-flex" action="#cgi.script_name#?p=details" method="post">
                 <input class="form-control me-2" type="search" name="searchme" placeholder="Search" aria-label="Search">
                 <button class="btn btn-outline-success" type="submit">Search</button>
             </form>
 
             <ul class="nav navbar-nav navbar-right">
                 <cfif session.user.isloggedin>
                     <li class="nav-item">
                         <span class="nav-link"> Welcome #session.user.firstname#</span>
                     </li>
                     <cfif session.user.isAdmin>
                         <li class="nav-item">
                             <a class ="nav-link" href="/codeBase/week9/management">Management</a>
                         </li>
                     </cfif>
                     <li class="nav-item">
                         <a class="nav-link" href="#cgi.script_name#?p=logoff">Logoff</a>
                     </li>
                 <cfelse>
                     <li class="nav-item">
                         <a class="nav-link" href="#cgi.script_name#?p=login">Login</a>
                     </li>
                 </cfif>
             </ul>
         </cfoutput>
     </div>
     </cfoutput>
 </nav> 
                                 