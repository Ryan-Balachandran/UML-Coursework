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








/*
Remove a single item by index
This example uses the splice() method to remove the string "Banana" from the fruits array — by specifying the index position of "Banana".

const fruits = ['Strawberry', 'Banana', 'Mango'];
const start = fruits.indexOf('Banana');
const deleteCount = 1;
const removedItems = fruits.splice(start, deleteCount);
console.log(fruits);
// ["Strawberry", "Mango"]
console.log(removedItems);
// ["Banana"]
*/








s.detectHandles = () => {
     let handle = [];
     s.canvas.onmousedown = (e) => {
          let [startX, startY] = s.mousePosition(e);
          // console.log(x, y);

          s.shapeArray.forEach(shape => {
               if(shape.showHitbox === true)
               {
                    // console.log("Look for that hitbox!");
                    handle = shape.handles;

                    for(let i = 0; i < handle.length; i++)
                    {
                         if(Math.sqrt(Math.pow(startX - handle[i].x, 2) + Math.pow(startY - handle[i].y, 2)) < 10)
                         {
                              s.isDrag = true;

                              if(i === 0)
                              {
                                   s.canvas.onmousemove = (e) => {
                                        if(!s.isDrag) return;
                                        let [x, y] = s.mousePosition(e);

                                        var dx = x - startX;
                                        var dy = y - startY;
                                        shape.x1 += dx;
                                        shape.y1 += dy;
                                        shape.x2 += dx;
                                        shape.y2 += dy;

                                        s.drawAll();

                                        startX = x;
                                        startY = y;
                                   }

                                   s.canvas.onmouseup = (e) => {
                                        s.isDrag = false;
                                        s.drawAll();
                                   }
                              }

                              if(i === 1)
                              {
                                   s.canvas.onmousemove = (e) => {
                                        if(!s.isDrag) return;
                                        let [x, y] = s.mousePosition(e);

                                        var dx = x - startX;
                                        var dy = y - startY;
                                        shape.x1 += dx;
                                        shape.y1 += dy;
                                        shape.x2 += dx;
                                        shape.y2 += dy;

                                        s.drawAll();

                                        startX = x;
                                        startY = y;
                                   }

                                   s.canvas.onmouseup = (e) => {
                                        s.isDrag = false;
                                        s.drawAll();
                                   }
                              }

                              if(i === 2)
                              {
                                   s.canvas.onmousemove = (e) => {
                                        if(!s.isDrag) return;
                                        let [x, y] = s.mousePosition(e);

                                        var dx = x - startX;
                                        var dy = y - startY;
                                        shape.x1 += dx;
                                        shape.y1 += dy;
                                        shape.x2 += dx;
                                        shape.y2 += dy;

                                        s.drawAll();

                                        startX = x;
                                        startY = y;
                                   }

                                   s.canvas.onmouseup = (e) => {
                                        s.drawAll();
                                   }
                              }
                         }
                    }
               }
          });
     }
}