<form>
    <fieldset>
        <input type="step" id="leftFoot" name="walking"/>
        <input type="step" id="rightFoot" name="walking"/>
    </fieldset>
</form>

// The javascript code might look something like this, where an event called onToeStub exists for feet.

// when a toe is stubbed, call the chooseReaction function and pass whichToe and painLevel as arguments.

leftFoot.addEventListener("onToeStub", chooseReaction(whichToe, painLevel));
rightFoot.addEventListener("onToeStub", chooseReaction(whichToe, painLevel));

function chooseReaction(wT, pL) {
    let reaction = "";
    let reactionMultiplier = "";

    // set reaction multiplier based on which toe has been stubbed.

    switch(wT) { 
        case "market":
            reactionMultiplier = 1;
        case "home":
        case "roastbeef":
        case "none":
            reactionMultiplier = 5;
        case "wee-wee-wee":
            reactionMultiplier = 10;
    }

    // choose a reaction based on pain level

    if (pL == 1) {
       reaction = "Wipe brow and be thankful!";
    } else if (pL > 1 && pL <= 5) {
       reaction = "Squint, crinkle nose, bite knuckle!!";
    } else if (pL > 5 && pL <= 9) {
      reaction = "Wince face, bite bottom lip, bend at knees and waist, utter something like ugggggghhhhhhh!!!";
    } else if (pL == 10) {
       reaction = "Repeatedly shout obscenities at full volume, clinch fists, be angry that anything even exists!!!!";
    } else if (pL > 10) {
       reaction = "Kill me now!!!!!";
    }

    let actualReaction = pL * reactionMultiplier;

    // make the reaction known for the appropriate number of repetitions

    for (let i = 0; i < actualReaction; i++) {
        document.write(reaction);
    }
}