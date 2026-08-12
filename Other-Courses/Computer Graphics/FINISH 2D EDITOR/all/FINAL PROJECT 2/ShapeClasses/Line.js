class Line extends Shape
{
     constructor(p) 
     {
          super(p);

          this.id         = `line${s.shapeCount}`;
          this.type       = "Line";
          this.points     = [];
          this.x1         = p.x1;
          this.y1         = p.y1;
          this.x2         = p.x2;
          this.y2         = p.y2;
          this.handles    = [];
          this.numPoints  = 2;
          this.handleSize = 10;
          this.linelength = 0;
          this.lineX      = 0;
          this.lineY      = 0;
          this.cx         = 0;
          this.cy         = 0;
          this.savecolor  = this.strokeStyle;
     }

     draw() 
     {
          // MAKE ANOTHER IF STATEMENT FOR WHETHER THE SHAPE IS SELECTED, REDRAW ON DIFFERENT CANVAS?
          super.draw();

          if(this.showHitbox == true)
          {
               s.ctx.save();
               s.ctx.translate(this.translateX, this.translateY);
               s.ctx.scale(this.scale, this.scale); // always scale equally
               s.ctx.rotate(this.rotation);
     
               s.ctx.beginPath();
               s.ctx.moveTo(this.x1, this.y1);
               s.ctx.lineTo(this.x2, this.y2);
               s.ctx.stroke();
               s.ctx.restore();
     
               this.hitBox(); 
          }
          else
          {
               s.ctx.save();
               s.ctx.translate(this.translateX, this.translateY);
               s.ctx.scale(this.scale, this.scale); // always scale equally
               s.ctx.rotate(this.rotation);
     
               // loop through points
               s.ctx.beginPath();
               s.ctx.moveTo(this.x1, this.y1);
               s.ctx.lineTo(this.x2, this.y2);
               s.ctx.stroke();
               s.ctx.restore();
          }
     }

     createEscapeEventHandler(e) 
     {
          super.createEscapeEventHandler(e);
          if (e.code === 'Escape') s.lineMode();
     }

     objectOutput()
     {
          const returnObject = super.objectOutput();
          returnObject.id = this.id;
          returnObject.type = "Line";
          returnObject.x1 = this.x1;
          returnObject.y1 = this.y1;
          returnObject.x2 = this.x2;
          returnObject.y2 = this.y2;
          returnObject.handles = this.handles;

          return returnObject;
     }

     hitBox()
     {
          this.cx = (this.x1 + this.x2) / 2;
          this.cy = (this.y1 + this.y2) / 2;

          s.ctx.save();
          s.ctx.beginPath();
          s.ctx.arc(this.x1, this.y1, this.handleSize, 0, 2 * Math.PI, false);

          s.ctx.fillStyle = 'red';
          s.ctx.strokeStyle = 'red';
          // s.ctx.globalAlpha = 0.8;
          s.ctx.fill();

          s.ctx.beginPath();
          s.ctx.lineWidth = 1;
          s.ctx.moveTo(this.x1, this.y1);
          s.ctx.lineTo(this.cx, this.cy);
          s.ctx.lineTo(this.x2, this.y2);
          s.ctx.stroke();

          s.ctx.beginPath();
          s.ctx.arc(this.cx, this.cy, this.handleSize, 0, 2 * Math.PI, false);
          s.ctx.fill();

          s.ctx.beginPath();
          s.ctx.arc(this.x2, this.y2, this.handleSize, 0, 2 * Math.PI, false);
          s.ctx.fill();
          s.ctx.restore();

          this.updateHitbox();
     }

     updateHitbox()
     {
          if(this.handles.length === 3)
          {
               this.handles = [];
               this.handles.push({x: this.x1, y: this.y1, clicked: false});
               this.handles.push({x: this.cx, y: this.cy, clicked: false});
               this.handles.push({x: this.x2, y: this.y2, clicked: false});
          }
     }

     length()
     {
          // Calculate length of the line
          let dx = this.x2 - this.x1;
          let dy = this.y2 - this.y1;

          this.lineX = dx;    // x component of the line
          this.lineY = dy;    // y component of the line

          let x = Math.pow(dx, 2);
          let y = Math.pow(dy, 2);

          let result = Math.sqrt(x + y);

          this.linelength = result;

          return this.linelength;
     }

     select()
     {
          s.canvas.onmousedown = (e) => {
               let [x, y] = s.mousePosition(e);

               for(let i = 0; i < this.handles.length; i++)
               {
                    if(Math.sqrt(Math.pow(x - this.handles[i].x, 2) + Math.pow(y - this.handles[i].y, 2)) < this.handleSize)
                    {
                         if(i === 0 || i === 1 || i === 2)
                         {
                              s.ctx.save();
                              // this.savecolor = this.strokeStyle;
                              this.strokeStyle = 'blue';
                              s.ctx.restore();

                              console.log("clicked", i);
                              this.handles[i].clicked = true;
                         }

                         // this.isSelected = true;
                    }
                    else if(Math.sqrt(Math.pow(x - this.handles[i].x, 2) + Math.pow(y - this.handles[i].y, 2)) > this.handleSize)
                    {
                         if(this.handles[0].clicked === true && this.handles[1].clicked === false && this.handles[2].clicked === false)
                         {
                              s.ctx.save();
                              this.strokeStyle = 'black';
                              s.ctx.restore();
                              console.log("hehjvkh");
                         }
                         // if(this.handles[0].clicked === true && this.handles[1].clicked === false && this.handles[2].clicked === false)
                         // {
                         //      console.log("was selected");
                              // s.ctx.save();
                              // this.strokeStyle = 'black';
                              // s.ctx.restore();
                         //      this.handles[0].clicked = false;
                         // }

                         console.log("Not clicking");
                    }
               }
          }

          s.canvas.onmouseup = () => {
               s.canvas.onmousemove = undefined;
               // this.isSelected = true;               
               s.drawAll();   
          }
          









          // if(this.isSelected === false)
          // {
          //      console.log("SELECTING SHAPE");

          //      s.canvas.onmousedown = (e) => {
          //           let [x, y] = s.mousePosition(e);
          //           console.log("mouse down");

          //           // s.ctx.save();
          //           // this.savecolor = this.strokeStyle;
          //           // this.strokeStyle = 'blue';
          //           // s.ctx.restore();
          //      }
          // }



          // s.canvas.onmousedown = (e) => {
          //      let [x, y] = s.mousePosition(e);

          //      s.ctx.save();
          //      this.savecolor = this.strokeStyle;
          //      this.strokeStyle = 'blue';
          //      s.ctx.restore();

          //      for(let i = 0; i < this.handles.length; i++)
          //      {
          //           if(Math.sqrt(Math.pow(x - this.handles[i].x, 2) + Math.pow(y - this.handles[i].y, 2)) < this.handleSize)
          //           {
          //                console.log("Clicked");
          //                this.isSelected = true;
          //           }
          //      }
          // }

     }

     translate()
     {
          console.log(this.id);
     }

     rotate()
     {

     }

     scale()
     {
          
     }
}

