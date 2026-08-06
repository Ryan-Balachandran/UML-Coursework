/* CLICK() EVENT */
/*
     The click event is triggered when the mouse button is pressed and 
     released while over the selected element. Example: $("h1").click(). 
     Press and release the mouse button while over an <h1> element to trigger the event.
*/
$(document).ready(function() {					   
     $("h1").click(function() {
          $(this).css("background-color","red");
     });
});




/* MOUSEDOWN() EVENT */
/* 
     The mousedown event is triggered when the mouse button is 
     pressed while over the selected element. Example: $("h1").mousedown().
      Press the mouse button while over an <h1> element to trigger the event.
*/
$(document).ready(function() {				   
     $("h1").mousedown(function() {
          $(this).css("background-color","red");
     });
});




/* MOUSEDOWN() AND MOUSEUP() EVENTS */
/* 
     The mousedown event is triggered when the mouse button is 
     pressed while over the selected element. Example: $("h1").mousedown(). 
     Press the mouse button while over an <h1> element to trigger the event.

     The mouseup event is triggered when the mouse button is 
     released while over the selected element. Example: $("h1").mouseup(). 
     Release the mouse button while over an <h1> element to trigger the event.
*/
$(document).ready(function() {				   
     $("h1").mousedown(function() {
          $(this).css("background-color","red");
     });

     $("h1").mouseup(function() {
          $(this).css("background-color","yellow");
     });
});




/* MOUSEENTER() AND MOUSELEAVE() EVENTS */
/* 
     The mouseenter event is triggered when the mouse cursor enters the selected element. 
     Example: $("h1").mouseenter(). Move the mouse cursor over an <h1> element to trigger 
     the event.

     The mouseleave event is triggered when the mouse cursor leaves the selected element.
      Example: $("h1").mouseleave(). Move the mouse cursor off of an <h1> element to trigger 
      the event.
*/
$(document).ready(function() {					   
     $("h1").mouseenter(function() {
          $(this).css("background-color","red");
     });

     $("h1").mouseleave(function() {
          $(this).css("background-color","yellow");
     });
});




/* UNBIND() METHOD - Sample 1 */
/*
     The unbind method removes the specified event. 
     Example: $(this).unbind() - All events for the 
     currently triggered event will be removed.
*/
$(document).ready(function() {				   
     $("h1").mouseenter(function() {
          $(this).css("background-color","red");
     });

     $("h1").mouseleave(function() {
          $(this).css("background-color","yellow");
          $(this).unbind();
     });
});




/* UNBIND() METHOD - Sample 2 */
/*
     The unbind method removes the specified event. 
     Example: $("*").unbind() - All events will be removed.
*/
$(document).ready(function() {				   
     $("h1").mouseenter(function() {
          $(this).css("background-color","red");
     });

     $("h1").mouseleave(function() {
          $(this).css("background-color","yellow");
          $("*").unbind();
     });
});




/* UNBIND() METHOD - Sample 3 */
/*
     The unbind() method removes the specified event. 
     Example: $("*").unbind("mouseleave") - All mouseleave events will be removed.
*/
$(document).ready(function() {			   
     $("h1").mouseenter(function() {
          $(this).css("background-color","red");
     });

     $("h1").mouseleave(function() {
          $(this).css("background-color","yellow");
          $("*").unbind("mouseleave");
     });
});