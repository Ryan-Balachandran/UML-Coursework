const g = function(id) { return document.getElementById(id); }

const drawRectangle = function() {
    const drCanvas = g('drCanvas');
    const ctx = drCanvas.getContext('2d');
    ctx.fillStyle = 'rgba(0, 0, 255, 1.0)';
    ctx.fillRect(120, 10, 150, 150);
}

const helloCanvas = function() {
    const canvas = g('helloCanvas');
    const colorSelect = g('colorSelect');

    const gl = getWebGLContext(canvas);

    const clear = function() {
        const c = JSON.parse(colorSelect.value);
        gl.clearColor(c.r, c.g, c.b, c.a);
        gl.clear(gl.COLOR_BUFFER_BIT);
    }

    colorSelect.onchange = clear;
    clear();
}

const helloPoint = function() {
    // HelloPoint1.js (c) 2012 Matsuda modified by John T. Vonachen (c) 2022

    const canvas = document.getElementById('hpCanvas');
    const gl = getWebGLContext(canvas);

    let x, y, z, w;
    x = y = z = 0.0;
    w = 1.0;
    const INCREMENT = 0.1;

    g('upButton').onclick    = function() { y += INCREMENT; drawPoint(); }
    g('downButton').onclick  = function() { y -= INCREMENT; drawPoint(); }
    g('leftButton').onclick  = function() { x -= INCREMENT; drawPoint(); }
    g('rightButton').onclick = function() { x += INCREMENT; drawPoint(); }
    g('zupButton').onclick   = function() { z += INCREMENT; drawPoint(); }
    g('zdownButton').onclick = function() { z -= INCREMENT; drawPoint(); }
    g('wupButton').onclick   = function() { w += INCREMENT; drawPoint(); }
    g('wdownButton').onclick = function() { w -= INCREMENT; drawPoint(); }

    const drawPoint = function() {
        g('xSpan').textContent = x;
        g('ySpan').textContent = y;
        g('zSpan').textContent = z;
        g('wSpan').textContent = w;

        const VSHADER_SOURCE =
            'void main() {\n' + // Set the vertex coordinates of the point
            `  gl_Position = vec4(${x}, ${y}, ${z}, ${w});\n` +
            '  gl_PointSize = 10.0;\n' + // Set the point size
            '}\n';
        const FSHADER_SOURCE =
            'void main() {\n' + // Set the point color
            '  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
            '}\n';
        if(!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
            console.log('Failed to initialize shaders.');
            return;
        }

        gl.clearColor(0.0, 0.0, 0.0, 1.0);
        gl.clear(gl.COLOR_BUFFER_BIT);
        gl.drawArrays(gl.POINTS, 0, 1);
    }
    drawPoint();
}

addEventListener('load', function() {
    drawRectangle();
    helloCanvas();
    helloPoint();

    const examplesSelect = g('examplesSelect');

    const changeDiv = function() {
        let div = 0;
        let o;
        while(o = g(`div${div++}`)) {
            o.style.visibility = 'hidden';
            o.style.display = 'none';
        }
        o = g(`div${examplesSelect.value}`);
        o.style.visibility = 'visible';
        o.style.display = 'inline';
    }

    examplesSelect.onchange = changeDiv;
    changeDiv();
});
