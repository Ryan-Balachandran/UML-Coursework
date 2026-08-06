/* TEXT() REPLACE TEXT */
/*
     Replaces the text in the selected elements. 
     Example: text("clicked") - Click on the heading text to change it.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).text("clicked");
     });
});

$(document).ready(function() {
     $("h1").click(function() {
          $("p").text("new text");
     });
});




/* TEXT() REPLACE TEXT WITH HTML SOURCE */
/*
     Replaces the text in the selected elements. 
     Example: text("new <b>text</b>") 
     - Click on the heading text to change the text in the <p> elements. 
     The HTML markup will be shown.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").text("new <b>text</b>");
     });
});




/* TEXT() REPLACE WITH HTML MARKUP */
/*
     Replaces the text with text and HTML markup. 
     Example: html("new <b>text</b>") 
     - Click on the heading text to change the text in the <p> elements. 
     The word "text" will be in bold.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").html("new <b>text</b>");
     });
});




/* HTML() REPLACE WITH HTML MARKUP INCLUDING ATTRIBUTES */
/*
     Replaces the text with text and HTML markup. 
     Example: html('new <b style="color: red;">text</b>') 
     - Click on the heading text to change the text in the <p> elements. 
     The word "text" will be red and bold.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").html('new <b style="color: red;">text</b>');
     });
});




/* HTML() REPLACES WHOLE CONTENT */
/*
     Replaces the text with text and HTML markup. 
     Example: html('new <b style="color: red;">text</b>') 
     - Click on the heading text to change the whole content of the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").html('new <b style="color: red;">text</b>');
     });
});




/* EMPTY() EMPTY THE CONTENTS */
/*
     Removes the content of the selected elements. 
     Example: empty() - Click on the heading text to remove the contents of the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").empty();
     });
});




/* APPEND() APPEND TEXT */
/*
     Append text at the end of the selected elements. 
     Example: append(" More text.") 
     - Click on the heading text to append text to the end of the <p> elements.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").append(" More text.");
     });
});




/* APPEND() APPEND HTML MARKUP */
/*
     Append HTML markup at the end of the selected elements. 
     Example: append("<p>new text</p>") 
     - Click on the heading text to append a <p> element to the end of the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").append("<p>new text</p>");
     });
});




/* AFTER() ADD HTML MARKUP AFTER SELECTION */
/*
     Add HTML markup after the selected elements. 
     Example: after("<p>new text</p>") 
     - Click on the heading text to add a <p> element after the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").after("<p>new text</p>");
     });
});




/* AFTER() ADD HTML MARKUP AFTER MULTIPLE SELECTIONS */
/*
     Add HTML markup after the selected elements. 
     Example: after("<p>new text</p>") 
     - Click on the heading text to add a <p> element after each of the two <p> elements.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").after("<p>new text</p>");
     });
});




/* PREPEND() PREDENT HTML MARKUP */
/*
     Prepend HTML markup at the start of the selected elements. 
     Example: prepend("<p>new text</p>") 
     - Click on the heading text to prepend a <p> element to the start of the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").prepend("<p>new text</p>");
     });
});




/* BEFORE() ADD HTML MARKUP BEFORE SELECTION */
/*
     Add HTML markup before the selected elements. 
     Example: before("<p>new text</p>") 
     - Click on the heading text to add a <p> element before the <div> element.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("div").before("<p>new text</p>");
     });
});




/* REPLACEWITH() REPLACE HTML MARKUP */
/*
     Replace the selected elements with new HTML markup. 
     Example: replaceWith("<h2>new text</h2>") 
     - Click on the heading text to replace the <p> elements with <h2> elements.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("p").replaceWith("<h2>new text</h2>");
     });
});