class Text {
    constructor(p) {
        this.name = `text${s.shapeIndex++}`;
        this.text = p.text;
        const mt = s.ctx.measureText(this.text);

        // normalize the shape so the center is 0
        this.p1x = p.p1x - mt.width / 2;
        this.p1y = p.p1y + (
            mt.actualBoundingBoxAscent - mt.actualBoundingBoxDescent
        ) / 2;

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

            s.ctx.strokeText(this.text, this.p1x, this.p1y);
        s.ctx.restore();
    }
}
