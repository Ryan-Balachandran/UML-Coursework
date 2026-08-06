var canvas = document.getElementById('myCanvas');
var ctx = canvas.getContext('2d');
var height = canvas.height;
var width = canvas.width;
var half_height = height/2;
var half_width = width/2;

// Variables to keep track of which options are currently selected for the shape and type of transformation
var currentShape = '';
var currentTransform = '';

// Event Handlers for Create Shape Buttons ------------------------------------
document.getElementById("rect-button").addEventListener("click", create_default_rect);
document.getElementById("line-button").addEventListener("click", create_default_line);
document.getElementById("circle-button").addEventListener("click", create_default_circle);
document.getElementById("triangle-button").addEventListener("click", create_default_triangle);
document.getElementById("poly-button").addEventListener("click", create_default_poly);
document.getElementById("clear-button").addEventListener("click", clear_shapes_and_transforms);
// ----------------------------------------------------------------------------

// Event Handlers for Transformation Buttons ----------------------------------
document.getElementById('translate-button').addEventListener("click", function translate(){ currentTransform = 'translate'; });
document.getElementById('scale-button').addEventListener("click", function scale(){ currentTransform = 'scale'; });
document.getElementById('rotate-button').addEventListener("click", function rotate(){ currentTransform = 'rotate'; });
// ----------------------------------------------------------------------------

// Track mouse within canvas
document.getElementById('myCanvas').addEventListener("mousemove", canvas_event);

// Function to choose which shape we are transforming
function canvas_event(){
    switch(currentShape){
        case 'line':
            transform_line();
            break;
        case 'rect':
            transform_rect();
            break;
        case 'circle':
            transform_circle();
            break;
        case 'triangle':
            transform_triangle();
            break;
        case 'poly':
            transform_poly();
            break;
        default:
            break;
    }
}

// Transformation related functions -------------------------------------------
function transform_line(){
    switch(currentTransform){
        case 'translate':
            // Begin by clearing the canvas
            clear_canvas();

            var length = 300;

            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var endx = mousex + length;
            var endy = mousey;

            // Create the line
            ctx.beginPath();
            ctx.moveTo(mousex, mousey);
            ctx.lineTo(endx, endy);
            ctx.stroke();
            break;

        case 'scale':
            // Begin by clearing the canvas
            clear_canvas();

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Line will be attached on the other end to center point of the canvas
            var startx = half_width;
            var starty = half_height;

            // Create the line
            ctx.beginPath();
            ctx.moveTo(startx, starty);
            ctx.lineTo(mousex, starty);
            ctx.stroke();
            break;
        case 'rotate':
            // Begin by clearing the canvas
            clear_canvas();

            // Set center point of the circle and radius
            var posx = half_width;
            var posy = half_height;
            var def_rad = 150;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var line1 = [posx, posy, posx, posy + 100];
            var line2 = [posx, posy, mousex, mousey];
            var angle = -get_angle_diff(line1, line2)-def_rad;

            // Use mouse x position as rotation angle
            var newx = def_rad*(Math.cos(angle)) - def_rad*(Math.sin(angle));
            var newy = def_rad*(Math.sin(angle)) + def_rad*(Math.cos(angle));

            // Create the line
            ctx.beginPath();
            ctx.moveTo(posx, posy);
            ctx.lineTo(newx + half_width, newy + half_height);
            ctx.stroke();
            break;
    }
}









