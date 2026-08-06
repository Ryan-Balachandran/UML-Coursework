<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Title</title>
        <link
            href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css"
            rel="stylesheet"
            integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3"
            crossorigin="anonymous"
        >
        <script
            src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"
            integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p"
            crossorigin="anonymous"
        ></script>
        <script src="//cdn.ckeditor.com/4.21.0/standard/ckeditor.js"></script>
    </head>

    <body>
        <cfparam name="tool" default="addEdit"/>
        
        <div class="container">
            <div id="navarea">
                <cfinclude template="managementNav.cfm" />
            </div>
            <div id="mainarea">
                <cfinclude template="#tool#.cfm"/>
            </div>
        </div>
    </body>
</html> 
                                