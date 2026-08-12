const s = {};

const g = function(id) { return document.getElementById(id); }

class Line {
    constructor(p) {
        this.name = `line${s.shapeIndex++}`;
        this.p1x = p.p1x;
        this.p1y = p.p1y;
        this.p2x = p.p2x;
        this.p2y = p.p2y;

        this.panX = p.panX
        this.panY = p.panY
        this.scale = p.scale;
        this.rotation = p.rotation;
    }

    // the local draw function
    draw() {
        s.ctx.save();
        s.ctx.translate(this.panX, this.panY);
        s.ctx.scale(this.scale, this.scale); // always scale equally
        s.ctx.rotate(this.rotation);

        s.ctx.setLineDash([1, 1]);
        s.ctx.beginPath();
        s.ctx.moveTo(this.p1x, this.p1y);
        s.ctx.lineTo(this.p2x, this.p2y);
        s.ctx.stroke();
        s.ctx.restore();
    }
}

class Rect {
    constructor(p) {
        this.name = `rect${s.shapeIndex++}`;
        this.p1x = p.p1x;
        this.p1y = p.p1y;
        this.width = p.width;
        this.height = p.height;

        this.panX = p.panX
        this.panY = p.panY
        this.scale = p.scale;
        this.rotation = p.rotation;
    }

    // the local draw function
    draw() {
        s.ctx.save();
        s.ctx.translate(this.panX, this.panY);
        s.ctx.scale(this.scale, this.scale); // always scale equally
        s.ctx.rotate(this.rotation);

        s.ctx.beginPath();
        s.ctx.strokeRect(this.p1x, this.p1y, this.width, this.height);
        s.ctx.restore();
    }
}

class Text {
    constructor(p) {
        this.name = `text${s.shapeIndex++}`;
        this.text = p.text;
        this.p1x = p.p1x;
        this.p1y = p.p1y;

        this.panX = p.panX
        this.panY = p.panY
        this.scale = p.scale;
        this.rotation = p.rotation;
    }

    // the local draw function
    draw() {
        s.ctx.save();
        s.ctx.translate(this.panX, this.panY);
        s.ctx.scale(this.scale, this.scale); // always scale equally
        s.ctx.rotate(this.rotation);

        s.ctx.beginPath();
        s.ctx.strokeText(this.text, this.p1x, this.p1y);
        s.ctx.restore();
    }
}

const drawAll = () => {
    s.ctx.clearRect(0, 0, s.mainCanvas.width, s.mainCanvas.height);

    // show where the global pan point is without any panning or scaling
    s.ctx.beginPath();
    s.ctx.moveTo(s.globalPanX, s.globalPanY - 10);
    s.ctx.lineTo(s.globalPanX, s.globalPanY + 10);
    s.ctx.stroke();
    s.ctx.moveTo(s.globalPanX - 10, s.globalPanY);
    s.ctx.lineTo(s.globalPanX + 10, s.globalPanY);
    s.ctx.stroke();

    // draw everything else with panning and scaling
    s.ctx.save();
        s.ctx.translate(s.globalPanX, s.globalPanY);
        s.ctx.scale(s.globalScale, s.globalScale); // always scale equally
        s.ctx.rotate(s.globalRotation);

        // show where the mouse pointer is
        s.ctx.beginPath();
        s.ctx.moveTo(s.mx, s.my - 10);
        s.ctx.lineTo(s.mx, s.my + 10);
        s.ctx.stroke();
        s.ctx.beginPath();
        s.ctx.moveTo(s.mx - 10, s.my);
        s.ctx.lineTo(s.mx + 10, s.my);
        s.ctx.stroke();

        s.shapeList.forEach(s => s.draw())
    s.ctx.restore();
}

const panXInput = (e, global) => {
    const val = parseFloat(e.target.value);
    if(global) s.globalPanX = val;
    else s.shapeList.find(function(sh) {
        return sh.name === s.shapeSelect.value;
    }).panX = val;
    drawAll();
}
const panYInput = (e, global) => {
    const val = parseFloat(e.target.value);
    if(global) s.globalPanY = val;
    else s.shapeList.find(function(sh) {
        return sh.name === s.shapeSelect.value;
    }).panY = e.target.value;
    drawAll();
}
const rotInput = (e, global) => {
    const val = parseFloat(e.target.value) / 100;
    if(global) s.globalRotation = val;
    else s.shapeList.find(function(sh) {
        return sh.name === s.shapeSelect.value;
    }).rotation = val;
    drawAll();
}
const scaleInput = (e, global) => {
    const val = parseFloat(e.target.value) / 100;
    if(global) s.globalScale = s.zoomToScale(val);
    else s.shapeList.find(function(sh) {
        return sh.name === s.shapeSelect.value;
    }).scale = s.zoomToScale(val);
    drawAll();
}

