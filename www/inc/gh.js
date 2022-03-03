// Used for single record images.
var openedImg = new Image();
openedImg.src = "icons/folderopen.gif";
var closedImg = new Image();
closedImg.src = "icons/folderclosed.gif";


function swapIconRec (htmlId) {
    objRecord = document.getElementById(htmlId);

    if ('[-]' == objRecord.innerHTML)
        objRecord.innerHTML = '[+]';
    else
        objRecord.innerHTML = '[-]';
}

function swapIconFolder (htmlId) {
    objRecord = document.getElementById(htmlId);

    if (openedImg.src == objRecord.src)
        objRecord.src = closedImg.src;
    else
        objRecord.src = openedImg.src;

/*
    if ('[/]' == objRecord.innerHTML)
        objRecord.innerHTML = '[+]';
    else
        objRecord.innerHTML = '[/]';
*/

    if ('Shrink this category' == objRecord.title)
        objRecord.title = 'Expand this category';
    else
        objRecord.title = 'Shrink this category';
}

function showContent(htmlId) {
    var objRecord = document.getElementById(htmlId);

    if(objRecord.style.display=="block")
        objRecord.style.display="none";
    else
        objRecord.style.display="block";
}

/*
// To fix getElementsByName not working in IE.
function getElementsByName_iefix(tag, name) {
    var elem = document.getElementsByTagName(tag);
    var arr = new Array();

    for (var i = 0, iarr = 0; i < elem.length; i++) {
        att = elem[i].getAttribute("name");

        if (att == name) {
            arr[iarr] = elem[i];
            iarr++;
        }
    }
    return arr;
}

function showAllContent() {
    // Display all record content.
    var recArr = getElementsByName_iefix("div", "child");
    glb_size = recArr.length;

    for ( var i = 0; i < recArr.length; i++ )
    {
        htmlId = recArr[i].id;
        objRecord = document.getElementById(htmlId);

        if(objRecord.style.display=="block")
            objRecord.style.display="none";
        else
            objRecord.style.display="block";
    }
}
*/
