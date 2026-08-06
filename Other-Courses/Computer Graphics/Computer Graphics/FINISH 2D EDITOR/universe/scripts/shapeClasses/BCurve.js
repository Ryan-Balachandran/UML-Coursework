class BCurve extends Shape {
    constructor(p) {
        super(p);

        this.mx  = p.mx;
        this.my  = p.my;
        this.c1x = p.c1x;
        this.c1y = p.c1y;
        this.c2x = p.c2x;
        this.c2y = p.c2y;
        this.ex  = p.ex;
        this.ey  = p.ey;
    }

    draw() {
        super.draw();

        let mx, my, c1x, c1y, c2x, c2y, ex, ey;

        [mx, my] = s.rotate(0, 0, this.mx, this.my, s.rotation);
        [c1x, c1y] = s.rotate(0, 0, this.c1x, this.c1y, s.rotation);
        [c2x, c2y] = s.rotate(0, 0, this.c2x, this.c2y, s.rotation);
        [ex, ey] = s.rotate(0, 0, this.ex, this.ey, s.rotation);

        mx = mx * this.scale * s.scale + this.panX + s.panX;
        my = my * this.scale * s.scale + this.panY + s.panY;
        c1x = c1x * this.scale * s.scale + this.panX + s.panX;
        c1y = c1y * this.scale * s.scale + this.panY + s.panY;
        c2x = c2x * this.scale * s.scale + this.panX + s.panX;
        c2y = c2y * this.scale * s.scale + this.panY + s.panY;
        ex = ex * this.scale * s.scale + this.panX + s.panX;
        ey = ey * this.scale * s.scale + this.panY + s.panY;

        s.ctx.setLineDash(this.ldn);

        s.ctx.beginPath();
        s.ctx.moveTo(mx, my);
        s.ctx.bezierCurveTo(c1x, c1y, c2x, c2y, ex, ey);
        if(this.stroke) s.ctx.stroke();
        if(this.fill) s.ctx.fill();

        super.postDraw();
    }

    createEscapeEventHandler(e) {
        super.createEscapeEventHandler(e);
        if(e.code === 'Escape') s.bCurveMode();
    }
}

s.bCurveMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['textShape', 'fontSize', 'fontFamily'];
    const enableList = ['shapeFillStyle', 'shapeFillAlpha', 'shapeStrokeStyle',
        'shapeStrokeAlpha', 'lineWidth', 'lineCap', 'lineDash', 'composite',
        'fillNStrokeButtonsRow', 'lineJoin'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'bCurve';
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

        s.bCurveFirstClick(x, y);
    }
}

s.bCurveFirstClick = (x, y) => {
    // create the shape object and push it to the step array
    s.shapeCount++;

    const newBCurve = new BCurve({mx: x, my: y,
        lineWidth:s.lineWidth.value, strokeStyle:s.shapeStrokeStyle.value,
        fillStyle:s.shapeFillStyle.value, lineCap:s.lineCap.select.value,
        strokeAlpha:s.shapeStrokeAlpha.value, fillAlpha:s.shapeFillAlpha.value,
        lineDash:s.lineDash.input.value,
        compOp:s.composite.select.value, stepDisplay:`bCurve ${s.shapeCount}`,
        counterclockwise:false, startAngle:0, endAngle:Math.PI * 2,
        stroke:s.mStrokeShapes, fill:s.mFillShapes
    });
    s.stepArray.push(newBCurve);
    s.stepListRow.update();

    // update the line to coords and drawAll for every mousemove event
    const r = s.universeCanvas.getBoundingClientRect();
    s.universeCanvas.onmousemove = (e) => {
        let ex = (e.clientX - r.x - s.borderOffset - s.panX) / s.scale;
        let ey = (e.clientY - r.y - s.borderOffset - s.panY) / s.scale;

        [ex, ey] = s.rotate(0, 0, ex, ey, -s.rotation);

        newBCurve.ex = ex;
        newBCurve.ey = ey;
        newBCurve.c1x = (newBCurve.mx + ex) / 2;
        newBCurve.c1y = (newBCurve.my + ey) / 2 + 100 / s.scale;
        newBCurve.c2x = (newBCurve.mx + ex) / 2;
        newBCurve.c2y = (newBCurve.my + ey) / 2 - 100 / s.scale;

        s.drawAll();
    }

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown',
        newBCurve.createEscapeEventHandler);

    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown',
            newBCurve.createEscapeEventHandler);
        s.bCurveMode();
    }
}