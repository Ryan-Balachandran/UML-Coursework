
s.drawAll = () => {
     // clear the canvas before painting stuff
     s.ctx.clearRect(0, 0, s.canvas.width, s.canvas.height);

     s.ctx.save();

     // FOR EACH, DO TRANSLATE, SCALE, ROTATE
     // s.ctx.translate(s.panX, s.panY);
     s.ctx.scale(s.scale, s.scale); // always scale equally
     s.ctx.rotate(s.rotation);

     if(s.showGrid === false)
     {
          s.shapeArray.forEach(shape => { if(shape.show) {shape.draw(); }});    
     }
     if(s.showGrid === true)
     {
          s.drawGrid();
          s.shapeArray.forEach(shape => { if(shape.show) shape.draw(); });
     }

     if(s.shapeSelect.value === 'none' && s.transformSelect.value === 'Select')
     {
          for(let i = 0; i < s.shapeArray.length; i++)
          {





               if(s.shapeArray[i].isSelected === false)
               {

                    console.log(s.shapeArray[i].id, "not selected");
                    s.shapeArray[i].select();
                    // s.selectedShape = [];
               }
               else if(s.shapeArray[i].isSelected === true)
               {
                    console.log(s.shapeArray[i].id, "selected");

                    if(s.selectedShape === null)
                    {
                         s.selectedShapeIndex = i;
                         s.selectedShape = s.shapeArray[s.selectedShapeIndex];
                         s.selectedShape.translate();
                    }
                    else if(s.selectedShape != null)
                    {
                         if(s.previousShapeIndex === null)
                         {
                              s.selectedShape.translate();
                         }
                         else if(s.selectedShapeIndex != s.previousShapeIndex)
                         {
                              s.selectedShapeIndex = i;
                              s.selectedShape = s.shapeArray[s.selectedShapeIndex];
                              s.selectedShape.translate();
                         }
                         else
                         {
                              s.selectedShape.translate();
                         }
                    }
               }


               


          }
     }

     s.ctx.restore();

     // console.log(s.shapeArray);
     // SELECT HERE?
}
