const s = {};

onload = () => {
    s.shapeIndex = s.globalZoom = s.mx = s.my = 0;
    s.sWheel = s.rWheel = false;

    s.setupControls();
    s.makeShapes();

    // make the shape options for the select
    s.shapeList.forEach(sh => {
        const newOption = document.createElement('option');
        s.shapeSelect.appendChild(newOption);
        newOption.textContent = sh.name;
    });




    // setup mouse stuff
    s.mainCanvas.onmousemove = (e) => {
        [s.mx, s.my] = s.mousePositionReversed(e);
        s.drawAll();
    }
    s.drawMouse = true;
    s.mainCanvas.onmouseover = () => {
        s.drawMouse = true;
        s.drawAll();
    }
    s.mainCanvas.onmouseout = () => {
        s.drawMouse = false;
        s.drawAll();
    }

    s.setupOnWheel();
    s.drawAll();
}











s.setupControls = () => {
    const g = function(id) { return document.getElementById(id); }

    s.shapeSelect          = g('shapeSelect');
    const globalPanXRange  = g('globalPanXRange');
    const globalPanYRange  = g('globalPanYRange');
    const globalRotRange   = g('globalRotRange');
    const globalScaleRange = g('globalScaleRange');

    // global
    s.globalPanX     = parseFloat(globalPanXRange.value);
    s.globalPanY     = parseFloat(globalPanYRange.value);
    s.globalRotation = parseFloat(globalRotRange.value) / 100;
    s.globalScale    = parseFloat(globalScaleRange.value) / 100;
    s.tx = s.globalPanX;
    s.ty = s.globalPanY;

    s.mainCanvas = g('mainCanvas');
    s.ctx = s.mainCanvas.getContext('2d');
    s.ctx.strokeStyle = 'black';

    g('shapePanXRange').oninput   = e => { s.panXInput(e); }
    g('shapePanYRange').oninput   = e => { s.panYInput(e); }
    g('shapeRotRange').oninput    = e => { s.rotInput(e); }
    g('shapeScaleRange').oninput  = e => { s.scaleInput(e); }

    globalPanXRange.oninput  = e => { s.panXInput(e, true); }
    globalPanYRange.oninput  = e => { s.panYInput(e, true); }
    globalRotRange.oninput   = e => { s.rotInput(e, true); }
    globalScaleRange.oninput = e => { s.scaleInput(e, true); }
}










s.makeShapes = () => {
    s.shapeList = [];

    const oneDegree = Math.PI / 180;
    s.shapeList.push(new Line({p1x:-20, p1y:10, p2x:-10, p2y:40, panX:100,
        panY:100, scale:1, rotation:oneDegree * 34}));
    s.shapeList.push(new Line({p1x:45, p1y:32, p2x:32, p2y:0, panX:50,
        panY:-50, scale:1.3, rotation:oneDegree * 147}));
    s.shapeList.push(new Rect({height:10, width:20, panX:20, panY:-20,
        scale:4, rotation:oneDegree * 35}));
    s.shapeList.push(new Rect({height:10, width:30, panX:-30, panY:-50,
        scale:2.3, rotation:oneDegree * 340}));
    s.shapeList.push(new Text({text:'John T. Vonachen', p1x:0, p1y:0, panX:5,
        panY:30, scale:2.4, rotation:oneDegree * 340}));
    s.shapeList.push(new Text({text:'Kaleb', p1x:0, p1y:0, panX:-20,
        panY:40, scale:10, rotation:oneDegree * 10}));

    // add more shapes here
}

s.setupOnWheel = () => {
    s.mainCanvas.onwheel = (e) => {
        const increment = e.deltaY / 100;
        if(e.altKey) {
            // rotate
            s.rotationIncrement = increment * (Math.PI / 180) * 5;
            s.globalRotation += s.rotationIncrement;
            s.rWheel = true;
        } else {
            // zoom
            s.globalZoom += increment;
            s.scaleIncrement = increment;
            s.globalScale = s.zoomToScale(s.globalZoom);
            s.sWheel = true;
        }
        s.drawAll();
        s.sWheel = s.rWheel = false;
    }
}

