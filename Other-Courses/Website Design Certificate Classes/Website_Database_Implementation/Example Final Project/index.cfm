 <cftry>
     <!doctype html>
     <html>
         <head>
             <title>My Bookstore</title>
             <!--- Links to Bootstrap and our custom CSS. You'll have /username/includes.... --->
             <link
                 href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css"
                 rel="stylesheet"
                 integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3"
                 crossorigin="anonymous">
             <script
                 src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"
                 integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p"
                 crossorigin="anonymous"
             ></script>
         </head>
         <body>
             <cfparam name="p" default="carousel"/>
             <cfset bookstoreFunctions = createObject('bookstore')/>

             <cfinclude template="stateInfo.cfm"/>
             <!--- This div "wraps" the visible portions of the site --->
             <div class="container">
                 <!--- This establishes the header area and the cfinclude pulls in the header.cfm file --->
                 <div id="topHeader" class="row">
                     <cfinclude template="header.cfm">
                 </div>
 
                 <!---
                     This establishes the Horoontal Navigation area and the cfinclude pulls in the horiontalnav.cfm file
                 --->
                 <div id="horizontalnav" class="row">
                     <cfinclude template="horizontalnav.cfm">
                 </div>
 
                 <!--- This establishes the main content area which has two columns in it --->
                 <div id="maincontent" class="row">
                     <!---
                         This establishes the Center area and the cfinclude pulls in the header.cfm file.
                         The center area comesfirst so that on mobile sites it was be on top and read first.
                         The "push" css moves it over so the genrenav can appear on the right on larger browsers
                     --->
                     <div id="center" class="col-sm-7 col-lg-7 col-md-7 col-sm-push-3">
                         <cfinclude template="#p#.cfm">
                     </div>
 
                     <!---
                         This establishes the genrenav area and the cfinclude pulls in the genrenav.cfm file. 
                         The "pull" css makes it appear on the left hand side of the screen on large screens 
                         even though it comes second in the hierarchy
                     --->
                     <div id="leftgutter" class="col-sm-3 order-first">
                         <cfinclude template="genrenav.cfm">
                     </div>
                 </div>
 
                 <!--- This establishes the footer area and the cfinclude pulls in the footer.cfm file --->
                 <div id="footer" class="row">
                     <cfinclude template="footer.cfm">
                 </div>
             </div>
         </body>
     </html>
     <cfcatch type="any">
         <cfdump var="#cfcatch#"/>
     </cfcatch>
 </cftry> 
                                 