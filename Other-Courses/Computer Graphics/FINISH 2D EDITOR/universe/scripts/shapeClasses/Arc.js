class Arc extends Shape{
    constructor(p) {
        super(p);

        this.centerX          = p.x; // where in main canvas to draw circle
        this.centerY          = p.y;
        this.radius           = p.radius;
        this.startAngle       = p.startAngle;
        this.endAngle         = p.endAngle;
        this.counterclockwise = p.counterclockwise;
    }

    draw() {
        super.draw();

        let x, y;

        [x, y] = s.rotate(0, 0, this.centerX, this.centerY, s.rotation);

        x = x * this.scale * s.scale + this.panX + s.panX;
        y = y * this.scale * s.scale + this.panY + s.panY;
        const radius = this.radius * this.scale * s.scale;

        s.ctx.setLineDash(this.ldn);

        s.ctx.beginPath();
        s.ctx.arc(x, y, radius, this.startAngle - s.rotation,
            this.endAngle - s.rotation,
            this.counterclockwise);
        if(this.stroke) s.ctx.stroke();
        if(this.fill) s.ctx.fill();
        super.postDraw();
    }

    createEscapeEventHandler(e) {
        super.createEscapeEventHandler(e);
        if(e.code === 'Escape') s.arcMode();
    }
}

s.arcMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['textShape', 'fontSize', 'fontFamily'];
    const enableList = ['shapeFillStyle', 'shapeFillAlpha', 'shapeStrokeStyle',
        'shapeStrokeAlpha', 'lineWidth', 'lineCap', 'lineDash', 'composite',
        'fillNStrokeButtonsRow', 'lineJoin'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'arc';
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
        [x, y] = s.rotate(0, 0, x, y, -s.rotation);

        s.arcFirstClick(x, y);
    }
}

s.arcFirstClick = (x, y) => {
    // create the shape object and push it to the step array
    s.shapeCount++;

    const newArc = new Arc({x: x, y: y,
        lineWidth:s.lineWidth.value, 
        strokeStyle:s.shapeStrokeStyle.value,
        strokeAlpha:s.shapeStrokeAlpha.value, 
        fillStyle:s.shapeFillStyle.value, 
        fillAlpha:s.shapeFillAlpha.value,

        lineCap:s.lineCap.select.value,
        lineDash:s.lineDash.input.value,
        compOp:s.composite.select.value, 
        stepDisplay:`Arc ${s.shapeCount}`,
        counterclockwise:false, 
        startAngle:s.rotation, endAngle:Math.PI * 2,
        stroke:s.mStrokeShapes, 
        fill:s.mFillShapes
    });
    s.stepArray.push(newArc);
    /** @property stepListRow */
    s.stepListRow.update();

    const findAngle = function(a, b, c) {
        const ab = Math.sqrt((b.x - a.x)**2 + (b.y - a.y)**2);
        const bc = Math.sqrt((b.x - c.x)**2 + (b.y - c.y)**2);
        const ac = Math.sqrt((c.x - a.x)**2 + (c.y - a.y)**2);
        return Math.acos((bc * bc + ab * ab - ac * ac) / (2 * bc * ab));
    }

    // update the line to coords and drawAll for every mousemove event
    const r = s.universeCanvas.getBoundingClientRect();
    s.universeCanvas.onmousemove = (e) => {
        let mx = (e.clientX - r.x - s.borderOffset - s.panX) / s.scale;
        let my = (e.clientY - r.y - s.borderOffset - s.panY) / s.scale;

        [mx, my] = s.rotate(0, 0, mx, my, -s.rotation);

        newArc.radius = Math.sqrt((newArc.centerX - mx)**2 + (newArc.centerY - my)**2);
        newArc.endAngle = 0;
        let scalar = 1;
        if(my < newArc.centerY) {
            newArc.endAngle = 0;
            scalar = -1
        }
        newArc.endAngle += scalar * findAngle(
            {x:mx, y:my},
            {x:newArc.centerX, y:newArc.centerY},
            {x:newArc.centerX + newArc.radius, y:newArc.centerY}
        );

        s.drawAll();
    }

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown', newArc.createEscapeEventHandler);


    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown',
            newArc.createEscapeEventHandler);
        s.arcMode();
    }
}