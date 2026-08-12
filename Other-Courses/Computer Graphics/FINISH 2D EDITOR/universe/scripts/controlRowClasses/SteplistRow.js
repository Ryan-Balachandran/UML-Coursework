class SteplistRow {
    constructor(p) {
        this.name = p.name;
        this.tableBody = document.createElement('tbody');
        this.show = true;

        this.update();
    }

    update() {
        this.tableBody.innerHTML = '';

        const trE = document.createElement('tr');
        this.tableBody.appendChild(trE);
        const tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 4;
        const buttonE = document.createElement('button');
        tdE.appendChild(buttonE);
        buttonE.innerText = 'Steps';
        buttonE.onclick = () => {
            this.show = !this.show;
            this.update();
        }

        if(!this.show) return;
        s.stepArray.forEach((st, i) => {
            const trE = document.createElement('tr');
            this.tableBody.appendChild(trE);

            let tdE = document.createElement('td');
            trE.appendChild(tdE);
            tdE.colSpan = 2;
            let buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.innerText = st.stepDisplay;
            buttonE.onclick = () => s.stepArray[i].edit();

            // the up/down buttons
            tdE = document.createElement('td');
            trE.appendChild(tdE);

            buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.classList.add('halfButtons');
            buttonE.textContent = '⇧';
            buttonE.onclick = () => s.stepUpDown(i, -1);

            buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.classList.add('halfButtons');
            buttonE.textContent = '⇩';
            buttonE.onclick = () => s.stepUpDown(i, 1);

            // the view/delete buttons
            tdE = document.createElement('td');
            trE.appendChild(tdE);

            buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.classList.add('halfButtons');
            buttonE.textContent = '👁';
            buttonE.onclick = () => s.stepShowHide(i);
            buttonE.style.color = 'black';
            buttonE.style.backgroundColor = 'navajowhite';
            if(s.stepArray[i].show) {
                buttonE.style.color = 'navajowhite';
                buttonE.style.backgroundColor = 'black';
            }

            buttonE = document.createElement('button');
            tdE.appendChild(buttonE);
            buttonE.classList.add('halfButtons');
            buttonE.textContent = 'X';
            buttonE.onclick = () => s.stepDelete(i);
        });
    }
}

s.stepUpDown = (i, move) => {
    if((i === 0 && move < 0) || (i === s.stepArray.length - 1 && move > 0))
        return;
    const swap = s.stepArray[i + move];
    s.stepArray[i + move] = s.stepArray[i];
    s.stepArray[i] = swap;
    s.stepListRow.update();
    s.drawAll();
}

s.stepShowHide = (i) => {
    s.stepArray[i].show = !s.stepArray[i].show;
    s.stepListRow.update();
    s.drawAll();
}

s.stepDelete = (i) => {
    s.stepArray.splice(i, 1);
    s.stepListRow.update();
    s.drawAll();
}
