/**
 * Created with JetBrains PhpStorm.
 * User: asahu
 * Date: 3/9/15
 * Time: 4:43 PM
 * To change this template use File | Settings | File Templates.
 */
window.onload = function() {
    applySearchColor();
    };
function applySearchColor(){
    var myHilitor = new Hilitor("");
    searchTerm = getURLParameter("searchTerms");
    myHilitor.apply(searchTerm);
    }
function getParameter(theParameter) {
    var params = window.location.search.substr(1).split('&');
console.log(params);
    for (var i = 0; i < params.length; i++) {
    var p=params[i].split('=');
    if (p[0] == theParameter) {
    return decodeURIComponent(p[1]);
    }
}
return false;
}

function getURLParameter(name) {
    return decodeURIComponent((new RegExp('[?|&]' + name + '=' + '([^&;]+?)(&|#|;|$)').exec(location.hash)||[,""])[1].replace(/\+/g, '%20'))||null
}