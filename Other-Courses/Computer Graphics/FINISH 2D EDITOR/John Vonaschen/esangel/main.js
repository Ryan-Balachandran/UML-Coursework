// Based on examples made by Edward Angel

"use strict";

const s = {}; // The global singleton

// makes selecting more concise
s.g = function(id) { return document.getElementById(id); }

// This gets called second by the callback of the first one below.
s.getVertexShader = function(callback) 
{
    //  Load shaders and initialize attribute buffers
    fetch('shaders/vshader21.glsl')
    .then(x => x.text())
    .then(y => {
        const s = document.createElement('script');
        s.id = "vertex-shader";
        s.type = "x-shader/x-vertex";
        s.textContent = y;
        document.head.appendChild(s);
        callback();
    });
}

// This gets called first and passes the callback to the next one above.  It's
//  important to note that I need not declare the above function expression,
//  above this one instead of below because it's called in a callback and would
//  be defined by the time it's called.
s.getShaders = function(callback) {
    fetch('shaders/fshader21.glsl')
    .then(x => x.text())
    .then(y => {
        const c = document.createElement('script');
        c.id = "fragment-shader";
        c.type = "x-shader/x-fragment";
        c.textContent = y;
        document.head.appendChild(c);
        s.getVertexShader(callback);
    });
}

s.render = function() 
{
    // before clearing and drawing set fragment values
    s.program.fr = s.gl.getUniformLocation(s.program, 'fr');
    s.program.fg = s.gl.getUniformLocation(s.program, 'fg');
    s.program.fb = s.gl.getUniformLocation(s.program, 'fb');
    s.program.fa = s.gl.getUniformLocation(s.program, 'fa');

    const r = parseFloat(s.redRange.value);   /** @property s.redRange */
    const g = parseFloat(s.greenRange.value); /** @property s.greenRange */
    const b = parseFloat(s.blueRange.value);  /** @property s.blueRange */

    s.gl.uniform1f(s.program.fr, r);
    s.gl.uniform1f(s.program.fg, g);
    s.gl.uniform1f(s.program.fb, b); /** @property s.alphaRange */
    s.gl.uniform1f(s.program.fa, parseFloat(s.alphaRange.value));

    // clear and draw - an inverse color with full opacity
    s.gl.clearColor(1 - r, 1 - g, 1 - b, 1.0);
    s.gl.clear(s.gl.COLOR_BUFFER_BIT);
    s.gl.drawArrays(s.gl.POINTS, 0, s.points.length);
}

s.loadDataIntoGPU = function() 
{
    if(!s.program) return;

    // Load the data into the GPU
    s.gl.bindBuffer(s.gl.ARRAY_BUFFER, s.gl.createBuffer());
    s.gl.bufferData(s.gl.ARRAY_BUFFER, flatten(s.points), s.gl.STATIC_DRAW);

    // Associate our shader variables with our data buffer
    const vPosition = s.gl.getAttribLocation(s.program, 'vPosition');
    s.gl.vertexAttribPointer(vPosition, 2, s.gl.FLOAT, false,
        0, 0);
    s.gl.enableVertexAttribArray(vPosition);

    s.program.vPointSize = s.gl.getUniformLocation(s.program,
        'vPointSize');
    /** @property s.PSRange */
    s.gl.uniform1f(s.program.vPointSize, parseFloat(s.PSRange.value));

    s.render();
}

s.changeGeometry = function() {
    const ratio = s.SGCanvas.height / s.SGCanvas.width;
    const third = Math.PI * 2 / 3;
    const rot = parseFloat(s.rotRange.value);   /** @property s.rotRange */
    const zoom = parseFloat(s.zoomRange.value); /** @property s.zoomRange */
    const ox = parseFloat(s.xRange.value);      /** @property s.xRange */
    const oy = parseFloat(s.yRange.value);      /** @property s.yRange */

    // Specify a starting point p for our iterations p must lie inside any set
    //  of three vertices
    const vertices = [
        vec2(
            ox + Math.cos(third + rot) * ratio * zoom,
            oy + Math.sin(third + rot) * zoom
        ),
        vec2(
            ox + Math.cos(third * 2 + rot) * ratio * zoom,
            oy + Math.sin(third * 2 + rot) * zoom
        ),
        vec2(
            ox + Math.cos(third * 3 + rot) * ratio * zoom,
            oy + Math.sin(third * 3 + rot) * zoom
        )
    ];
    const u = add(vertices[0], vertices[1]);
    const v = add(vertices[0], vertices[2]);
    let p = scale(0.25, add(u, v));

    // And, add our initial point into our array of points
    s.points = [p];

    // Compute new points - Each new point is located midway between last point
    //  and a randomly chosen vertex
    /** @property NOPRange */
    for(let i = 0; s.points.length < NOPRange.value; ++i) {
        const j = Math.floor(Math.random() * 3);
        p = add(s.points[i], vertices[j]);
        p = scale(0.5, p);
        s.points.push(p);
    }

    s.loadDataIntoGPU();
}

