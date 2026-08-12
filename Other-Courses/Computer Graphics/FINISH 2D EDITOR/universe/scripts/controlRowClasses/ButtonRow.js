class ButtonRow {
    constructor(buttons) {
        if(buttons.length > 4 || buttons.length < 1) {
            alert('1 to 4 buttons please.');
            return;
        }
        let columns = 0;
        buttons.forEach(b => columns += b.colspan );
        if(columns !== 4) {
            alert('The colspans don\'t ad up to 4');
            return;
        }

        let trE, tdE, buttonE;

        trE = document.createElement('tr');
        this.tableRow = trE;

        this.buttons = [];
        buttons.forEach(b => {
            const button = {};

            button.name    = b.name;
            button.colspan = b.colspan;
            button.display = b.display;
            button.title   = b.title;

            tdE = document.createElement('td');
            trE.appendChild(tdE);
            tdE.colSpan = b.colspan;
            buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.innerText = b.display;
            buttonE.onclick = b.click;
            buttonE.title = b.title;
            button.button = buttonE;

            this.buttons.push(button);
        });
    }
}