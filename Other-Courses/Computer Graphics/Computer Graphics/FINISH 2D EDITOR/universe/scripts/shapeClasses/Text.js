class Text extends Shape {
    constructor(p) {
        super(p);

        this.text       = p.text;
        this.x          = p.x;
        this.y          = p.y;
        this.maxWidth   = p.maxWidth;
        this.fontSize   = p.fontSize;
        this.fontFamily = p.fontFamily;

        this.updateFontAspects(this.fontSize);
    }

    updateFontAspects(size) {
        return `${size}px  ${this.fontFamily}`
    }

    draw() {
        super.draw();

        let x, y;

        [x, y] = s.rotate(0, 0, this.x, this.y, s.rotation);

        x = x * this.scale * s.scale + this.panX + s.panX;
        y = y * this.scale * s.scale + this.panY + s.panY;
        const maxWidth = this.maxWidth * this.scale * s.scale;

        s.ctx.font = this.updateFontAspects(this.fontSize * this.scale *
            s.scale);
        s.ctx.save();
        s.ctx.translate(x, y);
        s.ctx.rotate(-s.rotation);
        if(this.fill) s.ctx.fillText(this.text, x, y, maxWidth);
        if(this.stroke) s.ctx.strokeText(this.text, x, y, maxWidth);
        s.ctx.restore();

        super.postDraw();
    }

    createEscapeEventHandler(e) {
        super.createEscapeEventHandler(e);
        if(e.code === 'Escape') s.textMode();
    }

    edit() {
        super.edit();
        // TBD
    }
}

s.textMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['lineCap', 'lineJoin'];
    const enableList = ['textShape', 'fontSize', 'fontFamily', 'shapeFillStyle',
        'shapeFillAlpha', 'shapeStrokeStyle', 'shapeStrokeAlpha', 'lineWidth',
        'composite', 'fillNStrokeButtonsRow', 'lineDash'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'text';
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

        s.textFirstClick(x, y);
    }
}

s.textFirstClick = (x, y) => {
    // create the shape object and push it to the step array
    /** @property textShape */
    s.shapeCount++;

    const newText = new Text({x: x, y: y, lineWidth:s.lineWidth.value,
        strokeStyle:s.shapeStrokeStyle.value, text:s.textShape.input.value,
        fillStyle:s.shapeFillStyle.value, lineCap:s.lineCap.select.value,
        strokeAlpha:s.shapeStrokeAlpha.value, fontSize:s.fontSize.value,
        fillAlpha:s.shapeFillAlpha.value, lineDash:s.lineDash.input.value,
        compOp:s.composite.select.value, stepDisplay:`Text ${s.shapeCount}`,
        stroke:s.mStrokeShapes, fill:s.mFillShapes,
        fontFamily:s.fontFamily.select.value
    });
    s.stepArray.push(newText);
    s.stepListRow.update();

    // update the line to coords and drawAll for every mousemove event
    const r = s.universeCanvas.getBoundingClientRect();
    s.universeCanvas.onmousemove = (e) => {
        let x = (e.clientX - r.x - s.borderOffset - s.panX) / s.scale;
        let y = (e.clientY - r.y - s.borderOffset - s.panY) / s.scale;
        [x, y] = s.rotate(0, 0, x, y, -s.rotation);

        newText.maxWidth = x - newText.x;

        s.drawAll();
    }

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown', newText.createEscapeEventHandler);

    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown',
            newText.createEscapeEventHandler);
        s.textMode();
    }
}