s.resizeCanvasViewport = function() {
    // the width of the canvas is the innerWidth of window minus the width of
    //  the controlDiv
    const controlDivBCR = s.g('controlDiv').getBoundingClientRect();
    const w = innerWidth - controlDivBCR.width - 50;
    const h = innerHeight - 130;

    s.SGCanvas.width = w;
    s.SGCanvas.height = h;
    s.SGCanvas.style.width = w + 'px';
    s.SGCanvas.style.height = h + 'px';

    s.gl.viewport(0, 0, s.SGCanvas.width, s.SGCanvas.height);

    s.changeGeometry();
}

s.update = function(id, value) {
    s[`${id}Range`].value = value;
    let ds = value.toFixed(2);
    if(ds.length > 6) ds = '';
    s[`${id}RangeTD`].textContent = ds;
}

s.displayUpdate = function(co, then) {
    let ds = parseFloat(co.value).toFixed(2);
    if(ds.length > 6) ds = '';
    s[`${co.id}TD`].textContent = ds;
    then();
}

s.addKeyframe = function() {
    const newRow = s.controlTable.insertRow(s.keyframeButtonRow.rowIndex);
    newRow.value = {
        red:s.redRange.value,
        green:s.greenRange.value,
        blue:s.blueRange.value,
        alpha:s.alphaRange.value,
        PS:s.PSRange.value,
        NOP:s.NOPRange.value,
        x:s.xRange.value,
        y:s.yRange.value,
        rot:s.rotRange.value,
        zoom:s.zoomRange.value
    };
    newRow.title = JSON.stringify(newRow.value);
    let newCell = newRow.insertCell(0);
    let b = document.createElement('button');
    b.style.backgroundColor = 'red';
    b.style.color = 'white';
    b.textContent = 'X';
    b.style.width = '100%';
    newCell.appendChild(b);

    newCell = newRow.insertCell(0);
    b = document.createElement('button');
    b.style.backgroundColor = 'yellow';
    b.textContent = '000.000';
    b.style.width = '100%';
    newCell.appendChild(b);

    newCell = newRow.insertCell(0);
    b = document.createElement('button');
    b.style.backgroundColor = 'blue';
    b.style.color = 'white';
    b.textContent = 'KF';
    b.style.width = '100%';
    newCell.appendChild(b);
}

s.sierpinskiGasket = function() {
    //  Configure WebGL
    s.SGCanvas = s.g( "sierpinskiCanvas" );
    s.gl = WebGLUtils.setupWebGL(s.SGCanvas,
        {premultipliedAlpha: true});
    if(s.gl === null) {
        alert('sierpinskiGasket: call to WebGLUtils.setupWebGL returned null');
        return;
    }
    s.gl.enable(s.gl.BLEND);
    s.gl.blendFuncSeparate(s.gl.SRC_ALPHA, s.gl.ONE_MINUS_SRC_ALPHA, s.gl.ONE,
        s.gl.ONE_MINUS_SRC_ALPHA);

    // do stuff to dom objects
    const list = [{n:'red', d:0, c:0}, {n:'green', d:0, c:0},
        {n:'blue', d:0, c:0}, {n:'alpha', d:1, c:0}, {n:'PS', d:1, c:1},
        {n:'NOP', d:100000, c:2}, {n:'x', d:0, c:2},
        {n:'y', d:0, c:2}, {n:'rot', d:0, c:2}, {n:'zoom', d:1, c:2}];
    list.forEach(i => {
        // assign DOM objects to the singleton
        s[`${i.n}Range`] = s.g(`${i.n}Range`);
        s[`${i.n}RangeTD`] = s.g(`${i.n}RangeTD`);
        // set initial value
        s.update(i.n, i.d);
        // assign oninput event handlers
        switch(i.c) {
            case 0: s[`${i.n}Range`].oninput = function()
                { s.displayUpdate(this, s.render); }; break;
            case 1: s[`${i.n}Range`].oninput = function()
                { s.displayUpdate(this, s.loadDataIntoGPU); }; break;
            case 2: s[`${i.n}Range`].oninput = function()
                { s.displayUpdate(this, s.changeGeometry); }; break;
        }
    })

    // set onclick event handlers
    s.g('randColorButton').onclick = function() {
        s.update('red',   Math.random());
        s.update('green', Math.random());
        s.update('blue',  Math.random());
        s.render();
    };

    s.resizeCanvasViewport();

    s.getShaders(function() {
        s.program = initShaders(s.gl, 'vertex-shader',
            'fragment-shader');
        s.gl.useProgram(s.program);
        s.changeGeometry();
    });

    s.controlTable = s.g('controlTable');
    s.keyframeButtonRow = s.g('keyframeButtonRow');
    s.addKeyframeButton = s.g('addKeyframeButton');
    s.addKeyframeButton.onclick = s.addKeyframe;
}

s.sierpinskiGasket3D = function() {
}

onresize = s.resizeCanvasViewport;

// window is the "this", the context therefore no need to specify it here.
//  Saves keystrokes. :)
onload = function init() {
    const examplesSelect = s.g('examplesSelect');
    const changeDiv = function() {
        let div = 0;
        let o;
        while(o = s.g(`div${div++}`)) {
            o.style.visibility = 'hidden';
            o.style.display = 'none';
        }
        o = s.g(`div${examplesSelect.value}`);
        o.style.visibility = 'visible';
        o.style.display = 'inline';
    }
    examplesSelect.onchange = changeDiv;
    changeDiv();

    s.sierpinskiGasket();
    s.sierpinskiGasket3D();
};
