class Rect extends Shape {
    constructor(p) {
        super(p);

        this.x      = p.x;
        this.y      = p.y;
        this.x2     = 0;
        this.y2     = 0;
        this.x3     = 0;
        this.y3     = 0;
        this.x4     = 0;
        this.y4     = 0;
        this.width  = p.width;
        this.height = p.height;
    }

    draw() {
        super.draw();

        let x, y, x2, y2, x3, y3, x4, y4;

        [x, y]   = s.rotate(0, 0, this.x,  this.y,  s.rotation);
        [x2, y2] = s.rotate(0, 0, this.x2, this.y2, s.rotation);
        [x3, y3] = s.rotate(0, 0, this.x3, this.y3, s.rotation);
        [x4, y4] = s.rotate(0, 0, this.x4, this.y4, s.rotation);

        x  = x  * this.scale * s.scale + this.panX + s.panX;
        y  = y  * this.scale * s.scale + this.panY + s.panY;
        x2 = x2 * this.scale * s.scale + this.panX + s.panX;
        y2 = y2 * this.scale * s.scale + this.panY + s.panY;
        x3 = x3 * this.scale * s.scale + this.panX + s.panX;
        y3 = y3 * this.scale * s.scale + this.panY + s.panY;
        x4 = x4 * this.scale * s.scale + this.panX + s.panX;
        y4 = y4 * this.scale * s.scale + this.panY + s.panY;

        s.ctx.setLineDash(this.ldn);
        s.ctx.lineJoin = this.lineJoin;
        s.ctx.beginPath();
        // The regular rectangle, could not figure out how to angle it right
        //  with rotation, so I generically made it a kind of path.  This will
        //  be useful for more complex forms.  The beginning and end points need
        //  to be in the middle of a line to get the line join right.
        const topMidX = (x + x2) / 2;
        const topMidY = (y + y2) / 2;
        s.ctx.moveTo(topMidX, topMidY);
        s.ctx.lineTo(x2, y2);
        s.ctx.lineTo(x3, y3);
        s.ctx.lineTo(x4, y4);
        s.ctx.lineTo(x, y);
        s.ctx.lineTo(topMidX, topMidY);
        if(this.fill) s.ctx.fill();
        if(this.stroke) s.ctx.stroke();

        super.postDraw();
    }

    createEscapeEventHandler(e) {
        super.createEscapeEventHandler(e);
        if(e.code === 'Escape') s.rectMode();
    }
}

s.rectMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['textShape', 'fontSize', 'fontFamily'];
    const enableList = ['shapeFillStyle', 'shapeFillAlpha', 'shapeStrokeStyle',
        'shapeStrokeAlpha', 'lineWidth', 'lineDash', 'composite',
        'fillNStrokeButtonsRow', 'lineJoin'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'rect';
    s.universeCanvas.onmousemove = undefined;

    s.universeCanvas.onmouseout = () => {
        s.universeCanvas.style.cursor = 'default';
    }
    s.universeCanvas.onmouseenter = () => {
        s.universeCanvas.style.cursor = 'crosshair';
    }

    // change the cursor
    s.universeCanvas.style.cursor = 'crosshair';

    // capture keydown events to exit from the mode
    document.addEventListener('keydown', s.modeEscapeEventHandler);

    // capture the first click
    s.universeCanvas.onmousedown = (e) => {
        // Capture the position of the mouse relative to the origin of the
        //  canvas
        const r = s.universeCanvas.getBoundingClientRect();
        let x = (e.clientX - r.x - s.borderOffset - s.panX) / s.scale;
        let y = (e.clientY - r.y - s.borderOffset - s.panY) / s.scale;

        s.rectFirstClick(x, y);
    }
}

s.rectFirstClick = (x, y) => {
    // create the shape object and push it to the step array
    /** @property shapeStrokeAlpha */
    /** @property shapeFillAlpha */
    /** @property shapeStrokeStyle */
    s.shapeCount++;

    const newRect = new Rect({x: x, y: y, 
        lineWidth:s.lineWidth.value,
        strokeStyle:s.shapeStrokeStyle.value,
        fillStyle:s.shapeFillStyle.value, 
        strokeAlpha:s.shapeStrokeAlpha.value,
        fillAlpha:s.shapeFillAlpha.value, 
        stroke:s.mStrokeShapes, 
        fill:s.mFillShapes,
        lineCap:s.lineCap.select.value,
        lineJoin:s.lineJoin.select.value,

        lineDash:s.lineDash.input.value,
        compOp:s.composite.select.value, 
        stepDisplay:`Rect ${s.shapeCount}`,
    });
    s.stepArray.push(newRect);
    s.stepListRow.update();

    // update the line to coords and drawAll for every mousemove event
    const r = s.universeCanvas.getBoundingClientRect();
    s.universeCanvas.onmousemove = (e) => {
        const x3 = (e.clientX - r.x - s.borderOffset - s.panX) / s.scale;
        const y3 = (e.clientY - r.y - s.borderOffset - s.panY) / s.scale;

        newRect.width  = x + x3;
        newRect.height = y + y3;

        const x2 = x3;
        const y2 = y;
        const x4 = x;
        const y4 = y3;

        [newRect.x, newRect.y]   = s.rotate(0, 0,  x,  y, -s.rotation);
        [newRect.x2, newRect.y2] = s.rotate(0, 0, x2, y2, -s.rotation);
        [newRect.x3, newRect.y3] = s.rotate(0, 0, x3, y3, -s.rotation);
        [newRect.x4, newRect.y4] = s.rotate(0, 0, x4, y4, -s.rotation);

        s.drawAll();
    }

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown', newRect.createEscapeEventHandler);

    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown', newRect.createEscapeEventHandler);
        s.rectMode();
    }
}