s.lineMode = () => {
     s.canvas.onmousemove = undefined;
     // s.canvas.onclick = undefined;
     s.canvas.onmousedown = undefined;
     s.canvas.ondblclick = undefined;

     // capture keydown events to exit from the mode
     document.addEventListener('keydown', s.modeEscapeEventHandler);
     
     s.canvas.onmousedown = (e) => {
          let [x, y] = s.mousePosition(e);
          s.createLine(x, y);
     }
}

s.createLine = (x, y) => {
     // create the shape object and push it to the shape array
     /** @property linewidth */
     /** @property strokeStyle */
     /** @property strokeAlpha */
     /** @property lineCap */
     s.shapeCount++;

     const newLine = new Line({ x1: x, y1: y, x2: x, y2: y,
          lineWidth: s.linewidth.value,
          strokeStyle: s.colors[0].value,
          strokeAlpha: s.alphas[0].value,
          lineCap: s.lineCap.value
     });

     s.shapeArray.push(newLine);

     s.canvas.onmousemove = (e) => {
          // s.canvas.ondblclick = undefined;
          // s.canvas.onclick = undefined;
          [newLine.x2, newLine.y2] = s.mousePosition(e);
          s.drawAll();
     }

     // capture keydown events to exit from the mode
     document.removeEventListener('keydown', s.modeEscapeEventHandler);
     document.addEventListener('keydown', newLine.createEscapeEventHandler);

     s.canvas.onmouseup = () => {
          newLine.points.push({x:newLine.x1, y:newLine.y1});
          newLine.points.push({x:newLine.x2, y:newLine.y2});

          newLine.handles.push({x: newLine.x1, y: newLine.y1});
          newLine.handles.push({x: newLine.cx, y: newLine.cy});
          newLine.handles.push({x: newLine.x2, y: newLine.y2});

          s.canvas.onmouseup = undefined;
          document.removeEventListener('keydown', newLine.createEscapeEventHandler);
          s.lineMode();
     }
}