class GroupRow {
    constructor(p) {
        this.name = p.name;
        this.label = p.label;
        this.title = p.title;
        this.controls = p.controls;
        this.backgroundColor = p.backgroundColor;

        let trE;

        trE = document.createElement('tr');
        trE.title = this.title;
        this.tableRow = trE;

        // the label
        const tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 4;
        const buttonE = document.createElement('button');
        tdE.appendChild(buttonE);
        buttonE.textContent = this.label;
        buttonE.style.backgroundColor = this.backgroundColor;
    }
}
