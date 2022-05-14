// cheatSheets.js -- script to implement js of  cheatSheets.html
// Author: Geoff Jarman
// Started: 12-Oct-2021
// Log:
//    12-Oct-2021 start and test
//    13-Oct-2021 clean up comments and remove unused functions
//    14-Oct-2021 add fClearPage()
//    14-Oct-2021 show filter and results area on submit()
//    15-Oct-2021 add logic to disable Submit button if option = 'Choose'
//    16-Oct-2021 add fWrapText() to wrap/unwrap text in the results texbox
//    18-Oct-2021 troubleshoot wrap button
//    20-Oct-2021 clear the filter when Clear is pressed
//    21-Oct-2021 change the URL to include ? and & separators and = assignments
//    24-Oct-2021 add url encoding to the filter string
//    11-Feb-2022 add Assembly to the list of sheets
//    03-May-2022 add listener for enter key in filter textbox
//    03-May-2022 fix the wrap button to wrap the text area
//    04-May-2022 disable clearButton on fClearPage()
//    04-May-2022 change wrap button title

// globals

const uri1 = "http://www.risingfast.com/cgi-bin/cheatSheets.cgi";

// functions for action button to display and hide help ..........................................

function fShowHelp() {
    var x = document.getElementById("helpDiv");
    if (x.style.display === "none") {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
}

function fClearPage() {

    let h = document.getElementById("helpDiv");
    h.style.display="none"

    let y = document.getElementById("resultsArea");
    y.style.display="none";

    let z = document.getElementById("sheet");
    z.value="Choose";
    
    w = document.getElementById("wrapButton");
    w.disabled=true;
    w.innerHTML="Wrap";
    
    b = document.getElementById("submitButton");
    b.disabled=true;

    c = document.getElementById("clearButton");
    c.disabled=true;

    f = document.getElementById("filter");
    f.value="";
}

// function to set document model values to match action chosen by the user ............................................

function fSetAction() {
    var sChoice = document.getElementById("sheet").value;
    b = document.getElementById("submitButton");
    s = document.getElementById("sheet");
    if (s.value != 'Choose') {
        b.disabled=false;
        b.focus();
    } else {
        b.disabled=true;
    }

    let y = document.getElementById("resultsArea");
    y.style.display="none";
    
    fGetResults();
}

// function to ajax fetch text2 from the server

async function fGetResults() {

    let y = document.getElementById("resultsArea");
    y.style.display="block";

    w = document.getElementById("wrapButton");
    w.disabled=false;

    sFilterEncoded = encodeURIComponent(document.getElementById("filter").value);
    let sRequest = uri1 + '?' + 'action=' + document.getElementById("sheet").value + '&filter=' + sFilterEncoded;
    let response = await fetch(sRequest);
    if (response.ok) {
        let text = await response.text();
        document.getElementById("resultsArea").style.display="block";
        document.getElementById("resultsArea").value=text;
    } else {
        alert("HttpError: " + response.status);
    }
    
    c = document.getElementById("clearButton");
    c.disabled=false;
}

// function to set document model values to match action chosen by the user ............................................

async function fWrapText() {
    let r = document.getElementById("resultsArea");
    let w = document.getElementById("wrapButton");
    
    if(r.style.whiteSpace == "pre") {
        r.style.whiteSpace = "pre-wrap";
        w.innerHTML="Unwrap";
    } else {
       r.style.whiteSpace = "pre";
        w.innerHTML="Wrap";
    }
}

var input = document.getElementById("filter");

input.addEventListener("keypress", function(event) {
  if (event.key === "Enter") {
    event.preventDefault();
    document.getElementById("submitButton").click();
  }
});
