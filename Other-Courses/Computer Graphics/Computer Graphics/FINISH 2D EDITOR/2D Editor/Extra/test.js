// FREE FORM DRAWING
// MAKE ARRAY OF POINTS
var el = document.getElementById('c');
var ctx = el.getContext('2d');
var isDrawing;

el.onmousedown = function (e) 
{
     e.preventDefault();
     e.stopPropagation();
     
     isDrawing = true;
     ctx.moveTo(e.clientX, e.clientY);
};

el.onmousemove = function (e) 
{
     if (isDrawing) 
     {
          ctx.lineTo(e.clientX, e.clientY);
          ctx.stroke();
     }
};

el.onmouseup = function () 
{
     isDrawing = false;
};







const drawCircle = (canvas, descriptor = {}) => {
     const { x = 95
          , y = 50
          , radius = 40
          , lineWidth = 5
          , color = "red"
     } = descriptor

     canvas.beginPath()
     canvas.lineWidth = lineWidth
     canvas.strokeStyle = color
     canvas.arc(x, y, radius, 0, 2 * Math.PI)
     canvas.stroke()
}

const getCanvas = (id) =>
     document.getElementById(id).getContext("2d")

drawCircle(getCanvas('Editorcanvas')) // default styles
drawCircle(getCanvas('Editorcanvas'), { color: 'dimgray', x: 220, y: 500 })
drawCircle(getCanvas('Editorcanvas'), { color: 'purple', radius: 10, x: 210 })