onload = () => {
    s.shapeIndex = 0;
    s.globalZoom = 0;

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

    s.mainCanvas = g('mainCanvas');
    s.ctx = s.mainCanvas.getContext('2d');
    s.ctx.strokeStyle = 'black';

    g('shapePanXRange').oninput   = e => { panXInput(e); }
    g('shapePanYRange').oninput   = e => { panYInput(e); }
    g('shapeRotRange').oninput    = e => { rotInput(e); }
    g('shapeScaleRange').oninput  = e => { scaleInput(e); }
    globalPanXRange.oninput  = e => { panXInput(e, true); }
    globalPanYRange.oninput  = e => { panYInput(e, true); }
    globalRotRange.oninput   = e => { rotInput(e, true); }
    globalScaleRange.oninput = e => { scaleInput(e, true); }

    s.shapeList = [];
    s.shapeList.push(new Line({p1x:-10, p1y:0, p2x:10, p2y:0, panX:0, panY:0, scale:1, rotation:0}));
    s.shapeList.push(new Line({p1x:-10, p1y:0, p2x:10, p2y:0, panX:0, panY:0, scale:1, rotation:0}));
    s.shapeList.push(new Rect({p1x:-10, p1y:0, height:10, width:20, panX:0, panY:0, scale:1, rotation: 0}));
    s.shapeList.push(new Rect({p1x:-10, p1y:0, height:10, width:30, panX:0, panY:0, scale:1, rotation: 0}));
    s.shapeList.push(new Text({text:'John T. Vonachen', p1x:0, p1y:0, panX:0, panY:0, scale:1, rotation: 0}));
    s.shapeList.push(new Text({text:'Kaleb', p1x:0, p1y:0, panX:0, panY:0, scale:1, rotation:0}));
    // add more shapes here

    s.shapeList.forEach(sh => {
        const newOption = document.createElement('option');
        s.shapeSelect.appendChild(newOption);
        newOption.textContent = sh.name;
    });

    s.mx = s.globalPanX;
    s.my = s.globalPanY;
    s.mainCanvas.onmousemove = (e) => {
        [s.mx, s.my] = s.mousePosition(e);

        drawAll();
    }

    s.mainCanvas.onwheel = (e) => {
        // rotate
        if(e.altKey) {
            const rotationIncrement = (e.deltaY / 100) * (Math.PI / 180);
            s.globalRotation += rotationIncrement;
            [s.globalPanX, s.globalPanY] = s.rotate(s.mx, s.my, s.globalPanX,
                s.globalPanY, -s.globalRotation);
        }
        // zoom
        else {
            const zoomIncrement = e.deltaY / 100;
            const scaleIncrement = s.zoomToScale(zoomIncrement);
            s.globalZoom += zoomIncrement;
            s.globalScale += scaleIncrement; // This one zoom

            // move the global pan coords to or away from the current mouse pos
            // the unmodified mouse position
            const r = s.mainCanvas.getBoundingClientRect();
            let mx = e.clientX - r.x - 2;
            let my = e.clientY - r.y - 2;
            // distance from the global pan to the mouse pos
            let distance = Math.sqrt((s.globalPanX - mx)**2 +
                (s.globalPanY - my)**2);
            // adjust the distance
            distance *= scaleIncrement;
            // find the angle from the global pan to the mouse pos
            let angle = Math.atan2(my - s.globalPanY,
                mx - s.globalPanX);
            s.globalPanX = Math.cos(angle) * distance;
            s.globalPanY = Math.sin(angle) * distance;
        }

        [s.mx, s.my] = s.mousePosition(e);

        drawAll();
    }

    drawAll();
}

s.zoomToScale = (zoom) => {
    return Math.pow(1.1, zoom);
}

s.mousePosition = (e) => {
    // find the mouse position
    const r = s.mainCanvas.getBoundingClientRect();
    let x = e.clientX - r.x - 2;
    let y = e.clientY - r.y - 2;

    // reverse the angle
    let angle = Math.atan2(y - s.globalPanY, x - s.globalPanX) -
        s.globalRotation;
    [x, y] = s.rotate(s.globalPanX, s.globalPanY, x, y, angle);

    // reverse the scale
    return [x / s.globalScale, y / s.globalScale]
}

s.rotate = (cx, cy, ox, oy, angle) => {
    const distance = Math.sqrt((ox - cx)**2 + (oy - cy)**2);
    const x = Math.cos(angle) * distance;
    const y = Math.sin(angle) * distance;
    return [x, y];
}
