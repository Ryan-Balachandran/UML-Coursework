class Rect {
    constructor(p) {
        this.name = `rect${s.shapeIndex++}`;
        this.width = p.width;
        this.height = p.height;

        // normalize the shape so the center is 0
        this.p1x = -this.width / 2;
        this.p1y = -this.height / 2;

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

            s.ctx.strokeRect(this.p1x, this.p1y, this.width, this.height);
        s.ctx.restore();
    }
}