function transform_rect(){
    switch(currentTransform){
        case 'translate':
            // Begin by clearing the canvas
            clear_canvas();

            // Create width and height variables for the rectangle for easy size changes
            var h = 150;
            var w = 300;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Create a centered rectangle of size 200x100
            ctx.fillRect(mousex, mousey, w, h);
            break;

        case 'scale':
            // Begin by clearing the canvas
            clear_canvas();

            // Create width and height variables for the rectangle for easy size changes
            var h = 150;
            var w = 300;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Create a centered rectangle of size 200x100
            ctx.fillRect(100, 100, mousex - 100, mousey - 100);
            break;

        case 'rotate':
            // Begin by clearing the canvas
            clear_canvas();

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var posx = half_width;
            var posy = half_height;

            // Get angle of mouse compared to a straight up line on the canvas
            var line1 = [posx, posy, posx, posy + 100];
            var line2 = [posx, posy, mousex, mousey];
            var angle = -get_angle_diff(line1, line2)-250;

            var defw = 250;
            var defh = 150;

            // Define base rectangle points to be rotated ---
            var x1 = half_width;
            var y1 = half_height;

            var x2 = x1 + defw;
            var y2 = y1;

            var x3 = x2;
            var y3 = y2 + defh;

            var x4 = x3 - defw;
            var y4 = y3;
            // ---------------------------------------------

            // Get position in canvas of the user's mouse
            //var rect = canvas.getBoundingClientRect();
            //var mousex = event.clientX - rect.left;
            //var rad_angle = ((Math.PI/180) * mousex)/2;

            // Calculated new position of corner 2 after rotation
            var c2x = defw*(Math.cos(angle));
            var c2y = defw*(Math.sin(angle));

            // Calculated new position of corner 3 after rotation
            var c3x = defw*(Math.cos(angle)) - defh*(Math.sin(angle));
            var c3y = defw*(Math.sin(angle)) + defh*(Math.cos(angle));

            // Calculated new position of corner 4 after rotation
            var c4x = -(defh*(Math.sin(angle)));
            var c4y = defh*(Math.cos(angle));

            ctx.beginPath();
            ctx.moveTo(x1, y1);
            ctx.lineTo(c2x + x1, c2y + y1);
            ctx.lineTo(c3x + x1, c3y + y1);
            ctx.lineTo(c4x + x1, c4y + y1);
            ctx.fill();
            break;
    }
}









function transform_circle(){
    switch(currentTransform){
        case 'translate':
            // Begin by clearing the canvas
            clear_canvas();

            var rad = 150;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Create the circle
            ctx.beginPath();
            ctx.arc(mousex, mousey, rad, 0, (Math.PI/180)*360);
            ctx.fill();
            break;

        case 'scale':
            // Begin by clearing the canvas
            clear_canvas();

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var radx = mousex - half_width;
            var rady = mousey - half_height;

            var rad = Math.sqrt((radx*radx)+(rady*rady))

            // Create the circle
            ctx.beginPath();
            ctx.arc(half_width, half_height, rad, 0, (Math.PI/180)*360);
            ctx.fill();
            break;

        case 'rotate':
            // Begin by clearing the canvas
            clear_canvas();

            // Set center point of the circle and radius
            var posx = half_width;
            var posy = half_height;
            var def_rad = 150;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var line1 = [posx, posy, posx, posy + def_rad];
            var line2 = [posx, posy, mousex, mousey];
            var rad_angle = -get_angle_diff(line1, line2);
            var rad_angle_180 = rad_angle + (Math.PI/180)*180;
            var rad180 = (Math.PI/180)*180

            // Draw half the circle in default color
            ctx.fillStyle = '#000';
            ctx.beginPath();
            ctx.arc(posx, posy, def_rad, rad_angle+rad180, rad_angle+(2*rad180));
            ctx.fill();
            // Draw the other half in red
            ctx.fillStyle = '#02D6FD';
            ctx.beginPath();
            ctx.arc(posx, posy, def_rad, rad_angle+(2*rad180), rad_angle+(3*rad180));
            ctx.fill();
            break;
    }
}












