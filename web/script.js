var nodeMcuIp;

function clickMove(element) {
  if($('.pressing').length === 0) {
    var dir = element.attr('id');
    $.get(nodeMcuIp, {DIR:dir});
    $('#' + dir).addClass('pressing');
  }
}

function still() {
  $('.wheel.pressing').removeClass('pressing');
  $.get(nodeMcuIp, {DIR:'STILL'});
}

function pressMove(element) {
  if($('.pressing.wheel').length === 0) {
    var dir = element.attr('id');
    $.get(nodeMcuIp, {DIR:dir});
    element.addClass('pressing');
  }
}

function readIpFromInput() {
  nodeMcuIp = $('input.ip_input').val();
  nodeMcuIp = 'http://' + nodeMcuIp;
  $('input.ip_input').val('');
  $('#current_ip').text('Current IP: ' + nodeMcuIp);
}

function panCam(element) {
  if($('.pressing.cam').length == 0) {
    element.addClass('pressing');
    var dir = element.attr('id');
    $.get(nodeMcuIp, {CAM:dir});
  }
}

function stillCam() {
  $('.pressing.cam').removeClass('pressing');
  $.get(nodeMcuIp, {CAM:'STILL'});
}


$(document).ready(function(){
  $('button.ip_input').click(function() {
    readIpFromInput();
    console.log(nodeMcuIp);
  });
  $(".wheel").mousedown(function(){
    clickMove($(this));
  });
  $(document).mouseup(function(){
    still();
  });
  $(document).on( "keydown", function( event ) {
    var key = String.fromCharCode(event.keyCode);
    if(!$('input.ip_input').is(':focus')) {
      if (key === 'W') {
        pressMove($('.wheel#UP'));
      } else if (key === 'S') {
        pressMove($('.wheel#DOWN'))
      } else if (key === 'A') {
        pressMove($('.wheel#LEFT'))
      } else if (key === 'D') {
        pressMove($('.wheel#RIGHT'))
      } else if (event.keyCode === 190) {  //camera right
        panCam($('.cam#RIGHT'));
      } else if (event.keyCode === 188) {  //camera left
        panCam($('.cam#LEFT'));
      }
      var xhttp = new XMLHttpRequest();
      xhttp.open("GET", "http://10.2.6.157/", true);
      xhttp.send();
      if(this.readyState == 4) {
        alert(this.responseText);
      }
    } else {
      if(key === '\r') {
        readIpFromInput();
        console.log(nodeMcuIp);
      }
    }
  });
  $(document).on( "keyup", function(event) {
    var key = String.fromCharCode(event.keyCode);
    if(key === 'W' || key === 'S' || key === 'A' || key === 'D') {
      still();
    } else if(event.keyCode === 190 || event.keyCode === 188) {
      stillCam();
    }
  });
});
