class Line extends Shape 
{
    constructor(p) 
    {
        super(p);

        // parameters passed in
        this.x1 = p.x1;
        this.y1 = p.y1;
        this.x2 = p.x2;
        this.y2 = p.y2;
    }

    draw() {
        super.draw();

        s.ctx.save();
        s.ctx.translate(this.panX, this.panY);
        s.ctx.scale(this.scale, this.scale); // always scale equally
        s.ctx.rotate(this.rotation);

        s.ctx.beginPath();
        s.ctx.moveTo(this.x1, this.y1);
        s.ctx.lineTo(this.x2, this.y2);
        s.ctx.stroke();
        s.ctx.restore();

        super.postDraw();
    }

    createEscapeEventHandler(e) {
        super.createEscapeEventHandler(e);
        if(e.code === 'Escape') s.lineMode();
    }
}

s.lineMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['shapeFillStyle', 'shapeFillAlpha', 'textShape',
        'fontSize', 'fontFamily', 'fillNStrokeButtonsRow', 'lineJoin'];
    const enableList = ['shapeStrokeStyle', 'shapeStrokeAlpha', 'lineWidth',
        'lineCap', 'lineDash', 'composite'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'line';
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
        let [x, y] = s.mousePosition(e);
        s.lineFirstClick(x, y);
    }
}

s.lineFirstClick = (x, y) => {
    // create the shape object and push it to the step array
    /** @property shapeAlpha */
    /** @property shapeStrokeStyle */
    /** @property shapeFillStyle */
    s.shapeCount++;

    const newLine = new Line({x1: x, y1: y, x2: x, y2: y,
        lineWidth:s.lineWidth.value, 
        strokeStyle:s.shapeStrokeStyle.value,
        fillStyle:s.shapeFillStyle.value, 
        fillAlpha:s.shapeFillAlpha.value, 
        strokeAlpha:s.shapeStrokeAlpha.value,
        lineCap:s.lineCap.select.value,

        lineDash:s.lineDash.input.value, 
        compOp:s.composite.select.value,
        stepDisplay:`Line ${s.shapeCount}`
    });
    s.stepArray.push(newLine);
    s.stepListRow.update();

    // update the line to coords and drawAll for every mousemove event
    s.universeCanvas.onmousemove = (e) => {
        [newLine.x2, newLine.y2] = s.mousePosition(e);
        s.drawAll();
    }

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown', newLine.createEscapeEventHandler);

    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown', newLine.createEscapeEventHandler);
        s.lineMode();
    }
}