function transform_triangle(){
    switch(currentTransform){
        case 'translate':
            // Begin by clearing the canvas
            clear_canvas();

            // Set triangle side length
            var side_len = 300;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Calculate each of the corner positions
            var c1x = mousex;
            var c1y =  mousey - (half_height - ((Math.sqrt(3)/2)*side_len)/2) - 20;
            var c2x = c1x + side_len/2;
            var c2y = c1y + ((Math.sqrt(3)/2)*side_len);
            var c3x = c2x - side_len;
            var c3y = c2y;

            // Draw the triangle by drawing each point and filling
            ctx.beginPath();
            ctx.moveTo(c1x, c1y);
            ctx.lineTo(c2x, c2y);
            ctx.lineTo(c3x, c3y);
            ctx.fill();
            break;

        case 'scale':
            // Begin by clearing the canvas
            clear_canvas();

            // Set triangle side length
            var side_len = 300;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var scalex = Math.abs(half_width - mousex);
            var scaley = Math.abs(half_height - mousey);

            side_len = Math.abs(Math.sqrt((scalex*scalex)+(scaley*scaley)));

            // Calculate each of the corner positions
            var c1x = half_width;
            var c1y = half_height - ((Math.sqrt(3)/2)*side_len)/2;
            var c2x = c1x + side_len/2;
            var c2y = c1y + ((Math.sqrt(3)/2)*side_len);
            var c3x = c2x - side_len;
            var c3y = c2y;

            // Draw the triangle by drawing each point and filling
            ctx.beginPath();
            ctx.moveTo(c1x, c1y);
            ctx.lineTo(c2x, c2y);
            ctx.lineTo(c3x, c3y);
            ctx.fill();
            break;

        case 'rotate':
            // Begin by clearing the canvas
            clear_canvas();

            // Set triangle side length
            var side_len = 300;
            var tri_height = (Math.sqrt(3)*side_len)/2;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var posx = half_width;
            var posy = half_height;

            // Get angle of mouse compared to a straight up line on the canvas
            var line1 = [posx, posy, posx, posy + 100];
            var line2 = [posx, posy, mousex, mousey];
            var angle = -get_angle_diff(line1, line2);
            var centroid = side_len/Math.sqrt(3.0)

            // Use mouse x position as rotation angle
            var d_c1x = 0*(Math.cos(angle)) - centroid*(Math.sin(angle));
            var d_c1y = 0*(Math.sin(angle)) + centroid*(Math.cos(angle));

            // Use mouse x position as rotation angle
            var d_c2x = (side_len/2)*(Math.cos(angle)) - (-(centroid/2))*(Math.sin(angle));
            var d_c2y = (side_len/2)*(Math.sin(angle)) + (-(centroid/2))*(Math.cos(angle));

            // Use mouse x position as rotation angle
            var d_c3x = -(side_len/2)*(Math.cos(angle)) - (-(centroid/2))*(Math.sin(angle));
            var d_c3y = -(side_len/2)*(Math.sin(angle)) + (-(centroid/2))*(Math.cos(angle));

            // Draw the triangle by drawing each point and filling
            ctx.beginPath();
            ctx.moveTo(d_c1x + half_width, d_c1y + half_height);
            ctx.lineTo(d_c2x + half_width, d_c2y + half_height);
            ctx.lineTo(d_c3x + half_width, d_c3y + half_height);
            ctx.fill();
            break;
    }
}











function transform_poly(){
    switch(currentTransform){
        case 'translate':
            // Begin by clearing the canvas
            clear_canvas();
            ctx.fillStyle = '#02D6FD';

            // hexagon
            var numberOfSides = 6;
            var size = 150;
            var centerx = half_width;
            var centery = half_height;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            ctx.beginPath();
            ctx.moveTo (mousex +  size * Math.cos(0), mousey +  size *  Math.sin(0));

            for (var i = 1; i <= numberOfSides;i += 1) {
              ctx.lineTo (mousex + size * Math.cos(i * 2 * Math.PI / numberOfSides), mousey + size * Math.sin(i * 2 * Math.PI / numberOfSides));
            }
            ctx.fill();
            break;

        case 'scale':
            // Begin by clearing the canvas
            clear_canvas();
            ctx.fillStyle = '#02D6FD';

            // hexagon
            var numberOfSides = 6;
            var size = 150;
            var centerx = half_width;
            var centery = half_height;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            var scalex = Math.abs(half_width - mousex);
            var scaley = Math.abs(half_height - mousey);

            size = Math.abs(Math.sqrt((scalex*scalex)+(scaley*scaley)));

            ctx.beginPath();
            ctx.moveTo (centerx +  size * Math.cos(0), centery +  size *  Math.sin(0));

            for (var i = 1; i <= numberOfSides;i += 1) {
              ctx.lineTo (centerx + size * Math.cos(i * 2 * Math.PI / numberOfSides), centery + size * Math.sin(i * 2 * Math.PI / numberOfSides));
            }
            ctx.fill();
            break;

        case 'rotate':
            // Begin by clearing the canvas
            clear_canvas();
            ctx.fillStyle = '#02D6FD';

            // hexagon
            var numberOfSides = 6;
            var size = 150;
            var centerx = half_width;
            var centery = half_height;

            var posx = half_width;
            var posy = half_height;

            // Get position in canvas of the user's mouse
            var rect = canvas.getBoundingClientRect();
            var mousex = event.clientX - rect.left;
            var mousey = event.clientY - rect.top;

            // Get angle of mouse compared to a straight up line on the canvas
            var line1 = [posx, posy, posx, posy + 100];
            var line2 = [posx, posy, mousex, mousey];
            var angle = -get_angle_diff(line1, line2);

            ctx.beginPath();
            ctx.moveTo (centerx +  size * Math.cos(angle), centery +  size *  Math.sin(angle));

            for (var i = 1; i <= numberOfSides;i += 1) {
              ctx.lineTo (centerx + size * Math.cos((i * 2 * Math.PI / numberOfSides) + angle), centery + size * Math.sin((i * 2 * Math.PI / numberOfSides) + angle));
            }
            ctx.fill();
            break;
    }
}
// ----------------------------------------------------------------------------















