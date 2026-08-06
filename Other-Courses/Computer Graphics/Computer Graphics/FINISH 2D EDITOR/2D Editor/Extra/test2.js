select()
{
     s.canvas.onmousedown = (e) => {
          let [startX, startY] = s.mousePosition(e);
     
          s.ctx.save();
          this.savecolor = this.strokeStyle;
          this.strokeStyle = 'blue';
          s.ctx.restore();
     
          if(this.isSelected === false)
          {
               for(let i = 0; i < this.handles.length; i++)
               {
                    if(Math.sqrt(Math.pow(startX - this.handles[i].x, 2) + Math.pow(startY - this.handles[i].y, 2)) < this.handleSize)
                    {    
                         s.canvas.onmousemove = (e) => {
                              let [x, y] = s.mousePosition(e);
               
                              if(i === 0)
                              {
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x1 += dx;
                                   this.y1 += dy;     
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                              if(i === 1)
                              {
                                   // s.ctx.save();
     
                                   // var dx = x - startX;
                                   // var dy = y - startY;
                                   // startX = x;
                                   // startY = y;
     
                                   // this.x1 += dx;
                                   // this.y1 += dy;     
                                   // s.ctx.restore();
                                   // s.drawAll();
                              }
                              if(i === 2)
                              {
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x2 += dx;
                                   this.y2 += dy;     
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                         }
     
                         s.canvas.onmouseup = () => {
     
                              s.canvas.onmousemove = undefined;
                              this.isSelected = true;               
                              s.drawAll();   // GOES TO ELSE BEFORE IF REMOVED
                         }
                    }
               }
          }
          else
          {
               console.log("****** ------------------ WHAT TO DO HERE");
          }
     }     
}















translate()
{

     console.log("TRANSLATING SHAPE", this.id);

     if(this.isSelected === true && s.previousShapeIndex === null)
     {
          s.previousShapeIndex = s.selectedShapeIndex;

          s.canvas.onmousedown = (e) => {
               let [startX, startY] = s.mousePosition(e);


               for(let i = 0; i < this.handles.length; i++)
               {
                    if(Math.sqrt(Math.pow(startX - this.handles[i].x, 2) + Math.pow(startY - this.handles[i].y, 2)) < this.handleSize)
                    {
                         s.canvas.onmousemove = (e) => {
                              let [x, y] = s.mousePosition(e);

                              if(i === 0)
                              {
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;

                                   this.x1 += dx;
                                   this.y1 += dy;
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                              if(i === 1)
                              {          
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x1 += dx;
                                   this.y1 += dy;   
                                   this.x2 += dx;
                                   this.y2 += dy;   
                                   s.ctx.restore();  
                                   s.drawAll();
                              }
                              if(i === 2)
                              {          
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x2 += dx;
                                   this.y2 += dy;     
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                         }

                         s.canvas.onmouseup = () => {
                              s.canvas.onmousemove = undefined;
                              // s.drawAll();
                         }
                    }
                    else if(Math.sqrt(Math.pow(startX - this.handles[i].x, 2) + Math.pow(startY - this.handles[i].y, 2)) > this.handleSize)
                    {

                         s.canvas.onmouseup = () => {
                              s.canvas.onmousemove = undefined;

                              this.isSelected = false;
                              s.ctx.save();
                              this.strokeStyle = this.savecolor;
                              s.ctx.restore();

                              // s.selectedShape = [];
                              s.selectedShapeIndex = null;
                              s.previousShapeIndex = null;
                              s.drawAll();
                         }
                    }
               }
          }
     }







     else if(this.isSelected === true && s.previousShapeIndex != null)
     {

          s.canvas.onmousedown = (e) => {
               let [startX, startY] = s.mousePosition(e);

               for(let i = 0; i < this.handles.length; i++)
               {
                    if(Math.sqrt(Math.pow(startX - this.handles[i].x, 2) + Math.pow(startY - this.handles[i].y, 2)) < this.handleSize)
                    {
                         s.canvas.onmousemove = (e) => {
                              let [x, y] = s.mousePosition(e);

                              if(i === 0)
                              {
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;

                                   this.x1 += dx;
                                   this.y1 += dy;
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                              if(i === 1)
                              {          
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x1 += dx;
                                   this.y1 += dy;   
                                   this.x2 += dx;
                                   this.y2 += dy;   
                                   s.ctx.restore();  
                                   s.drawAll();
                              }
                              if(i === 2)
                              {          
                                   s.ctx.save();
                                   var dx = x - startX;
                                   var dy = y - startY;
                                   startX = x;
                                   startY = y;
     
                                   this.x2 += dx;
                                   this.y2 += dy;     
                                   s.ctx.restore();
                                   s.drawAll();
                              }
                         }

                         s.canvas.onmouseup = () => {
                              s.canvas.onmousemove = undefined;
                              // s.drawAll();
                         }
                    }






                    
                    else if(Math.sqrt(Math.pow(startX - this.handles[i].x, 2) + Math.pow(startY - this.handles[i].y, 2)) > this.handleSize)
                    {

                         s.canvas.onmouseup = () => {
                              s.canvas.onmousemove = undefined;

                              this.isSelected = false;
                              s.ctx.save();
                              this.strokeStyle = this.savecolor;
                              s.ctx.restore();
                              // s.selectedShape = [];
                              s.selectedShapeIndex = null;
                              s.previousShapeIndex = null;
                              s.drawAll();
                         }
                    }
               }
          }
     }
}

