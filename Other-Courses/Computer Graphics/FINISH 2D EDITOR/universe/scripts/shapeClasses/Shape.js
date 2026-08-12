class Shape 
{
    constructor(p) 
    {
        this.lineWidth   = p.lineWidth;
        this.fillStyle   = p.fillStyle;
        this.fillAlpha   = p.fillAlpha;
        this.fill        = p.fill;
        this.strokeStyle = p.strokeStyle;
        this.strokeAlpha = p.strokeAlpha;
        this.stroke      = p.stroke;
        this.lineCap     = p.lineCap;
        this.lineJoin    = p.lineJoin;
        this.zoom        = 0;              
        this.show        = true;

        this.stepDisplay = p.stepDisplay;
        this.panX        = 0;               // NO
        this.panY        = 0;               // NO
        this.lineDash    = p.lineDash;      // NO
        this.ldn         = [];              // NO
        this.compOp      = p.compOp;        // NO

        this.updateScale();
        this.updateStrokeStyleOrAlpha();
        this.updateFillStyleOrAlpha();
        this.updateLineDash();              // NO
    }

    updateScale() 
    {
        this.scale = Math.pow(1.1, this.zoom);
    }

    constructColors(type) 
    {
        const hexString = this[`${type}Style`];
        // color pickers do not output a value with alpha so to do this the way
        //  I want I have to construct a CSS rgba function. Get hex string
        //  values from '#RRGGBB' and then the alpha.
        return `rgba(${
            parseInt(hexString.substring(1, 3), 16).
            toString(10)}, ${
            parseInt(hexString.substring(3, 5), 16).
            toString(10)}, ${
            parseInt(hexString.substring(5), 16).
            toString(10)}, ${this[`${type}Alpha`] / 100})`;
        // phew, there's gotta be a better way
    }

    updateStrokeStyleOrAlpha() 
    {
        if(!this.strokeStyle) return;
        this.strokeStyle = this.constructColors('stroke');
    }

    updateFillStyleOrAlpha() 
    {
        if(!this.fillStyle) return;
        this.fillStyle = this.constructColors('fill');
    }





    // NO
    // Called either in the constructor without parameter or externally with one
    updateLineDash(newLineDashString) {
        if(newLineDashString) this.lineDash = newLineDashString;
        // trim it just in case and then make an array
        let lineDash = this.lineDash.trim().split(/\s+/);
        this.lineDashNums = [];
        if(lineDash[0] !== '') { // if lineDash is '' make it work correctly
            lineDash.forEach((e) => {
                const n = parseFloat(e);
                this.lineDashNums.push(n);
            });
        }
    }






    draw() 
    {
        if(this.fillStyle) s.ctx.fillStyle = this.fillStyle;
        if(this.strokeStyle) s.ctx.strokeStyle = this.strokeStyle;
        s.ctx.lineWidth = this.lineWidth;
        if(this.lineCap) s.ctx.lineCap = this.lineCap;  

        

        // NO
        if(this.compOp) {
            this.previousCompOp = s.ctx.globalCompositeOperation;
            s.ctx.globalCompositeOperation = this.compOp;
        }
        if(this.lineDash) s.ctx.setLineDash(this.lineDashNums);
    }








    // NO
    postDraw() 
    {
        if(this.compOp) s.ctx.globalCompositeOperation = this.previousCompOp;
    }

    createEscapeEventHandler(e) 
    {
        if(e.code === 'Escape') 
        {
            s.stepArray.pop();
            s.shapeCount--;
            s.drawAll();
        }
    }

    edit() 
    {
        // tbd
    }
}

s.mousePosition = (e) => {
    // find the mouse position
    const r = s.universeCanvas.getBoundingClientRect();
    let x = e.clientX - r.x - s.borderOffset;
    let y = e.clientY - r.y - s.borderOffset;

    // reverse the angle
    let angle = Math.atan2(y - s.panY, x - s.panX);
    angle -= s.rotation;
    const distance = Math.sqrt((x - s.panX)**2 + (y - s.panY)**2);
    x = Math.cos(angle) * distance;
    y = Math.sin(angle) * distance;

    // reverse the scale
    return [x / s.scale, y / s.scale]
}
