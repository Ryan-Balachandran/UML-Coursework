<cftry>
     <cfparam name="book" default=""/>
     <cfparam name="qterm" default=""/>

     <cfset addEditFunctions = createObject('addedit')/>
     <cfset addEditFunctions.processForms(form)/>
 
     <div class="row">
         <div id="main" class="col-9">
             <cfif book neq ''>
                 <cfoutput>
                     #mainForm()#
                 </cfoutput>
             </cfif>
         </div>
         <div id="leftGutter" class="col-lg-3 order-first">
             <cfoutput>#sideNav()#</cfoutput>
         </div>
     </div>
 
     <cfcatch type="any">
         <cfdump var="#cfcatch#">
     </cfcatch>
 </cftry>
 
 <cffunction name="mainForm">
     <cfset thisBookDetails = addEditFunctions.bookDetails(book)>
     <cfset allPublishers = addEditFunctions.allPublishers()>
     <cfset allGenres = addEditFunctions.allGenres()/>
     <cfset bookGenres = addEditFunctions.bookGenres(book)/>
 
     <cfoutput>
         <form action="#cgi.script_name#?tool=addEdit&book=#book#&qterm=#qterm#" method="POST" enctype="multipart/form-data">
             <div class="form-floating mb-3">
                 <input type="text" id="isbn13" name="isbn13" class="form-control" value="#thisBookDetails.isbn13#" placeholder="Please Enter The ISBN13 of the book"/>
                 <label for="isbn13">ISBN 13: </label>
             </div>
 
             <div class="form-floating mb-3">
                 <input type="text" id="title" name="title" class="form-control" value="#thisBookDetails.title#" placeholder="Please Enter The title of the book"/>
                 <label for="title">Title: </label>
             </div>
 
             <div class="form-floating mb-3">
                 <input type="number" id="weight" name="weight" step=".1" class="form-control" value="#thisBookDetails.weight#" placeholder="Please Enter The weight of the book"/>
                 <label for="weight">Weight: </label>
             </div>
 
             <div class="form-floating mb-3">
                 <input type="number" id="year" name="year" class="form-control" value="#thisBookDetails.year#" placeholder="Please Enter The year of publication of the book"
                 />
                 <label for="year">Year: </label>
             </div>
 
             <div class="form-floating mb-3">
                 <input type="number" id="pages" name="pages" class="form-control" value="#thisBookDetails.pages#" placeholder="Please Enter nyumber of pages of the book"
                 />
                 <label for="year">Pages: </label>
             </div>
 
             <div class="form-floating mb-3">
                 <select class="form-select" id="publisher" name="publisher" aria-label="Publisher Select Control">
                     <option></option>
                     <cfloop query="allPublishers">
                         <option value="#id#" #id == thisBookDetails.publisher ? "selected" : ""#> #name#</option>
                     </cfloop>
                 </select>
                 <label for="publisher">Publisher</label>
             </div>
 
             <div class="row">
                 <div class="col">
                     <label for="uploadImage">Upload Cover</label>
                     <div class="input-group mb-3">
                         <input type="file" id="uploadImage" name="uploadimage" class="form-control"/>
                         <input type="hidden" name="image" value="#trim(thisBookDetails.image[1])#"/>
                     </div>
                 </div>
                 <div class="col">
                     <cfif thisBookDetails.image[1].len() gt 0>
                         <img src="../images/#trim(thisBookDetails.image[1])#" style="width:200px"/>
                     </cfif>
                 </div>
             </div>
 
             <div class="form-floating mb-3">
                 <textarea id="description" name="description" class="form-control">
                     <cfoutput>#thisBookDetails.description#</cfoutput>
                 </textarea>
                 <script>CKEDITOR.replace('description');</script>
             </div>
 
             <label>Genres</label>
             <div class="form-floating mb-3">
                 <cfloop query="allGenres">
                     <input id="genre#genreid#" type="checkbox" name="genre" value="#genreid#" /> #genrename#<br/>
                 </cfloop>

                 <cfloop query="bookGenres">
                     <script>document.getElementById('genre#genreid#').checked=true;</script>
                 </cfloop>
             </div>
 
             <button type="submit" class="btn btn-primary" style="width: 100%">Add Book</button>
         </form>
     </cfoutput>
 </cffunction>
 
 <cffunction name="sideNav">
     <cfset allBooks = addEditFunctions.allBooks(qterm)/>

     <div>
         Book List
     </div>

     <cfoutput>
         #findBookForm()#
     </cfoutput>

     <cfoutput>
         <ul class="nav flex-column">
             <li class="nav-item">
                 <a href="#cgi.script_name#?tool=addedit&book=new&qterm=#qterm#" class="nav-link">
                     New Book
                 </a>
             </li>
             <cfif qterm.len() == 0>
                 No Search Term Entered
                 <cfelseif allBooks.recordcount == 0>
                 No Results Found
                 <cfelse>
                 <cfloop query="allBooks">
                     <li class="nav-item">
                         <a href="#cgi.script_name#?tool=addedit&book=#isbn13#&qterm=#qterm#" class="nav-link">#trim(title)#</a>
                     </li>
                 </cfloop>
             </cfif>
         </ul>
     </cfoutput>
 </cffunction>
 
 <cffunction name="findBookForm">
     <cfoutput>
         <form action="#cgi.script_name#" method="post" class="form-inline">
             <div class="form-floating mb-3">
                 <input type="text" id="qterm" name="qterm" class="form-control" value="#qterm#" placeholder="Enter a search term to find a book to edit"/>
                 <label for="qterm">Search Inventory </label>
             </div>
         </form>
     </cfoutput>
 </cffunction> 
                                 