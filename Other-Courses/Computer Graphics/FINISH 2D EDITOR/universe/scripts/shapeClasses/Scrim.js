class Scrim extends Shape {
    constructor(p) {
        super(p);
    }

    draw() {
        super.draw();
        s.ctx.fillRect(0, 0, s.universeCanvas.width, s.universeCanvas.height);
        super.postDraw();
    }
}

s.scrimMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['textShape', 'fontSize', 'fontFamily',
        'shapeStrokeStyle', 'shapeStrokeAlpha', 'lineWidth', 'lineDash',
        'fillNStrokeButtonsRow', 'lineJoin'];
    const enableList = ['shapeFillStyle', 'shapeFillAlpha', 'composite'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });
    enableList.forEach(c => { s[c].tableRow.style.display = ''; });

    s.shapeSelect.select.value = 'scrim';
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
    s.universeCanvas.onmousedown = () => {
        s.scrimFirstClick();
    }
}

s.scrimFirstClick = () => {
    // create the shape object and push it to the step array
    /** @property shapeStrokeAlpha */
    /** @property shapeFillAlpha */
    /** @property shapeStrokeStyle */
    s.shapeCount++;

    const newScrim = new Scrim({fillStyle:s.shapeFillStyle.value,
        fillAlpha:s.shapeFillAlpha.value, compOp:s.composite.select.value,
        stepDisplay:`Scrim ${s.shapeCount}`, lineDash:''
    });
    s.stepArray.push(newScrim);
    s.stepListRow.update();

    s.drawAll();

    // capture keydown events to exit from the mode
    document.removeEventListener('keydown', s.modeEscapeEventHandler);
    document.addEventListener('keydown', newScrim.createEscapeEventHandler);

    s.universeCanvas.onmouseup = () => {
        s.universeCanvas.onmouseup = undefined;
        document.removeEventListener('keydown',
            newScrim.createEscapeEventHandler);
        s.scrimMode();
    }
}