// ------------- Default Shape Functions ----------------------------
function create_default_line() {
    // Begin by clearing the canvas
    clear_canvas();
    ctx.strokeStyle = '#02D6FD';
    ctx.lineWidth = 3;

    // Default line length if no tranformation being applied
    var length = 300;

    // Start the line on the left side of the canvas by default
    var x1 = half_width - length/2;
    var x2 = x1 + length;

    // The line will just render at a default height (which is half height)
    var y = half_height;

    // Create the line
    ctx.beginPath();
    ctx.moveTo(x1, y);
    ctx.lineTo(x2, y);
    ctx.stroke();

    currentShape = 'line';
    currentTransform = '';
}

function create_default_rect() {
    // Begin by clearing the canvas
    clear_canvas();
    ctx.fillStyle = '#02D6FD';

    // Create width and height variables for the rectangle for easy size changes
    var h = 150;
    var w = 300;

    // Create a centered rectangle of size 200x100
    ctx.fillRect(half_width - w/2, half_height - h/2, w, h);

    currentShape = 'rect';
    currentTransform = '';
}

function create_default_circle() {
    // Begin by clearing the canvas
    clear_canvas();
    ctx.fillStyle = '#02D6FD';

    // Set center point of the circle and radius
    var posx = half_width;
    var posy = half_height;
    var rad = 150;

    // Create the circle
    ctx.beginPath();
    ctx.arc(posx, posy, rad, 0, (Math.PI/180)*360);
    ctx.fill();

    currentShape = 'circle';
    currentTransform = '';
}

function create_default_triangle() {
    // Begin by clearing the canvas
    clear_canvas();
    ctx.fillStyle = '#02D6FD';

    // Set triangle side length
    var side_len = 300;
    var tri_height = (Math.sqrt(3.0)*side_len)/2;

    // Calculate each of the corner positions
    var c1x = half_width;
    var c1y = half_height - side_len/Math.sqrt(3.0);

    var c2x = c1x + side_len/2.0;
    var c2y = c1y + tri_height;
    
    var c3x = c2x - side_len;
    var c3y = c2y;

    // Draw the triangle by drawing each point and filling
    ctx.beginPath();
    ctx.moveTo(c1x, c1y);
    ctx.lineTo(c2x, c2y);
    ctx.lineTo(c3x, c3y);
    ctx.fill();

    currentShape = 'triangle';
    currentTransform = '';
}

function create_default_poly(){
    // Begin by clearing the canvas
    clear_canvas();
    ctx.fillStyle = '#02D6FD';

    // hexagon
    var numberOfSides = 6;
    var size = 150;
    var centerx = half_width;
    var centery = half_height;

    ctx.beginPath();
    ctx.moveTo (centerx +  size * Math.cos(0), centery +  size *  Math.sin(0));

    for (var i = 1; i <= numberOfSides;i += 1) {
      ctx.lineTo (centerx + size * Math.cos(i * 2 * Math.PI / numberOfSides), centery + size * Math.sin(i * 2 * Math.PI / numberOfSides));
    }
    ctx.fill();

    currentShape = 'poly';
    currentTransform = '';
}
// ------------------------------------------------------------

// Clear any of the shapes drawn to the canvas
function clear_canvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}
// Clear the shapes on the canvas as well as any transformations being applied
function clear_shapes_and_transforms(){
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    currentShape = '';
    currentTransform = '';
}

// --- Other Handy Functions ---- //
function get_angle_diff(line1, line2)
{
    // Function to return the angle (in radians) between two lines
    var line1_x1 = line1[0];
    var line1_y1 = line1[1];
    var line1_x2 = line1[2];
    var line1_y2 = line1[3];

    var line2_x1 = line2[0];
    var line2_y1 = line2[1];
    var line2_x2 = line2[2];
    var line2_y2 = line2[3];

    var angle1 = Math.atan2(line1_y1 - line1_y2, line1_x1 - line1_x2);
    var angle2 = Math.atan2(line2_y1 - line2_y2, line2_x1 - line2_x2);

    return angle1 - angle2;
}
