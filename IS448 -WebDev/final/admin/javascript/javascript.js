
function validateForm() {
  var x = document.forms["myguest"]["firstname"].value;
  if (x == "") {
    alert("First Name must be filled out");
    return false;
  }
}