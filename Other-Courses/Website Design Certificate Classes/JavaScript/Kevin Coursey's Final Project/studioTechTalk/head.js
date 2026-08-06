"use strict";

let headerElement =
`<header>
    <table>
        <tr>
            <td>
                <a href="index.html"><img src="studioImages/studioTechTalk-50x375.png" id="studioLogo" height="50" width="375" alt="Studio Tech Talk Logo" title="Studio Tech Talk Main Page"></a>
            </td>
            <td id="soundwave">
                <img src="studioImages/soundwave.png">
            </td>
        </tr>
    </table>
</header>`;

let footerElement =
`<footer>
    <address>    
    Corner of Walk and Don't Walk &#8226; Winslow, AZ &#8226; 555.867.5309<br>
    feel free to <a href="mailto:kevin_coursey@student.uml.edu">contact me</a> if you're actually interested in something you see here
    </address>
</footer>`;

document.getElementById("head").innerHTML = headerElement;
document.getElementById("foot").innerHTML = footerElement;
