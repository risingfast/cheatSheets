// cheatsheets.js -- script to implement js of  cheatsheets.html
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
//    11-May-2022 change helpDiv to uppercase
//    12-May-2022 change "none" to "" in x.style.display
//    17-May-2022 extend Clear function
//    31-May-2022 set cornerimage rotation
//    18-Jun-2022 move fSetCornerImage() to common.js

// globals

const uri1 = "http://www.risingfast.com/cgi-bin/cheatSheets.cgi";

function fClearCheatsheetsPage() {

    let h = document.getElementById("HELPDIV");
    h.style.display=""

    let y = document.getElementById("resultsArea");
    y.value="";

    let z = document.getElementById("sheet-options");
    z.value="Choose";
    
    w = document.getElementById("wrapButton");
    w.disabled=true;
    w.innerHTML="Wrap";
    
    b = document.getElementById("submitButton");
    b.disabled=true;

    c = document.getElementById("clearButton");
    c.disabled=true;

    f = document.getElementById("filter-input");
    f.value="";

    fcClearExtras();
}

// function to set document model values to match action chosen by the user ............................................

function fSetAction() {
    var sChoice = document.getElementById("sheet-options").value;
    b = document.getElementById("submitButton");
    s = document.getElementById("sheet-options");
    if (s.value != 'Choose') {
        b.disabled=false;
        b.focus();
    } else {
        b.disabled=true;
    }

    let y = document.getElementById("resultsArea");
    y.style.display="";
    
    c = document.getElementById("clearButton");
    c.disabled=false;

    fGetResults();
}

// function to ajax fetch text2 from the server

async function fGetResults() {

    let y = document.getElementById("resultsArea");
    y.style.display="block";

    w = document.getElementById("wrapButton");
    w.disabled=false;

    sFilterEncoded = encodeURIComponent(document.getElementById("filter-input").value);
    let sRequest = uri1 + '?' + 'action=' + document.getElementById("sheet-options").value + '&filter=' + sFilterEncoded;
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

var input = document.getElementById("filter-input");

input.addEventListener("keypress", function(event) {
  if (event.key === "Enter") {
    event.preventDefault();
    document.getElementById("submitButton").click();
  }
});

