class Line 
{
    constructor(p) 
    {
        this.name = `line${s.shapeIndex++}`;

        // normalize the shape so the center is 0
        const cx = (p.p1x + p.p2x) / 2;
        const cy = (p.p1y + p.p2y) / 2;

        this.p1x = p.p1x - cx;
        this.p1y = p.p1y - cy;
        this.p2x = p.p2x - cx;
        this.p2y = p.p2y - cy;

        this.panX = p.panX;
        this.panY = p.panY;
        this.scale = p.scale;
        this.rotation = p.rotation;
    }

    // the local draw function
    draw(color) {
        s.ctx.save();
            s.ctx.strokeStyle = color;
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
