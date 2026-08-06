const s = {};

s.WIDTH = 500;
s.HEIGHT = 500;
s.CHANNELS = 4;

s.putPixel = (id, x, y, c) => {
    let p = s.CHANNELS * s.WIDTH * (y - 1) + x * s.CHANNELS;
    const d = id.data;
    d[p++] = c.r;
    d[p++] = c.g;
    d[p++] = c.b;
    d[p] = c.a;
}

s.getPixel = (id, x, y) => {
    let p = s.CHANNELS * s.WIDTH * (y - 1) + x * s.CHANNELS;
    const d = id.data;
    return { r:d[p++], g:d[p++], b:d[p++], a:d[p] };
}

s.clear = (id, c) => {
    for(let x = 0; x < s.WIDTH; x++) {
        for(let y = 0; y < s.HEIGHT; y++) {
            s.putPixel(id, x, y, c);
        }
    }
}

s.line = (id, p1, p2, c) => {
    const dx = p2.x - p1.x;
    const dy = p2.y - p1.y;
    const steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);
    const xInc = dx / steps;
    const yInc = dy / steps;

    let x = p1.x;
    let y = p1.y;
    for (let i = 0; i <= steps; i++) {
        s.putPixel(id, Math.floor(x), Math.floor(y), c);
        x += xInc;
        y += yInc;
    }
}

s.randomLines = (id, n, c) => {
    for(let i = 0; i < n; i++) {
        s.line(id, {x:s.randomX(), y:s.randomY()}, {x:s.randomX(),
            y:s.randomY()}, c);
    }
}

s.randomX  = () => { return Math.floor(Math.random() * s.WIDTH) };
s.randomY  = () => { return Math.floor(Math.random() * s.HEIGHT) };
s.randomCC = () => { return Math.floor(Math.random() * 256) };

s.noise = (id, step, a) => {
    for(let x = 0; x < s.WIDTH; x += step) {
        for(let y = 0; y < s.HEIGHT; y += step) {
            s.putPixel(id, x, y, {r:s.randomCC(),
                g:s.randomCC(), b:s.randomCC(), a:a}
            );
        }
    }
}

s.averageFade = (ctx, id, denominator) => {
    const secondImageData = ctx.createImageData(s.WIDTH, s.HEIGHT);

    for(let x = 1; x < s.WIDTH - 1; x++) {
        for(let y = 1; y < s.HEIGHT - 1; y++) {
            const sum = {r:0, g:0, b:0};
            const avg = {r:0, g:0, b:0};
            for(let sx = -1; sx < 2; sx++) {
                for(let sy = -1; sy < 2; sy++) {
                    const p = s.getPixel(id, x + sx, y + sy);
                    sum.r += p.r;
                    sum.g += p.g;
                    sum.b += p.b;
                }
            }
            avg.r = Math.round(sum.r / denominator);
            avg.g = Math.round(sum.g / denominator);
            avg.b = Math.round(sum.b / denominator);
            avg.a = 255;
            s.putPixel(secondImageData, x, y, avg);
        }
    }
    ctx.putImageData(secondImageData, 0, 0);
    secondImageData.data.forEach((e, i) => id.data[i] = e);
}

s.randomWhitePixels = (id) => {
    for(let i = 0; i < 100; i++) {
        s.putPixel(id, s.randomX(), s.randomY(),
            {r: 255, g: 255, b: 255, a: 255});
    }
}

s.brensenham = (id, p1, p2, c) => {
    const dx = Math.abs(p2.x - p1.x);
    const sx = p1.x < p2.x ? 1 : -1;
    const dy = -Math.abs(p2.y - p1.y);
    const sy = p1.y < p2.y ? 1 : -1;

    let err = dx + dy;

    while (true) {
        s.putPixel(id, p1.x, p1.y, c);

        if(p1.x === p2.x && p1.y === p2.y) break;
        const e2 = 2 * err;
        if(e2 >= dy) {
            if(p1.x === p2.x) break;
            err += dy;
            p1.x += sx;
        }
        if(e2 <= dx) {
            if(p1.y === p2.y) break;
            err += dx;
            p1.y += sy;
        }
    }
}

s.randomBLines = (id, n, c) => {
    for(let i = 0; i < n; i++) {
        s.brensenham(id, {x:s.randomX(), y:s.randomY()}, {x:s.randomX(),
            y:s.randomY()}, c);
    }
}

s.compare = (id, c) => {
    const iterations = 1000000;

    // This one should be slower
    let start = Date.now();
    for(let i = 0; i < iterations; i++) {
        s.line(id, {x:s.randomX(), y:s.randomY()}, {x:s.randomX(),
            y:s.randomY()}, c);
    }
    const first = Date.now() - start;

    // This one should be faster...but it was not *shrug*
    //  For 1,000,000 lines it took on average a second longer.
    start = Date.now();
    for(let i = 0; i < iterations; i++) {
        s.brensenham(id, {x:s.randomX(), y:s.randomY()}, {x:s.randomX(),
            y:s.randomY()}, c);
    }
    const second = Date.now() - start;
    document.getElementById('displaySpan').textContent =
        `diff: ${first - second}`;
}

s.ellipse = (id, a, b, c) => {
    for(let x = -a; x < a; x += 0.01) {
        const y = Math.sqrt(
            1 - (
                (Math.pow(x, 2) / Math.pow(a, 2))
            ) * (Math.pow(b, 2))
        );
        s.putPixel(id, 250 + x, 250 + y, c);
        s.putPixel(id, 250 - x, 250 + y, c);
    }
}

onload = () => {
    const mainCanvas = document.getElementById('mainCanvas');
    mainCanvas.width = s.WIDTH;
    mainCanvas.height = s.HEIGHT;
    mainCanvas.style.border = 'solid';

    const ctx = mainCanvas.getContext('2d');
    const myImageData = ctx.createImageData(s.WIDTH, s.HEIGHT);
    const opaqueBlack = {r:0, b:0, g:0, a:255};
    const opaqueWhite = {r:255, g:255, b:255, a:255};

    s.clear(myImageData, opaqueWhite);

    document.getElementById('randomBlackLineButton').onclick = () => {
        s.randomLines(myImageData, 1, opaqueBlack);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('randomWhiteBrensenhamLineButton').onclick = () => {
        s.randomBLines(myImageData, 1, opaqueWhite);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('clearWhiteButton').onclick = () => {
        s.clear(myImageData, opaqueWhite);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('clearBlackButton').onclick = () => {
        s.clear(myImageData, opaqueBlack);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('noiseButton').onclick = () => {
        s.noise(myImageData, 1, 255);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('averageFadeButton').onclick = () => {
        s.averageFade(ctx, myImageData, 9);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('randomWhitePixelsButton').onclick = () => {
        s.randomWhitePixels(myImageData, 100);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('compareButton').onclick = () => {
        s.compare(myImageData, opaqueWhite);
        ctx.putImageData(myImageData, 0, 0);
    }
    document.getElementById('ellipseButton').onclick = () => {
        s.ellipse(myImageData, 100, 50, opaqueWhite);
        ctx.putImageData(myImageData, 0, 0);
    }
}