s.drawCross = (x, y) => {
    s.ctx.beginPath();
    s.ctx.moveTo(x, y - 10);
    s.ctx.lineTo(x, y + 10);
    s.ctx.stroke();
    s.ctx.moveTo(x - 10, y);
    s.ctx.lineTo(x + 10, y);
    s.ctx.stroke();
}






s.drawAll = () => {
    s.ctx.clearRect(0, 0, s.mainCanvas.width, s.mainCanvas.height);

    // show where the global pan point is without any panning or scaling
    s.drawCross(s.globalPanX, s.globalPanY);

    if(s.sWheel) {
        s.ctx.translate(s.mx, s.my);
        s.ctx.scale(s.scaleIncrement, s.scaleIncrement);
        s.ctx.translate(-s.mx, -s.my);
    }
    if(s.rWheel) {
        s.ctx.translate(s.mx, s.my);
        s.ctx.rotate(s.rotationIncrement);
        s.ctx.translate(-s.mx, -s.my);
    }

    // draw everything else with panning and scaling
    s.ctx.save();
        s.ctx.translate(s.globalPanX, s.globalPanY);
        s.ctx.scale(s.globalScale, s.globalScale); // always scale equally
        s.ctx.rotate(s.globalRotation);

        if(s.drawMouse) s.drawCross(s.mx, s.my);


        // SELECT SHAPE HERE
        s.shapeList.forEach(sh => {
            if(Math.sqrt(
                Math.pow(sh.panX - s.mx, 2) +
                Math.pow(sh.panY - s.my, 2)
            ) < 5) {
                sh.draw("#FF0000");
            } else {
                sh.draw("#000000");
            }
        });
    s.ctx.restore();
}

s.panXInput = (e, global) => {
    // the value from either the global rotation range input or the shape
    //  rotation range input
    const val = parseFloat(e.target.value);

    if(global) {
        s.globalPanX = val;
    } else {
        s.shapeList.find(function(sh) {
            return sh.name === s.shapeSelect.value;
        }).panX = val;
    }
    s.drawAll();
}

s.panYInput = (e, global) => {
    // the value from either the global rotation range input or the shape
    //  rotation range input
    const val = parseFloat(e.target.value);

    if(global) {
        s.globalPanY = val;
    } else {
        s.shapeList.find(function(sh) {
            return sh.name === s.shapeSelect.value;
        }).panY = val;
    }
    s.drawAll();
}

s.rotInput = (e, global) => {
    // the value from either the global rotation range input or the shape
    //  rotation range input
    const val = parseFloat(e.target.value) / 100;

    if(global) {
        s.globalRotation = val;
    } else {
        s.shapeList.find(function(sh) {
            return sh.name === s.shapeSelect.value;
        }).rotation = val;
    }
    s.drawAll();
}

s.scaleInput = (e, global) => {
    // the value from either the global rotation range input or the shape
    //  rotation range input
    const val = s.zoomToScale(parseFloat(e.target.value) / 100);

    if(global) {
        s.globalScale = val;
    } else {
        s.shapeList.find(function(sh) {
            return sh.name === s.shapeSelect.value;
        }).scale = val;
    }
    s.drawAll();
}

s.zoomToScale = (zoom) => {
    return Math.pow(1.1, zoom);
}

// The mouses position with reversed global transforms, so it can be drawn
s.mousePositionReversed = (e) => {
    // find the mouse position
    const r = s.mainCanvas.getBoundingClientRect();
    let x = e.clientX - r.x - 2;
    let y = e.clientY - r.y - 2;

    // reverse the angle
    let angle = Math.atan2(y - s.globalPanY, x - s.globalPanX) -
        s.globalRotation;
    [x, y] = s.rotate(s.globalPanX, s.globalPanY, x, y, angle);

    // reverse the scale
    x /= s.globalScale;
    y /= s.globalScale;

    return [x, y];
}

s.rotate = (cx, cy, ox, oy, angle) => {
    const distance = Math.sqrt((ox - cx)**2 + (oy - cy)**2);
    const x = Math.cos(angle) * distance;
    const y = Math.sin(angle) * distance;
    return [x, y];
}
